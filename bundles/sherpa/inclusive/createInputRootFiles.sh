#!/bin/bash

python $SRC/python/bundleHistos.py -f `pwd`/bundleSV0_allJets.cfg -o SherpaSV0.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleJetCombNN_60_allJets.cfg -o SherpaJetCombNN_60.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleJetCombNN_70_allJets.cfg -o SherpaJetCombNN_70.root
