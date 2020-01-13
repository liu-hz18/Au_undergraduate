
from wordcloud import WordCloud
from collections import Counter
import re
import imageio
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
import jieba.analyse

#词频分析
class TextStaticAnalysis(object):
	"""docstring for TextStaticAnalysis"""

	def __init__(self, textfilename, stopwordfile, maskfile, userdict):
		super(TextStaticAnalysis, self).__init__()
		self.textfilename = textfilename
		self.stopwordfile = stopwordfile
		self.maskfile = maskfile
		self.stopwords = []
		self.wordlist = []
		self.wordcount = {}
		self.text = ''
		jieba.load_userdict(userdict)

	#读取文件
	def loadFile(self):
		text = ''
		with open(self.textfilename, 'r', encoding = 'utf-8') as f:
			text = f.read()
		#移除网址等干扰信息
		self.text = re.sub(r'(https|http)?:\/\/(\w|\.|\/|\?|\=|\&|\%)*\b', '', text, flags=re.MULTILINE)
		return self.text


	#上载停用词
	def loadStopWords(self):
		stopwords = [line.strip() for line in open(self.stopwordfile, 'r').readlines()]
		self.stopwords = stopwords
		return stopwords


	#统计词频,返回词典
	def getWordCount(self):
		wordCount = Counter(self.wordlist)
		self.wordCount = wordCount
		return wordCount


	#得到分词结果
	def getKeyWordsList(self):
		self.loadStopWords()
		words = jieba.cut(self.loadFile().strip(), cut_all = False, HMM = True)
		for word in words:
			if word not in self.stopwords:
				if word != '\n' and word != ' ' and len(word) > 1:
					self.wordlist.append(word)
		return self.wordlist


	#得到分词结果
	def getKeyWordsList_forSearch(self):
		self.loadStopWords()
		self.loadFile()
		words = jieba.cut_for_search(self.text.strip(), HMM = True)
		result = []
		for word in words:
			if word not in self.stopwords:
				if word != '\n' and word != ' ':
					result.append(word)
		return result

		#生成词云
	def createWordCloud(self):
		if self.maskfile:
			mask = imageio.imread(self.maskfile)
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
		cloud = w.generate(self.text)
		w.to_file('./wordcloud.png')#保存到文件
		#注释部分是在线显示
		#plt.imshow(cloud, interpolation = 'bilinear')
		#plt.axis('off')#不显示坐标轴
		#pylab.show()#显示图片


	def createCloud(self):
		self.text = " ".join(self.getKeyWordsList())
		self.createWordCloud()#必须为白底照片，不能是透明底

	
	#得到词频统计图形，默认为柱形图('bar')其他:折线图('plot'),饼图('pie')
	def createChart(self, piclass = 'bar', number = 15):
		self.getKeyWordsList()
		self.getWordCount()
		x = [x[0] for x in self.wordCount.most_common(number)]
		y = [x[1] for x in self.wordCount.most_common(number)]
		font_set = FontProperties(fname = r'C:/Windows/WinSxS/amd64_microsoft-windows-font-truetype-simfang_31bf3856ad364e35_10.0.18362.1_none_5a7f93f39ed619f0/simfang.ttf', size=12)
		plt.rcParams['font.sans-serif'] = ['Fangsong']
		plt.rcParams['savefig.dpi'] = 300 #图片像素
		plt.rcParams['figure.dpi'] = 300 #分辨率
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


if __name__ == '__main__':
	textname = './text.txt'
	stopname = './stopword.txt'
	maskfile = './mask7.png'
	s = TextStaticAnalysis(textname, stopname, maskfile)
	#外部接口
	#生成词云
	s.createCloud()
	#生成统计表，参数选择:bar, plot, pie
	s.createChart(piclass = 'bar')

