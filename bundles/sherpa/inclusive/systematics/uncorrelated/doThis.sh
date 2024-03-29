python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_HeavyFlavorBTagEffDown.cfg -o SherpaIP3DSV1_70_NProtoIncl_sumSV12mass_HeavyFlavorBTagEffDown.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_HeavyFlavorBTagEffUp.cfg -o SherpaIP3DSV1_70_NProtoIncl_sumSV12mass_HeavyFlavorBTagEffUp.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JERDOWN.cfg -o SherpaIP3DSV1_70_NProtoIncl_sumSV12mass_JERDOWN.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JERUP.cfg -o SherpaIP3DSV1_70_NProtoIncl_sumSV12mass_JERUP.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JESDOWN.cfg -o SherpaIP3DSV1_70_NProtoIncl_sumSV12mass_JESDOWN.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_JESUP.cfg -o SherpaIP3DSV1_70_NProtoIncl_sumSV12mass_JESUP.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_LightBTagEffDown.cfg -o SherpaIP3DSV1_70_NProtoIncl_sumSV12mass_LightBTagEffDown.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_LightBTagEffUp.cfg -o SherpaIP3DSV1_70_NProtoIncl_sumSV12mass_LightBTagEffUp.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_MuonEff.cfg -o SherpaIP3DSV1_70_NProtoIncl_sumSV12mass_MuonEff.root
python $SRC/python/bundleHistos.py -f ./bundleIP3DSV1_70_allJets_sumSV12mass_MuonPt.cfg -o SherpaIP3DSV1_70_NProtoIncl_sumSV12mass_MuonPt.root
for file in *root; do (python /amnt/remote/pkthafc.home/psteinb/development/sandbox/fitter/python/printEnvFile.py -f ${file} -3 |egrep "^.*[A-Z].*" > ${file/.root/.env});done
