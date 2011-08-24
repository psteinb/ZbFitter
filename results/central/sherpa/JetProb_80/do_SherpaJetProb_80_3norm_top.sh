RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/SherpaJetProb_80.root  -c SherpaJetProb_80_3norm_top.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaJetProb_80_3norm_top -r 5  > $SRC/results/central/SherpaJetProb_80_3norm_top.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/SherpaJetProb_80.root  -c SherpaJetProb_80_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop -r 5 > $SRC/results/central/SherpaJetProb_80_2norm_fixedLight_fixedTop.log 2>&1 &

