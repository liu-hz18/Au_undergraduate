# -*- coding: UTF-8 -*-
import sys, json
from operator import itemgetter
from char2corpus import objectpath


# 3元模型, 对排名前1000000的二元组做三元组统计
def char_3gram():
    print("Begin init 3 gram model...")
    with open(objectpath+"/vocab2id.json", "r", encoding="utf-8") as f:
        vocab2id = json.load(f)
    with open(objectpath+"/top2gram.txt", 'r', encoding='utf-8') as f:
        top2gram = eval(f.read())
    count_3gram = {}#字典太慢了，换成矩阵吧
    print("Begin build char3gram matrix...")
    countline = 0
    with open(objectpath+"/corpus.txt", "r", encoding="utf-8") as f:
        for line in f.readlines():
            if len(line) < 3:
                continue
            countline += 1
            if countline % 100 == 0:
                sys.stdout.write("readlines:" + str(countline) + "\r")
            ch0 = vocab2id['</bos>']
            ch1 = vocab2id['</bos>']
            ch2 = vocab2id['</bos>']
            words = list(map(int, line.strip("\n").strip(' ').split(" ")))
            for ch in words:
                ch2 = ch
                if (ch0, ch1) in top2gram:
                    k = (ch0, ch1, ch2)
                    count_3gram[k] = count_3gram.get(k, 0) + 1
                ch0 = ch1
                ch1 = ch2
    temp = sorted(count_3gram.items(), key=itemgetter(1), reverse=True)[:1000000]
    gramdict = {}
    for item in temp:
        gramdict[item[0]] = int(item[1])
    with open(objectpath+"/count_3gram.txt", "w+", encoding="utf-8") as f:
        f.write(str(gramdict))