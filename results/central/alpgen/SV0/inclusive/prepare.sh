python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/AlpgenSV0_allJets_sumSV0mass.root -3|egrep "^[A-Za-z]" > AlpgenSV0_3norm_top_allJets_sumSV0mass.env
python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/AlpgenSV0_allJets_sumSV0mass.root -2|egrep "^[A-Za-z]" > AlpgenSV0_2norm_fixedLight_fixedTop_sumSV1mass.env 
