RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/Saclay_ee.root -c $SRC/results/environments/BinnedEMLFraction.Saclay_ee.1fixed1omitted.env -D "data" -T "mcb,mcl,mcc" -o Saclay_3to1Fractions_ee_15k -i 15000 -r 5 > $SRC/results/ensemble/Saclay_3to1Fractions_ee_15k.log 2>&1 &
RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/Saclay_mumu.root -c $SRC/results/environments/BinnedEMLFraction.Saclay_mumu.1fixed1omitted.env -D "data" -T "mcb,mcl,mcc" -o Saclay_3to1Fractions_mumu_15k -i 15000 -r 5 > $SRC/results/ensemble/Saclay_3to1Fractions_mumu_15k.log 2>&1 &

RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/Saclay_ee.root -c $SRC/results/environments/BinnedEMLFraction.Saclay_ee.1fixed1omitted.env -D "data" -T "mcb,mcl,mcc" -o Saclay_3to1Fractions_ee_15k_x100 -i 15000 -r 5 -P 100 > $SRC/results/ensemble/Saclay_3to1Fractions_ee_15k_x100.log 2>&1 &
RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/Saclay_mumu.root -c $SRC/results/environments/BinnedEMLFraction.Saclay_mumu.1fixed1omitted.env -D "data" -T "mcb,mcl,mcc" -o Saclay_3to1Fractions_mm_15k_x100 -i 15000 -r 5 -P 100 > $SRC/results/ensemble/Saclay_3to1Fractions_mm_15k_x100.log 2>&1 &

RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/AlpgenZmumuJetVertexMassByFlav.root -c $SRC/results/environments/BinnedEMLFraction.UCL_mumu.1fixed1omitted.env -D "Data" -T "MC_Signal_B,MC_Signal_L,MC_Signal_C" -o UCL_3to1Fractions_mumu_15k -i 15000 -r 5 > $SRC/results/ensemble/UCL_3to1Fractions_mumu_15k.log 2>&1 &
RunPseudoExperimentsOnFractions.exe -M Migrad -d $SRC/AlpgenZeeJetVertexMassByFlav.root -c $SRC/results/environments/BinnedEMLFraction.UCL_ee.1fixed1omitted.env -D "Data" -T "MC_Signal_B,MC_Signal_L,MC_Signal_C" -o UCL_3to1Fractions_ee_15k -i 15000 -r 5 > $SRC/results/ensemble/UCL_3to1Fractions_ee_15k.log 2>&1 &