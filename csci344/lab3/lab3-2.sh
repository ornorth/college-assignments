#!/bin/bash
#find the location of the 'ls' command and remove it from PATH
echo "Before: " $PATH
x=`whereis ls | awk '{printf $2}' | sed 's|/ls||g'`
x=:$x:
y=`echo $PATH | sed "s|$x|:|g"`
export PATH=$y
echo "After:  " $PATH
