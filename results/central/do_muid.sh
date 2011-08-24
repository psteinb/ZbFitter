#plain fit
RunFitter.exe -M Migrad -d $SRC/ZeeSherpa_allBackgrounds.root  -c muid.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,Background" -o muid -r 5 -m 6  

#RunFitter.exe -M Migrad -d $SRC/ZmumuSherpa_allBackgrounds.root  -c $SRC/results/environments/SherpaAdded/BinnedEML.2p2params.Sherpa_mumu_allBackgrounds.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,Background" -o Sherpa_2p2Normalisations_mumu_allBackgrounds_paper -r 5 -m 6  


#with goodness-of-fit (need to create argument to -p beforehand)
#RunFitter.exe -M Migrad -d $SRC/Sherpa_added.root  -c $SRC/results/environments/SherpaAdded/BinnedEML.4params.Sherpa_added_top.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar" -o Sherpa_3Normalisations_added_top -r 5 -m 6 -p $SRC/results/central/Sherpa_3Normalisations_added_15k_top_MeansSigmasPullsMaxLLH.root

