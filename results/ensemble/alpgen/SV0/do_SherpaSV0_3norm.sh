RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_top_sumSV0mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o AlpgenSV0_3norm_top -r 5 -i 50000  > $SRC/results/central/AlpgenSV0_3norm_top.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_background_sumSV0mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenSV0_3norm_background -r 5 -i 50000  > $SRC/results/central/AlpgenSV0_3norm_background.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/customSV0_allJets_sumSV0mass.root  -c AlpgenSV0_3norm_background_sumSV0mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenSV0_3norm_background_x200 -r 5 -i 10000 -P 200  > $SRC/results/central/AlpgenSV0_3norm_background_x200.log 2>&1 &


#RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/AlpgenSV0.root  -c AlpgenSV0_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Alpgen_2norm_fixedLight_fixedTop -r 5 -i 15000 > $SRC/results/central/AlpgenSV0_2norm_fixedLight_fixedTop.log 2>&1 &

