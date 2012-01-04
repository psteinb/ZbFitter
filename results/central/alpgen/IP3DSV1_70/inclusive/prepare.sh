python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/AlpgenIP3DSV1_70_allJets_sumSV12mass.root -3 -N "TrueB,TrueC,TrueL,Top"|egrep "^[A-Za-z]" > AlpgenIP3DSV1_70_3norm_top_sumSV12mass.env
python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/AlpgenIP3DSV1_70_allJets_sumSV12mass.root -3|egrep "^[A-Za-z]" > AlpgenIP3DSV1_70_3norm_background_sumSV12mass.env 
