RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/customSV0_allJets_sumSV0mass.root  -c SherpaSV0_3norm_top_sumSV0mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaSV0_3norm_top -r 5 -i 15000  > $SRC/results/central/SherpaSV0_3norm_top.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/customSV0_allJets_sumSV0mass.root  -c SherpaSV0_3norm_background_sumSV0mass_custom.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o SherpaSV0_3norm_background -r 5 -i 15000  > $SRC/results/central/SherpaSV0_3norm_background.log 2>&1 &

#RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/SherpaSV0.root  -c SherpaSV0_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop -r 5 -i 15000 > $SRC/results/central/SherpaSV0_2norm_fixedLight_fixedTop.log 2>&1 &

