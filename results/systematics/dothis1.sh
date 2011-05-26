
echo -e "\n\n DOING BTAGdown,BTAGup,JESUdown,JESUup"
for sys in {"BTAGdown","BTAGup","JESUdown","JESUup"};do
    set -x
    (RunPseudoExperiments.exe -M Migrad -d $SRC/Lecce_Sherpa_mumu_Systematics.root -c $SRC/results/environments/Lecce/BinnedEML.4params.Sherpa_added_top_Pseudo.env -D "baseline_Mass_DATA" -T "baseline_MC_beauty_fit,baseline_MC_charm_fit,baseline_MC_light_fit,baseline_MC_fit_bckTOT" -o Lecce_${sys} -i 10000 -r 5 -p "${sys}_MC_beauty_fit,${sys}_MC_charm_fit,${sys}_MC_light_fit,${sys}_MC_fit_bckTOT" > ${sys}.log 2>&1 &)
    set +x
done
