#!/bin/bash

#original file
touch myfile
for i in {1..1000}
do
  echo "$i" >> myfile
done

#split 1-200
head -n  200 myfile > split1

#split 201-400
tail -n  800 myfile > tmp
head -n  200 tmp    > split2

#split 401-600
tail -n  600 myfile > tmp
head -n  200 tmp    > split3

#split 601-800
head -n -200 myfile > tmp
tail -n  200 tmp    > split4

#split 801-1000
tail -n  200 myfile > split5

#delete temporary file
rm tmp

#recombine
cat split1  > myfile #overwrite original
cat split2 >> myfile #append to current file
cat split4 >> myfile
cat split5 >> myfile

