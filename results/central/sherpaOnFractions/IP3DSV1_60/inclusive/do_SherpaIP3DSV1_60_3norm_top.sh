
RunFitterOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_60_sumSV12mass.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_sumSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_inclusive_sumSV12mass -r 5 > $SRC/results/central/sherpaOnFractions/IP3DSV1_60/inclusive/SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_sumSV12mass.log 2>&1 &

RunFitterOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_60_sumSV12mass.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_sumSV1mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_inclusive_sumSV12mass_PseudoData -r 5 > $SRC/results/central/sherpaOnFractions/IP3DSV1_60/inclusive/SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_sumSV12mass_PseudoData.log 2>&1 &


RunFitterOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_60_maxSV12mass.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_maxSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_inclusive_maxSV12mass -r 5 > $SRC/results/central/sherpaOnFractions/IP3DSV1_60/inclusive/SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_maxSV12mass.log 2>&1 &

RunFitterOnFractions.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_60_maxSV12mass.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_maxSV1mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_inclusive_maxSV12mass_PseudoData -r 5 > $SRC/results/central/sherpaOnFractions/IP3DSV1_60/inclusive/SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_maxSV12mass_PseudoData.log 2>&1 &

