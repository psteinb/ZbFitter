#!/bin/bash

for file in $*;
do 
    echo
    if [[ $file == *cfg ]];then
	echo "processing ${file}"
	python $SRC/python/bundleHistos.py -f `pwd`/$file -o ${file/cfg/root} > ${file/.cfg/.log} 2>&1 &
    else
	echo "cannot process ${file}"
    fi
done