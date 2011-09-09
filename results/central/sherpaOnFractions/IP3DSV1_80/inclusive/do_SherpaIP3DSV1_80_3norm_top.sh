RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_80_SV12Mass.root  -c SherpaIP3DSV1_80_3norm_top.env -D "Data" -T "TrueB,TrueL,Top,TrueC" -o SherpaIP3DSV1_80_3norm_top_inclusive -r 5 > $SRC/results/central/sherpa/IP3DSV1_80/inclusive/SherpaIP3DSV1_80_3norm_top.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_80_SV12Mass.root  -c SherpaIP3DSV1_80_3norm_top.env -D "PseudoData" -T "TrueB,TrueL,Top,TrueC" -o SherpaIP3DSV1_80_3norm_top_inclusive_PseudoData -r 5 > $SRC/results/central/sherpa/IP3DSV1_80/inclusive/SherpaIP3DSV1_80_3norm_top_PseudoData.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_80_SV12Mass.root  -c SherpaIP3DSV1_80_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueL,Top,TrueC" -o Sherpa_2norm_fixedLight_fixedTop_inclusive -r 5 > $SRC/results/central/sherpa/IP3DSV1_80/inclusive/SherpaIP3DSV1_80_2norm_fixedLight_fixedTop.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_80_SV12Mass.root  -c SherpaIP3DSV1_80_2norm_fixedLight_fixedTop.env -D "PseudoData" -T "TrueB,TrueL,Top,TrueC" -o Sherpa_2norm_fixedLight_fixedTop_inclusive_PseudoData -r 5 > $SRC/results/central/sherpa/IP3DSV1_80/inclusive/SherpaIP3DSV1_80_2norm_fixedLight_fixedTop_PseudoData.log 2>&1 &

