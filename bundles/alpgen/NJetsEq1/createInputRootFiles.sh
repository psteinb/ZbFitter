#!/bin/bash

for file in *cfg;
do 
    echo "processing file ${file}"
    python $SRC/python/bundleHistos.py -f `pwd`/$file -o ${file/cfg/root}
done