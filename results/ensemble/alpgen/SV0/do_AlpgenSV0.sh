##RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_top_sumSV0mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o AlpgenSV0_3norm_top -r 5 -i 50000  > $SRC/results/central/AlpgenSV0_3norm_top.log 2>&1 &

#RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_background_sumSV0mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenSV0_3norm_background -r 5 -i 50000  > $SRC/results/central/AlpgenSV0_3norm_background.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3free_background_sumSV0mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenSV0_3free_background -r 5 -i 50000  > $SRC/results/central/AlpgenSV0_3free_background.log 2>&1 &


#RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_background_sumSV0mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenSV0_3norm_background_x150 -r 5 -i 25000 -P 150  > $SRC/results/central/AlpgenSV0_3norm_background_x150.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3free_background_sumSV0mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenSV0_3free_background_x150 -r 5 -i 25000 -P 150  > $SRC/results/central/AlpgenSV0_3free_background_x150.log 2>&1 &



