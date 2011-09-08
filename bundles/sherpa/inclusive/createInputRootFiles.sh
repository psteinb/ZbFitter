#!/bin/bash

python $SRC/python/bundleHistos.py -f `pwd`/bundleSV0_allJets_sumSV0mass.cfg -o SherpaSV0_sumSV0mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_60_allJets_sumSV12mass.cfg -o SherpaIP3DSV1_60_sumSV12mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_70_allJets_sumSV12mass.cfg -o SherpaIP3DSV1_70_sumSV12mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_80_allJets_sumSV12mass.cfg -o SherpaIP3DSV1_80_sumSV12mass.root

python $SRC/python/bundleHistos.py -f `pwd`/bundleSV0_allJets_maxSV0mass.cfg -o SherpaSV0_maxSV0mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_60_allJets_maxSV12mass.cfg -o SherpaIP3DSV1_60_maxSV12mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_70_allJets_maxSV12mass.cfg -o SherpaIP3DSV1_70_maxSV12mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_80_allJets_maxSV12mass.cfg -o SherpaIP3DSV1_80_maxSV12mass.root
