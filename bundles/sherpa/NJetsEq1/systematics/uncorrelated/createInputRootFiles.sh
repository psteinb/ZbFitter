#!/bin/bash

for i in `pwd`/*cfg;do
    echo "processing " $i
    python $SRC/python/bundleHistos.py -f $i -o ${i/cfg/root} > ${i/cfg/log} 2>&1 
done