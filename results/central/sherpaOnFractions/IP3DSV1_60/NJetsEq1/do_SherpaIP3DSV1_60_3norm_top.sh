
RunFitterOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_60_NJetsEq1.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_60_2norm_2fixed_NJetsEq1_fractions -r 5   > $SRC/results/central/sherpaOnFractions/IP3DSV1_60/NJetsEq1/SherpaIP3DSV1_60_2norm_2fixed.log 2>&1 &

RunFitterOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_60_NJetsEq1.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_60_2norm_2fixed_NJetsEq1_fractions_PseudoData -r 5   > $SRC/results/central/sherpaOnFractions/IP3DSV1_60/NJetsEq1/SherpaIP3DSV1_60_2norm_2fixed_PseudoData.log 2>&1 &


