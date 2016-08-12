#!/bin/bash

DelayCount()
{
	seq $1 | tac | while read line
			do
				echo -en "\a倒计时...${line}\r"
				sleep 1
			done
}

DelayCount 30
