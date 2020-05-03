
import numpy as np
import torch
import torch.nn as nn
from torch.utils.tensorboard import SummaryWriter
import torch.nn.functional as F
from FocalLoss import FocalLoss


class TextSentimentRCNN(nn.Module):
    """docstring for TextSentimentRCNN"""
    def __init__(self, vocab_size, embed_dim=300, num_class=8, rnn='lstm',
                 rnn_hidden_size=256, batch_size=64, drop_out=0.5, num_layers=2,
                 loss_func='cross_entropy', mlp_1_hidden_size=512, mlp_2_hidden_size=128,
                 init_std=0.05, embed_path=None, device='cpu'):
        super(TextSentimentRCNN, self).__init__()
        self.init_std = init_std
        self.batch_size = batch_size
        self.hidden_size = rnn_hidden_size
        self.loss_type = loss_func
        self.num_class = num_class
        self.drop_out = drop_out
        self.device = torch.device(device)
        if num_layers == 1:
            self.drop_out = 0.0
        self.embed_size = embed_dim
        if embed_path != None:
            emb = torch.Tensor(np.load(embed_path)[:vocab_size])
            self.embedding = nn.Embedding.from_pretrained(emb, freeze=True)
        else:
            self.embedding = nn.Embedding(vocab_size, embed_dim)
        # RNN Strcture
        if rnn == 'lstm':
            self.rnn = nn.LSTM(input_size=embed_dim,
                               hidden_size=rnn_hidden_size,
                               num_layers=num_layers,
                               dropout=self.drop_out,
                               batch_first=True,
                               bidirectional=True)
        elif rnn == 'gru':
            self.rnn = nn.GRU(input_size=embed_dim,
                              hidden_size=rnn_hidden_size,
                              num_layers=num_layers,
                              dropout=self.drop_out,
                              batch_first=True,
                              bidirectional=True)
        else:
            self.rnn = nn.RNN(input_size=embed_dim,
                              hidden_size=rnn_hidden_size,
                              num_layers=num_layers,
                              dropout=self.drop_out,
                              batch_first=True,
                              bidirectional=True)
        rnn_hidden_size = 2 * rnn_hidden_size
        self.dropout = nn.Dropout(drop_out)
        self.mlp_1 = nn.Sequential(
            nn.Linear(rnn_hidden_size + embed_dim, mlp_1_hidden_size),
            nn.ReLU(),
            nn.Dropout(drop_out),
        )
        self.mlp_2 = nn.Sequential(
            nn.Linear(rnn_hidden_size + embed_dim, mlp_1_hidden_size),
            nn.ReLU(),
            nn.Dropout(drop_out),
            nn.Linear(mlp_1_hidden_size, num_class),
        )
        self.init_loss(loss_func)

    def forward(self, text, target, dropout=True):
        # text = text[:256]
        embedded = self.embedding(text)
        if dropout:
            embedded = self.dropout(embedded)
        out, _ = self.rnn(embedded)  # out: (B x LENGTH x HIDDEN_SIZE)
        # combine = self.mlp_1(torch.cat((embedded, out), dim=2)).permute(0, 2, 1)
        combine = F.relu(torch.cat((embedded, out), dim=2)).permute(0, 2, 1)
        Y = F.max_pool1d(combine, combine.size(2)).squeeze(2)
        # print(Y.shape)
        output = self.mlp_2(Y)
        labels = F.softmax(output, dim=1)
        if self.loss_type == 'cross_entropy' or self.loss_type == 'focal':
            loss = self.loss_fn(output, torch.argmax(target, dim=1))
        else:
            loss = self.loss_fn(labels, target)
        return loss, labels.detach()

    def init_loss(self, loss_type):
        if loss_type == 'l1':
            self.loss_fn = nn.L1Loss()
        elif loss_type == 'mse':
            self.loss_fn = nn.MSELoss()
        elif loss_type == 'focal':
            self.loss_fn = FocalLoss(self.num_class)
        else:
            self.loss_type = 'cross_entropy'
            self.loss_fn = nn.CrossEntropyLoss()


def load_rcnn(config, path, device):
    if config['use_pretrained']:
        model = torch.load(path).to(device)
    else:
        model = TextSentimentRCNN(vocab_size=config['vocab_size'],
                                  embed_dim=config['embed_size'],
                                  num_class=config['num_class'],
                                  rnn_hidden_size=config['rnn_hidden_size'],  # rnn hidden_size
                                  batch_size=config['batch_size'],
                                  rnn=config['rnn'],
                                  drop_out=config['drop_out'],
                                  num_layers=config['num_layers'],
                                  loss_func=config['loss_type'],
                                  mlp_1_hidden_size=config['mlp_1_hidden_size'],
                                  mlp_2_hidden_size=config['mlp_2_hidden_size'],
                                  embed_path=config['embed_path'],
                                  device=config['device']
                                  ).to(device)
    return model
