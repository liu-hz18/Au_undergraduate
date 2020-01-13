
from django.urls import path,re_path
from . import views

urlpatterns = [
    # re_path(r'^search',views.search,name = "search")
    path('search',views.search,name = "search"),
    path('home',views.home,name  = "home"),
]
