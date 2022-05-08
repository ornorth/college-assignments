#!/bin/bash

ls /home > userlist	#list of users
declare -A myarray	#array to store id/disc
rm myfile 2>/dev/null
touch myfile		#file to store id/disc

#iterate through user list
while read userline
do
  #check if user is valid
  id -u $userline >/dev/null 2>/dev/null
  if [ $? -eq 0 ]
  then
    #get id and disc usage of user
    myid=$(id -u $userline)
    myval=$(du -s /home/$userline 2>/dev/null | awk '{ printf $1 }')
    #store info in myarray and myfile
    myarray[$myid]=$myval
    echo $myval $myid >> myfile
  fi
done < userlist

#sort the data (file - array is discarded at this point)
#reverse order to make print at end easier
sort --output=myfile -g -r myfile 

#repeat as long as a value < 8000 is present
flag=0
while [ $flag -eq 0 ]
do
  myval=`tail -n 1 myfile | awk '{ printf $1 }'`
  if (( $myval <= 8000 ))
  then
    #truncate the last line in myfile
    head -n -1 myfile > tmp
    cat tmp > myfile
  else
    #exit while loop
    flag=1
  fi
done

#print top 3 disc users
head -n 3 myfile

#remove temporary files
rm userlist tmp #myfile
