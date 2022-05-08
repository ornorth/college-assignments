#!/bin/bash
#search processes for anything running longer than 5 minutes
#could easily be modified to check for any other interval,
#or make it an argument passed in at execution time

#read in raw data from 'ps'
rm rawdata 2> /dev/null
ps -ef > rawdata

#truncate first line
sed -i -e "1d" rawdata

#optional/unnecessary - remove all lines for processes with a time of 00:00:00
#I don't know whether including this will make the program run faster or slower
sed -i -e "/00\:00\:00/d" rawdata

#for each process
while read line
do
	#convert time to seconds
	#using regular expression "0*([0-9]*)" in 'sed' to remove leading zeros
	rawtime=`echo $line | awk '{printf $7}'`

	#for the hour section, I also remove any hyphens
	#I assume that an output of x-xx from 'ps -ef' is equivalent to xxx hours
	x=`echo $rawtime | awk -F':' '{printf $1}' | sed -r 's/0*([0-9]*)/\1/' | sed -r 's/-//g'`
	time=$(( 360*x ))

	x=`echo $rawtime | awk -F':' '{printf $2}' | sed -r 's/0*([0-9]*)/\1/'`
	time=$(( 60*x + time ))

	x=`echo $rawtime | awk -F':' '{printf $3}' | sed -r 's/0*([0-9]*)/\1/'`
	time=$(( time + x ))
	#echo $rawtime ": " $time

	#display only processes over 5 minutes
	if [ $time -gt 300  ]
	then
		#get process ID
		pid=`echo $line | awk '{printf $2}'`

		#get full text of the command
		cmd=`echo $line | awk '{$1=$2=$3=$4=$5=$6=$7=""; print $0}'`

		#display time, pid, and command
		echo "CPU time is" $time "seconds used by:" $pid". CMD =" $cmd
	fi
done < rawdata

#clean up extra data
rm rawdata 2> /dev/null
