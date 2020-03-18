# -*- coding: UTF-8 -*-

import numpy as np
import json
import scipy.io as scio
from initmat import get_count

objectpath = "./sina_news_vocab"
pinyin2char = {}
vocab2id = {}
weightmat = []
count_3gram = {}
top2gram = {}


def load_model():
    global pinyin2char, vocab2id, weightmat, count_3gram, top2gram
    print("Loading Model...Please wait for about 10-15 seconds...")
    with open(objectpath+"/pinyin2char.json", "r", encoding="utf-8") as f:
        pinyin2char = json.load(f)
    with open(objectpath+"/vocab2id.json", "r", encoding="utf-8") as f:
        vocab2id = json.load(f)
    total, countlist = get_count()
    weightmat = scio.loadmat(objectpath+"/weightmat.mat")['weightmat']
    with open(objectpath+"/top2gram.txt", "r", encoding='utf-8') as f:
        top2gram = eval(f.read())
    with open(objectpath+"/count_3gram.txt", "r", encoding="utf-8") as f:
        count_3gram = eval(f.read())


# 2gram模型vitebi算法, 输入参数的拼音序列
def vitebi_2gram(sentence, outputfile):
    # print(sentence)
    pinyin_list = sentence.strip().split(' ')
    dp = np.zeros((len(pinyin_list)+1, 120), dtype=float)
    mem = []
    resultlist = []
    # 检测是否合法
    for item in pinyin_list:
        if not item.isalpha():
            print("String: " + sentence + " is not valid!")
            with open(outputfile, 'a+', encoding="utf-8") as f:
                f.write('\n')
            return
    # 初始化dp数组
    first_py = pinyin_list[0]
    # 从</bos>到</eos>
    candidate = pinyin2char[first_py]
    for i in range(len(candidate)):
        dp[0][i] = weightmat[vocab2id["</bos>"]][vocab2id[candidate[i]]]

    t = 1
    lastcandidate = candidate
    candidate = pinyin2char[pinyin_list[1]]
    lastlast = vocab2id["</bos>"]
    memlist = []
    for i in range(len(candidate)):
        cur = vocab2id[candidate[i]]
        for j in range(len(lastcandidate)):
            last = vocab2id[lastcandidate[j]]
            factor = weightmat[last][cur]
            if (lastlast, last, cur) in count_3gram:
                factor += 2.0 * count_3gram[(lastlast, last, cur)] / top2gram[(lastlast, last)]
            if dp[t][i] <= dp[t-1][j] * factor:
                dp[t][i] = dp[t-1][j] * factor
                flagj = j
        memlist.append(flagj)
    mem.append(memlist)

    t = 2
    lastlastcandidate = lastcandidate
    lastcandidate = candidate
    for pinyin in pinyin_list[2:]:
        candidate = pinyin2char[pinyin]
        memlist = []
        for i in range(len(candidate)):
            flagj = 0
            cur = vocab2id[candidate[i]]
            for j in range(len(lastcandidate)):
                last = vocab2id[lastcandidate[j]]
                factor = weightmat[last][cur]
                for k in range(len(lastlastcandidate)):
                    lastlast = vocab2id[lastlastcandidate[k]]
                    if (lastlast, last, cur) in count_3gram:
                        factor += top2gram[(lastlast, last)] / 100000000
                        if mem[t-2][j] == k:
                            factor += count_3gram[(lastlast, last, cur)] / top2gram[(lastlast, last)]
                if dp[t][i] < dp[t-1][j] * factor:
                    dp[t][i] = dp[t-1][j] * factor
                    flagj = j
            memlist.append(flagj)
        mem.append(memlist)
        lastlastcandidate = lastcandidate
        lastcandidate = candidate
        t += 1
    # 处理</eos>
    flagj = 0
    for j in range(len(lastcandidate)):
        last = vocab2id[lastcandidate[j]]
        cur = vocab2id['</eos>']
        factor = weightmat[last][cur]
        for k in range(len(lastlastcandidate)):
            lastlast = vocab2id[lastlastcandidate[k]]
            if (lastlast, last, cur) in count_3gram:
                factor += top2gram[(lastlast, lastlast)] / 100000000
                if mem[t-2][j] == k:
                    factor += count_3gram[(lastlast, last, cur)] / top2gram[(lastlast, last)]
        if dp[t][0] < dp[t-1][j] * factor:
            dp[t][0] = dp[t-1][j] * factor
            flagj = j
    # 回溯找到最优解
    while t > 1:
        resultlist.append(pinyin2char[pinyin_list[t-1]][flagj])
        flagj = mem[t-2][flagj]
        t -= 1
    resultlist.append(pinyin2char[pinyin_list[0]][flagj])
    resultlist.reverse()
    result = "".join(resultlist)
    with open(outputfile, 'a+', encoding="utf-8") as f:
        f.write(result + '\n')
    # print(result)


