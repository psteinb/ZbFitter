#!/bin/bash

FILES=$*
if [[ -z $FILES ]];then
    FILES=$PWD/*cfg
fi

for file in $FILES;
do 
    echo "processing file ${file}"
    python $SRC/python/bundleHistos.py -f `pwd`/$file -o ${file/cfg/root}
done