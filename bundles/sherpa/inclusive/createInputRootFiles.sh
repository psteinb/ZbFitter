#!/bin/bash

python $SRC/python/bundleHistos.py -f `pwd`/bundleSV0_allJets.cfg -o SherpaSV0.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_60_allJets.cfg -o SherpaIP3DSV1_60_SV12Mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_70_allJets.cfg -o SherpaIP3DSV1_70_SV12Mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_80_allJets.cfg -o SherpaIP3DSV1_80_SV12Mass.root
