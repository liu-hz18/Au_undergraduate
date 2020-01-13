
# begin training... total words:1012019, vocabsize:10000, batchNum:20240, device:cuda:0
# done... batchnum:20200  Loss:4.355042   ppl:74.89036630


import math
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
    def __init__(self, embed_size=300, hidden_size=150, dropout=0.5,
                 vocabsize=10000):
        super(ptbLSTM, self).__init__()
        # 获取预训练词向量
        self.embed = nn.Embedding(vocab_size, embed_size)
        # 构建网络
        self.lstm = nn.LSTM(input_size=embed_size,
                            hidden_size=hidden_size,
                            num_layers=2,
                            dropout=dropout)
        # 网络输出层映射到词汇表大小
        self.hidden2word = nn.Linear(hidden_size, vocabsize)

    # 前向传播
    def forward(self, text):
        embeds = self.embed(text)
        out, (h_n, c_n) = self.lstm(embeds.view(len(text), 1, -1))
        tag = self.hidden2word(out.view(len(text), -1))
        return tag


def run(embedsize=300, hiddensize=400, totepoch=12, batchsize=40, lr=1.0, dropout=0.5):

    with open('./ptb.word2id.json', 'r') as f:
        word2id = json.load(f)
    text = readData(train_data_file)
    trainsize = len(text)
    vocabsize = len(word2id)
    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
    model = ptbLSTM(embed_size=embedsize, hidden_size=hiddensize, dropout=dropout, vocabsize=vocabsize).to(device)
    # model = torch.load('./ptblstm.model').to(device)
    optimizer = optim.SGD(model.parameters(), lr=lr)
    utils.clip_grad_norm_(model.parameters(), max_norm=5)
    batchNum = trainsize // batchsize
    loss_fn = nn.CrossEntropyLoss()
    print('begin training... total words:{}, vocabsize:{}, batchNum:{}, device:{}'.format(trainsize, vocabsize, batchNum, device))
    aver_loss = 0.0
    scheduler = optim.lr_scheduler.LambdaLR(optimizer, lr_lambda=lambda epoch:
        0.84 if epoch > 6 else 1.00)
    inputlist = []
    outputlist = []
    for i in range(batchNum):
        inputlist.append(torch.LongTensor(text[i*batchsize:(i+1)*batchsize]))
        outputlist.append(torch.LongTensor(text[i*batchsize+1:(i+1)*batchsize+1]))
    for epoch in range(totepoch):
        aver_loss = 0.0
        for i in range(batchNum):
            model.zero_grad()# pytorch会累计梯度，所以每次循环记得置零
            input = inputlist[i].to(device)
            target = outputlist[i].to(device)
            output = model(input)
            loss = loss_fn(output, Variable(target))
            aver_loss += loss.item()
            loss.backward()
            optimizer.step()
            scheduler.step()
            if i % 100 == 0:
                sys.stdout.write('epoch:{}\tbatchnum:{}\ttrain Loss:{:.6f}\t  train ppl:{:.6f}\r'.format(epoch, i, aver_loss/(i+1), math.exp(aver_loss/(i+1))))
                sys.stdout.flush()
        evaluate(model, device, batchsize, loss_fn, optimizer)

    print('done...')
    torch.save(model, './ptblstm.model')
    return model, input


def evaluate(model, device, batchsize, loss_fn, optimizer):
    text = readData(valid_data_file)
    validsize = len(text)
    batchNum = validsize // batchsize - 1
    inputlist = []
    outputlist = []
    for i in range(batchNum):
        inputlist.append(torch.LongTensor(text[i*batchsize:(i+1)*batchsize]))
        outputlist.append(torch.LongTensor(text[i*batchsize+1:(i+1)*batchsize+1]))
    aver_loss = 0.0
    for i in range(batchNum):
        model.zero_grad()
        input = inputlist[i].to(device)
        target = outputlist[i].to(device)
        output = model(input)
        loss = loss_fn(output, Variable(target))
        aver_loss += loss.item()
        loss.backward()
        optimizer.step()
    sys.stdout.write('valid loss:{:.6f}\tvalid ppl:{:.6f}\n'.format(aver_loss/batchNum, math.exp(aver_loss/batchNum)))


def generateSeq(text='the meaning of life'):
    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
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
            input = torch.LongTensor(textid[-50:]).to(device)
            output = model(input)
            nxt = output[len(input)-1].tolist()
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
    '''
    model, input = run()
    writer = SummaryWriter('runlstm/ptblstm_expriment')
    writer.add_graph(model, (input,))
    writer.close()
    '''
    generateSeq('we have no useful information on whether users are at risk')
    '''
    we have no useful information on whether users are at risk <eos> \
    the market is n't going to be a good thing <eos> \
    the dow industrials industrial average plunged a day after a brief drop \
    in the dow jones industrial average on oct.
    '''

"""
C:/Users/lenovo/Desktop/ptblstm>python langmodel.py
begin training... total words:929589, vocabsize:10000, batchNum:23239, device:cuda:0
valid loss:5.155986     valid ppl:173.466754      train ppl:245.50076953
valid loss:4.911259     valid ppl:135.810303      train ppl:154.0787928
valid loss:4.772762     valid ppl:118.245406      train ppl:129.2557081
valid loss:4.677465     valid ppl:107.497229      train ppl:115.1131754
valid loss:4.602884     valid ppl:99.771675       train ppl:105.7259731
valid loss:4.541371     valid ppl:93.819350       train ppl:98.65207792
valid loss:4.494377     valid ppl:89.512398       train ppl:93.30456086
valid loss:4.451197     valid ppl:85.729504       train ppl:88.97131377
valid loss:4.410112     valid ppl:82.278654       train ppl:85.20769707
valid loss:4.379158     valid ppl:79.770802       train ppl:81.94404199
valid loss:4.343481     valid ppl:76.974989       train ppl:79.46267393
valid loss:4.316129     valid ppl:74.898141       train ppl:77.19914952
"""
