# -*- coding: UTF-8 -*-
import numpy as np
import json, sys
import scipy.io as scio

objectpath = "./sina_news_vocab"


# 2元模型
def char_2gram():
    with open(objectpath+"/vocab2id.json", "r", encoding="utf-8") as f:
        vocab2id = json.load(f)
    vocabsize = len(vocab2id)
    matrix_2gram = np.zeros((vocabsize, vocabsize))
    print("Begin build char2gram matrix...")
    countline = 0
    with open(objectpath+"/corpus.txt", "r", encoding="utf-8") as f:
        for line in f.readlines():
            if len(line) < 2:
                continue
            countline += 1
            if countline % 100 == 0:
                sys.stdout.write("readlines:" + str(countline) + "\r")
            ch0 = vocab2id['</bos>']
            ch1 = vocab2id['</bos>']
            words = list(map(int, line.strip("\n").strip(' ').split(" ")))
            for ch in words:
                ch1 = ch
                matrix_2gram[ch0][ch1] += 1
                ch0 = ch1
    matrix_2gram = np.mat(matrix_2gram)
    scio.savemat(objectpath+"/char2gram.mat", {'char2gram': matrix_2gram})


# 获得排名靠前的二元组
def get_top_2gram():
    print("Begin find top 2 grams...Please wait for about 20 seconds...")
    with open(objectpath+"/vocab2id.json", "r", encoding="utf-8") as f:
        vocab2id = json.load(f)
    vocabsize = len(vocab2id)
    mat2gram = scio.loadmat(objectpath+"/char2gram.mat")['char2gram']
    # 获得排名前1000000的二元组
    char3gram = []
    for i in range(vocabsize):
        for j in range(vocabsize):
            char3gram.append((i, j, mat2gram[i][j]))
    char3gram = sorted(char3gram, key=lambda x: x[2], reverse=True)[:1000000]
    top2gram = {}
    for t in char3gram:
        top2gram[(t[0], t[1])] = t[2]
    # json无法保存元组作为key的字典
    with open(objectpath+"/top2gram.txt", 'w+', encoding='utf-8') as f:
        f.write(str(top2gram))