RunFitterOnFractions.exe -M Migrad -d $SRC/Sherpa_ee.root  -c $SRC/results/environments/Sherpa/BinnedEMLFraction.1o3.Sherpa_ee_top.env -D "Data" -T "Zjets_b,Zjets_l,TTbar,Zjets_c" -o Sherpa_3fractionfit_ee_top -r 5 > $SRC/results/central/Sherpa_3fractionfit_ee_top.log 2>&1 &

RunFitterOnFractions.exe -M Migrad -d $SRC/Sherpa_mumu.root  -c $SRC/results/environments/Sherpa/BinnedEMLFraction.1o3.Sherpa_mumu_top.env -D "Data" -T "Zjets_b,Zjets_l,TTbar,Zjets_c" -o Sherpa_3fractionfit_mumu_top -r 5 > $SRC/results/central/Sherpa_3fractionfit_mumu_top.log 2>&1 &

RunFitterOnFractions.exe -M Migrad -d $SRC/Sherpa_combined.root  -c $SRC/results/environments/Sherpa/BinnedEMLFraction.1o3.Sherpa_joined_top.env -D "Data_joined" -T "Zjets_b_joined,Zjets_l_joined,TTbar_joined,Zjets_c_joined" -o Sherpa_3fractionfit_joined_top -r 5 > $SRC/results/central/Sherpa_3fractionfit_joined_top.log 2>&1 &

