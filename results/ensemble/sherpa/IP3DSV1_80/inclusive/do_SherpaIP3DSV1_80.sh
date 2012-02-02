RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/customIP3DSV1_80_allJets_sumSV12mass.root  -c SherpaIP3DSV1_80_3norm_top_sumSV12mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_80_3norm_top_inclusive_sumSV12mass -r 5 -i 50000 > $SRC/results/ensemble/sherpa/IP3DSV1_80/inclusive/SherpaIP3DSV1_80_3norm_top_sumSV12mass.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/customIP3DSV1_80_allJets_sumSV12mass.root  -c SherpaIP3DSV1_80_3norm_background_sumSV12mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o SherpaIP3DSV1_80_3norm_background_inclusive_sumSV12mass -r 5 -i 50000 > $SRC/results/ensemble/sherpa/IP3DSV1_80/inclusive/SherpaIP3DSV1_80_3norm_background_sumSV12mass.log 2>&1 &





