#!/bin/bash
#update permissions, but this time arguments are decided at execution instead of via user prompt

if [ $# -lt 0 ]
then
	echo "Usage: ./lab4-2.sh <filename> <permissions>"
else

	val=
	for i in $( eval echo {1..$#} )
	do
	if [ "${!i}" == "read" ]
	then
		val=$val"r"
	fi
	if [ "${!i}" == "write" ]
	then
		val=$val"w"
	fi
	if [ "${!i}" == "execute" ]
	then
		val=$val"x"
	fi
	done

	chmod u=$val $1
fi
