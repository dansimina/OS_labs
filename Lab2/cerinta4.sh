#find . -name "*.c" | wc -l
FIS=`find . -name "*.c"`
for FNAME in $FIS
do
	nLines=`wc -l $FNAME | cut -d" " -f -1`
	if test $nLines -gt $1
	then
		echo $FNAME
	fi
done
