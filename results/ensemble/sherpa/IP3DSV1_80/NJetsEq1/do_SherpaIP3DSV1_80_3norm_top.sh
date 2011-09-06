RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_80_NJetsEq1.root  -c SherpaIP3DSV1_80_3norm_top.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_80_3norm_top_NJetsEq1 -r 5   > $SRC/results/central/sherpa/IP3DSV1_80/NJetsEq1/SherpaIP3DSV1_80_3norm_top.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_80_NJetsEq1.root  -c SherpaIP3DSV1_80_3norm_top.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_80_3norm_top_NJetsEq1_PseudoData -r 5   > $SRC/results/central/sherpa/IP3DSV1_80/NJetsEq1/SherpaIP3DSV1_80_3norm_top_PseudoData.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_80_NJetsEq1.root  -c SherpaIP3DSV1_80_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_NJetsEq1 -r 5   > $SRC/results/central/sherpa/IP3DSV1_80/NJetsEq1/SherpaIP3DSV1_80_2norm_fixedLight_fixedTop.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_80_NJetsEq1.root  -c SherpaIP3DSV1_80_2norm_fixedLight_fixedTop.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_NJetsEq1_PseudoData -r 5   > $SRC/results/central/sherpa/IP3DSV1_80/NJetsEq1/SherpaIP3DSV1_80_2norm_fixedLight_fixedTop_PseudoData.log 2>&1 &

