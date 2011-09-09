RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_70_NJetsGe2_maxSV12mass.root  -c SherpaIP3DSV1_70_3norm_top_sumSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_70_3norm_top_sum_maxSV12mass -r 5 -i 15000   > $SRC/results/ensemble/sherpa/IP3DSV1_70/NJetsGe2/SherpaIP3DSV1_70_3norm_top_sum_maxSV12mass.lg 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_70_NJetsGe2_sumSV12mass.root  -c SherpaIP3DSV1_70_3norm_top_sumSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_70_3norm_top_sum_sumSV12mass -r 5 -i 15000   > $SRC/results/ensemble/sherpa/IP3DSV1_70/NJetsGe2/SherpaIP3DSV1_70_3norm_top_sum_sumSV12mass.lg 2>&1 &



RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_70_NJetsGe2_maxSV12mass.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_maxSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_NJetsGe2_maxSV1mass -r 5 -i 15000   > $SRC/results/ensemble/sherpa/IP3DSV1_70/NJetsGe2/SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_maxSV1mass.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_70_NJetsGe2_sumSV12mass.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_sumSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_NJetsGe2_sumSV1mass -r 5 -i 15000   > $SRC/results/ensemble/sherpa/IP3DSV1_70/NJetsGe2/SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_sumSV1mass.log 2>&1 &

