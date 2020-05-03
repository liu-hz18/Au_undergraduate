
import numpy as np
import codecs
import sys
import json

vector_path = 'word2vec/sgns.sogounews.bigram-char'
matrix_path = 'word2vec/matrix'
vocab_path = 'word2vec/vocab'
# model = Word2Vec.load(vector_path)
# print(model.wv['申请'])

words_list = []


def sentence_process(line):
    blocks = line.strip().split('\t')
    sentiments, sentences = blocks[1].strip().split(), blocks[2].strip().split()
    lable = [int(score.strip().split(':')[-1]) for score in sentiments[1:]]
    return lable, sentences


def read_words():
    global words_list
    with open('sina/sinanews.train', 'r', encoding='utf-8') as f:
        for line in f.readlines():
            _, words = sentence_process(line)
            words_list.extend(words)
    with open('sina/sinanews.valid', 'r', encoding='utf-8') as f:
        for line in f.readlines():
            _, words = sentence_process(line)
            words_list.extend(words)
    with open('sina/sinanews.test', 'r', encoding='utf-8') as f:
        for line in f.readlines():
            _, words = sentence_process(line)
            words_list.extend(words)
    words_list = set(words_list)


def load_dense_drop_repeat(path, topn):
    print('loading word vectors...')
    vocab_size, size = 0, 0
    vocab = {}
    vocab["i2w"], vocab["w2i"] = [], {}
    count = 1
    with codecs.open(path, "r", "utf-8") as f:
        first_line = True
        for line in f:
            if first_line:
                first_line = False
                vocab_size = int(line.strip().split()[0])
                size = int(line.rstrip().split()[1])
                matrix = np.zeros(shape=(min(vocab_size, topn) if topn > 0 else vocab_size, size), dtype=np.float32)
                vocab['w2i']['<unk>'] = 0
                continue
            vec = line.strip().split()
            if len(vec) != 301:
                continue
            if vec[0] in words_list and not vocab["w2i"].__contains__(vec[0]):
                vocab["w2i"][vec[0]] = count
                matrix[count, :] = np.array([float(x) for x in vec[1:]])
                count += 1
                if count % 100 == 0:
                    sys.stdout.write(str(count) + '\r')
                if topn > 0 and count >= topn:
                    break
        matrix[0, :] = np.mean(matrix[1:, :])  # <unk> is mean of other vectors
    for w, i in vocab["w2i"].items():
        vocab["i2w"].append(w)
    return matrix, vocab, size, len(vocab["i2w"])


# vocab['i2w'], vocab['w2i']
read_words()
print(len(words_list))
matrix, vocab, size, length = load_dense_drop_repeat(vector_path, topn=0)
np.save(matrix_path, matrix)
with open(vocab_path, 'w', encoding='utf-8') as f:
    json.dump(vocab, f)
print(length)