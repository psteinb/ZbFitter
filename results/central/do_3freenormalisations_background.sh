#plain fit
RunFitter.exe -M Migrad -d $SRC/ZllSherpa_allBackgrounds_added.root  -c $SRC/results/environments/SherpaAdded/BinnedEML.4params.Sherpa_added_allBackgrounds.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,Background" -o Sherpa_3Normalisations_added_allBackgrounds -r 5 -m 6  

#with goodness-of-fit (need to create argument to -p beforehand)
#RunFitter.exe -M Migrad -d $SRC/Sherpa_added.root  -c $SRC/results/environments/SherpaAdded/BinnedEML.4params.Sherpa_added_top.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar" -o Sherpa_3Normalisations_added_top -r 5 -m 6 -p $SRC/results/central/Sherpa_3Normalisations_added_15k_top_MeansSigmasPullsMaxLLH.root

