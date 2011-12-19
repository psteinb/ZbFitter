RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/AlpgenSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_top_allJets_sumSV0mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o AlpgenSV0_3norm_top_inclusive_allJets_sumSV0mass -r 5 > $SRC/results/central/alpgen/SV0/inclusive/AlpgenSV0_3norm_top_inclusive_allJets_sumSV0mass.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/AlpgenSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_top_allJets_sumSV0mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o AlpgenSV0_3norm_top_inclusive_allJets_sumSV0mass_PseudoData -r 5 > $SRC/results/central/alpgen/SV0/inclusive/AlpgenSV0_3norm_top_inclusive_allJets_sumSV0mass_PseudoData.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/AlpgenSV0_maxSV0mass.root  -c AlpgenSV0_3norm_top_maxSV0mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o AlpgenSV0_3norm_top_inclusive_maxSV0mass -r 5 > $SRC/results/central/alpgen/SV0/inclusive/AlpgenSV0_3norm_top_inclusive_maxSV0mass.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/AlpgenSV0_maxSV0mass.root  -c AlpgenSV0_3norm_top_maxSV0mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o AlpgenSV0_3norm_top_inclusive_maxSV0mass_PseudoData -r 5 > $SRC/results/central/alpgen/SV0/inclusive/AlpgenSV0_3norm_top_inclusive_maxSV0mass_PseudoData.log 2>&1 &


