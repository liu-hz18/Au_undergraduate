#-*-coding:utf-8-*-#
from django.shortcuts import render
from django.http import HttpResponse
from django.core.paginator import Paginator,PageNotAnInteger,EmptyPage,InvalidPage
import re
import json
import time
import jieba
import html
import math
from .models import News,Team

inverted_index_dict = {}
news_dict_list = []
team_list = []
team_keyword_list = []
haveload = False

# Create your views here.
def home(request):
        global haveload
        if haveload  == False:
                invert_index()
                readteam()
                getTeamNews()
                getTeamKeyword()
                haveload = True
        return render(request,"home.html")

# invert index
def invert_index():
        news_file_path = '/home/liuhongzun/tutorial/news_data.json'
        global inverted_index_dict
        temp_inverted_index_dict = {}
        with open(news_file_path,'r',encoding = 'utf-8') as f:
                line  = f.readline()
                while line:          
                        news_dict = dict(json.loads(line))
                        news_dict_list.append(news_dict)
                        title = news_dict['title']
                        content = news_dict['content']
                        templist = jieba.lcut_for_search(title) + jieba.lcut_for_search(content)
                        for word in templist:
                                if word not in temp_inverted_index_dict:
                                        temp_inverted_index_dict[word] = set()
                                temp_inverted_index_dict[word].add(news_dict['index']) # save as the index in each news
                        line  = f.readline()
        
        for key,value in temp_inverted_index_dict.items():
                inverted_index_dict[key] = tuple(value)

# search result
def search(request):
        global inverted_index_dict
        global news_dict_list
        news_file_path = '/home/liuhongzun/tutorial/news_data.json'
        temp = request.GET.get("url_text").split('?')
        searchword = temp[0].replace('+','')
        
        if len(temp) == 1:
                page = 1
        else: 
                page = re.findall(r'\b\d+\b',temp[1])[0]
        # searchword = url_text
        wordlist = jieba.lcut_for_search(searchword)
        keywordlist = jieba.lcut(searchword)

        news_list = []
        news_index_list = []
        for word in wordlist:
                if word in inverted_index_dict.keys():
                        news_index_list.extend(list(inverted_index_dict[word]))
        news_index_list = list(set(news_index_list))
        
        # find news
        find_count  = len(news_index_list) # find pages count
        begintime = time.time()
        for news in news_dict_list:
                if news['index'] in news_index_list:
                        a_news = News()
                        a_news.body = news['content']
                        if len(a_news.body) > 250 : 
                                a_news.body = a_news.body[0:250] + "......"
                        a_news.title = news['title']
                        a_news.index = news['index']
                        news_list.append(a_news)
        endtime =  time.time()
        tottime = (endtime - begintime)  #search time used
        if find_count == 0: 
                tottime = .0
        
        # tf - idf
        tf_idf = [] # size is n
        doc_num = len(news_list)
        idf = [] # size is k
        # get idf
        for word in wordlist:
                count  = 0
                for news in news_list:
                        if word in news.body:
                                count += 1
                if count == 0:
                        count = 1
                count = math.log(len(news_list) / count)
                idf.append(count)
        # get tf
        tf = []
        for news in news_list:
                temp_doc_word_list = jieba.lcut_for_search(news.body)
                word_in_doc = [] 
                for word in wordlist:
                        temp = temp_doc_word_list.count(word) / len(temp_doc_word_list)
                        word_in_doc.append(temp)
                tf.append(word_in_doc)
        # get tf-idf
        for i in range(0,len(news_list)):
                temp = 0
                for k in range(0,len(wordlist)):
                        temp += tf[i][k] * idf [k]
                tf_idf.append(temp)
        # sort the docs
        doc_tf_idf_dict = zip(news_list,tf_idf)
        doc_tf_idf_dict = sorted(doc_tf_idf_dict,key = lambda x:x[1],reverse=True )
        news_list = [item[0] for item in doc_tf_idf_dict]

        # divide page
        paginator = Paginator(news_list, 10)
        if request.method == "GET":
                try:
                        news_s = paginator.page(page)
                # if not an integer num,return to page 1
                except PageNotAnInteger:
                        news_s = paginator.page(1)
                except InvalidPage:
                        return HttpResponse("Page not Found!")
                # if not in the range of pages,return the last page
                except EmptyPage:
                        news_s = paginator.page(paginator.num_pages)

        print(searchword)
        print(wordlist)
        return render(request,'search.html',{'post_list':news_s,'num':find_count,'time':tottime,'te':searchword,'keywl':keywordlist,})

