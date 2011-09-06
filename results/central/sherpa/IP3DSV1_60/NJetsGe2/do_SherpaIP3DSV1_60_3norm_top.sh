RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_60_NJetsGe2.root  -c SherpaIP3DSV1_60_3norm_top.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_60_3norm_top_NJetsGe2 -r 5   > $SRC/results/central/sherpa/IP3DSV1_60/NJetsGe2/SherpaIP3DSV1_60_3norm_top.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_60_NJetsGe2.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_NJetsGe2 -r 5   > $SRC/results/central/sherpa/IP3DSV1_60/NJetsGe2/SherpaIP3DSV1_60_2norm_fixedLight_fixedTop.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_60_NJetsGe2_maxSV12mass.root  -c SherpaIP3DSV1_60_3norm_top_maxSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_60_3norm_top_NJetsGe2_maxSV1mass -r 5   > $SRC/results/central/sherpa/IP3DSV1_60/NJetsGe2/SherpaIP3DSV1_60_3norm_top_maxSV1mass.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_60_NJetsGe2_maxSV12mass.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_maxSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_NJetsGe2_maxSV1mass -r 5   > $SRC/results/central/sherpa/IP3DSV1_60/NJetsGe2/SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_maxSV1mass.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_60_NJetsGe2_sumSV12mass.root  -c SherpaIP3DSV1_60_3norm_top_sumSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_60_3norm_top_NJetsGe2_sumSV1mass -r 5   > $SRC/results/central/sherpa/IP3DSV1_60/NJetsGe2/SherpaIP3DSV1_60_3norm_top_sumSV1mass.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_60_NJetsGe2_sumSV12mass.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_sumSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_NJetsGe2_sumSV1mass -r 5   > $SRC/results/central/sherpa/IP3DSV1_60/NJetsGe2/SherpaIP3DSV1_60_2norm_fixedLight_fixedTop_sumSV1mass.log 2>&1 &
