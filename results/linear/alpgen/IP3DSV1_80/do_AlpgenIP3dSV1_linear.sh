
for item in $*;
do
if [[ $item != *.env ]];then
    continue
fi
envId=`echo $item|sed -e 's/.*custom\(.*\)\.env/\1/'`
echo "processing $item (id: ${envId})"
RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/linearity/customIP3DSV1_80_allJets_sumSV12mass_TrueB_scaled.root  -c $item -D "Data" -T "TrueB${envId},TrueC,TrueL,Background" -o ${item/.env/} -r 5 -i 15000  > ${item/.env/.log} 2>&1 &
RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/linearity/customIP3DSV1_80_allJets_sumSV12mass_TrueB_scaled.root  -c $item -D "Data" -T "TrueB${envId},TrueC,TrueL,Background" -o ${item/.env/_x200} -r 5 -i 15000 -P 200  > ${item/.env/_x200.log} 2>&1 &

done
#RunPseudoExperiments.exe -M Migrad -d $SRC/bundles/alpgen/AlpgenSV0.root  -c AlpgenSV0_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Alpgen_2norm_fixedLight_fixedTop -r 5 -i 15000 > $SRC/results/central/AlpgenSV0_2norm_fixedLight_fixedTop.log 2>&1 &

