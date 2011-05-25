RunPseudoExperiments.exe -M Migrad -d $SRC/Sherpa_ee.root -c $SRC/results/environments/Sherpa/BinnedEML.4params.Sherpa_ee_top.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar" -o Sherpa_3Normalisations_ee_15k_top -i 15000 -r 5 > ./Sherpa_ee_3normalisations_top.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/Sherpa_mumu.root -c $SRC/results/environments/Sherpa/BinnedEML.4params.Sherpa_mumu_top.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar" -o Sherpa_3Normalisations_mumu_15k_top -i 15000 -r 5 > ./Sherpa_mumu_3normalisations_top.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/Sherpa_combined.root -c $SRC/results/environments/Sherpa/BinnedEML.4params.Sherpa_joined_top.env -D "Data_joined" -T "Zjets_b_joined,Zjets_c_joined,Zjets_l_joined,TTbar_joined" -o Sherpa_3Normalisations_joined_15k_top -i 15000 -r 5 > ./Sherpa_joined_3normalisations_top.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/Sherpa_mumu.root -c $SRC/results/environments/Sherpa/BinnedEML.4params.Sherpa_mumu_top_x100.env -D "Data" -T "Zjets_b,Zjets_c,Zjets_l,TTbar" -o Sherpa_3Normalisations_mumu_15k_top_x100 -i 15000 -r 5 -P 100 > ./Sherpa_mumu_3normalisations_top_x100.log 2>&1 &
