
RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_70_sumSV12mass.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_sumSV1mass.env -D "Data" -T "TrueB,TrueL,Top,TrueC" -o Sherpa_2norm_fixedLight_fixedTop_inclusive_sumSV12mass -r 5 -i 15000 > $SRC/results/ensemble/sherpaOnFractions/IP3DSV1_70/inclusive/SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_sumSV12mass.log 2>&1 &




RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_70_maxSV12mass.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_maxSV1mass.env -D "Data" -T "TrueB,TrueL,Top,TrueC" -o Sherpa_2norm_fixedLight_fixedTop_inclusive_maxSV12mass -r 5 -i 15000 > $SRC/results/ensemble/sherpaOnFractions/IP3DSV1_70/inclusive/SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_maxSV12mass.log 2>&1 &



