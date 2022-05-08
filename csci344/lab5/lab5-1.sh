#!/bin/bash
#count lines and characters in a file

lines=`wc file1 | awk '{ printf $1 }'`
chars=`wc -c file1 | awk '{ printf $1 }'`
echo $(( chars / lines ))
