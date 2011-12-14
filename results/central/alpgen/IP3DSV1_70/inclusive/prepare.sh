python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/AlpgenIP3DSV1_70_allJets_sumSV12mass.root -3|egrep "^[A-Za-z]" > AlpgenIP3DSV1_70_3norm_top_sumSV12mass.env
python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/AlpgenIP3DSV1_70_allJets_sumSV12mass.root -2|egrep "^[A-Za-z]" > AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_sumSV1mass.env 
