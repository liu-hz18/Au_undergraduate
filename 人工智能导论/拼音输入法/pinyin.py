# -*- coding: UTF-8 -*-
import os, sys

from char2corpus import read_save_vocab
from char2gram import char_2gram, get_top_2gram
from char3gram import char_3gram
from initmat import get_weight_mat, read_pinyin_candidate
from run import load_model, vitebi


# 统计字正确率
def get_accuracy():
    print("Begin analysis accuracy...")
    with open(answerfile, 'r', encoding='utf-8') as f:
        answerlist = f.readlines()
    with open(outputfile, 'r', encoding='utf-8') as f:
        outputlist = f.readlines()
    total = 0
    correct = 0
    sentencecorrect = 0
    totalsentence = 0
    for i in range(len(answerlist)):
        if len(answerlist[i]) == len(outputlist[i]):
            totalsentence += 1
        else:
            continue
        for j in range(len(answerlist[i])):
            total += 1
            if answerlist[i][j] == outputlist[i][j]:
                correct += 1
        if answerlist[i] == outputlist[i]:
            sentencecorrect += 1
    acc = correct / total
    senacc = sentencecorrect / totalsentence
    print("Char Accuracy:", acc, "Sentence Accuracy:", senacc, "\nTotal Char:", total, "Total sentence:", totalsentence)


def printhelp():
    print(" If you HAVE NOT preprocessed data, please run:")
    print("      python -p")
    print("\n Attention:\n  This preprocess will takes for about 30 mins and 5GB memory!!!")
    print("\n If you HAVE preprocessed data, please run:")
    print("      python pinyin.py inputfile outputfile [answerfile]")
    print("\n A simple demo is:")
    print("      python pinyin.py ./input.txt ./output.txt ./answer.txt")


def preprocessdata():
    read_save_vocab()
    char_2gram()
    get_top_2gram()
    # if you change lambda, you need to rerun function: get_weight_mat()
    get_weight_mat(lamb=0.05)
    char_3gram()
    read_pinyin_candidate()


def run_translator(inputfile, outputfile):
    with open(outputfile, 'w+', encoding='utf-8') as f:
        f.write('')
    count = 0
    load_model()
    print('Begin translating sentences to file >> ' + outputfile)
    with open(inputfile, 'r', encoding='utf-8') as f:
        for line in f.readlines():
            count += 1
            print("translate sentence:", count, end='\r')
            vitebi(line, outputfile)
    print("Finished!")


if __name__ == '__main__':
    # python pinyin.py ./input.txt ./output.txt ./answer.txt
    if len(sys.argv) < 2:
        printhelp()
    elif sys.argv[1] == '-h' or sys.argv[1] == '-help':
        printhelp()
    elif sys.argv[1] == '-p':
        print("Begin preprocess data...The whole process takes about 30 mins and 5GB Memory !!!")
        print("continue? [y/n]", end=' ')
        s = input()
        if s == 'y':
            preprocessdata()
    elif len(sys.argv) == 4 or len(sys.argv) == 3:
        inputfile = sys.argv[1]
        outputfile = sys.argv[2]
        if not os.path.exists(inputfile):
            print("Input file not found!")
            sys.exit()
        run_translator(inputfile, outputfile)
        if len(sys.argv) == 4:
            answerfile = sys.argv[3]
            if os.path.exists(answerfile):
                get_accuracy()
            else:
                print("Answer file not found!")
                sys.exit()
    else:
        printhelp()
