#/bin/bash
# file: silent_grep.sh

if [ $# -ne 2 ]; then
 echo "usage : $0 match text filename"
 exit 1
fi

match_text=$1
filename=$2

grep -q "$match_text" $filename

if [ $? -eq 0 ]; then
 echo "the text exist in the file"
else
 echo "the text not exist in the file"
fi

