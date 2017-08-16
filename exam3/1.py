import re
import sys
import os

def GetFileList1(dir, fileList, size):
	newDir = dir
	if os.path.isfile(dir):
		if os.path.getsize(dir) > size:
			fileList.append(dir.decode('utf-8'))
	elif os.path.isdir(dir):
		for s in os.listdir(dir):
			newDir = os.path.join(dir, s)
			GetFileList1(newDir, fileList, size)
		return fileList

def GetFileList2(dir, fileList, type):
	newDir = dir
	if os.path.isfile(dir):
		if (dir.split('.')[-1] == type):
			fileList.append(dir.decode('utf-8'))
	elif os.path.isdir(dir):
		for s in os.listdir(dir):
			newDir = os.path.join(dir, s)
			GetFileList2(newDir, fileList, type)
		return fileList

def GetFileList3(dir, fileList, key):
	newDir = dir
	if os.path.isfile(dir):
		flag = 1
		fileopen = open(dir, 'r')
		data = fileopen.read()
		splitkey = key.split(' ')
		for item in splitkey:
			if (data.find(item) == -1):
				flag = 0
				break;
		if (flag == 1):
			fileList.append(dir.decode('utf-8'))
	elif os.path.isdir(dir):
		for s in os.listdir(dir):
			newDir = os.path.join(dir, s)
			GetFileList3(newDir, fileList, key)
		return fileList

print 'arguments = ', sys.argv

if (len(sys.argv) >= 4):
	if (sys.argv[1] == 'size'):
		size = int(sys.argv[3])
		list = GetFileList1('/Users/yuhui/Desktop/exam3/1', [], size)
		print list
	elif (sys.argv[1] == 'file'):
		type = sys.argv[3]
		list = GetFileList2('/Users/yuhui/Desktop/exam3/1', [], type)
		print list
	elif (sys.argv[1] == 'key'):
		key = sys.argv[3]
		list = GetFileList3('/Users/yuhui/Desktop/exam3/1', [], key)
		print list