#page of detailed news
def newspage(request,ind):
        global team_keyword_list
        for news in news_dict_list:
                if int(ind) == news['index']:
                        temp_news_content = news['content']
                        news_title = news['title']
                        news_time = news['date']
                        news_src = news['source']
                        contentword = jieba.lcut(temp_news_content)
                        news_content = ''
                        # print(contentword)
                        for word in contentword:
                                index = 0
                                for keywordlist in team_keyword_list:
                                        index += 1
                                        for keyword in keywordlist:
                                                print(keyword)
                                                print(word)
                                                if keyword == word:
                                                        print("replace one")
                                                        # havn't finished yet!!!
                                                        word = '<a class=\"active\" href=\"/team/' + str(index)  + '/1\"  '+  'target=\"_blank\">' + word + '</a>'
                                                        word = html.unescape(word)
                                                        break
                                news_content += word
                       #  print(news_content)
                        return render(request,'newspage.html',{'title':news_title,'source':news_src,'date':news_time,'para':news_content})
        return render(request,'newspage.html',{'title':"Page not Found!"})

# get news for each team
def getTeamNews():
        global inverted_index_dict
        global team_list
        for team in team_list:
                name = team['name'].split('（')[0] # get the chinese name of a team
                wordlist = jieba.lcut_for_search(name)
                for word in wordlist:
                        if word in inverted_index_dict.keys():
                                team['newslist'].extend(inverted_index_dict[word])
                team['newslist'] = list(set(team['newslist'])) # save the index list of news
                team['newsnum'] = len(team['newslist'])

#read team info(dict) into a list
def readteam():
        global team_list
        path = '/home/liuhongzun/teamspider/team_data.json'
        with open(path,'r',encoding = 'utf-8') as f:
                line = f.readline()
                while line:
                        news_dict = dict(json.loads(line))
                        team_list.append(news_dict)
                        line = f.readline()

# get key word for each team,the index is consistent with index in team_list
def getTeamKeyword():
        global team_keyword_list
        for team in team_list:
                tempwordlist = []
                tempwordlist.extend(jieba.lcut_for_search(team['name']))
                for member in team['member']:
                        tempwordlist.extend(jieba.lcut_for_search(member))
                tempwordlist = list(set(tempwordlist))
                wordlist = []
                for index in range(0,len(tempwordlist)):
                        if len(tempwordlist[index]) >= 2:
                                wordlist.append(tempwordlist[index])
                team_keyword_list.append(wordlist)
        # print(team_keyword_list)

# hostpage of teams
def teampage(request,id,page = 1):
        global team_list
        _id  = int(id) - 1
        teamname = team_list[_id]['name']
        createtime = team_list[_id]['createtime']
        coach = team_list[_id]['coach']
        city = team_list[_id]['city']
        home = team_list[_id]['home']
        intro = team_list[_id]['introduc']
        memberlist = team_list[_id]['member']
        newslist = []
        for news in news_dict_list:
                if news['index'] in team_list[_id]['newslist']:
                        a_news = News()
                        a_news.title = news['title']
                        a_news.body = news['content']
                        if len(a_news.body) > 200 : 
                                a_news.body = a_news.body[0:150] + "......"
                        a_news.index = news['index']
                        newslist.append(a_news)

        # divide page
        paginator = Paginator(newslist, 5)
        if request.method == "GET":
                try:
                        news_s = paginator.page(page)
                # if not an integer num,return to page 1
                except PageNotAnInteger:
                        news_s = paginator.page(1)
                except InvalidPage:
                        return HttpResponse("Page not Found!")
                # if not in the range of pages,return the last page
                except EmptyPage:
                        news_s = paginator.page(paginator.num_pages)

        return render(request,'teamhome.html',{'teamname':teamname,'createtime':createtime,'coach':coach,'city':city,'home':home,'intro':intro,'memberlist':memberlist,'newslist':news_s,'id':id})

# hot list of teams
def hottable(request):
        teamLi = []
        size = len(team_list)
        for temp in team_list:
                team = Team()
                team.index = temp['index']
                team.name = temp['name']
                team.newsnum = int(temp['newsnum'])
                teamLi.append(team)
        teamLi = sorted(teamLi,key = lambda x:x.newsnum,reverse=True)
        for i in range(0,size):
                teamLi[i].rank = i + 1
        return render(request,'hotlist.html',{'teamlist':teamLi})
