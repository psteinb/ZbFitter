#!/bin/bash

python $SRC/python/bundleHistos.py -f `pwd`/bundleSV0_NJetsGe2.cfg -o SherpaSV0_NJetsGe2.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleJetCombNN_60_NJetsGe2.cfg -o SherpaJetCombNN_60_NJetsGe2.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleJetCombNN_70_NJetsGe2.cfg -o SherpaJetCombNN_70_NJetsGe2.root
