python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_BtagEfficiency_HeavyDownLightDown.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_BtagEfficiency_HeavyDownLightDown.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_BtagEfficiency_HeavyDownLightUp.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_BtagEfficiency_HeavyDownLightUp.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_BtagEfficiency_HeavyUpLightDown.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_BtagEfficiency_HeavyUpLightDown.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_BtagEfficiency_HeavyUpLightUp.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_BtagEfficiency_HeavyUpLightUp.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JESDOWN_BtagHeavyFlDown.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_JESDOWN_BtagHeavyFlDown.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JESDOWN_BtagHeavyFlUp.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_JESDOWN_BtagHeavyFlUp.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JESDOWN_BtagLightFlDown.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_JESDOWN_BtagLightFlDown.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JESDOWN_BtagLightFlUp.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_JESDOWN_BtagLightFlUp.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JESUP_BtagHeavyFlDown.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_JESUP_BtagHeavyFlDown.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JESUP_BtagHeavyFlUp.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_JESUP_BtagHeavyFlUp.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JESUP_BtagLightFlDown.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_JESUP_BtagLightFlDown.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JESUP_BtagLightFlUp.cfg -o SherpaIP3DSV1_70_allJets_sumSV12mass_JESUP_BtagLightFlUp.root
for file in *root; do (python /amnt/remote/pkthafc.home/psteinb/development/sandbox/fitter/python/printEnvFile.py -f ${file} -3 |egrep "^.*[A-Z].*" > ${file/.root/.env});done
