#!/bin/bash
#roundabout way of updating personal file permissions by prompting user for input

val=
read -p "Enter the name of the file > " file
read -p "Do you want to allow read permission? > " r
read -p "Do you want to allow write permission? > " w
read -p "Do you want to allow execute permission? > " x

if [ "$r" == "yes" ]
then
	val=$val"r"
fi

if [ "$w" == "yes" ]
then
	val=$val"w"
fi

if [ "$x" == "yes" ]
then
	val=$val"x"
fi

chmod u=$val $file
