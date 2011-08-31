RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaJetCombNN_70.root  -c SherpaJetCombNN_70_3norm_top.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaJetCombNN_70_3norm_top_inclusive -r 5 > $SRC/results/central/sherpa/JetCombNN_70/inclusive/SherpaJetCombNN_70_3norm_top.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaJetCombNN_70.root  -c SherpaJetCombNN_70_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_inclusive -r 5 > $SRC/results/central/sherpa/JetCombNN_70/inclusive/SherpaJetCombNN_70_2norm_fixedLight_fixedTop.log 2>&1 &


RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaJetCombNN_70.root  -c SherpaJetCombNN_70_3norm_top.env -D "MC" -T "TrueB,TrueC,TrueL,Top" -o SherpaJetCombNN_70_3norm_top_inclusive_withMC -r 5 > $SRC/results/central/sherpa/JetCombNN_70/inclusive/SherpaJetCombNN_70_3norm_top_withMC.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaJetCombNN_70.root  -c SherpaJetCombNN_70_2norm_fixedLight_fixedTop.env -D "MC" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop_inclusive_withMC -r 5 > $SRC/results/central/sherpa/JetCombNN_70/inclusive/SherpaJetCombNN_70_2norm_fixedLight_fixedTop_withMC.log 2>&1 &
