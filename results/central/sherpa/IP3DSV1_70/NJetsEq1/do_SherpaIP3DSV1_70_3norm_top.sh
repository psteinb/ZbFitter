#RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_70_NJetsEq1.root  -c SherpaIP3DSV1_70_3norm_top.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_70_3norm_top_NJetsEq1 -r 5   > $SRC/results/central/sherpa/IP3DSV1_70/NJetsEq1/SherpaIP3DSV1_70_3norm_top.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_70_NJetsEq1.root  -c SherpaIP3DSV1_70_3norm_top.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_70_3norm_top_NJetsEq1_PseudoData -r 5   > $SRC/results/central/sherpa/IP3DSV1_70/NJetsEq1/SherpaIP3DSV1_70_3norm_top_PseudoData.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_70_NJetsEq1.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_NJetsEq1 -r 5   > $SRC/results/central/sherpa/IP3DSV1_70/NJetsEq1/SherpaIP3DSV1_70_2norm_fixedLight_fixedTop.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_70_NJetsEq1.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_NJetsEq1_PseudoData -r 5   > $SRC/results/central/sherpa/IP3DSV1_70/NJetsEq1/SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_PseudoData.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_70_NJetsEq1.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_HIGHc_lowb.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_NJetsEq1_HIGHc_lowb -r 5   > $SRC/results/central/sherpa/IP3DSV1_70/NJetsEq1/SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_HIGHc_lowb.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_70_NJetsEq1.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_lowc_HIGHb.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_NJetsEq1_lowc_HIGHb -r 5   > $SRC/results/central/sherpa/IP3DSV1_70/NJetsEq1/SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_lowc_HIGHb.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaIP3DSV1_70_NJetsEq1.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop.env -D "Data" -T "smoothedTrueB,smoothedTrueC,smoothedTrueL,smoothedTop" -o Sherpa_2norm_fixedLight_fixedTop_NJetsEq1_smoothed -r 5   > $SRC/results/central/sherpa/IP3DSV1_70/NJetsEq1/SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_smoothed.log 2>&1 &
