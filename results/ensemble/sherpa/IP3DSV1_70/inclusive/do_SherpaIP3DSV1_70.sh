RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_70_sumSV12Mass.root  -c SherpaIP3DSV1_70_3norm_top_sumSV12mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_70_3norm_top_inclusive_sumSV12mass -r 5 -i 15000 > $SRC/results/ensemble/sherpa/IP3DSV1_70/inclusive/SherpaIP3DSV1_70_3norm_top_sumSV12mass.log 2>&1 &


RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_70_sumSV12Mass.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_sumSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_inclusive_sumSV12mass -r 5 -i 15000 > $SRC/results/ensemble/sherpa/IP3DSV1_70/inclusive/SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_sumSV12mass.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_70_maxSV12Mass.root  -c SherpaIP3DSV1_70_3norm_top_maxSV12mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_70_3norm_top_inclusive_maxSV12mass -r 5 -i 15000 > $SRC/results/ensemble/sherpa/IP3DSV1_70/inclusive/SherpaIP3DSV1_70_3norm_top_maxSV12mass.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaIP3DSV1_70_maxSV12Mass.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_maxSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_inclusive_maxSV12mass -r 5 -i 15000 > $SRC/results/ensemble/sherpa/IP3DSV1_70/inclusive/SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_maxSV12mass.log 2>&1 &



