# -*-encoding=utf-8-*-#
import os
import random
import threading
import time
import math
import sys
import numpy as np

MAX_STRING = 100
MAX_EXP = 6
MAX_TABLE_SIZE = 1000
MAX_SENTENCE_LENGTH = 1000
MAX_CODE_LENGTH = 40


# 单词，存储词频、单词、哈夫曼编码
class vocab_word():
    def __init__(self, word):
        self.count = 0
        self.word = word
        self.codelen = 0
        self.code = [0] * MAX_CODE_LENGTH
        self.point = [0] * MAX_CODE_LENGTH

    def getCount(self):
        return self.count

# 多线程训练
class MyThread(threading.Thread):
    def __init__(self, threadID, model):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.model = model

    def run(self):
        Word2Vec.TrainModelTread(self.model, threadid=self.threadID)


# word2vec
class Word2Vec(object):
    """class for Word2Vec""" 
    def __init__(self, train_file, output_file, vocab_file, size=100, window=5,
                 min_count=5, iternum=5, negative=5, hs=0, cbow=1, sample=1e-3, alpha=0.025,
                 debug_mode=1, threads=12):
        self.train_file_name = train_file
        self.output_file_name = output_file
        self.save_vocab_file_name = vocab_file
        self.read_vocab_file_name = vocab_file
        self.layer1_size = size
        self.window = window
        self.min_count = min_count
        self.iternum = iternum
        self.negative = negative
        self.hs = hs
        self.cbow = cbow
        self.sample = sample
        self.alpha = alpha
        self.debug_mode = debug_mode
        self.num_threads = threads
        self.min_reduce = 1
        self.vocab_max_size = 1000
        self.vocab_size = 0
        self.train_words = 0
        self.word_count_actual = 0
        self.file_size = 0
        self.starting_alpha = alpha
        self.table_size = 100000000
        self.table, self.vocab, self.syn0, self.syn1, self.syn1neg = [], [], [], [], []
        self.vocab_hash_size = 30319321
        self.vocab_hash = [0] * self.vocab_hash_size
        self.expTable = [1 - 1 / (1 + math.exp((i / MAX_TABLE_SIZE * 2 - 1) * MAX_EXP)) for i in range(MAX_TABLE_SIZE)]
        self.start = 0
        self.threadLock = threading.Lock()
        

    # 初始化采样表
    def initable(self, power_list):
        d1 = power_list[0]
        a, i, last_a = 0, 0, 0
        print('begin init table...')
        while a < self.table_size:
            if a > d1 and i < self.vocab_size - 1:
                self.table[last_a:a] = i
                i += 1
                d1 += power_list[i]
                last_a = a
            if i >= self.vocab_size - 1:
                break
            a += 1
        print('begin init left %d table...' % (self.table_size - a))
        self.table[last_a:self.table_size] = self.vocab_size - 1

    # 初始化采样表
    def InitUnigramTable(self):
        power = 0.75
        power_list = np.array(
            [self.vocab[i].count**power for i in range(self.vocab_size)])
        train_words_pow = sum(power_list)
        power_list *= self.table_size / train_words_pow
        self.initable(power_list)
        del power_list

    # 从文件中读取一个单词
    def readWord(self, fin):
        a = 0
        word = []
        while 1:
            ch = fin.read(1)
            if not ch:
                break
            if ch == '\r':
                continue
            if ch == ' ' or ch == '\t' or ch == '\n':
                if a > 0:
                    if ch == '\n':
                        return '</s>'
                    break
                continue
            word.append(ch)
            a += 1
            if a >= MAX_STRING - 1:
                a -= 1
        return ''.join(word)

    # 得到单词在词表中的索引
    def readWordIndex(self, fin):
        word = self.readWord(fin)
        if len(word) == 0:
            return -1
        return self.searchVocab(word)

    # 查找单词在词汇表中的位置
    def searchVocab(self, word):
        hashnum = hash(word) % self.vocab_hash_size
        while 1:
            if self.vocab_hash[hashnum] == -1:
                return -1
            if word == self.vocab[self.vocab_hash[hashnum]].word:
                return self.vocab_hash[hashnum]
            hashnum = (hashnum + 1) % self.vocab_hash_size
        return -1

    # 将单词加入词汇表
    def AddWordToVocab(self, word):
        length = len(word) + 1
        if length > MAX_STRING:
            length = MAX_STRING
        self.vocab.append(vocab_word(word))
        self.vocab_size += 1
        hashnum = hash(word) % self.vocab_hash_size
        while self.vocab_hash[hashnum] != -1:
            hashnum = (hashnum + 1) % self.vocab_hash_size
        self.vocab_hash[hashnum] = self.vocab_size - 1
        return self.vocab_size - 1

    # 对 单词按词频排序
    def sortVocab(self):
        self.vocab = sorted(self.vocab, key=lambda x: x.getCount(), reverse=True)
        self.vocab_hash = [-1] * self.vocab_hash_size
        self.vocab_size = len(self.vocab)
        size = self.vocab_size
        self.train_words = 0
        for a in range(size):
            if self.vocab[a].count < self.min_count and a != 0:
                self.vocab_size -= 1
            else:
                hashnum = hash(self.vocab[a].word) % self.vocab_hash_size
                while self.vocab_hash[hashnum] != -1:
                    hashnum = (hashnum + 1) % self.vocab_hash_size
                self.vocab_hash[hashnum] = a
                self.train_words += self.vocab[a].count
        self.train_words -= 1

    # 将单词从词表中去除
    def ReduceVocab(self):
        b = 0
        for a in range(self.vocab_size):
            if self.vocab[a].count > self.min_reduce:
                self.vocab[b].count = self.vocab[a].count
                self.vocab[b].word = self.vocab[a].word
                b += 1
        self.vocab_size = b
        self.vocab_hash = [-1] * self.vocab_hash_size
        for a in range(self.vocab_size):
            hashnum = hash(self.vocab[a].word) % self.vocab_hash_size
            while self.vocab_hash[hashnum] != -1:
                hashnum = (hashnum + 1) % self.vocab_hash_size
            self.vocab_hash[hashnum] = a
        self.min_reduce += 1

    # 创建哈夫曼二叉树
    def CreateBinaryTree(self):
        count = [int(1e15)] * (self.vocab_size * 2)
        binary = [0] * (self.vocab_size * 2 + 1)
        parent_node = [0] * (self.vocab_size * 2 + 1)
        code = [0] * MAX_CODE_LENGTH
        point = [0] * MAX_CODE_LENGTH
        min1i, min2i = 0, 0
        for a in range(0, self.vocab_size):
            count[a] = self.vocab[a].count
        pos1 = self.vocab_size - 1
        pos2 = self.vocab_size
        for a in range(0, self.vocab_size - 1):
            if pos1 >= 0 and count[pos1] < count[pos2]:
                min1i = pos1
                pos1 -= 1
            else:
                min1i = pos2
                pos2 += 1
            if pos1 >= 0 and count[pos1] < count[pos2]:
                min2i = pos1
                pos1 -= 1
            else:
                min2i = pos2
                pos2 += 1
            count[self.vocab_size + a] = count[min1i] + count[min2i]
            parent_node[min1i] = self.vocab_size + a
            parent_node[min2i] = self.vocab_size + a
            binary[min2i] = 1

        for a in range(0, self.vocab_size):
            b = a
            i = 0
            while 1:
                code[i] = binary[b]
                point[i] = b
                i += 1
                b = parent_node[b]
                if b >= self.vocab_size * 2 - 2:
                    break
            self.vocab[a].codelen = i
            self.vocab[a].point[0] = self.vocab_size - 2
            for b in range(0, i):
                self.vocab[a].code[i - b - 1] = code[b]
                self.vocab[a].point[i - b] = point[b] - self.vocab_size
        del count
        del binary
        del parent_node

    # 从训练文本中读取单词，并构建词表
    def LearnVocabFromTrainFile(self):
        with open(self.train_file_name, 'r', encoding='utf-8', errors='ignore') as fin:
            while 1:
                word = self.readWord(fin)
                if not word:
                    break
                if word == '</s>':
                    continue
                self.train_words += 1
                if self.train_words % 20000 == 0:
                    print('Words read: %d K ' %
                          (self.train_words / 1000), end='\r', flush=False)
                i = self.searchVocab(word)
                if i == -1:
                    a = self.AddWordToVocab(word)
                    self.vocab[a].count = 1
                else:
                    self.vocab[i].count += 1
                if self.vocab_size > self.vocab_hash_size * 0.7:
                    self.ReduceVocab()

    # 保存词表到文件
    def saveVocab(self):
        with open(self.save_vocab_file_name, 'w', encoding='utf-8', errors='ignore') as fout:
            for i in range(0, self.vocab_size):
                fout.write('%s %d\n' %
                           (self.vocab[i].word, self.vocab[i].count))

    # 如果有词表文件，就从硬盘读取词表
    def readVocab(self):
        i = 0
        with open(self.read_vocab_file_name, 'r', encoding='utf-8', errors='ignore') as fin:
            self.vocab_hash = [-1] * self.vocab_hash_size
            self.vocab_size = 0
            lines = fin.readlines()
            for line in lines:
                wordinfo = line.split(' ')
                a = self.AddWordToVocab(wordinfo[0])
                self.vocab[a].count = int(wordinfo[1])
            self.sortVocab()
            if self.debug_mode > 0:
                print('Vocab Size: %d' % self.vocab_size)
                print('Words in train file: %d' % self.train_words)
        self.file_size = os.path.getsize(self.train_file_name)

    # 初始化权重网络
    def InitNet(self):
        print('init syn1 and syn1neg...')
        if self.hs:
            self.syn1 = np.zeros((self.vocab_size, self.layer1_size))
        if self.negative > 0:
            self.syn1neg = np.zeros((self.vocab_size, self.layer1_size))
        print('init syn0...')
        self.syn0 = np.random.random((self.vocab_size, self.layer1_size)) - 0.5
        print('Create binary tree...')
        self.CreateBinaryTree()

    # 训练模型
    def train(self):
        print("\nStarting training using file %s ..." % self.train_file_name)
        if os.path.exists(self.read_vocab_file_name) == False:
            print('begin read vocab from vocabulary...')
            self.readVocab()
        else:
            print('begin read vocab from train file...')
            self.vocab_hash = [-1] * self.vocab_hash_size
            self.file_size = os.path.getsize(self.train_file_name)
            self.train_words = 0
            # AddWordToVocab('</s>')
            self.LearnVocabFromTrainFile()
            self.sortVocab()
            if self.debug_mode > 0:
                print('\nVocab size: %d ' % self.vocab_size)
                print('Words in train file: %d' % self.train_words)
        if self.output_file_name[0] == '0':
            return
        if self.save_vocab_file_name != '0':
            self.saveVocab()

        print('begin init net...')
        self.InitNet()
        if self.negative > 0:
            print('begin init unigram table...')
            self.table = np.zeros(self.table_size)
            self.InitUnigramTable()

        print('begin training in %d threads...' % self.num_threads)
        thread_list = []
        self.start = time.time()
        for a in range(self.num_threads):
            temp = MyThread(a, self)
            temp.setDaemon(True)
            temp.start()
            thread_list.append(temp)
        for t in thread_list:
            t.join()

        print("\nAll Threads Finished")

        with open(self.output_file_name, "w", encoding='utf-8', errors='ignore') as f:
            f.write("%d %d\n" % (self.vocab_size, self.layer1_size))
            for a in range(self.vocab_size):
                f.write("%s " % self.vocab[a].word)
                for b in range(self.layer1_size):
                    f.write("%lf " % self.syn0[a][b])
                f.write("\n")


    # 子线程的训练核心函数,注意加锁
    def TrainModelTread(self, threadid):
        sentence_length, sentence_position = 0, 0
        word_count, last_word_count = 0, 0
        l1, l2, c = 0, 0, 0
        target, label = 0, 0
        cw, wordid = 0, 0
        sen = np.zeros(MAX_SENTENCE_LENGTH + 1)
        local_iter = self.iternum
        neu1 = np.zeros(self.layer1_size)
        neu1e = np.zeros(self.layer1_size)
        # 预先计算
        lower_alpha = self.starting_alpha * 0.0001
        dominator = MAX_TABLE_SIZE / MAX_EXP / 2
        total_words = self.train_words * self.iternum
        temp = self.sample * self.train_words
        flag = 0
        with open(self.train_file_name, 'r', encoding='utf-8', errors='ignore') as fin:
            fin.seek((self.file_size // self.num_threads) * threadid)
            while local_iter > 0:
                if sentence_length == 0:
                    flag = 0
                    while 1:
                        wordid = self.readWordIndex(fin)
                        if fin.tell() >= (self.file_size // self.num_threads) * (threadid + 1):
                            flag = 1
                            break
                        if wordid == -1:
                            continue
                        word_count += 1
                        if wordid == 0:
                            break
                        if self.sample > 0:
                            ran = temp / self.vocab[wordid].count
                            ran += math.sqrt(ran)
                            if ran < random.uniform(0, 1):
                                continue
                        sen[sentence_length] = wordid
                        sentence_length += 1
                        if sentence_length >= MAX_SENTENCE_LENGTH:
                            break
                    sentence_position = 0

                wordid = sen[sentence_position]
                if wordid == -1:
                    continue
                neu1 = np.zeros(self.layer1_size)
                neu1e = np.zeros(self.layer1_size)
                b = random.randint(1, self.window)

                if self.cbow:
                    cw = 0
                    for a in range(b, self.window * 2 + 1 - b):
                        if a != self.window:
                            c = sentence_position - self.window + a
                            if c < 0 or c >= sentence_length:
                                continue
                            last_wordid = sen[c]
                            if last_wordid == -1:
                                continue
                            self.threadLock.acquire()
                            neu1 += self.syn0[int(last_wordid)]
                            self.threadLock.release()
                            cw += 1
                    if cw > 0:
                        neu1 /= cw
                        if self.hs > 0:
                            for d in range(0, self.vocab[wordid].codelen):
                                l2 = int(self.vocab[wordid].point[d])
                                self.threadLock.acquire()
                                f = np.dot(neu1, self.syn1[l2])
                                self.threadLock.release()
                                if f <= -MAX_EXP or f >= MAX_EXP:
                                    continue
                                else:
                                    f = self.expTable[int((f + MAX_EXP) * dominator)]
                                g = (1 - self.vocab[wordid].code[d] - f) * self.alpha
                                self.threadLock.acquire()
                                neu1e += self.syn1[l2] * g
                                self.syn1[l2] += neu1 * g
                                self.threadLock.release()
                        if self.negative > 0:
                            for d in range(0, self.negative + 1):
                                if d == 0:
                                    target = wordid
                                    label = 1
                                else:
                                    rand = random.randint(0, self.table_size - 1)
                                    target = self.table[rand]
                                    if target == 0:
                                        target = rand % (self.vocab_size - 1) + 1
                                    if target == wordid:
                                        continue
                                    label = 0
                                l2 = int(target)
                                self.threadLock.acquire()
                                f = np.dot(neu1, self.syn1neg[l2])
                                self.threadLock.release()
                                if f > MAX_EXP:
                                    g = (label - 1) * self.alpha
                                elif f < -MAX_EXP:
                                    g = (label - 0) * self.alpha
                                else:
                                    g = (
                                        label - self.expTable[int((f + MAX_EXP) * dominator)]) * self.alpha
                                self.threadLock.acquire()
                                neu1e += self.syn1neg[l2] * g
                                self.syn1neg[l2] += neu1 * g
                                self.threadLock.release()

                        for a in range(b, self.window * 2 + 1 - b):
                            if a != self.window:
                                c = sentence_position - self.window + a
                                if c < 0 or c >= sentence_length:
                                    continue
                                last_wordid = int(sen[c])
                                if last_wordid == -1:
                                    continue
                                self.threadLock.acquire()
                                self.syn0[last_wordid] += neu1e
                                self.threadLock.release()
                else:
                    for a in range(b, self.window * 2 + 1 - b):
                        if a != self.window:
                            c = sentence_position - self.window + a
                            if c < 0 or c >= sentence_length:
                                continue
                            last_wordid = sen[c]
                            if last_wordid == -1:
                                continue
                            l1 = int(last_wordid)
                            neu1e = np.zeros(self.layer1_size)
                            if self.hs > 0:
                                for d in range(self.vocab[wordid].codelen):
                                    l2 = int(self.vocab[wordid].point[d])
                                    self.threadLock.acquire()
                                    f = np.dot(self.syn0[l1], self.syn1[l2])
                                    self.threadLock.release()
                                    if f <= -MAX_EXP or f >= MAX_EXP:
                                        continue
                                    else:
                                        f = self.expTable[
                                            int((f + MAX_EXP) * dominator)]
                                    g = (
                                        1 - self.vocab[wordid].code[d] - f) * self.alpha
                                    self.threadLock.acquire()
                                    neu1 += self.syn1[l2] * g
                                    self.syn1[l2] += self.syn0[l1] * g
                                    self.threadLock.release()
                            if self.negative > 0:
                                for d in range(self.negative + 1):
                                    if d == 0:
                                        target = wordid
                                        label = 1
                                    else:
                                        rand = random.randint(0, self.table_size - 1)
                                        target = self.table[rand]
                                        if target == 0:
                                            target = rand % (
                                                self.vocab_size - 1) + 1
                                        if target == wordid:
                                            continue
                                        label = 0
                                    l2 = int(target)
                                    self.threadLock.acquire()
                                    f = np.dot(self.syn0[l1], self.syn1neg[l2])
                                    self.threadLock.release()
                                    if f > MAX_EXP:
                                        g = (label - 1) * self.alpha
                                    elif f < -MAX_EXP:
                                        g = (label - 0) * self.alpha
                                    else:
                                        g = (
                                            label - self.expTable[int((f + MAX_EXP) * dominator)]) * self.alpha
                                    self.threadLock.acquire()
                                    neu1e += self.syn1neg[l2] * g
                                    self.syn1neg[l2] += self.syn0[l1] * g
                                    self.threadLock.release()
                            self.threadLock.acquire()
                            self.syn0[l1] += neu1e
                            self.threadLock.release()

                sentence_position += 1
                if word_count - last_word_count > 1000:
                    self.word_count_actual += word_count - last_word_count
                    last_word_count = word_count
                    if self.debug_mode > 0:
                        now = time.time()
                        leftword = total_words - self.word_count_actual
                        speed = self.word_count_actual / (now - self.start + 1)
                        timeleft = leftword / speed
                        sys.stdout.write("%c Alpha: %f  Word trained: %d  Progress: %.4f%%  Words/thread/sec: %.4fk Time left: %.4f min" % (
                            13, self.alpha, self.word_count_actual, self.word_count_actual / total_words * 100, speed / 1000, timeleft / 60))
                        sys.stdout.flush()
                    self.threadLock.acquire()
                    self.alpha = self.starting_alpha * (1 - self.word_count_actual / (total_words + 1))
                    if self.alpha < lower_alpha:
                        self.alpha = lower_alpha
                    self.threadLock.release()

                if sentence_position >= sentence_length:
                    sentence_length = 0
                    if flag == 1:
                        flag = 2

                if flag == 2:
                    self.word_count_actual += word_count - last_word_count
                    local_iter -= 1
                    if local_iter == 0:
                        break
                    word_count, last_word_count, sentence_length = 0, 0, 0
                    fin.seek((self.file_size // self.num_threads) * threadid)
                    continue


if __name__ == '__main__':
    wv = Word2Vec(
        train_file='./test.txt',
        output_file='./output.txt',
        vocab_file='./vocab.txt',
        size=200,
        window=6,
        min_count=6,
        negative=5,
        iternum=5,
        threads=12)
    wv.train()
