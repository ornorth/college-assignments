#!/usr/bin/python3.5
"""
File: 			fsystem.py
Author: 		Owen North
Class:			CSCI 344
Date Created:	2/28/2022
Last Modified:	3/1/2022

Description:
	Contains a hierarchy of classes to simulate a basic file system
	Classes 'Directory' and 'File' inherit from 'Item'
		(all class variables are declared in constructor)
	Simulator contained at 'fsys_simulator.py'
"""


from datetime import datetime

"""
'Item' class - inherited by 'Directory' and 'File'
Contains basic information needed by both Files and Directories
"""
class Item:
	def __init__(self):
		self.name = ""		#name of the file
		self.parentDir = None	#directory housing the file - "/" represents root
		self.permissions = "rwx"#permissions for reading, modifying, and executing the file

	#overloaded '>' operator for use of sort()
	def __gt__(self, other):
		return (self.name > other.name)

"""
'Directory' class - inherits 'Item'
member variable 'updDate' is updated at object's creation and at addition/removal of contents
"""
class Directory(Item):
	def __init__(self):
		super().__init__()
		self.updDate = datetime.now().strftime("%H:%M:%S")	#time of latest modification
		self.dir = [ ]						#list of File and Directory objects contained here

	#add file or directory to object's list
	#resort list and update modification time
	def addFile(self, x):
		self.dir.append(x)
		self.dir.sort()
		self.updDate = datetime.now().strftime("%H:%M:%S")

	#delete file from object's list
	def delFile(self, x):
		for file in self.dir:
			if file.name == x:
				self.dir.remove(file)
		return True

	"""
	semi-complex print function. Prints file system in tree formation
	Assumptions:
		- list 'dir' contains only File and Directory objects
		- 'permissions' member variable is a string of length 3
		- 'updDate' value is in the format 'XX:XX:XX'
	Output is unpredictable if these assumptions are not met
	Added features:
		- permissions for Files and Directories are printed at beginning of each line
		- updDate is printed after permissions for directories only
		- contents of a directory are indented relative to that directory
		- '*' is appended to the name of Files that are executable
	"""
	def display(self, nest=0):
		basePrepend = ""
		for i in range(nest):
			basePrepend += "  "
		for x in self.dir:
			append = ""
			prepend = basePrepend
			isDir = isinstance(x, Directory)
			if isDir:
				prepend = f"{x.updDate}{prepend}"
			else:
				prepend = f"        {prepend}"
			if 'x' in x.permissions and not isDir:
				append = "*"
			print(f"{x.permissions}: {prepend}  {x.name}{append}")
			if isDir:
				x.display(nest+1)

"""
'File' class - inherits 'Item'
Very simple conpared to 'Directory'
Member variable 'size' is set but never used
"""
class File(Item):
	def __init__(self):
		super().__init__()
		self.size = "1"
