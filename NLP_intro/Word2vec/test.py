
# 测试脚本
from word2vec import Word2Vec
from gensim.test.utils import datapath
from gensim.models import KeyedVectors

# 准确度较高的参数设置
# size = 300, window = 6, min_count = 6, iternum = 20, threads = 12, negative = 5
# hs = 0, sample = 1e-3, cbow

# 训练
wordvec = Word2Vec(
    train_file='./test.txt',
    output_file='./output.txt',
    vocab_file='./vocab.txt',
    size=300,
    window=6,
    min_count=6,
    negative=5,
    iternum=5,
    threads=12
    )
wordvec.train()

#准确率测试
# 读取词向量文件
wv = KeyedVectors.load_word2vec_format('./output.txt', binary=False)

# 测试词类比准确率
with open('./result.txt', 'w', encoding='utf-8') as f:
    re = wv.evaluate_word_analogies(datapath('./questions-words.txt'))
    print(re[0])
    f.write(str(re).lower())

# 测试词相似度准确率
with open('./simlilarity-result.txt', 'w', encoding='utf-8') as f:
    sim_acc = wv.evaluate_word_pairs(datapath('./wordsim-353.txt'))
    re = sim_acc[1].correlation
    f.write(str(re) + '\n' + str(sim_acc))

# 一些其他测试
'''
print(wv.most_similar("play"))
print(wv.most_similar(positive=['woman', 'king'], negative=['man']))
print(wv.most_similar_cosmul(positive=['woman', 'king'], negative=['man']))
print(wv.similarity('woman', 'man'))
'''
