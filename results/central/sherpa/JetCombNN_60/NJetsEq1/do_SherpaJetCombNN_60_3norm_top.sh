RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaJetCombNN_60_NJetsEq1.root  -c SherpaJetCombNN_60_3norm_top.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o SherpaJetCombNN_60_3norm_top_NJetsEq1 -r 5   > $SRC/results/central/sherpa/JetCombNN_60/NJetsEq1/SherpaJetCombNN_60_3norm_top.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/NJetsEq1/SherpaJetCombNN_60_NJetsEq1.root  -c SherpaJetCombNN_60_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o Sherpa_2norm_fixedLight_fixedTop_NJetsEq1 -r 5   > $SRC/results/central/sherpa/JetCombNN_60/NJetsEq1/SherpaJetCombNN_60_2norm_fixedLight_fixedTop.log 2>&1 &

