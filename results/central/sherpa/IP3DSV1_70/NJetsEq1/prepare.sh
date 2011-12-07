python $SRC/python/printEnvFile.py -f $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_70_NJetsEq1.root -3|egrep "^[A-Za-z]" > SherpaIP3DSV1_70_3norm_top.env
python $SRC/python/printEnvFile.py -f $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_70_NJetsEq1.root -2|egrep "^[A-Za-z]" > SherpaIP3DSV1_70_2norm_fixedLight_fixedTop.env 
