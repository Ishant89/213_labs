#!/bin/bash

path=/afs/cs/academic/class/15213-s16/autolab/proxylab/grading/$1@andrew.cmu.edu/$1@andrew.cmu.edu_*_proxylab-handin.tar

echo "$path"

if [ -e $path ]
then 
	echo "$path exists"
	rm $path
fi
./runHandinProxy.sh 17899 $1


