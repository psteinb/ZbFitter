RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customIP3DSV1_70_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_70_3norm_top_sumSV12mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_70_3norm_top_inclusive_sumSV12mass_custom -r 5 > $SRC/results/central/alpgen/IP3DSV1_70/inclusive/AlpgenIP3DSV1_70_3norm_top_inclusive_sumSV12mass_custom.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customIP3DSV1_70_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_70_3norm_background_sumSV12mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenIP3DSV1_70_3norm_background_inclusive_sumSV12mass_custom -r 5 > $SRC/results/central/alpgen/IP3DSV1_70/inclusive/AlpgenIP3DSV1_70_3norm_background_inclusive_sumSV12mass_custom.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customIP3DSV1_70_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_70_3norm_top_sumSV12mass_custom.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_70_3norm_top_inclusive_sumSV12mass_custom_PseudoData -r 5 > $SRC/results/central/alpgen/IP3DSV1_70/inclusive/AlpgenIP3DSV1_70_3norm_top_inclusive_sumSV12mass_custom_PseudoData.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customIP3DSV1_70_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_70_3norm_background_sumSV12mass_custom.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Background" -o AlpgenIP3DSV1_70_3norm_background_inclusive_sumSV12mass_custom_PseudoData -r 5 > $SRC/results/central/alpgen/IP3DSV1_70/inclusive/AlpgenIP3DSV1_70_3norm_background_inclusive_sumSV12mass_custom_PseudoData.log 2>&1 &


