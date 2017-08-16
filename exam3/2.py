 # -*- coding: utf-8 -*-   
from pdfminer.pdfparser import PDFParser
from pdfminer.pdfdocument import PDFDocument
from pdfminer.pdfpage import PDFPage
from pdfminer.pdfpage import PDFTextExtractionNotAllowed
from pdfminer.pdfinterp import PDFResourceManager
from pdfminer.pdfinterp import PDFPageInterpreter
from pdfminer.pdfdevice import PDFDevice
from pdfminer.layout import *
from pdfminer.converter import PDFPageAggregator
import os
os.chdir(r'/Users/yuhui/Desktop/exam3/2')
fp = open('area.pdf', 'rb')
#来创建一个pdf文档分析器
parser = PDFParser(fp)  
#创建一个PDF文档对象存储文档结构
document = PDFDocument(parser)
# 检查文件是否允许文本提取
if not document.is_extractable:
    raise PDFTextExtractionNotAllowed
else:
    # 创建一个PDF资源管理器对象来存储共赏资源
    rsrcmgr=PDFResourceManager()
    # 设定参数进行分析
    laparams=LAParams()
    # 创建一个PDF设备对象
    # device=PDFDevice(rsrcmgr)
    device=PDFPageAggregator(rsrcmgr,laparams=laparams)
    # 创建一个PDF解释器对象
    interpreter=PDFPageInterpreter(rsrcmgr,device)
    # 处理每一页
    for page in PDFPage.create_pages(document):
        interpreter.process_page(page)
        # 接受该页面的LTPage对象
        layout=device.get_result()
        for y in layout:
            
            if(isinstance(y,LTTextBoxHorizontal)):
                with open('a.txt','a') as f:
                    f.write(y.get_text().encode('utf-8')+'\n')


fp = open('a.txt', 'rb')
data = fp.read().decode('utf-8')
import xlwt
import re
#创建workbook和sheet对象
workbook = xlwt.Workbook() #注意Workbook的开头W要大写
sheet1 = workbook.add_sheet('sheet1',cell_overwrite_ok=True)
#向sheet页中写入数据
sheet1.write(0,0,'Rank')
sheet1.write(0,1,'Sovereign state/dependency')
sheet1.write(0,2,'Total in km2 (mi2)')
sheet1.write(0,3,'Land in km2 (mi2)')
pattern1 = re.compile('\d+ .*')
items = re.findall(pattern1, data)

print items
for i in range(0, len(items)-1):
    splitline = items[i].split(' ', 1)
    sheet1.write(i+1,0,splitline[0])
    sheet1.write(i+1,1,splitline[1])

pattern2 = re.compile('\d+,.+ ')
items2 = re.findall(pattern2, data)
print items2

for i in range(0, len(items)-1):
    sheet1.write(i+1,2,items2[i])

for i in range(len(items), 2*len(items)-1):
    sheet1.write(i-len(items)+1,3,items2[i])



# sheet1.write(0,0,'this should overwrite1')
# sheet1.write(0,1,'aaaaaaaaaaaa')
# sheet2.write(1,0,'this should overwrite2')
# sheet2.write(1,2,'bbbbbbbbbbbbb')

#保存该excel文件,有同名文件时直接覆盖
workbook.save('2.xls')
print '创建excel文件完成！'




