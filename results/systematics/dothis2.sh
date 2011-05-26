
echo -e "\n\n DOING trkrew Wbd Wbmu baseline"

RunPseudoExperiments.exe -M Migrad -d $SRC/Lecce_Sherpa_mumu_Systematics.root -c $SRC/results/environments/Lecce/BinnedEML.4params.Sherpa_added_top_Pseudo.env -D "baseline_Mass_DATA" -T "baseline_MC_beauty_fit,baseline_MC_charm_fit,baseline_MC_light_fit,baseline_MC_fit_bckTOT" -o Lecce_trkrew -i 10000 -r 5 -p "trkrew_MC_beauty_fitTOT,trkrew_MC_charm_fitTOT,trkrew_MC_light_fitTOT,trkrew_MC_fit_bckTOT" > trkrew.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/Lecce_Sherpa_mumu_Systematics.root -c $SRC/results/environments/Lecce/BinnedEML.4params.Sherpa_added_top_Pseudo.env -D "baseline_Mass_DATA" -T "baseline_MC_beauty_fit,baseline_MC_charm_fit,baseline_MC_light_fit,baseline_MC_fit_bckTOT" -o Lecce_Wbd -i 10000 -r 5 -p "Wbd_MC_beauty_fit_Wb_dt,Wbd_MC_charm_fit_Wb_dt,Wbd_MC_light_fit_Wb,Wbd_MC_fit_bckTOT" > Wbd.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/Lecce_Sherpa_mumu_Systematics.root -c $SRC/results/environments/Lecce/BinnedEML.4params.Sherpa_added_top_Pseudo.env -D "baseline_Mass_DATA" -T "baseline_MC_beauty_fit,baseline_MC_charm_fit,baseline_MC_light_fit,baseline_MC_fit_bckTOT" -o Lecce_Wbmu -i 10000 -r 5 -p "Wbmu_MC_beauty_fit_Wb,Wbmu_MC_charm_fit_Wb,Wbmu_MC_light_fit_Wb,Wbmu_MC_fit_bckTOT" > Wbmu.log 2>&1 &

RunPseudoExperiments.exe -M Migrad -d $SRC/Lecce_Sherpa_mumu_Systematics.root -c $SRC/results/environments/Lecce/BinnedEML.4params.Sherpa_added_top_Pseudo.env -D "baseline_Mass_DATA" -T "baseline_MC_beauty_fit,baseline_MC_charm_fit,baseline_MC_light_fit,baseline_MC_fit_bckTOT" -o Lecce_baseline -i 10000 -r 5 > baseline.log 2>&1 &

