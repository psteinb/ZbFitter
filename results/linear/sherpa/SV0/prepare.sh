

for item in {"","_0d5","_0d75","_1d25","_1d5"};
do
    echo "processing TrueB"$item
    python $SRC/python/printEnvFile.py -f $SRC/bundles/sherpa/inclusive/linearity/customSV0_allJets_sumSV0mass_TrueB_scaled.root -3 -N "TrueB${item},TrueC,TrueL,Background"|egrep "^[A-Za-z]" > SherpaSV0_3norm_background_sumSV0mass_custom${item}.env
done

#python $SRC/python/printEnvFile.py -f $SRC/bundles/sherpa/inclusive/customSV0_allJets_sumSV0mass.root -3 -N "TrueB,TrueC,TrueL,Top"|egrep "^[A-Za-z]" > SherpaSV0_3norm_top_sumSV0mass_custom.env
