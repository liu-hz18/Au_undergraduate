
from scrapy.exceptions import DropItem
import json

class MyPipeline(object):
    def __init__(self):
        # open a file
        self.file = open('team_data.json','w',encoding = 'utf-8')

    #handle the data    
    def process_item(self,item,spider):
        line = json.dumps(dict(item),ensure_ascii = False) + '\n'
        self.file.write(line)
        return item
    
    # executed when spider is on
    def open_spider(self, spider):
        pass
    
    # excuted when spider is off
    def close_spider(self,spider):
        pass
