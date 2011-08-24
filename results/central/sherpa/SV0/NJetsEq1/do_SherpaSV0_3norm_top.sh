RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaSV0_NJetsEq1.root  -c SherpaSV0_3norm_top.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_3Normalisations_ee_top -r 5 > $SRC/results/central/sherpa/SV0/NJetsEq1/SherpaSV0_3norm_top.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaSV0_NJetsEq1.root  -c SherpaSV0_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop -r 5 > $SRC/results/central/sherpa/SV0/NJetsEq1/SherpaSV0_2norm_fixedLight_fixedTop.log 2>&1 &

