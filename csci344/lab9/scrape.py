#!/usr/bin/python3.5
#Craigslist scraper
#Arguments:
#   url of the craigslist page
#   keyword to search for (filter)
#   maximum price (filter)
#   maximum number of found items to list
#
#This program was designed for periodic execution (like with cron)
#so it writes the output to a file and sends an email if the contents of the file have changed

#check proper input before anything else
#doing this because the imports are large and I want a fast exit if input is improper
import sys
print("Craigslist Scraper:")
if len(sys.argv) != 8:
	print("usage: ./scrape.py <url> <query> <max-price> <num-products> <sender_email> <password> <receiver_email>")
	quit()

#import dependencies
from bs4 import BeautifulSoup
from urllib.request import urlopen
from operator import itemgetter
import csv, lxml, smtplib, ssl

#returns the value of a given tag and class if it can be found
def getStr(listing, _tag, _class):
	if listing.find(_tag, _class):
		return(listing.find(_tag, _class).string.strip(' \n'))
	return None

#read in arguments
page = sys.argv[1]		#url to open
query = sys.argv[2].lower()	#keyword to look for
maxPrice = int(sys.argv[3])	#maximum price we want to include in our results
numProducts = int(sys.argv[4])	#maximum results we want to include
sender_email = sys.argv[5]      #email the program will use to send the results
password = sys.argv[6]          #password for the email
receiver_email = sys.argv[7]    #email the program will send the results to
count = 0			#track current number of results to stay under numProducts
resultList = []

#this loop repeats the search for every page
nextPage = True
while nextPage and count < numProducts:
	print("Opening " + page)
	#request HTML file and turn it into soup
	html = urlopen(page)
	soup = BeautifulSoup(html, 'lxml')

	#iterate through all listings
	for listing in soup.find_all('div', class_='result-info'):
		title = getStr(listing, 'a', 'result-title hdrlnk').replace(",","'")
		price = int(getStr(listing, 'span', 'result-price').strip('$').replace(',',''))
		city = getStr(listing, 'span', 'result-hood')

		#only include listings with all 3 parameters
		if title and price and city:
			flag = True #check all requirements before writing
			flag = flag and (title.lower().find(query) >= 0) #query matches
			flag = flag and (price < maxPrice) #price is under max
			flag = flag and (count < numProducts) #we have not reached the cap on listings
			if flag:
				#place fields in a list (done this way for sorting purposes)
				resultList.append([title, price, city])
				count += 1

	#check if there is another page, exit if not
	nextTag = soup.find('link', attrs={'rel': 'next'})
	if nextTag:
		page = nextTag['href']
	else:
		nextPage = False

#this segment serves 2 purposes: construct the email and determine any differences from the last run
resultList = sorted(resultList, key=itemgetter(1))
print(resultList)
flag = False
message = """\
Subject: Craigslist fridge update

Most recent fridge postings in your area:
"""
with open('/home/ornorth/lab9/listings.csv', 'r') as csv_file:
	#iterate through the first 5 observations
	i = 0
	for row in csv_file:
		if row == 'TITLE,PRICE,CITY\n': continue
		#format new listing
		newline = "{},${},{}\n".format(resultList[i][0], resultList[i][1], resultList[i][2])
		#append listing to email message
		message += newline
		#check for differences
		flag = flag or (newline != row)
		i += 1
		#if i > max(len(resultList)-1, 4): break
		if i > len(resultList)-1: break

#update csv file
wfile = open('/home/ornorth/lab9/listings.csv', 'w')
wfile.write('TITLE,PRICE,CITY\n')
for listing in resultList:
	wfile.write("{},${},{}\n".format(listing[0], listing[1], listing[2]))
wfile.close()

#if differences were found, send an email to 'owenonorth@gmail.com'
if flag:
	print(message)
	port = 465
	smtp_server = "smtp.gmail.com"

	context = ssl.create_default_context()
	with smtplib.SMTP_SSL(smtp_server, port, context=context) as server:
		server.login(sender_email, password)
		server.sendmail(sender_email, receiver_email, message)
else:
	print('NO CHANGES')
