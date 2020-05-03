
import torch
import sys
from run_net import run_net

VOCAB_SIZE = 45818
NUM_CLASS = 8
print('vocab_size:', VOCAB_SIZE)

# tensorboard --logdir save/mlp/run
# pipreqs . --encoding=utf8 --force

basic_config = {
    'use_pretrained': False,
    'vocab_size': VOCAB_SIZE,
    'embed_size': 300,
    'num_class': NUM_CLASS,
    'seed': 20001220,
    'embed_path': 'word2vec/matrix.npy',
    'device': "cuda:0" if torch.cuda.is_available() else "cpu"
}

seed = basic_config['seed']
torch.manual_seed(seed)
torch.cuda.manual_seed(seed)
torch.cuda.manual_seed_all(seed)
torch.backends.cudnn.benchmark = False
torch.backends.cudnn.deterministic = True


def run_mlp():
    config = {
        'net': 'mlp',
        'output_path': 'save/mlp',
        'hidden_sizes': [256, 64],
        'max_length': 256,
        'batch_size': 64,
        'num_layers': 2,
        'drop_out': 0.5,
        'lr': 0.001,
        'epochs': 100,
        'lr_decay': 0.0,
        'weight_decay': 0.0001,
        'loss_type': 'cross_entropy'  # 'focal'
    }
    run_net(dict(basic_config, **config))


def run_cnn():
    config = {
        'net': 'cnn',
        'output_path': 'save/cnn',
        'max_length': 256,
        'kernel_size': 5,
        'padding': 2,
        'conv_stride': 1,
        'out_channel': 256,
        'pool_kernel_size': 4,
        'pool_stride': 4,
        'batch_size': 64,
        'drop_out': 0.5,
        'mlp_hidden_size': 512,
        'lr': 0.01,
        'epochs': 200,
        'lr_decay': 0.0,
        'weight_decay': 0.001,
        'loss_type': 'cross_entropy'  # 'focal'
    }
    run_net(dict(basic_config, **config))


def run_textcnn():  # best: 61.3
    config = {
        'net': 'textcnn',
        'output_path': 'save/textcnn',
        'kernel_sizes': [2, 3, 4, 5],  # multiple region size
        'kernel_num': 100,  # feature maps for each region size
        'batch_size': 64,
        'drop_out': 0.5,
        'mlp_hidden_size': 512,
        'lr': 0.01,
        'epochs': 200,
        'lr_decay': 0.0,
        'weight_decay': 0.001,
        'loss_type': 'cross_entropy'  # 'focal'
    }
    run_net(dict(basic_config, **config))

# gru best: 60.2
# lstm best: 62.1
# rnn best: 55.5


def run_rnn():
    config = {
        'net': 'rnn',
        'output_path': 'save/rnn',
        'rnn': 'lstm',  # 'rnn' or 'lstm' or 'gru'
        'batch_size': 64,
        'drop_out': 0.5,
        'hidden_size': 256,
        'num_layers': 1,  # suggested 1 for bidirectional
        'bidirectional': True,

        'attention': True,
        'param_da': 350,  # for Attention
        'param_r': 30,  # for Attention

        'lr': 0.01,
        'epochs': 150,
        'lr_decay': 0.0,
        'weight_decay': 0.001,
        'mlp_hidden_size': 256,
        'loss_type': 'cross_entropy'  # 'focal'
    }
    run_net(dict(basic_config, **config))


def run_rcnn():  # best: 60.9
    config = {
        'net': 'rcnn',
        'output_path': 'save/rcnn',
        'rnn': 'gru',  # 'rnn' or 'lstm' or 'gru'
        'batch_size': 64,
        'drop_out': 0.5,
        'rnn_hidden_size': 256,
        'num_layers': 1,  # suggested 1 for bidirectional
        'mlp_1_hidden_size': 512,
        'mlp_2_hidden_size': 128,
        'lr': 0.01,
        'epochs': 150,
        'lr_decay': 0.0,
        'weight_decay': 0.001,
        'loss_type': 'cross_entropy'  # 'focal'
    }
    run_net(dict(basic_config, **config))


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python main.py [mlp|cnn|rnn]')
    elif sys.argv[1] == 'mlp':
        run_mlp()
    elif sys.argv[1] == 'cnn':
        run_cnn()
    elif sys.argv[1] == 'rnn':
        run_rnn()
    elif sys.argv[1] == 'textcnn':
        run_textcnn()
    elif sys.argv[1] == 'rcnn':
        run_rcnn()
    else:
        print('Usage: python main.py [mlp|cnn|rnn]')
