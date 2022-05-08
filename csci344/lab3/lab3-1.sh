#!/bin/bash
#reads in any number of arguments and returns the sum
if [ $# -ne 0 ]
then
	sum=0

	for i in $( eval echo {1..$#} )
	do
		sum=$((sum + ${!i}))
	done

	echo $sum
else
	echo "Usage: ./lab3-1.sh <number 1> <number 2>...<number n>"
fi
