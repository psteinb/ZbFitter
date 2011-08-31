#!/bin/bash

python $SRC/python/bundleHistos.py -f `pwd`/bundleSV0_allJets.cfg -o SherpaSV0.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleJetCombNN_60_allJets_jFitMass.cfg -o SherpaJetCombNN_60_jFitMass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleJetCombNN_70_allJets_jFitMass.cfg -o SherpaJetCombNN_70_jFitMass.root
