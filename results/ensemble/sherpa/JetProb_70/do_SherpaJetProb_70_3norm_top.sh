RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/SherpaJetProb_70.root  -c SherpaJetProb_70_3norm_top.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaJetProb_70_3norm_top -r 5 -i 15000  > $SRC/results/central/SherpaJetProb_70_3norm_top.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/SherpaJetProb_70.root  -c SherpaJetProb_70_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop -r 5 -i 15000 > $SRC/results/central/SherpaJetProb_70_2norm_fixedLight_fixedTop.log 2>&1 &


#RunFitter.exe -M Migrad -d $SRC/Sherpa_mumu.root  -c $SRC/results/environments/Sherpa/BinnedEML.4params.Sherpa_mumu_top.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar" -o Sherpa_3Normalisations_mumu_top -r 5 > $SRC/results/central/Sherpa_3Normalisations_mumu_top.log 2>&1 &
#
#RunFitter.exe -M Migrad -d $SRC/Sherpa_combined.root  -c $SRC/results/environments/Sherpa/BinnedEML.4params.Sherpa_joined_top.env -D "Data_joined" -T "Zjets_b_joined,Zjets_c_joined,Zjets_l_joined,TTbar_joined" -o Sherpa_3Normalisations_joined_top -r 5 > $SRC/results/central/Sherpa_3Normalisations_joined_top.log 2>&1 &
