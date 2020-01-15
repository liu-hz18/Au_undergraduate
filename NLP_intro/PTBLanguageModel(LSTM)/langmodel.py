
import math
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import json
import sys
import re
from torch.autograd import Variable
import torch.nn.utils as utils
from torch.utils.tensorboard import SummaryWriter

dtype = torch.FloatTensor
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

# 词index文件
train_data_file = './ptb.train.id.txt'
test_data_file = './ptb.test.id.txt'
valid_data_file = './ptb.valid.id.txt'

# 训练集
vocab_size = 10000


# 将单词id文件读入内存，返回编号列表
def readData(filepath):
    with open(filepath, 'r') as f:
        string = ' '.join([line.strip() for line in f.readlines()])
    idlist = [int(word) for word in string.split()]
    return idlist


class ptbLSTM(nn.Module):
    """docstring for ptbLSTM"""
    def __init__(self, embed_size=128, hidden_size=150, batchsize=20, dropout=0.5,
                 vocabsize=10000, num_layers=2, init_parameter=0.05):
        super(ptbLSTM, self).__init__()
        self.batchsize = batchsize
        # 获取预训练词向量
        self.embed = nn.Embedding(vocab_size, embed_size)
        # 构建网络
        self.lstm = nn.LSTM(input_size=embed_size,
                            hidden_size=hidden_size,
                            num_layers=num_layers,
                            dropout=dropout,
                            batch_first=True)
        # 参数初始化
        for i in range(num_layers):
            for j in range(4):
                nn.init.uniform_(self.lstm.all_weights[i][j], -init_parameter, init_parameter)
        # 网络输出层映射到词汇表大小
        self.hidden2word = nn.Linear(hidden_size, vocabsize)
        self.dropout = nn.Dropout(dropout)

    # 前向传播
    def forward(self, text, dropout=True):
        if dropout:
            embeds = self.dropout(self.embed(text))
        else:
            embeds = self.embed(text)
        out, hidden = self.lstm(embeds)
        tag = self.hidden2word(out).permute(0, 2, 1)
        return tag


def getBatch(text, batchsize, num_step, i):
    inputbatch = torch.LongTensor(batchsize, num_step)
    targetbatch = torch.LongTensor(batchsize, num_step)
    for j in range(batchsize):
        pos = np.random.randint(0, num_step)
        inputbatch[j] = torch.LongTensor(text[(i*batchsize+j)*num_step+pos:(i*batchsize+(j+1))*num_step+pos]).to(device)
        targetbatch[j] = torch.LongTensor(text[(i*batchsize+j)*num_step+pos+1:(i*batchsize+(j+1))*num_step+pos+1]).to(device)
    return inputbatch.to(device), targetbatch.to(device)


# 训练集上训练
def run(embedsize=300, hiddensize=350, totepoch=40, num_step=35, batchsize=25, lr=1.0, dropout=0.5):
    with open('./ptb.word2id.json', 'r') as f:
        word2id = json.load(f)
    text = readData(train_data_file)
    trainsize = len(text)
    vocabsize = len(word2id)
    model = ptbLSTM(embed_size=embedsize, hidden_size=hiddensize, dropout=dropout, vocabsize=vocabsize).to(device)
    # model = torch.load('./ptblstm.model').to(device)
    optimizer = optim.SGD(model.parameters(), lr=lr)
    batchNum = trainsize // (num_step*batchsize) - 1
    loss_fn = nn.CrossEntropyLoss()
    scheduler = optim.lr_scheduler.StepLR(optimizer, step_size=6, gamma=0.8)
    print(f'begin training... total words:{trainsize}, vocabsize:{vocabsize},\
         batchNum:{batchNum}, device:{device}')
    aver_loss = 0.0

    # train
    for epoch in range(totepoch):
        aver_loss = 0.0
        model.train()
        for i in range(batchNum):
            input, target = getBatch(text, batchsize, num_step, i)

            model.zero_grad()
            output = model(input, dropout=True)

            loss = loss_fn(output, target)
            aver_loss += loss.item()

            loss.backward()
            utils.clip_grad_norm_(model.parameters(), max_norm=5)
            optimizer.step()
        scheduler.step()

        valid_loss = evaluate(model, device, 1, num_step, loss_fn)
        sys.stdout.write(f'epoch:{epoch}\t train loss:{aver_loss/batchNum:.6f}\
                        train ppl:{math.exp(aver_loss/batchNum):5.6f}\n\
                        lr:{scheduler.get_lr()[0]:2.5f}\tvalid loss:{valid_loss:.6f}\
                        valid ppl:{math.exp(valid_loss):5.6f}\n'
                        )
    print('done...')
    torch.save(model, './ptblstm.model')
    return model


# valid测试
def evaluate(model, device, batchsize, num_step, loss_fn):
    model.eval()
    text = readData(valid_data_file)
    validsize = len(text)
    batchNum = validsize // (batchsize*num_step) - 1
    aver_loss = 0.0
    with torch.no_grad():
        for i in range(batchNum):
            input, target = getBatch(text, batchsize, num_step, i)

            output = model(input, dropout=False)

            loss = loss_fn(output, Variable(target))
            aver_loss += loss.item()

    return aver_loss/batchNum


# 给定开头生成句子
def generateSeq(text='the meaning of life'):
    model = torch.load('./ptblstm.model').to(device)
    with open('./ptb.word2id.json', 'r') as f:
        word2id = json.load(f)
    wordlist = list(word2id.keys())
    text = text.split(' ')
    print(text)
    textid = []
    for word in text:
        textid.append(word2id[word])
    i = 0
    print(textid)
    stopword = [' ', 'N', '$']
    with torch.no_grad():# 不更新梯度
        while i < 1000:
            input = torch.LongTensor([textid[-50:]]).to(device)
            output = model(input, dropout=False)
            nxt = output[0][len(input[0])-1].tolist()
            flag = nxt.index(max(nxt))
            if wordlist[flag] not in stopword:
                textid.append(flag)
                text.append(wordlist[flag])
            i += 1
    text = '_'.join(text)
    text = re.sub(' ', '', re.sub('N', '', re.sub('$', '', re.sub('<unk>', '', re.sub('\t', '', text)))))
    text = re.sub('_', ' ', re.sub(' +', '', text))
    print(text)


if __name__ == '__main__':
    model = run()
    # generateSeq('we have no useful information on whether users are at risk')
    '''
    训练后,句子生成结果:
    we have no useful information on whether users are at risk <eos> \
    the market is n't going to be a good thing <eos> \
    the dow industrials industrial average plunged a day after a brief drop \
    in the dow jones industrial average on oct.
    '''
