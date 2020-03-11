# -*- coding: UTF-8 -*-
import os, re, json
from zhon.hanzi import punctuation
from operator import itemgetter

vocab_dict = {"</bos>": 0, "</eos>": 0}
prefix = "./sina_news_gbk/2016-"
suffix = ".txt"
tablefile = "./拼音汉字表_12710172/一二级汉字表.txt"
tablestr = ""
objectpath = "./sina_news_vocab"
punctuation += "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.%!()【】（）.．/~`●\n\t\r"


# 读取一二级汉字表
def read_char():
    global tablestr
    with open(tablefile, encoding="gbk") as f:
        tablestr = f.read()


# 数据清洗，同时将一个句子处理成带有</bos>和</eos>符号的句子
def modify(sentence):
    if len(sentence) > 0 and sentence[-1] in (r"[%s]+" % punctuation):
        sentence = sentence[:-1]
    sentence = re.sub(r"[%s]+" % punctuation, "EB", sentence)
    sentence = "B" + sentence + "E"
    return sentence


# 读取语料
# 句子的分割以一个标点符号为标志，而不是句号
def read_save_vocab():
    global vocab_dict
    read_char()
    filename = ""
    count = 0
    print("Begin read corpus file...")
    for fileid in range(2, 12):
        if fileid < 10:
            filename = prefix + "0" + str(fileid) + suffix
        else:
            filename = prefix + str(fileid) + suffix
        if os.path.exists(filename):
            print("Begin read file " + filename + " ...")
            with open(filename, "r", encoding="gbk") as f:
                for line in f.readlines():
                    sentence = modify(json.loads(line, encoding="gbk")["html"])
                    for ch in sentence:
                        if ch in tablestr:
                            count += 1
                            vocab_dict[ch] = vocab_dict.get(ch, 0) + 1
                        elif ch == "B":
                            vocab_dict["</bos>"] += 1
                        elif ch == "E":
                            vocab_dict["</eos>"] += 1
    # 排序
    vocab_dict = sorted(vocab_dict.items(), key=itemgetter(1), reverse=True)
    vocab2id = {}
    rank = 0
    if not os.path.exists(objectpath):
        os.mkdir(objectpath)
    # 保存词频统计文件
    print("Begin save vocab file...")
    with open(objectpath+"/vocab.txt", mode="w+", encoding="utf-8") as f:
        f.write(str(count) + "\n")
        # print(vocab_dict)
        for item in vocab_dict:
            vocab2id[item[0]] = rank # 编号
            rank += 1
            f.write(item[0] + " " + str(item[1]) + "\n")
    # 保存语料文件
    print("Begin save corpus file...")
    with open(objectpath+"/corpus.txt", mode="w+", encoding="utf-8") as f:
        for fileid in range(2, 12):
            if fileid < 10:
                filename = prefix + "0" + str(fileid) + suffix
            else:
                filename = prefix + str(fileid) + suffix
            if os.path.exists(filename):
                print("Begin save id file " + filename + " ...")
                with open(filename, "r", encoding="gbk") as g:
                    f.write(str(vocab2id["</bos>"]) + " ")
                    for line in g.readlines():
                        sentence = modify(json.loads(line, encoding="gbk")["html"])
                        for ch in sentence:
                            if ch in vocab2id:
                                f.write(str(vocab2id[ch]) + " ")
                        f.write("\n")
    # 保存vocab2id 映射表
    print("Save vocab2id...")
    with open(objectpath+"/vocab2id.json", "w+", encoding="utf-8") as f:
        json.dump(vocab2id, f)