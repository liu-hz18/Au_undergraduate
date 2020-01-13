# -*- coding: UTF-8 -*-

import scrapy
import json
from tutorial.newsItem import NewsItem

count = 0
pages = 0

class QuotesSpider(scrapy.Spider):
	name = "quotes"
	start_urls = [ 'https://voice.hupu.com/nba/', ]
	

	def parse(self,response):
		global pages
		for block in response.xpath('//div[contains(@class, "news-list")]//li'):
			href = block.xpath('.//div[contains(@class,"list-hd")]//h4//a/@href').extract_first()
			# parse the content
			yield scrapy.Request(url = href, callback = self.parse_content)
		# parse next page
		page_next = response.xpath('//a[contains(text(),"下一页")]/@href').extract()
		if(page_next and pages < 65):
			pages += 1
			page = 'https://voice.hupu.com' + page_next[0]
			# print(page)
			yield scrapy.Request(page,callback = self.parse)

	def  parse_content(self,response):
		global count
		for body in response.xpath('//div[contains(@class,"voice-main")]'):
			# all items are strings
			title = body.xpath('//h1[@class="headline"]/text()').extract()[0].replace('\r\n','').strip(' ')
			content = body.xpath('//div[@class = "artical-main-content"]//p/text()').extract()
			content = ''.join(content)
			source = body.xpath('//span[@id = "source_baidu"]//a/text()').extract()[0]
			url = body.xpath('//span[@id = "source_baidu"]//a/@href').extract()[0]
			date = body.xpath('//span[@id = "pubtime_baidu"]/text()').extract()[0].strip(' ')
			if title and content and source and date and count < 4000:			
				item = NewsItem()
				count += 1
				item['index'] = count
				item['title'] = title
				item['source'] = source
				item['url'] = url
				item['date'] = date
				item['content' ]  = content
				yield item