
import scrapy

class TeamItem(scrapy.Item):
    name = scrapy.Field() 
    createtime = scrapy.Field()
    member = scrapy.Field()
    city = scrapy.Field()
    coach = scrapy.Field()
    home = scrapy.Field() #host field
    introduc = scrapy.Field()