python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/NJetsEq1/AlpgenIP3DSV1_80_NJetsEq1_SV12mass.root -3|egrep "^[A-Za-z]" > AlpgenIP3DSV1_80_3norm_top.env
python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/NJetsEq1/AlpgenIP3DSV1_80_NJetsEq1_SV12mass.root -2|egrep "^[A-Za-z]" > AlpgenIP3DSV1_80_2norm_fixedLight_fixedTop.env 
