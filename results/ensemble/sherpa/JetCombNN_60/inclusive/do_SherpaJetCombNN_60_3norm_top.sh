RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaJetCombNN_60.root  -c SherpaJetCombNN_60_3norm_top.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaJetCombNN_60_3norm_top_inclusive -r 5 -i 15000  > $SRC/results/ensemble/sherpa/JetCombNN_60/inclusive/SherpaJetCombNN_60_3norm_top.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaJetCombNN_60.root  -c SherpaJetCombNN_60_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_inclusive -r 5 -i 15000  > $SRC/results/ensemble/sherpa/JetCombNN_60/inclusive/SherpaJetCombNN_60_2norm_fixedLight_fixedTop.log 2>&1 &

