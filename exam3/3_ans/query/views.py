from django.shortcuts import render
import re


textlist = list()
timelist = list()
# Create your views here.
def myfunc(request):
    text = time = ""
    if request.GET.has_key('text'):
        text = request.GET['text']
    if request.GET.has_key('time'):
        time = request.GET['time']

    result = []

    if request.GET.has_key('add'):
        textlist.append(text)
        timelist.append(time)

    if request.GET.has_key('query'):
        for i in range(0, len(textlist)):
            ltext = textlist[i]
            ltime = timelist[i]
            if (ltext.find(text) != -1):
                result.append(ltext + ' ' + ltime)
            elif (ltime == time):
                result.append(ltext + ' ' + ltime)
            elif (len(text) == 0 and len(time) == 0):
                result.append(ltext + ' ' + ltime)

    if request.GET.has_key('reset'):
        pass

    if request.GET.has_key('delete'):
        deleteitem = request.GET['delete']
        split = deleteitem.split(' ')
        for i in range(0, len(textlist)):
            ltext = textlist[i]
            ltime = timelist[i]
            if (ltext == split[1]):
                del textlist[i]
                del timelist[i]
                break
            

    return render(request, 'index.html', {'text':text, 'time':time, 'result': result,})