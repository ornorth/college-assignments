#!/usr/bin/python3.7
#example usage of the pandas library
#read in 2 csv files, merge, and convert to a dictionary

import pandas

filmsFields = ['Year', 'Length', 'Title', 'Director']
filmsDF = pandas.read_csv('Films.csv', skipinitialspace=True, usecols=filmsFields, encoding='ISO-8859-1')

moviesFields = ['Year', 'Length', 'Title', 'budget', 'rating', 'Action' , 'Animation', 'Comedy', 'Drama', 'Documentary', 'Romance', 'Short']
moviesDF = pandas.read_csv('Movies.csv', skipinitialspace=True, usecols=moviesFields, encoding='ISO-8859-1')

mergeDF = moviesDF.merge(filmsDF, on=['Year', 'Length', 'Title'])
mergeDF = mergeDF.dropna(subset=['budget'])
mergeDF = mergeDF.reset_index(drop=True) #unnecessary, I'm keeping this here as a note to myself

mydict = mergeDF.set_index('Title').T.to_dict('list')

flag = True
while flag:
	title = input("Enter title: ")
	if title == "quit" or title == "Quit":
		flag = False
		print("Goodbye!")
	else:
		if title in mydict:
			print(mydict[title])
			print()
		else:
			print("Title not found\n")
