python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/bundleIP3DSV1_80_allJets_sumSV12mass.root -3 -N "TrueB,TrueC,TrueL,Top"|egrep "^[A-Za-z]" > AlpgenIP3DSV1_80_3norm_top_sumSV12mass.env
python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/bundleIP3DSV1_80_allJets_sumSV12mass.root -3|egrep "^[A-Za-z]" > AlpgenIP3DSV1_80_3norm_background_sumSV12mass.env 

python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/customIP3DSV1_80_allJets_sumSV12mass.root -3 -N "TrueB,TrueC,TrueL,Top"|egrep "^[A-Za-z]" > AlpgenIP3DSV1_80_3norm_top_sumSV12mass_custom.env
python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/customIP3DSV1_80_allJets_sumSV12mass.root -3|egrep "^[A-Za-z]" > AlpgenIP3DSV1_80_3norm_background_sumSV12mass_custom.env 
