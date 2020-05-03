
import numpy as np
import torch
import torch.nn as nn
from torch.utils.tensorboard import SummaryWriter
import torch.nn.functional as F
from FocalLoss import FocalLoss


class TextSentimentRNN(nn.Module):

    def __init__(self, vocab_size, embed_dim=300, num_class=8, rnn='lstm',
                 hidden_size=256, batch_size=64, drop_out=0.5, num_layers=2,
                 bidirectional=False, loss_func='cross_entropy',
                 param_da=350, param_r=30, init_std=0.05, mlp_hidden_size=64,
                 embed_path=None, device='cpu', attention=True):
        super(TextSentimentRNN, self).__init__()
        self.init_std = init_std
        self.batch_size = batch_size
        self.bidirectional = bidirectional
        self.hidden_size = hidden_size
        self.loss_type = loss_func
        self.param_da = param_da
        self.param_r = param_r
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
                               hidden_size=hidden_size,
                               num_layers=num_layers,
                               dropout=self.drop_out,
                               batch_first=True,
                               bidirectional=bidirectional)
        elif rnn == 'gru':
            self.rnn = nn.GRU(input_size=embed_dim,
                              hidden_size=hidden_size,
                              num_layers=num_layers,
                              dropout=self.drop_out,
                              batch_first=True,
                              bidirectional=bidirectional)
        else:
            self.rnn = nn.RNN(input_size=embed_dim,
                              hidden_size=hidden_size,
                              num_layers=num_layers,
                              dropout=self.drop_out,
                              batch_first=True,
                              bidirectional=bidirectional)
        if bidirectional:
            hidden_size = 2 * hidden_size
        # self.ln = nn.LayerNorm(normalized_shape=hidden_size)
        self.dropout = nn.Dropout(drop_out)
        # Attention
        self.attention = attention
        if attention:
            self.Ws1 = nn.Parameter(torch.randn(param_da, hidden_size))
            self.Ws2 = nn.Parameter(torch.randn(param_r, param_da))
            self.mlp = nn.Sequential(
                nn.Linear(param_r*hidden_size, mlp_hidden_size),
                nn.ReLU(),
                nn.Dropout(drop_out),
                nn.Linear(mlp_hidden_size, num_class),
            )
        else:
            self.mlp = nn.Sequential(
                nn.Linear(hidden_size, mlp_hidden_size),
                nn.ReLU(),
                nn.Dropout(drop_out),
                nn.Linear(mlp_hidden_size, num_class)
            )
        self.init_loss(loss_func)

    def forward(self, text, target, dropout=True):
        embedded = self.embedding(text)
        if dropout:
            embedded = self.dropout(embedded)
        out, hidden = self.rnn(embedded)  # out: (B x LENGTH x HIDDEN_SIZE)
        # print(out.shape, hidden.shape)
        # out = self.ln(out)
        # Self-Attention
        if self.attention:
            A = F.softmax(torch.matmul(self.Ws2, torch.tanh(torch.matmul(self.Ws1, out.transpose(1, 2)))), dim=2)  # (B x param_r x length)
            M = torch.matmul(A, out)  # M: (B x param_r x hidden_size)
            output = self.mlp(M.view(M.size(0), -1))
        else:
            output = self.mlp(out[:, -1, :])
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


def load_rnn(config, path, device):
    if config['use_pretrained']:
        model = torch.load(path).to(device)
    else:
        model = TextSentimentRNN(vocab_size=config['vocab_size'],
                                 embed_dim=config['embed_size'],
                                 num_class=config['num_class'],
                                 hidden_size=config['hidden_size'],  # rnn hidden_size
                                 batch_size=config['batch_size'],
                                 rnn=config['rnn'],
                                 drop_out=config['drop_out'],
                                 num_layers=config['num_layers'],
                                 bidirectional=config['bidirectional'],
                                 loss_func=config['loss_type'],
                                 param_da=config['param_da'],
                                 param_r=config['param_r'],
                                 mlp_hidden_size=config['mlp_hidden_size'],
                                 embed_path=config['embed_path'],
                                 device=config['device'],
                                 attention=config['attention']
                                 ).to(device)
    return model
