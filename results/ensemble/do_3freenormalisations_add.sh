
RunPseudoExperiments.exe -M Migrad -d $SRC/Sherpa_added.root -c $SRC/results/environments/SherpaAdded/BinnedEML.4params.Sherpa_added_top_Pseudo.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar" -o Sherpa_3FreeNormalisations_add_15k_top -i 15000 -r 5 > ./Sherpa_mumu_3normalisations_top.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/Sherpa_added.root -c $SRC/results/environments/SherpaAdded/BinnedEML.4params.Sherpa_added_top_Pseudo.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar" -o Sherpa_3FreeNormalisations_add_15k_top_x100 -i 15000 -r 5 -P 100 > ./Sherpa_mumu_3normalisations_top.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/Sherpa_added.root -c $SRC/results/environments/SherpaAdded/BinnedEML.4params.Sherpa_added_top_QCD_Pseudo.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar,QCD" -o Sherpa_3FreeNormalisations_add_15k_top_QCD -i 15000 -r 5 > ./Sherpa_mumu_3normalisations_top_QCD.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/Sherpa_added.root -c $SRC/results/environments/SherpaAdded/BinnedEML.4params.Sherpa_added_top_QCD_Pseudo.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar,QCD" -o Sherpa_3FreeNormalisations_add_15k_top_QCD_x100 -i 15000 -r 5 -P 100 > ./Sherpa_mumu_3normalisations_top_QCD.log 2>&1 &


