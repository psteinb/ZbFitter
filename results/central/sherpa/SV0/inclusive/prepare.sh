python $SRC/python/printEnvFile.py -f $SRC/bundles/sherpa/inclusive/bundleSV0_allJets_sumSV0mass.root -3|egrep "^[A-Za-z]" > SherpaSV0_3norm_background_sumSV0mass.env
python $SRC/python/printEnvFile.py -f $SRC/bundles/sherpa/inclusive/bundleSV0_allJets_sumSV0mass.root -3 -N "TrueB,TrueC,TrueL,Top"|egrep "^[A-Za-z]" > SherpaSV0_3norm_top_sumSV0mass.env
