
RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_60_NJetsEq1.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueL,Top,TrueC" -o SherpaIP3DSV1_60_2norm_2fixed_NJetsEq1_fractions -r 5 -i 15000   > $SRC/results/ensemble/sherpaOnFractions/IP3DSV1_60/NJetsEq1/SherpaIP3DSV1_60_2norm_2fixed.log 2>&1 &


RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_60_NJetsEq1.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueL,Top,TrueC" -o SherpaIP3DSV1_60_2norm_2fixed_NJetsEq1_fractions_x100 -r 5 -i 15000 -P 100   > $SRC/results/ensemble/sherpaOnFractions/IP3DSV1_60/NJetsEq1/SherpaIP3DSV1_60_2norm_2fixed_x100.log 2>&1 &



