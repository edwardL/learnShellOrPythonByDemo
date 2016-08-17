#!/bin/bash
#LANG=zh_CN.utf8

DelayCount()
{
	seq $1 | tac | while read line
			do
				echo -en "\a倒计时...${line}\r"
				sleep 1
			done
}

CheckTargetExist()
{
	ready_status=""
	checkCount=0
	echo "检测 $1"
	while [ "$ready_status" = "" ]
	do
		sleep 1
		ready_status=`ls -l $1 2>/dev/null`
		((checkCount=$checkCount+1))
		echo $checkCount"/30..."
		if [ "$checkCount" == "30" ]
		then
			echo "检测时间过长,启动出错，终止进程"
			exit 1
		fi		
	done
	echo "删除 $1"
	rm -f $1
}

displayArgs()
{
	echo "number: $#"
	echo "program : $0"
	echo "arg1 : $1"
	echo "arg2 : $2"
	echo "arg3 : $3"
	echo "arg list : $@"
	echo "arg param list : $*"
	echo "progress id: $$"
	echo "progress stat: $?"
}




#DelayCount 30

#CheckTargetExist a.txt

displayArgs 1 2 3
