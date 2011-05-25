RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/Sherpa_ee.root -c $SRC/results/environments/Sherpa/BinnedEMLFraction.1o3.Sherpa_ee_top.env -D "Data" -T "Zjets_b,Zjets_l,TTbar,Zjets_c" -o Sherpa_3fractionfit_ee_15k_top -i 15000 -r 5 > ./Sherpa_ee_3fractionfit_top.log 2>&1 &

RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/Sherpa_mumu.root -c $SRC/results/environments/Sherpa/BinnedEMLFraction.1o3.Sherpa_mumu_top.env -D "Data" -T "Zjets_b,Zjets_l,TTbar,Zjets_c" -o Sherpa_3fractionfit_mumu_15k_top -i 15000 -r 5 > ./Sherpa_mumu_3fractionfit_top.log 2>&1 &

RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/Sherpa_mumu.root -c $SRC/results/environments/Sherpa/BinnedEMLFraction.1o3.Sherpa_mumu_top.env -D "Data" -T "Zjets_b,Zjets_l,TTbar,Zjets_c" -o Sherpa_3fractionfit_mumu_15k_top_x100 -i 15000 -r 5 -P 100 > ./Sherpa_mumu_3fractionfit_top_x100.log 2>&1 &


RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/Sherpa_combined.root -c $SRC/results/environments/Sherpa/BinnedEMLFraction.1o3.Sherpa_joined_top.env -D "Data_joined" -T "Zjets_b_joined,Zjets_l_joined,TTbar_joined,Zjets_c_joined" -o Sherpa_3fractionfit_joined_15k_top -i 15000 -r 5 > ./Sherpa_joined_3fractionfit_top.log 2>&1 &
