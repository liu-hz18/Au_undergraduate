
import numpy as np
import torch
import torch.nn as nn
from torch.utils.tensorboard import SummaryWriter
import torch.nn.functional as F
from FocalLoss import FocalLoss


class TextSentimentCNNOrigin(nn.Module):

    def __init__(self, vocab_size, embed_dim, num_class=8, kernel_size=5, out_channel=512,
                 padding=0, conv_stride=1, pool_kernel_size=4, pool_stride=2, batch_size=64, 
                 drop_out=0.5, init_std=0.05, loss_func='cross_entropy',
                 max_length=512, mlp_hidden_size=128, embed_path=None, device='cpu'):
        super(TextSentimentCNNOrigin, self).__init__()
        self.init_std = init_std
        self.batch_size = batch_size
        self.loss_type = loss_func
        self.max_length = max_length
        self.num_class = num_class
        self.embed_size = embed_dim
        self.device = torch.device(device)
        if embed_path != None:
            emb = torch.Tensor(np.load(embed_path)[:vocab_size])
            self.embedding = nn.Embedding.from_pretrained(emb, freeze=True)
        else:
            self.embedding = nn.Embedding(vocab_size, embed_dim, padding_idx=0)
        self.cnn = nn.Sequential(
            nn.Conv1d(embed_dim, out_channel, kernel_size, padding=padding, stride=conv_stride),
            nn.ReLU(),
            nn.Dropout(drop_out),
            nn.MaxPool1d(pool_kernel_size, pool_stride),
        )
        pool_input_size = (max_length + 2 * padding - kernel_size) // conv_stride + 1
        mlp_input_size = (pool_input_size - pool_kernel_size) // pool_stride + 1
        self.dropout = nn.Dropout(drop_out)
        self.zeroarr = torch.zeros(self.batch_size, self.max_length).long().to(self.device)
        self.mlp = nn.Sequential(
            nn.Linear(out_channel * mlp_input_size, mlp_hidden_size),
            # nn.BatchNorm1d(mlp_hidden_size),
            nn.ReLU(),
            nn.Dropout(drop_out),
            nn.Linear(mlp_hidden_size, num_class),
        )
        self.init_loss(loss_func)

    def forward(self, text, target, dropout=True):
        if text.size(1) < self.max_length:
            text = torch.cat((text, self.zeroarr[:, :self.max_length-text.size(1)]), 1)
        else:
            text = text[:, :self.max_length]
        embedded = self.embedding(text)  # out: (B x 1 x MAX_LENGTH x EMBED_SIZE)
        if dropout:
            embedded = self.dropout(embedded)
        out = self.cnn(embedded.transpose(1, 2))
        output = self.mlp(out.view(out.size(0), -1))
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


def load_cnn_origin(config, path, device):
    if config['use_pretrained']:
        model = torch.load(path).to(device)
    else:
        model = TextSentimentCNNOrigin(vocab_size=config['vocab_size'],
                                       embed_dim=config['embed_size'],
                                       num_class=config['num_class'],
                                       batch_size=config['batch_size'],
                                       out_channel=config['out_channel'],
                                       kernel_size=config['kernel_size'],
                                       padding=config['padding'],
                                       conv_stride=config['conv_stride'],
                                       pool_kernel_size=config['pool_kernel_size'],
                                       pool_stride=config['pool_stride'],
                                       drop_out=config['drop_out'],
                                       loss_func=config['loss_type'],
                                       max_length=config['max_length'],
                                       mlp_hidden_size=config['mlp_hidden_size'],
                                       embed_path=config['embed_path'],
                                       device=config['device']
                                       ).to(device)
    return model
