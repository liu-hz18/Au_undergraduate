
import re
import difflib

#数据清洗
def cleanData(filename, outputfile):
	newline = []
	with open(filename, 'r', encoding = 'utf-8') as f:
		lines = f.readlines()
		for line in lines:
			line = line[72:-11].replace('@', '').replace('#', '').replace(u'【', '').replace(u'】', '').replace(u'-', '').replace(u'—', '').replace('...','').replace('  ',' ').replace('  ',' ').strip()
			line = re.sub(r'(https|http)?:\/\/(\w|\.|\/|\?|\=|\&|\%)*\b', '', line, flags = re.MULTILINE)
			if line not in newline:
				newline.append(line)
	with open(outputfile, 'w', encoding = 'utf-8') as f:
		count = 0
		newline = sorted(newline)
		lastline = ''
		for line in newline:
			if difflib.SequenceMatcher(None, line, lastline).ratio() < 0.700 or line in lastline:
				count += 1
				f.write(str(count) + '. ' +  line + '\n')
				lastline = line


if __name__ == '__main__':
	cleanData('./假疫苗_blog.txt', './yimiao.txt')
	cleanData('./#提发际线修鬓角清单近4万#_blog.txt', './fajixian.txt')
	cleanData('./转基因_blog.txt', './jiyin.txt')
