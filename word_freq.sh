#/bin/bash
# file : word_freq.sh

if [ $# -ne 1 ];
then
 echo "usage: $0 filename";
 exit -1
fi

filename=$1

egrep -o "\b[[:alpha:]]+\b" $filename | \

awk '{count[$0]++}
END{printf("%-14s%s\n","Word","Count");
for(ind in count)
{printf("%-14s%d\n",ind,count[ind]); }

}'
