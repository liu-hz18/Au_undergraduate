# -*- coding: UTF-8 -*-
import scipy.io as scio
import numpy as np
import json

objectpath = "./sina_news_vocab"
pyfile_candidate = "./拼音汉字表_12710172/拼音汉字表.txt"


# 获得词频统计文件
def get_count():
    countlist = []
    with open(objectpath+"/vocab.txt", "r", encoding="utf-8") as f:
        for line in f.readlines()[1:]:
            countlist.append(int(line.split(' ')[1]))
    with open(objectpath+"/vocab.txt", "r", encoding="utf-8") as f:
        count = int(f.readline())
    return count, countlist


# 获取平滑后的权重矩阵
def get_weight_mat(lamb=0.05):
    with open(objectpath+"/vocab2id.json", "r", encoding="utf-8") as f:
        vocab2id = json.load(f)
    vocabsize = len(vocab2id)
    count, countlist = get_count()
    mat2gram = scio.loadmat(objectpath+"/char2gram.mat")['char2gram']
    weightmat = np.zeros((vocabsize, vocabsize))# 预处理a[prev][cur]
    print("Begin init weight matrix...")
    for i in range(vocabsize):
        for j in range(vocabsize):
            weightmat[i][j] = (1.0 - lamb) * mat2gram[i][j] / countlist[i] + lamb * countlist[j] / count
    weightmat = np.mat(weightmat)
    scio.savemat(objectpath+"/weightmat.mat", {'weightmat': weightmat})


# 读取并解析拼音候选列表
def read_pinyin_candidate():
    print("Begin read usable pinyin...")
    pinyin2char = {}
    with open(objectpath+"/vocab2id.json", "r", encoding="utf-8") as f:
        vocab2id = json.load(f)
    with open(pyfile_candidate, 'r', encoding="gbk") as f:
        for line in f.readlines():
            linelist = line.strip().split(' ')
            pinyin2char[linelist[0]] = []
            for ch in linelist[1:]:
                if ch in vocab2id:
                    pinyin2char[linelist[0]].append(ch)
    with open(objectpath+"/pinyin2char.json", "w+", encoding="utf-8") as f:
        json.dump(pinyin2char, f)