# 2gram模型vitebi算法, 输入参数的拼音序列
def vitebi_3gram(sentence, outputfile):
    # print(sentence)
    pinyin_list = sentence.strip().split(' ')
    dp = np.zeros((len(pinyin_list)+1, 120, 120), dtype=float)# 概率矩阵
    prevj = np.zeros((len(pinyin_list)+1, 120, 120), dtype=int)# 前向指针
    previ = np.zeros((len(pinyin_list)+1, 120, 120), dtype=int)
    # 检测是否合法
    for item in pinyin_list:
        if not item.isalpha():
            print("String: " + sentence + " is not valid!")
            with open(outputfile, 'a+', encoding="utf-8") as f:
                f.write('\n')
            return
    # 初始化dp数组
    first_py = pinyin_list[0]
    candidate = pinyin2char[first_py]
    for i in range(len(candidate)):
        dp[0][0][i] = weightmat[vocab2id["</bos>"]][vocab2id[candidate[i]]]
    # 从list[1]到</eos>
    t = 1
    lastlastcandidate = ['</bos>']
    lastcandidate = pinyin2char[pinyin_list[t-1]]
    for pinyin in pinyin_list[1:]:
        candidate = pinyin2char[pinyin_list[t]]
        for i in range(len(candidate)):
            cur = vocab2id[candidate[i]]
            for j in range(len(lastcandidate)):
                last = vocab2id[lastcandidate[j]]
                prob = weightmat[last][cur]
                factor = 0.0
                maxk = 0
                for k in range(len(lastlastcandidate)):
                    lastlast = vocab2id[lastlastcandidate[k]]
                    if (lastlast, last, cur) in count_3gram:
                        factor = count_3gram[(lastlast, last, cur)] / top2gram[(lastlast, last)]
                    if dp[t][j][i] < dp[t-1][k][j] * (prob + factor):
                        dp[t][j][i] = dp[t-1][k][j] * (prob + factor)
                        maxk = k
                prevj[t][j][i] = maxk
                previ[t][j][i] = j
        t += 1
        lastlastcandidate = lastcandidate
        lastcandidate = candidate
    # 处理最后一个字符
    cur = vocab2id['</eos>']
    for j in range(len(lastcandidate)):
        last = vocab2id[lastcandidate[j]]
        prob = weightmat[last][cur]
        factor = 0
        maxk = 0
        for k in range(len(lastlastcandidate)):
            lastlast = vocab2id[lastlastcandidate[k]]
            if (lastlast, last, cur) in count_3gram:
                factor = count_3gram[(lastlast, last, cur)] / top2gram[(lastlast, last)]
            if dp[t][j][0] < dp[t-1][k][j] * (prob + factor):
                dp[t][j][0] = dp[t-1][k][j] * (prob + factor)
                maxk = k
        prevj[t][j][0] = maxk
        previ[t][j][0] = j
    tempmax = 0
    flagj = 0
    for j in range(120):
        if tempmax < dp[t][j][0]:
            tempmax = dp[t][j][0]
            flagj = j
    flagi = 0
    resultlist = []
    # 回溯找到最优解
    while t > 1:
        resultlist.append(pinyin2char[pinyin_list[t-1]][flagj])
        temp = flagj
        flagj = prevj[t][flagj][flagi]
        flagi = previ[t][temp][flagi]
        t -= 1
    resultlist.append(pinyin2char[pinyin_list[0]][flagj])
    resultlist.reverse()
    result = "".join(resultlist)
    with open(outputfile, 'a+', encoding="utf-8") as f:
        f.write(result + '\n')
    # print(result)