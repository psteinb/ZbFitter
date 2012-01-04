python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/bundleSV0_allJets_sumSV0mass.root -3 -N "TrueB,TrueC,TrueL,Top"|egrep "^[A-Za-z]" > AlpgenSV0_3norm_top_allJets_sumSV0mass.env
python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/bundleSV0_allJets_sumSV0mass.root -3|egrep "^[A-Za-z]" > AlpgenSV0_3norm_background_allJets_sumSV0mass.env
