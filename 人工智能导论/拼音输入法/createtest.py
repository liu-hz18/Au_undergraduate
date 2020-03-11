
import pypinyin
import re
from zhon.hanzi import punctuation

suffix = "nor"
srcfilepath = "./src_" + suffix + ".txt"
inputfile = "./input_" + suffix + ".txt"
answerfile = "./answer_" + suffix + ".txt"
punctuation += "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.%!()【】（）.．/~`●；：:;+-*/\n\t\r"


def modify(sentence):
    if len(sentence) > 0 and sentence[-1] in (r"[%s]+" % punctuation):
        sentence = sentence[:-1]
    sentence = re.sub(r"[%s]+" % punctuation, "-", sentence)
    sentence = re.sub(r'\[', '-', sentence)
    sentence = re.sub(r']', '-', sentence)
    sentencelist = sentence.split('-')
    return sentencelist


# 生成测试集文件,直接使用训练的子集就可以
def create_test():
    with open(srcfilepath, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()
    # 清除非中文符号
    newline = []
    for line in lines:
        if len(line) > 4:
            linelist = modify(line)
            newline.extend(linelist)
    # print(newline)
    # 生成对应拼音
    with open(inputfile, 'w+', encoding='utf-8') as f:
        for line in newline:
            if len(line) > 4:
                f.write(' '.join([item[0] for item in pypinyin.pinyin(line, style=pypinyin.NORMAL)]) + '\n')
    with open(answerfile, 'w+', encoding='utf-8') as f:
        for line in newline:
            if len(line) > 4:
                f.write(line + "\n")


if __name__ == '__main__':
    create_test()
