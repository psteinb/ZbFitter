
RunFitterOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_70_NJetsEq1.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueL,Top,TrueC" -o SherpaIP3DSV1_70_2norm_2fixed_NJetsEq1_fractions -r 5   > $SRC/results/central/sherpaOnFractions/IP3DSV1_70/NJetsEq1/SherpaIP3DSV1_70_2norm_2fixed.log 2>&1 &

RunFitterOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_70_NJetsEq1.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop.env -D "PseudoData" -T "TrueB,TrueL,Top,TrueC" -o SherpaIP3DSV1_70_2norm_2fixed_NJetsEq1_fractions_PseudoData -r 5   > $SRC/results/central/sherpaOnFractions/IP3DSV1_70/NJetsEq1/SherpaIP3DSV1_70_2norm_2fixed_PseudoData.log 2>&1 &


