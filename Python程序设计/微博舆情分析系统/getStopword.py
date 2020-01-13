
# 获取停用词
def readFile(filename):
	wordDict = {}
	#读取文件单词和词频
	with open(filename, 'r', encoding = 'utf-8') as f:
		for line in f.readlines():
			l = line.strip().split(' ')
			wordDict[l[0]] = l[1]
	#排序
	result = sorted(wordDict.items(), key = lambda wordDict:int(wordDict[1]), reverse = True)
	outputfile = "./stopword.txt"
	with open(outputfile, 'w+') as outf:
		for word in result:
			outf.write(word[0] + ' ' + word[1] + '\n')


def main():
	readFile("./BosonNLP_char_freq.txt")

if __name__ == '__main__':
	main()