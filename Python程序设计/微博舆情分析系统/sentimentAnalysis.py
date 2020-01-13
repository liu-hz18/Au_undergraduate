
from snownlp import SnowNLP
from snownlp import sentiment
from wordcloud import WordCloud
from collections import Counter
import re
import imageio
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
import pylab
import jieba.analyse

#上载停用词
def loadStopWords(filename):
	stopwords = [line.strip() for line in open(filename, 'r').readlines()]
	return stopwords

#得到分词结果
def getKeyWordsList(text, stopwords):
	words = jieba.cut(text.strip(), cut_all = False, HMM = True)
	result = []
	for word in words:
		if word not in stopwords:
			if word != '\n' and word != ' ':
				result.append(word)
	return result

#得到分词结果
def getKeyWordsList_forSearch(text, stopwords):
	words = jieba.cut_for_search(text.strip(), HMM = True)
	result = []
	for word in words:
		if word not in stopwords:
			if word != '\n' and word != ' ':
				result.append(word)
	#result = list(set(result))
	return result

#统计词频
def getWordCount(wordlist):
	wordCount = Counter(wordlist)
	return wordCount

#得到词频统计图形，默认为柱形图('bar')其他:折线图('plot'),饼图('pie')
def createBarChart(wordCount, piclass = 'bar', number = 15):
	x = [x[0] for x in wordCount.most_common(number)]
	y = [x[1] for x in wordCount.most_common(number)]
	font_set = FontProperties(fname = r'C:/Windows/WinSxS/amd64_microsoft-windows-font-truetype-simfang_31bf3856ad364e35_10.0.18362.1_none_5a7f93f39ed619f0/simfang.ttf', size=12)
	plt.rcParams['font.sans-serif'] = ['Fangsong']
	plt.rcParams['savefig.dpi'] = 300 #图片像素
	plt.rcParams['figure.dpi'] = 300 #分辨率
	fig = plt.figure()
	plt.title('微博文本词频统计')
	if piclass == 'bar':
		plt.bar(x, y, color = 'red')
		plt.xticks(x, x, rotation = 36)
		plt.xlabel('单词', FontProperties = font_set)
		plt.ylabel('词频', FontProperties = font_set)
		plt.savefig('./WordBarChart.png')
	elif piclass == 'plot':
		plt.grid(linestyle='-.')
		plt.plot(x, y, color = 'red')
		plt.xticks(x, x, rotation = 36)
		plt.xlabel('单词', FontProperties = font_set)
		plt.ylabel('词频', FontProperties = font_set)
		plt.savefig('./WordPlotChart.png')
	elif piclass == 'pie':
		explode = [0 for i in range(number)]
		explode[0] = 0.1 #最大的数据分离出来
		if number > 1:
			explode[1] = 0.05
		if number > 2:
			explode[2] = 0.03
		plt.pie(y, labels = x, explode = explode , shadow = False, autopct='%1.1f%%', startangle = 150)
		plt.savefig('./WordPieChart.png')


#关键词抽取,基于tf-idf
def getKeyWords_TFIDF(text):
	result = jieba.analyse.extract_tags(text, topK = 25, withWeight = False, allowPOS = ())
	stopwords = loadStopWords('./stopword.txt')
	final = []
	for word in result:
		if word not in stopwords:
			if word != '\n' and word != ' ':
				final.append(word)
	return " ".join(final[0:25])
	

#关键词抽取，基于textrank算法,效果更好一点
def getKeyWords_textrank(text):
	#认为名词比动词更能体现特征，所以名词取20个，动词取2个
	result = jieba.analyse.textrank(text, topK = 20, withWeight = False, allowPOS = ('n', 'ns', 'nr'))
	result += jieba.analyse.textrank(text, topK = 5, withWeight = False, allowPOS = ('v'))
	stopwords = loadStopWords('./stopword.txt')
	final = []
	for word in result:
		if word not in stopwords:
			if word != '\n' and word != ' ':
				final.append(word)
	#print(final)
	return " ".join(final[0:25])


#预训练 情感分析模型
def trainSentimentModel(positivefile, negativefile):
	sentiment.train(negativefile, positivefile)
	sentiment.save('./sentiment.marshal')


#情感分析
def sentimentAnalysis(text):
	s = SnowNLP(text)
	score = 0.0
	count = 0
	for sentence in s.sentences:
		score += SnowNLP(sentence).sentiments
		count += 1
	score /= count
	if score < 0.45:
		return 'negative'
	elif score > 0.55:
		return 'positive'
	else:
		return 'neutral'


#生成词云
def createWordCloud(text, maskfile = None):
	if maskfile:
		mask = imageio.imread(maskfile)
	#fontpath参数是字体路径，需要自己在C:/Windows文件夹下找对应的字体文件。注意更改路径
	#scale参数是清晰度，越大越清晰，但是会拖慢速度
	w = WordCloud(
		background_color = 'white', 
		margin = 2, 
		mask = mask, 
		scale = 4, 
		font_path = 'C:/Windows/WinSxS/amd64_microsoft-windows-font-truetype-simfang_31bf3856ad364e35_10.0.18362.1_none_5a7f93f39ed619f0/simfang.ttf', 
		max_words = 250, 
		max_font_size = 100
	)
	cloud = w.generate(text)
	w.to_file('./wordcloud.png')#保存到文件
	#注释部分是在线显示
	#plt.imshow(cloud, interpolation = 'bilinear')
	#plt.axis('off')#不显示坐标轴
	#pylab.show()#显示图片


#读取文件
def loadFile(filename):
	text = ''
	with open(filename, 'r', encoding = 'utf-8') as f:
		text = f.read()
	#移除网址等干扰信息
	text = re.sub(r'(https|http)?:\/\/(\w|\.|\/|\?|\=|\&|\%)*\b', '', text, flags=re.MULTILINE)
	return text

#获取关键词
def getKeyWords(filename):
	keywordlist1 = getKeyWords_TFIDF(loadFile(filename)).split(' ')
	keywordlist2 = getKeyWords_textrank(loadFile(filename)).split(' ')
	result = []
	for word in keywordlist1:
		if word in keywordlist2:
			result.append(word)
	if len(result) < 2:
		return " ".join(keywordlist1[0:5])
	return " ".join(result)


def createCloud(filename, maskname):
	text = " ".join(getKeyWordsList_forSearch(loadFile(filename), loadStopWords('./stopword.txt')))
	#print(text)
	createWordCloud(text, maskfile = maskname)#必须为白底照片，不能是透明底


if __name__ == '__main__':
	text = '资生堂很棒，但我还是喜欢兰蔻'
	#trainSentimentModel('./pos.txt', './neg.txt')
	print(sentimentAnalysis(text))
	createCloud('./text.txt', './mask7.png')
	print(getKeyWords('./text.txt'))
	wordlist = getKeyWordsList(loadFile('./text.txt'), loadStopWords('./stopword.txt'))
	createBarChart( getWordCount(wordlist), piclass = 'pie') 




#几个模块
#分词,生成三种统计图，生成词云图，情感分析，关键词抽取