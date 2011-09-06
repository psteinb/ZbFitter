#!/bin/bash

python $SRC/python/bundleHistos.py -f `pwd`/bundleSV0_NJetsGe2.cfg -o SherpaSV0_NJetsGe2.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_60_NJetsGe2.cfg -o SherpaIP3DSV1_60_NJetsGe2.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_70_NJetsGe2.cfg -o SherpaIP3DSV1_70_NJetsGe2.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_80_NJetsGe2.cfg -o SherpaIP3DSV1_80_NJetsGe2.root

python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_60_NJetsGe2_maxSV12mass.cfg -o SherpaIP3DSV1_60_NJetsGe2_maxSV12mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_70_NJetsGe2_maxSV12mass.cfg -o SherpaIP3DSV1_70_NJetsGe2_maxSV12mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_80_NJetsGe2_maxSV12mass.cfg -o SherpaIP3DSV1_80_NJetsGe2_maxSV12mass.root

python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_60_NJetsGe2_sumSV12mass.cfg -o SherpaIP3DSV1_60_NJetsGe2_sumSV12mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_70_NJetsGe2_sumSV12mass.cfg -o SherpaIP3DSV1_70_NJetsGe2_sumSV12mass.root
python $SRC/python/bundleHistos.py -f `pwd`/bundleIP3DSV1_80_NJetsGe2_sumSV12mass.cfg -o SherpaIP3DSV1_80_NJetsGe2_sumSV12mass.root
