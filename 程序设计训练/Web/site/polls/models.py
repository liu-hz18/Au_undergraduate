
from django.db import models

# Create your models here.
class News(models.Model):
    # title
    title = models.CharField(max_length = 70)
    #body
    body = models.TextField()
    #index
    index = models.IntegerField()

class Team(models.Model):
    # rank
    rank = models.IntegerField()
    #name
    name = models.CharField(max_length  = 70)
    #newsnum
    newsnum = models.IntegerField()
    #index 
    index = models.IntegerField()