#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_top_custom_sumSV0mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o AlpgenSV0_3norm_top_inclusive_custom_sumSV0mass -r 5 > $SRC/results/central/alpgen/SV0/inclusive/AlpgenSV0_3norm_top_inclusive_custom_sumSV0mass.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_top_custom_sumSV0mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o AlpgenSV0_3norm_top_inclusive_custom_sumSV0mass_PseudoData -r 5 > $SRC/results/central/alpgen/SV0/inclusive/AlpgenSV0_3norm_top_inclusive_custom_sumSV0mass_PseudoData.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_background_custom_sumSV0mass.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenSV0_3norm_background_inclusive_custom_sumSV0mass -r 5 > $SRC/results/central/alpgen/SV0/inclusive/AlpgenSV0_3norm_background_inclusive_custom_sumSV0mass.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_background_custom_sumSV0mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Background" -o AlpgenSV0_3norm_background_inclusive_custom_sumSV0mass_PseudoData -r 5 > $SRC/results/central/alpgen/SV0/inclusive/AlpgenSV0_3norm_background_inclusive_custom_sumSV0mass_PseudoData.log 2>&1 &


