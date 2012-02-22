
echo "using input files from $SRC/bundles/alpgen/inclusive/systematics/IP3DSV1_80"

    for file in {AllFlavorsBTagEffDown,AllFlavorsBTagEffUp,HeavyFlavorBTagEffDown,HeavyFlavorBTagEffUp,JER,JESDOWN,JESUP,LightBTagEffDown,LightBTagEffUp,MuonEff,MuonPt,BackgroundUp,BackgroundDown};
    do
	ENVFILE=Alpgen_customIP3DSV1_80_allJets_sumSV12mass_${file}_3norm_background_templVaried.env
	set -x
	
#	RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/systematics/IP3DSV1_80/customIP3DSV1_80_allJets_sumSV12mass_${file}.root -c Alpgen_3norm_background_templNominal.env -D "PseudoData_varied" -T "TrueB,TrueC,TrueL,Top" -o DataVaried_Alpgen_3norm_background_templNominal_${file} -r 5 > `pwd`/DataVaried_Alpgen_3norm_background_templNominal_${file}.log 2>&1 &

	BACKFILE=${ENVFILE/.env/}
	RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/systematics/IP3DSV1_80/customIP3DSV1_80_allJets_sumSV12mass_${file}.root -c ${ENVFILE} -D "PseudoData" -T "TrueB_varied,TrueC_varied,TrueL_varied,Background_varied" -o ShapeVaried_$BACKFILE -r 5 > `pwd`/ShapeVaried_$BACKFILE.log 2>&1 &

	set +x
    done


if [[ -e $PWD/Alpgen_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background_templVaried.env ]];then
    RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/systematics/IP3DSV1_80/shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal.root -c Alpgen_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background.env -D "PseudoData" -T "TrueB_varied,TrueC_varied,TrueL_varied,Background_varied" -o ShapeVaried_Alpgen_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background -r 5 > `pwd`/ShapeVaried_Alpgen_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background.log 2>&1 &
fi
