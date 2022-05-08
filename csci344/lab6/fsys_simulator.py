#!/usr/bin/python3.8
"""
File: 		fsys_simulator.py
Author: 	Owen North
Class:		CSCI 344
Date Created:	2/28/2022
Last Modified:	5/7/2022

Description:
	Contains a file system simulator using classes defined in 'fsystem.py'
	File metadata is stored but contents do not exist (system is only a superficial recreation)
	Contents of a filesystem do not persist between runs of the program
"""
from fsystem import Item, Directory, File

#"root" directory - represents filesystem as a whole
root = Directory()

#Use instead of quit() function to also print "Goodbye!"
def exit():
	print("Goodbye!")
	quit()

#Use instead of input() function to automatically terminate program if "quit" is entered
def user_input(prompt):
	x = input(prompt)
	if x == "quit":
		exit()
	else: return x

#Display the menu
def print_menu(flag):
	if flag:
		print("\n\nMain Menu:")
		print("1. Create a File")
		print("2. Create a Directory")
		print("3. Remove a File/Directory")
		print("4. Display File System")
		print("5. Exit\n")
	return False

"""
Iteratively searches the filesystem for a directory matching the user's request
Returns:
	Directory object if a matching path is found,
	None otherwise
"""
def find_dir(name, home):
	if name == "/":
		return root
	foundDir = None
	for curDir in home.dir:
		if isinstance(curDir, File):
			continue
		curName = curDir.parentDir.name + curDir.name
		if curName == name:
			return curDir
		foundDir = find_dir(name, curDir)
		if foundDir != None: break
	return foundDir

def main():
	#flag to determine whether to reprint the menu
	#only set to True when a command is executed
	printMenu = True

	while True:
		printMenu = print_menu(printMenu)
		cmd = user_input("Choice: ")

		#create file
		if (cmd == '1'):
			myFile = File()
			myFile.name = user_input("Please enter a file name or quit: ")

			#find parent directory
			myParent = None
			while myParent == None:
				myParent = find_dir(user_input("Please enter a parent directory or quit: "), root)
				#ERROR 1: directory not found
				if myParent == None:
					print("ERROR: Parent Directory Does not Exist")
				#ERROR 2: directory is root, object is a File
				elif myParent == root:
					print("ERROR: Files cannot be placed in home directory")
					myParent = None
				#ERROR 3: file name already taken
				#it is currently possible to softlock yourself by making a copy of a file in each directory and trying to make another
				#could fix by making "quit" return to menu instead of terminating the program
				#but that would require refactoring the code, which I don't want to do right now
				else:
					for x in myParent.dir:
						if x.name == myFile.name:
							print("ERROR: Directory already has file of the same name")
							myParent = None
							break
			myFile.parentDir = myParent

			myFile.permissions = user_input("Please enter access permissions using format rwx or quit: ")
			myFile.size = user_input("Please enter size (1-Small, 2-Medium, 3-Large): ")
			myParent.addFile(myFile)
			print(f"Created file: {myFile.parentDir.name}/{myFile.name}")
			printMenu = True

		#create directory
		elif (cmd == '2'):
			myDir = Directory()
			myDir.name = user_input("Please enter Directory name or quit: ")

			#find parent directory
			myParent = None
			while myParent == None:
				myParent = find_dir(user_input("Please enter a parent directory or quit: "), root)
				#ERROR 1: directory not found
				if myParent == None:
					print("ERROR: Parent Directory Does not Exist")
				#ERROR 2: file name already taken
				#it is currently possible to softlock yourself by making a copy of a file in each directory and trying to make another
				#could fix by making "quit" return to menu instead of terminating the program
				#but that would require refactoring the code, which I don't want to do right now
				else:
					for x in myParent.dir:
						if x.name == myDir.name:
							print("ERROR: Directory already has file of the same name")
							myParent = None
							break
			myDir.parentDir = myParent

			myDir.permissions = user_input("Please enter access permissions uging format rwx or quit: ")
			myParent.addFile(myDir)
			print(f"Created file: {myDir.parentDir.name}{myDir.name}")
			printMenu = True

		#delete file or directory
		elif (cmd == '3'):
			myFile = user_input("Please enter name of the file to delete or quit: ")
			#find directory specified
			myParent = None
			while myParent == None:
				myParent = find_dir(user_input("Please enter a parent directory or quit: "), root)
				if myParent == None:
					print("ERROR: Parent Directory Does not Exist")
			#attempt to delete given filename from found directory
			if myParent.delFile(myFile):
				print("File successfully deleted")
			#file not found, return to menu
			else:
				print(f"ERROR: File {myFile} not found in {myParent.name}")
			printMenu = True


		#print tree view of file system
		elif (cmd == '4'):
			root.display()
			printMenu = True

		#exit program
		elif (cmd == '5'):
			exit()


main()
