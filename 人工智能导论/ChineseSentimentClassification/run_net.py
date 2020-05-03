
import os
import sys
import json
from load_data import id2vocab_file, train_id_file, train_lable_file, valid_id_file, valid_lable_file, test_id_file, test_lable_file
import numpy as np
import torch
import torch.optim as optim
from tensorboardX import SummaryWriter
from torch.autograd import Variable
from torch.nn.utils.rnn import pad_sequence
from scipy.stats import pearsonr
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

from mlp import load_mlp
from cnn import load_cnn
from rnn import load_rnn
from rcnn import load_rcnn
from cnn_ori import load_cnn_origin

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
dtype = torch.FloatTensor
train_text = np.load(train_id_file, allow_pickle=True)
train_lable = np.load(train_lable_file, allow_pickle=True)
valid_text = np.load(valid_id_file, allow_pickle=True)
valid_lable = np.load(valid_lable_file, allow_pickle=True)
test_text = np.load(test_id_file, allow_pickle=True)
test_lable = np.load(test_lable_file, allow_pickle=True)


def batch_generator(text, lable, batch_size, training=True):
    batch_num = len(text) // batch_size
    for batch in range(batch_num):
        input, target, lens = [], [], []
        if training:
            idx = torch.randperm(batch_size)
        else:
            idx = torch.arange(batch_size)
        for sen in idx:
            temp_text = text[batch*batch_size+sen]
            lens.append(len(temp_text))
            input.append(torch.Tensor(temp_text))
            target.append(lable[batch*batch_size+sen])
        input = pad_sequence(input, batch_first=True).long().to(device)
        # target = torch.argmax(torch.Tensor(target), dim=1).to(device)
        target = torch.Tensor(target).long().to(device)
        lens = torch.Tensor(lens).long().to(device)
        yield input, target, lens


def evaluate(output, target, average='macro'):  # 'macro' or 'micro'
    pred = torch.argmax(output, dim=1).cpu()
    groud_truth = torch.argmax(target, dim=1).cpu()
    # print(pred.shape, groud_truth.shape)
    acc = accuracy_score(pred, groud_truth)
    f1 = f1_score(pred, groud_truth, average=average)
    co = pearsonr(pred, groud_truth)[0]
    if np.isnan(co):
        co = 0.0
    return acc, f1, co


def train_func(model, optimizer, batch_size):
    model.train()
    pred_list, target_list = [], []
    train_loss = []
    for input, target, _ in batch_generator(train_text, train_lable, batch_size):
        optimizer.zero_grad()
        loss, pred = model(input, target, dropout=True)
        loss.backward()
        optimizer.step()
        train_loss.append(loss.item())
        pred_list.append(pred)
        target_list.append(target)
    acc, f1, co = evaluate(torch.cat(pred_list, 0), torch.cat(target_list, 0))
    return np.mean(train_loss), acc, f1, co


def valid_func(model, batch_size):
    model.eval()
    pred_list, target_list = [], []
    with torch.no_grad():
        valid_loss = []
        for input, target, _ in batch_generator(valid_text, valid_lable, batch_size, training=False):
            loss, pred = model(input, target, dropout=False)
            valid_loss.append(loss.item())
            pred_list.append(pred)
            target_list.append(target)
    acc, f1, co = evaluate(torch.cat(pred_list, 0), torch.cat(target_list, 0))
    return np.mean(valid_loss), acc, f1, co


def test_func(model, batch_size):
    model.eval()
    pred_list, target_list = [], []
    with torch.no_grad():
        test_loss = []
        for input, target, _ in batch_generator(test_text, test_lable, batch_size, training=False):
            loss, pred = model(input, target, dropout=False)
            test_loss.append(loss.item())
            pred_list.append(pred)
            target_list.append(target)
    acc, f1, co = evaluate(torch.cat(pred_list, 0), torch.cat(target_list, 0))
    return np.mean(test_loss), acc, f1, co


def save_config(config):
    print(config)
    os.makedirs(config['output_path'], exist_ok=True)
    with open(os.path.join(config['output_path'], 'config.json'), 'w') as f:
        json.dump(config, f, indent=1)


def run_net(config):
    save_config(config)
    writer = SummaryWriter(log_dir=os.path.join(config['output_path'], 'run'))
    if config['net'] == 'mlp':
        model = load_mlp(config, os.path.join(config['output_path'], config['net'] + '.model'), device)
    elif config['net'] == 'textcnn':
        model = load_cnn(config, os.path.join(config['output_path'], config['net'] + '.model'), device)
    elif config['net'] == 'rnn':
        model = load_rnn(config, os.path.join(config['output_path'], config['net'] + '.model'), device)
    elif config['net'] == 'cnn':
        model = load_cnn_origin(config, os.path.join(config['output_path'], config['net'] + '.model'), device)
    elif config['net'] == 'rcnn':
        model = load_rcnn(config, os.path.join(config['output_path'], config['net'] + '.model'), device)
    optimizer = optim.Adagrad(model.parameters(), lr=config['lr'], lr_decay=config['lr_decay'], weight_decay=config['weight_decay'])
    best_acc = 0.0
    best_epoch = 0
    batch_size = config['batch_size']
    # train and valid
    for epoch in range(config['epochs']):
        train_loss, train_acc, train_f1, train_co = train_func(model, optimizer, batch_size)
        valid_loss, valid_acc, valid_f1, valid_co = valid_func(model, batch_size)
        if best_acc < valid_acc:
            best_acc = valid_acc
            best_epoch = epoch
            test_loss, test_acc, test_f1, test_co = test_func(model, batch_size)
        sys.stdout.write(f'epoch:{epoch}\n\tbest_epoch:{best_epoch}\tbest_acc:{best_acc}\ttest_acc:{test_acc}\ttest F1:{test_f1}\ttest CORR:{test_co}\n')
        sys.stdout.write(f'\ttrain loss:{train_loss}\ttrain acc:{train_acc}\ttrain F1:{train_f1}\ttrain CORR:{train_co}\n')
        sys.stdout.write(f'\tvalid loss:{valid_loss}\tvalid acc:{valid_acc}\tvalid F1:{valid_f1}\tvalid CORR:{valid_co}\n')
        # tensor borad
        writer.add_scalar('train_loss', train_loss, epoch)
        writer.add_scalar('train_acc', train_acc, epoch)
        writer.add_scalar('train_F1_macro', train_f1, epoch)
        writer.add_scalar('train_CORR', train_co, epoch)
        writer.add_scalar('dev_acc', valid_acc, epoch)
        writer.add_scalar('dev_F1_macro', valid_f1, epoch)
        writer.add_scalar('dev_CORR', valid_co, epoch)
    # test
    test_loss, test_acc, test_f1, test_co = test_func(model, batch_size)
    sys.stdout.write(f'test loss:{test_loss}\ttest acc:{test_acc}\ttest F1:{test_f1}\ttest CORR:{test_co}\n')
    torch.save(model, os.path.join(config['output_path'], config['net'] + '.model'))
    # for input, target, _ in batch_generator(train_text, train_lable, config['batch_size'], training=False):
    #    writer.add_graph(model, (input, target))
    #    break
    writer.close()