#!/bin/bash

permision=""
if test "$1" = "read" 
then
	echo "read"
	permision="r"
elif test "$1" = "write"
then
	echo "write"
	permision="w"
elif test "$1" = "execute"
then
	echo "execute"
	permision="x"
else
	echo "eroare"
	exit
fi

for FNAME in `ls` 
do
	if ! test -d $FNAME
	then
		line=`ls -l $FNAME`
		#echo "${line:0:4}"
		#echo $line
		
		if echo "${line:1:4}" | grep -q "$permision"
		then
			#echo $FSIZE
			#echo `echo ${FNAME} | cut -d"." -f1`
			
			FSIZE=`du -b $FNAME | cut -f 1`
			name=`echo ${FNAME} | cut -d"." -f1`
			mkdir "$name.dir"
			path=`pwd`
			cd "$name.dir"
			touch "size.txt"
			echo $FSIZE > size.txt
			cd $path
		fi
	fi
done
