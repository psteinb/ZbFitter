
echo "using input files from $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80"

    for file in {AllFlavorsBTagEffDown,AllFlavorsBTagEffUp,HeavyFlavorBTagEffDown,HeavyFlavorBTagEffUp,JER,JESDOWN,JESUP,LightBTagEffDown,LightBTagEffUp,MuonEff,MuonPt,BackgroundUp,BackgroundDown};
    do
	ENVFILE=Sherpa_customIP3DSV1_80_allJets_sumSV12mass_${file}_3norm_background_templVaried.env
	set -x
	
#	RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80/customIP3DSV1_80_allJets_sumSV12mass_${file}.root -c Sherpa_3norm_background_templNominal.env -D "PseudoData_varied" -T "TrueB,TrueC,TrueL,Background" -o DataVaried_Sherpa_3norm_background_templNominal_${file} -r 5 > `pwd`/DataVaried_Sherpa_3norm_background_templNominal_${file}.log 2>&1 &

	BACKFILE=${ENVFILE/.env/}
	RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80/customIP3DSV1_80_allJets_sumSV12mass_${file}.root -c ${ENVFILE} -D "PseudoData" -T "TrueB_varied,TrueC_varied,TrueL_varied,Background_varied" -o ShapeVaried_$BACKFILE -r 5 > `pwd`/ShapeVaried_$BACKFILE.log 2>&1 &

	set +x
    done


if [[ -e $PWD/Sherpa_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background.env ]];then
    RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80/shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal.root -c Sherpa_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background.env -D "PseudoData" -T "TrueB_varied,TrueC_varied,TrueL_varied,Background_varied" -o ShapeVaried_Sherpa_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background -r 5 > `pwd`/ShapeVaried_Sherpa_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background.log 2>&1 &
fi

# RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80/customIP3DSV1_80_allJets_sumSV12mass_JER.root -c Sherpa_3norm_background_templNominal.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Background" -o DataVaried_Sherpa_3norm_background_templNominal_CentralJER -r 5 > `pwd`/DataVaried_Sherpa_3norm_background_templNominal_CentralJER.log 2>&1 &

# RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/customIP3DSV1_80_allJets_sumSV12mass.root -c Sherpa_3norm_background_templNominal.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Background" -o DataVaried_Sherpa_3norm_background_templNominal_StdCentral -r 5 > `pwd`/DataVaried_Sherpa_3norm_background_templNominal_StdCentral.log 2>&1 &