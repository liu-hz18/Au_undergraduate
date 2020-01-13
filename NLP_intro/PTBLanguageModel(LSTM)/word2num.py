# -*- encoding = utf-8 -*-#

import collections
import json
from operator import itemgetter

# 原始文件
train_file = 'ptb.train.txt'
#train_file = './dataset_1.txt'
test_file = 'ptb.test.txt'
valid_file = 'ptb.valid.txt'

# 词汇表
output_file = './ptb.vocab.txt'
word2id_file = './ptb.word2id.json'
id2word_file = './ptb.id2word.json'

# 词index文件
train_data_file = './ptb.train.id.txt'
test_data_file = './ptb.test.id.txt'
valid_data_file = './ptb.valid.id.txt'

word2id = {}
id2word = {}


def get_id_file():
    global word2id
    global id2word
    counter = collections.Counter()
    with open(train_file, 'r', errors='ignore') as f:
        for line in f:
            for word in line.strip().split():
                counter[word] += 1
    # print(counter.items())
    sorted_word2count = sorted(counter.items(), key=itemgetter(1), reverse=True)
    sorted_words = ['<eos>'] + [x[0] for x in sorted_word2count]
    # sorted_words = ['<pad>', '<go>', '<eos>'] + sorted_words
    word2id = {k: v for (k, v) in zip(sorted_words, range(len(sorted_words)))}
    id2word = dict(zip(word2id.values(), word2id.keys()))
    with open(output_file, 'w') as f:
        for word in sorted_words:
            f.write(word + '\n')

    with open(word2id_file, 'w') as f:
        json.dump(word2id, f)
        # word2id = json.load(f)

    with open(id2word_file, 'w') as f:
        json.dump(id2word, f)


def getid(word):
    return word2id[word] if word in word2id else word2id['<eos>']


def write_id_file(file_in, file_out):
    fout = open(file_out, 'w')
    with open(file_in, 'r', errors='ignore') as f:
        for line in f:
            words = line.strip().split() + ['<eos>']
            output_line = ' '.join(str(getid(w)) for w in words) + '\n'
            fout.write(output_line)
    fout.close()


if __name__ == '__main__':
    get_id_file()
    write_id_file(train_file, train_data_file)
    write_id_file(valid_file, valid_data_file)
    write_id_file(test_file, test_data_file)
    print("successfully saved")
