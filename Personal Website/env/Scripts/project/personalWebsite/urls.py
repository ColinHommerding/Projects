from django.urls import path
from . import views
  
urlpatterns = [
    path("", views.home, name="home"),
    path("wordle/", views.wordle, name="wordle"),
    path("contact/", views.contact, name="contact"),
    path("propfinder/", views.propfinder, name="propfinder"),
]