RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_60_SV12Mass.root  -c SherpaIP3DSV1_60_3norm_top.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_60_3norm_top_inclusive -r 5 -i 15000 > $SRC/results/ensemble/sherpa/IP3DSV1_60/inclusive/SherpaIP3DSV1_60_3norm_top.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_60_SV12Mass.root  -c SherpaIP3DSV1_60_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_inclusive -r 5 -i 15000 > $SRC/results/ensemble/sherpa/IP3DSV1_60/inclusive/SherpaIP3DSV1_60_2norm_fixedLight_fixedTop.log 2>&1 &

