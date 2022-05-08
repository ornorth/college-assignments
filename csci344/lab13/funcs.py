#!/usr/bin/python3.7
import csv

def help():
	print("###########################################---LAB 13---###########################################")
	print("NAME")
	print("   lab13\n")
	print("USAGE: ./lab13 --[TYPE] --day [#|#-#] [OPTIONS] [FILE]\n")
	print("DESCRIPTION")
	print("   parses an HTTP log file with form [HOST] - - [TIMESTAMP] [REQUEST] [HTTP REPLY CODE] [BYTES]")
	print("   displays a sorted count of all entries that match the given specifications\n")
	print("--resources:")
	print("   counts how many times each resource has been requested")
	print("   output is in form [COUNT]: [RESOURCE]\n")
	print("--requesters:")
	print("   counts how many times each source IP has requested a resource")
	print("   output is in the form [COUNT]: [HOSTNAME]\n")
	print("--errors:")
	print("   same as '--resources' except it only counts those with HTTP status codes starting with 4 or 5")
	print("   output is in the form [COUNT]: [RESOURCE]\n")
	print("--hourly:")
	print("   filters and counts the requests by hour")
	print("   output is in the form [COUNT]: [HOUR]\n")
	print("--day [DAYS] is a REQUIRED argument")
	print("      [DAYS] is of the form [INT] or [INT-INT] such that 0 < [INT] < 29")
	print("      filters results by specified day or days\n")
	print(" --number [NUMBER] is an OPTIONAL argument")
	print("   limit output to the top [NUMBER] entries - must be an integer > 0\n")
	print("the last input must be the HTTP log file")
	print("##################################################################################################")

def resources(log_file, days, number=0):
	print("RESOURCES")
	items = {}
	#open log file
	with open(log_file, newline='', encoding='utf8', errors='ignore') as file:
		csvFile = csv.reader(file, delimiter=' ')
		for lines in csvFile:
			if len(lines) == 8:
				#count all resources within the range of days
				day = int(lines[3][1])*10 + int(lines[3][2])
				if (lines[5] in items) and (day in days):
					items[lines[5]] += 1
				else:
					items[lines[5]] = 1
	#convert dictionary to a sorted list
	objs = []
	for key in items:
		i = 0
		while (i < len(objs)) and (items[key] < objs[i][0]): i += 1
		objs.insert(i, [items[key], key])
	#print list - if number was specified, limit output to <number>
	if number == 0: number = len(objs)
	for i in range(number):
		print(f'{objs[i][0]}: {objs[i][1]}')

def requesters(log_file, days, number=0):
	print("REQUESTERS")
	items = {}
	#open log file
	with open(log_file, newline='', encoding='utf8', errors='ignore') as file:
		csvFile = csv.reader(file, delimiter=' ')
		for lines in csvFile:
			if len(lines) == 8:
				#count all unique requesters within the range of days
				day = int(lines[3][1])*10 + int(lines[3][2])
				if (lines[0] in items) and (day in days):
					items[lines[0]] += 1
				else:
					items[lines[0]] = 1
	#convert dictionary to a sorted list
	objs = []
	for key in items:
		i = 0
		while (i < len(objs)) and (items[key] < objs[i][0]): i += 1
		objs.insert(i, [items[key], key])
	#print list - if number was specified, limit output to <number>
	if number == 0: number = len(objs)
	for i in range(number):
		print(f'{objs[i][0]}: {objs[i][1]}')

def errors(log_file, days, number=0):
	print("ERRORS")
	items = {}
	#open log file
	with open(log_file, newline='', encoding='utf8', errors='ignore') as file:
		csvFile = csv.reader(file, delimiter=' ')
		for lines in csvFile:
			if len(lines) == 8:
				#count all unique requesters that return errors within the range of days
				day = int(lines[3][1])*10 + int(lines[3][2])
				if (lines[6].find('4') == 0 or lines[6].find('5') == 0) and (lines[5] in items) and (day in days):
					items[lines[5]] += 1
				else:
					items[lines[5]] = 1
	#convert dictionary to a sorted list
	objs = []
	for key in items:
		i = 0
		while (i < len(objs)) and (items[key] < objs[i][0]): i += 1
		objs.insert(i, [items[key], key])
	#print list - if number was specified, limit output to <number>
	if number == 0: number = len(objs)
	for i in range(number):
		print(f'{objs[i][0]}: {objs[i][1]}')

def hourly(log_file, days, number=0):
	print("HOURLY")
	items = {}
	#ensure that every hour has a dictionary entry
	for i in range(24):
		items[i] = 0
	#open log file
	with open(log_file, newline='', encoding='utf8', errors='ignore') as file:
		csvFile = csv.reader(file, delimiter=' ')
		for lines in csvFile:
			if len(lines) == 8:
				#count all requests that come in for each hour within the range of days
				day = int(lines[3][1])*10 + int(lines[3][2])
				if day in days:
					hour = int(lines[3][13])*10 + int(lines[3][14])
					items[hour] += 1
	#convert dictionary to a sorted list
	objs = []
	for key in items:
		i = 0
		while (i < len(objs)) and (items[key] < objs[i][0]): i += 1
		objs.insert(i, [items[key], key])
	#print list - if number was specified, limit output to <number>
	if number == 0: number = len(objs)
	for i in range(number):
		print(f'{objs[i][0]}: {objs[i][1]}')
