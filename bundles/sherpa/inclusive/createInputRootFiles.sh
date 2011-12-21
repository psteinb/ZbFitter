#!/bin/bash

python $SRC/python/bundleHistos.py -f `pwd`/bundleSV0_allJets_sumSV0mass.cfg -o SherpaSV0_sumSV0mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_70_allJets_sumSV12mass.cfg -o SherpaIP3DSV1_70_sumSV12mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_80_allJets_sumSV12mass.cfg -o SherpaIP3DSV1_80_sumSV12mass.root

python $SRC/python/bundleHistos.py -f `pwd`/customSV0_allJets_sumSV0mass.cfg -o SherpaSV0_sumSV0mass_custom.root
python $SRC/python/bundleHistos.py -f `pwd`/customIP3DSV1_70_allJets_sumSV12mass.cfg -o SherpaIP3DSV1_70_sumSV12mass_custom.root
python $SRC/python/bundleHistos.py -f `pwd`/customIP3DSV1_80_allJets_sumSV12mass.cfg -o SherpaIP3DSV1_80_sumSV12mass_custom.root

