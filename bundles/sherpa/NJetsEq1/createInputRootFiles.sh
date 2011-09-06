#!/bin/bash

python $SRC/python/bundleHistos.py -f `pwd`/bundleSV0_NJetsEq1.cfg -o SherpaSV0_NJetsEq1.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_60_NJetsEq1.cfg -o SherpaIP3DSV1_60_NJetsEq1.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_70_NJetsEq1.cfg -o SherpaIP3DSV1_70_NJetsEq1.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_80_NJetsEq1.cfg -o SherpaIP3DSV1_80_NJetsEq1.root
