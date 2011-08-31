#!/bin/bash

python $SRC/python/bundleHistos.py -f `pwd`/bundleSV0_NJetsEq1.cfg -o SherpaSV0_NJetsEq1.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleJetCombNN_60_NJetsEq1.cfg -o SherpaJetCombNN_60_NJetsEq1.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleJetCombNN_70_NJetsEq1.cfg -o SherpaJetCombNN_70_NJetsEq1.root
