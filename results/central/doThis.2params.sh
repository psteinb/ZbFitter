#IKTP
RunFitter.exe -M Migrad -d ./extractedSV0.root -c /amnt/remote/pkthafc.home/psteinb/development/sandbox/fitter/results/central/BinnedEML.2params.env -D "data_muid" -T "z_muid_trueB,z_muid_trueCpL" -o muid.2params -r 5 -m 1 > fit.Sherpa.log 2>&1 &

#UCL
RunFitter.exe -M Migrad -d $SRC/AlpgenZmumuJetVertexMassByFlav.root  -c /amnt/remote/pkthafc.home/psteinb/development/sandbox/fitter/results/central/BinnedEML.2params.env -D "Data" -T "MC_Signal_B,MC_Signal_CpL" -o UCL.2params -r 10 -m 1 -P UCL.10k__MeansSigmasPullsMaxLLH.root > $SRC/results/central/fit.Alpgen.log 2>&1 &
RunFitter.exe -M Migrad -d $SRC/AlpgenZeeJetVertexMassByFlav.root  -c /amnt/remote/pkthafc.home/psteinb/development/sandbox/fitter/results/central/BinnedEML.2params.env -D "Data" -T "MC_Signal_B,MC_Signal_CpL" -o UCL.2params.ee -r 10 -m 1 -P UCL.10k_ee_MeansSigmasPullsMaxLLH.root> $SRC/results/central/fit.Alpgen.ee.log 2>&1 &

#Saclay
RunFitter.exe -M Migrad -d /amnt/remote/pkthafc.home/psteinb/development/sandbox/fitter/Saclay_mumu.root  -c /amnt/remote/pkthafc.home/psteinb/development/sandbox/fitter/results/central/BinnedEML.Alpgen.env -D "data" -T "mcb,mccpl" -o Saclay.2params -r 5 -m 1 -P Saclay.10k__MeansSigmasPullsMaxLLH.root > $SRC/results/central/fit.Saclay.mumu.log 2>&1 &
RunFitter.exe -M Migrad -d /amnt/remote/pkthafc.home/psteinb/development/sandbox/fitter/Saclay_ee.root  -c /amnt/remote/pkthafc.home/psteinb/development/sandbox/fitter/results/central/BinnedEML.Alpgen.env -D "data" -T "mcb,mccpl" -o Saclay.2params.ee -r 5 -m 1 -P Saclay.10k_ee_MeansSigmasPullsMaxLLH.root> $SRC/results/central/fit.Saclay.ee.log 2>&1 &
