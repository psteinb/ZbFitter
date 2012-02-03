

for item in {"","_0d5","_0d75","_1d25","_1d5"};
do
    echo "processing TrueB"$item
    python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/linearity/customIP3DSV1_80_allJets_sumSV12mass_TrueB_scaled.root -3 -N "TrueB${item},TrueC,TrueL,Background"|egrep "^[A-Za-z]" > AlpgenIP3DSV1_80_3norm_background_sumSV12mass_custom${item}.env
done

#python $SRC/python/printEnvFile.py -f $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root -3 -N "TrueB,TrueC,TrueL,Top"|egrep "^[A-Za-z]" > AlpgenSV0_3norm_top_sumSV0mass_custom.env
