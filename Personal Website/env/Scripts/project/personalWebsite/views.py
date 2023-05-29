from django.shortcuts import render

# Create your views here.

from django.shortcuts import render
  
def home(request):
    return render(request, "home.html")
  
def wordle(request):
    return render(request, "wordle.html")
  
def contact(request):
    return render(request, "contact.html")

def propfinder(request):
	return render(request, "propfinder.html")