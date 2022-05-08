#!/usr/bin/python3.7
#reads and parses an HTTP log file
#output is determined by arguments given at runtime
#for full description, run './lab13.py --help'
import sys
import funcs

#interpret '--day []' argument as a list of integers
def get_day_list(dayStr):
	try:
		if '-' in dayStr:
			borders = dayStr.split('-')#, dayStr)
			days = []
			if (int(borders[0]) > 0) and (int(borders[0]) < 29) and (int(borders[1]) >= int(borders[0])) and (int(borders[1]) < 29):
				for i in range(int(borders[0]), int(borders[1])):
					days.append(i)
				return days
			else:
				print('ERROR: invalid format for day argument')
				quit()
		return [int(dayStr)]
	except ValueError:
		print('ERROR: invalid format for day argument')
		quit()


days = []
argc = len(sys.argv)

#option 1: input is "--help"
if argc == 2:
	if sys.argv[1] == '--help':
		funcs.help()
	else:
		print('Invalid input. See "./lab13.py --help" for usage')

#option 2: input is one of 4 main options, then day range
elif argc == 5:
	if sys.argv[2] == '--day':
		days = get_day_list(sys.argv[3])
	else:
		print(f'expected argument "--day", not "{sys.argv[2]}"')
		quit()
	log_file = sys.argv[4]
	path = sys.argv[1]
	if path == '--resources':
		funcs.resources(log_file, days)
	elif path == '--requesters':
		funcs.requesters(log_file, days)
	elif path == '--errors':
		funcs.errors(log_file, days)
	elif path == '--hourly':
		funcs.hourly(log_file, days)
	else:
		print(f'Command "{path}" not recognized')

#option 3: input is one of 4 main options, then day range, then number of arguments to return
elif argc == 7:
	number = 0
	if sys.argv[2] == '--day':
		days = get_day_list(sys.argv[3])
	else:
		print(f'Expected argument "--day", not "{sys.argv[2]}"')
		quit()
	if sys.argv[4] == '--number':
		try:
			if int(sys.argv[5]) > 0:
				number = int(sys.argv[5])
			else:
				print('ERROR: expected a positive value for "--number"')
				print('proceeding without a number argument')
		except ValueError:
			print('ERROR: invalid input for number argument')
			print('proceeding without a number argument')
	else:
		print(f'Expected argument "--number", not "{sys.argv[4]}"')
		quit()
	log_file = sys.argv[6]
	path = sys.argv[1]
	if path == '--resources':
		funcs.resources(log_file, days, number)
	elif path == '--requesters':
		funcs.requesters(log_file, days, number)
	elif path == '--errors':
		funcs.errors(log_file, days, number)
	elif path == '--hourly':
		funcs.hourly(log_file, days, number)
	else:
		print(f'Command "{path}" not recognized')

#if input is invalid, refer to help function
else:
	print('See ./lab13.py --help for usage')
