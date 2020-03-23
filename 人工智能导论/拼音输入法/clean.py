#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import json
import re
import multiprocessing as mp
from zhon.hanzi import punctuation
from tqdm import tqdm

punctuation += "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.%!()【】（）.．/~`●■★\n\t\r"


def modify(sentence):
    if len(sentence) > 0 and sentence[-1] in (r"[%s]+" % punctuation):
        sentence = sentence[:-1]
    return "B" + re.sub(r"[%s]+" % punctuation, "EB", sentence.lstrip("原标题：")) + "E"


def readFile(name):
    print(name)
    try:
        with open(name + ".txt", 'r', encoding="gbk", errors="ignore") as f:
            lines = f.readlines()
            for line in lines:
                sentence = modify(json.loads(line, encoding="gbk")["html"])
                with open(name + "_con.txt", 'a+', encoding='utf-8') as fin:
                    fin.write(sentence + "\n")
        return None
    except:
        print("error occured when reading file" + name)
        return None


def readJson(name):
    namelist = ["头条新闻", "综合新闻", "要闻聚焦", "媒体清华"]
    with open(name + ".json", 'r', encoding="utf-8", errors='ignore') as f:
        news = json.load(f)
    with open(name + "_con.txt", 'w+', encoding="utf-8") as f:
        for name in namelist:
            infolist = news[name]
            for info in infolist:
                if info is not None:
                    f.write(modify(info['content']) + "\n")



if __name__ == '__main__':
    filename = ["./2016-02", "./2016-03", "./2016-04", "./2016-05", "./2016-06", \
                "./2016-07", "./2016-08", "./2016-09", "./2016-10", "./2016-11"]
    #with mp.Pool(10) as pool:
    #    pool.imap_unordered(readFile, filename)
    #for name in filename:
    #    readFile(name)
    readJson("./news")