python $SRC/python/printEnvFile.py -f $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_70_sumSV12mass.root -3 -N "TrueB,TrueC,TrueL,Top"|egrep "^[A-Za-z]" > SherpaIP3DSV1_70_3norm_top_sumSV12mass.env
python $SRC/python/printEnvFile.py -f $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_70_sumSV12mass.root -3|egrep "^[A-Za-z]" > SherpaIP3DSV1_70_3norm_background_sumSV12mass.env 
