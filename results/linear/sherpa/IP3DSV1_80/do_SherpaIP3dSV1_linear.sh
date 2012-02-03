
for item in $*;
do
if [[ $item != *.env ]];then
    continue
fi
envId=`echo $item|sed -e 's/.*custom\(.*\)\.env/\1/'`
echo "processing $item (id: ${envId})"
RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/linearity/customIP3DSV1_80_allJets_sumSV12mass_TrueB_scaled.root  -c $item -D "Data" -T "TrueB${envId},TrueC,TrueL,Background" -o ${item/.env/} -r 5 -i 15000  > ${item/.env/.log} 2>&1 &
done
#RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/sherpa/SherpaSV0.root  -c SherpaSV0_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_2norm_fixedLight_fixedTop -r 5 -i 15000 > $SRC/results/central/SherpaSV0_2norm_fixedLight_fixedTop.log 2>&1 &

