# -*- coding: UTF-8 -*-#

import scrapy
import json
from  teamspider.teamItems import TeamItem

class TeamSpider(scrapy.Spider):
    name = "teams"
    start_urls = [ 'https://nba.hupu.com/teams/', ]
	
    def parse(self,response):
	    for a_link in response.xpath('//div[@class = "all"]//a[@class = "a_teamlink"]/@href').extract():
		    yield scrapy.Request(url = a_link, callback = self.parse_team)

    def parse_team(self,response):
        templist = response.xpath('//div[@class = "font"]//p/text()').extract()
        name = response.xpath('//span[@class ="title-text"]/text()').extract()[0]
        createtime = templist[0].split('：')[-1]
        temp_memberlist = response.xpath('//div[@class = "x_list"]//a[@target = "_blank"]/text()').extract()
        memberlist  = [member.strip('\n') for member in temp_memberlist]
        
        temp = templist[1].split('：')
        city = temp[2]
        home = temp[1][0:-5]
        coach = templist[3].split('：')[-1]
        
        introduc = response.xpath('//div[@class = "txt"]/text()').extract()[0].strip('\n')
        if name and createtime and memberlist and city and coach and home and introduc:
            item = TeamItem()
            item['name'] = name
            item['createtime'] = createtime
            item['member'] = memberlist
            item['city'] = city
            item['coach'] = coach
            item['home'] = home
            item['introduc'] = introduc
            yield item
