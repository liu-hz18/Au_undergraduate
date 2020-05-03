
import numpy as np
import torch
import torch.nn as nn
from torch.utils.tensorboard import SummaryWriter
import torch.nn.functional as F
from FocalLoss import FocalLoss


class TextSentimentCNN(nn.Module):

    def __init__(self, vocab_size, embed_dim, num_class=8, kernel_sizes=[2, 3, 4, 5],
                 kernel_num=4, padding=2, pool_kernel_size=2, pool_stride=2,
                 batch_size=64, drop_out=0.5, init_std=0.05, loss_func='cross_entropy',
                 mlp_hidden_size=128, embed_path=None, device='cpu'):
        super(TextSentimentCNN, self).__init__()
        self.init_std = init_std
        self.batch_size = batch_size
        self.kernel_num = kernel_num
        self.kernel_sizes = kernel_sizes
        self.loss_type = loss_func
        self.num_class = num_class
        self.embed_size = embed_dim
        self.device = torch.device(device)
        if embed_path != None:
            emb = torch.Tensor(np.load(embed_path)[:vocab_size])
            self.embedding = nn.Embedding.from_pretrained(emb, freeze=True)
        else:
            self.embedding = nn.Embedding(vocab_size, embed_dim, padding_idx=0)
        self.convs = nn.ModuleList([
            nn.Sequential(
                nn.Conv2d(1, kernel_num, (K, embed_dim)),
                nn.BatchNorm2d(kernel_num),
                nn.ReLU(),
                # nn.Tanh(),
            )
            for K in kernel_sizes]
        )
        self.dropout = nn.Dropout(drop_out)
        self.mlp = nn.Sequential(
            nn.Linear(len(kernel_sizes)*kernel_num, mlp_hidden_size),
            # nn.BatchNorm1d(mlp_hidden_size),
            nn.ReLU(),
            nn.Dropout(drop_out),
            nn.Linear(mlp_hidden_size, num_class),
        )
        self.init_loss(loss_func)

    def forward(self, text, target, dropout=True):
        embedded = self.embedding(text).unsqueeze(1)  # out: (B x 1 x MAX_LENGTH x EMBED_SIZE)
        if dropout:
            embedded = self.dropout(embedded)
        input = [conv(embedded).squeeze(3) for conv in self.convs]  # out: (len(kernel_sizes) x B x kernel_num)
        out = [F.max_pool1d(line, line.size(2)).squeeze(2) for line in input]
        out = self.dropout(torch.cat(out, 1))  # out: (B x kernel_num x len(kernel_sizes))
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


def load_cnn(config, path, device):
    if config['use_pretrained']:
        model = torch.load(path).to(device)
    else:
        model = TextSentimentCNN(vocab_size=config['vocab_size'],
                                 embed_dim=config['embed_size'],
                                 num_class=config['num_class'],
                                 batch_size=config['batch_size'],
                                 kernel_sizes=config['kernel_sizes'],
                                 kernel_num=config['kernel_num'],  # num for each kernel size
                                 drop_out=config['drop_out'],
                                 loss_func=config['loss_type'],
                                 mlp_hidden_size=config['mlp_hidden_size'],
                                 embed_path=config['embed_path'],
                                 device=config['device']
                                 ).to(device)
    return model
