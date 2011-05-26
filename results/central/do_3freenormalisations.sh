RunFitter.exe -M Migrad -d $SRC/Sherpa_added.root  -c $SRC/results/environments/SherpaAdded/BinnedEML.4params.Sherpa_added_top_QCD.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar,QCD" -o Sherpa_3Normalisations_added_top_QCD -r 5 -m 6  

RunFitter.exe -M Migrad -d $SRC/Sherpa_added.root  -c $SRC/results/environments/SherpaAdded/BinnedEML.4params.Sherpa_added_top.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar" -o Sherpa_3Normalisations_added_top -r 5 -m 6 -p $SRC/results/central/Sherpa_3Normalisations_added_15k_top_MeansSigmasPullsMaxLLH.root

