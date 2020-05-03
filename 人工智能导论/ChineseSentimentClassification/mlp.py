
import numpy as np
import torch
import torch.nn as nn
from torch.utils.tensorboard import SummaryWriter
import torch.nn.functional as F
from FocalLoss import FocalLoss


class TextSentimentMLP(nn.Module):

    def __init__(self, vocab_size, embed_dim=300, hidden_sizes=[512, 128],
                 max_length=500, num_class=8, batch_size=64, drop_out=0.5,
                 num_layers=2, loss_type='cross_entropy', init_std=0.05,
                 embed_path=None, device='cpu'):
        super(TextSentimentMLP, self).__init__()
        self.max_length = max_length
        self.drop_out = drop_out
        self.hidden_sizes = hidden_sizes
        self.loss_type = loss_type
        self.embed_size = embed_dim
        self.device = torch.device(device)
        if embed_path != None:
            emb = torch.Tensor(np.load(embed_path)[:vocab_size])
            self.embedding = nn.Embedding.from_pretrained(emb, freeze=True)
        else:
            self.embedding = nn.Embedding(vocab_size, embed_dim)
        self.dropout = nn.Dropout(drop_out)
        self.num_class = num_class
        self.zeroarr = torch.zeros(batch_size, self.max_length).long().to(self.device)
        if num_layers == 2:
            self.mlp = nn.Sequential(
                nn.Linear(max_length*embed_dim, hidden_sizes[0]),
                nn.BatchNorm1d(hidden_sizes[0]),
                nn.ReLU(),
                # nn.LeakyReLU(),
                nn.Dropout(drop_out),
                nn.Linear(hidden_sizes[0], hidden_sizes[1]),
                nn.BatchNorm1d(hidden_sizes[1]),
                nn.ReLU(),
                # nn.LeakyReLU(),
                nn.Dropout(drop_out),
                nn.Linear(hidden_sizes[1], num_class),
            )
        else:
            self.mlp = nn.Sequential(
                nn.Linear(max_length*embed_dim, hidden_sizes[0]),
                nn.BatchNorm1d(hidden_sizes[0]),
                nn.ReLU(),
                # nn.LeakyReLU(),
                nn.Dropout(drop_out),
                nn.Linear(hidden_sizes[0], num_class),
            )
        self.init_loss(loss_type)

    def forward(self, text, target, dropout=True):
        if text.size(1) < self.max_length:
            text = torch.cat((text, self.zeroarr[:, :self.max_length-text.size(1)]), 1)
        else:
            text = text[:, :self.max_length]
        embedded = self.embedding(text)  # out: (B x max_length x EMBE)
        if dropout:
            embedded = self.dropout(embedded)
        output = self.mlp(embedded.view(embedded.size(0), -1))  # out: (B x num_class)
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


def load_mlp(config, path, device):
    if config['use_pretrained']:
        model = torch.load(path).to(device)
    else:
        model = TextSentimentMLP(vocab_size=config['vocab_size'],
                                 embed_dim=config['embed_size'],
                                 hidden_sizes=config['hidden_sizes'],
                                 max_length=config['max_length'],
                                 num_class=config['num_class'],
                                 batch_size=config['batch_size'],
                                 drop_out=config['drop_out'],
                                 loss_type=config['loss_type'],
                                 num_layers=config['num_layers'],
                                 embed_path=config['embed_path'],
                                 device=config['device']
                                 ).to(device)
    return model
