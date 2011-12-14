python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/NJetsGe2/AlpgenIP3DSV1_80_NJetsGe2_sumSV12mass.root -3|egrep "^[A-Za-z]" > AlpgenIP3DSV1_80_3norm_top_sumSV12mass.env
python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/NJetsGe2/AlpgenIP3DSV1_80_NJetsGe2_sumSV12mass.root -2|egrep "^[A-Za-z]" > AlpgenIP3DSV1_80_2norm_fixedLight_fixedTop_sumSV1mass.env 
