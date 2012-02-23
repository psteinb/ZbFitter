##RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customIP3DSV1_80_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_80_3norm_top_sumSV12mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_80_3norm_top_inclusive_sumSV12mass -r 5 -i 50000 > $SRC/results/ensemble/alpgen/IP3DSV1_80/AlpgenIP3DSV1_80_3norm_top_sumSV12mass.log 2>&1 &

#RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customIP3DSV1_80_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_80_3norm_background_sumSV12mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenIP3DSV1_80_3norm_background_inclusive_sumSV12mass -r 5 -i 50000 > $SRC/results/ensemble/alpgen/IP3DSV1_80/AlpgenIP3DSV1_80_3norm_background_sumSV12mass.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customIP3DSV1_80_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_80_3free_background_sumSV12mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenIP3DSV1_80_3free_background_inclusive_sumSV12mass -r 5 -i 50000 > $SRC/results/ensemble/alpgen/IP3DSV1_80/AlpgenIP3DSV1_80_3free_background_sumSV12mass.log 2>&1 &

#RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customIP3DSV1_80_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_80_3norm_background_sumSV12mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenIP3DSV1_80_3norm_background_inclusive_sumSV12mass_x150 -r 5 -i 25000 -P 150 > $SRC/results/ensemble/alpgen/IP3DSV1_80/AlpgenIP3DSV1_80_3norm_background_sumSV12mass_x150.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customIP3DSV1_80_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_80_3free_background_sumSV12mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenIP3DSV1_80_3free_background_inclusive_sumSV12mass_x150 -r 5 -i 25000 -P 150 > $SRC/results/ensemble/alpgen/IP3DSV1_80/AlpgenIP3DSV1_80_3free_background_sumSV12mass_x150.log 2>&1 &


