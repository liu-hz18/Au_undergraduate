
import numpy as np
import os
import re
import collections
import json
from jieba.analyse.analyzer import ChineseAnalyzer
import jieba.posseg as pseg


data_dir = "sina"
train_data_file = "sinanews.train"
valid_data_file = "sinanews.valid"
test_data_file = "sinanews.test"

train_file = os.path.join(data_dir, train_data_file)
valid_file = os.path.join(data_dir, valid_data_file)
test_file = os.path.join(data_dir, test_data_file)

word2id_file = os.path.join(data_dir, "vocab2id.json")
id2vocab_file = os.path.join(data_dir, "id2vocab.json")
vocab2id_file = 'word2vec/vocab'

train_id_file = os.path.join(data_dir, "train_id.npy")
valid_id_file = os.path.join(data_dir, "valid_id.npy")
test_id_file = os.path.join(data_dir, "test_id.npy")

train_lable_file = os.path.join(data_dir, 'train_lable.npy')
valid_lable_file = os.path.join(data_dir, 'valid_lable.npy')
test_lable_file = os.path.join(data_dir, 'test_lable.npy')


MIN_COUNT = 6


def create_valid_data():
    if os.path.exists(valid_file) == False:
        with open(test_file, 'r', encoding='utf-8', errors='ignore') as fin:
            lines = fin.readlines()
            sents = len(lines)
        with open(valid_file, 'w', encoding='utf-8') as fout:
            for line in lines[:sents//2]:
                fout.write(line)
        with open(test_file, 'w', encoding='utf-8') as fout:
            for line in lines[sents//2:]:
                fout.write(line)


def sentence_process(line):
    blocks = line.strip().split('\t')
    sentiments, sentences = blocks[1].strip().split(), blocks[2].strip().split()
    lable = [int(score.strip().split(':')[-1]) for score in sentiments[1:]]
    return lable, sentences


namelist = ['nr', 'nrj', 'nrf', 'nrfg']
locationlist = ['ns', 'nsf']


def containName(line):
    words = pseg.cut(line)
    for word in words:
        if word.flag in namelist:
            return True
    return False


def get_vocab_id():
    vocab_counter = collections.Counter()
    with open(train_file, 'r', encoding='utf-8', errors='ignore') as fin:
        lines = fin.readlines()
        for line in lines:
            _, words = sentence_process(line)
            vocab_counter.update(words)
    with open(valid_file, 'r', encoding='utf-8', errors='ignore') as fin:
        lines = fin.readlines()
        for line in lines:
            _, words = sentence_process(line)
            vocab_counter.update(words)
    with open(test_file, 'r', encoding='utf-8', errors='ignore') as fin:
        lines = fin.readlines()
        for line in lines:
            _, words = sentence_process(line)
            vocab_counter.update(words)
    vocab_counter.most_common()
    word2id = {}
    count = 0
    for k in vocab_counter:
        if vocab_counter[k] < MIN_COUNT or bool(re.search(r'\d', k)):
            word2id[k] = 0
        elif containName(k):
            word2id[k] = 1  # name
        else:
            word2id[k] = count
            count += 1
    # word2id = {k: v+1 if vocab_counter[k] > 1 else k: 0 for (k, v) in zip(vocab_counter, range(len(vocab_counter)))}
    id2word = dict(zip(word2id.values(), word2id.keys()))
    print(len(word2id))
    print(len(id2word))
    with open(word2id_file, 'w', encoding='utf-8') as f:
        json.dump(word2id, f)
    with open(id2vocab_file, 'w', encoding='utf-8') as f:
        json.dump(id2word, f)


def create_data_file(in_file, out_lable_file, out_text_file):
    with open(vocab2id_file, 'r', encoding='utf-8') as f:
        word2id = json.load(f)['w2i']
    lable_list = []
    words_list = []
    lens_list = []
    with open(in_file, 'r', encoding='utf-8', errors='ignore') as fin:
        lines = fin.readlines()
        for line in lines:
            lables, words = sentence_process(line)
            words_id = [word2id[word] if word in word2id else 0 for word in words]
            lable_list.append(np.array(lables))
            words_list.append(np.array(words_id))
            lens_list.append(len(words_id))
    # print(lens_list)
    rank_list = np.argsort(np.array(lens_list))  # up-rank
    words_list = np.array([words_list[rank] for rank in rank_list])
    lable_list = np.array([lable_list[rank] for rank in rank_list])
    np.save(out_lable_file, lable_list)
    np.save(out_text_file, words_list)


def read_text(in_file):
    text = np.load(in_file)
    print(text)


if __name__ == '__main__':
    # create_valid_data()
    # get_vocab_id()
    create_data_file(train_file, train_lable_file, train_id_file)
    create_data_file(valid_file, valid_lable_file, valid_id_file)
    create_data_file(test_file, test_lable_file, test_id_file)