set -x

RunPseudoExperiments.exe -M Migrad -d $SRC/results/ensemble/extractedSV0.root -c $SRC/results/ensemble/BinnedEML.env -D "data_muid" -T "z_muid_trueB,z_muid_trueCpL" -o results.10k_ -i 10000 -r 5 > $SRC/results/ensemble/runPseudo.10k.log 2>&1 &

#SACLAY
RunPseudoExperiments.exe -M Migrad -d /home/psteinb/development/sandbox/ZbFitter/Saclay_ee.root -c /home/psteinb/development/sandbox/ZbFitter/results/ensemble/BinnedEML.2params.env -D "data" -T "mcb,mccpl" -o Saclay.10k_ee -i 10000 -r 5 > Saclay.10k.ee.2.log 2>&1 &
RunPseudoExperiments.exe -M Migrad -d /home/psteinb/development/sandbox/ZbFitter/Saclay_mumu.root -c /home/psteinb/development/sandbox/ZbFitter/results/ensemble/BinnedEML.2params.env -D "data" -T "mcb,mccpl" -o Saclay.10k_ -i 10000 -r 5 > Saclay.10k.2.log 2>&1 &

#UCL
RunPseudoExperiments.exe -M Migrad -d /home/psteinb/development/sandbox/ZbFitter/AlpgenZeeJetVertexMassByFlav.root -c /home/psteinb/development/sandbox/ZbFitter/results/ensemble/BinnedEML.2params.env -D "Data" -T "MC_Signal_B,MC_Signal_CpL" -o UCL.10k_ee -i 10000 -r 5 > UCL.10k.ee.2.log 2>&1 &
RunPseudoExperiments.exe -M Migrad -d /home/psteinb/development/sandbox/ZbFitter/AlpgenZmumuJetVertexMassByFlav.root -c /home/psteinb/development/sandbox/ZbFitter/results/ensemble/BinnedEML.2params.env -D "Data" -T "MC_Signal_B,MC_Signal_CpL" -o UCL.10k_ -i 10000 -r 5 > UCL.10k.2.log 2>&1 &


set +x


