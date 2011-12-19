#!/bin/bash

if [[ -n $1 ]];then
    for file in $1;do
	echo -e "\nprocessing " $file
	python $SRC/python/bundleHistos.py -f $file -o ${file/.cfg/.root} > ${file/.cfg/.log} 2>&1 &
    done
else
    for file in `pwd`/*;do
	echo -e "\nprocessing " $file
	python $SRC/python/bundleHistos.py -f $file -o ${file/.cfg/.root} > ${file/.cfg/.log} 2>&1 &
    done
fi