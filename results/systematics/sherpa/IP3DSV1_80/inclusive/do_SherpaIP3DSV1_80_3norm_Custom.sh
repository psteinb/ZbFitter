
echo "using input files from $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80"

    for file in {AllFlavorsBTagEffDown,AllFlavorsBTagEffUp,HeavyFlavorBTagEffDown,HeavyFlavorBTagEffUp,JER,JESDOWN,JESUP,LightBTagEffDown,LightBTagEffUp,MuonEff,MuonPt};
    do
	ENVFILE=Sherpa_customIP3DSV1_80_allJets_sumSV12mass_${file}_3norm_background.env
	set -x
	TOPFILE=InclusivePseudoData_${ENVFILE/.env/}
	RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80/bundleIP3DSV1_80_allJets_sumSV12mass_${file}.root -c Sherpa_3norm_background_templNominal.env -D "PseudoData_varied" -T "TrueB,TrueC,TrueL,Top" -o Sherpa_3norm_background_templNominal_${file} -r 5 > `pwd`/Sherpa_3norm_background_templNominal_${file}.log 2>&1 &
	BACKFILE=${TOPFILE//top/background}
	RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80/customIP3DSV1_80_allJets_sumSV12mass_${file}.root -c ${ENVFILE/top/background} -D "PseudoData" -T "TrueB_varied,TrueC_varied,TrueL_varied,Background_varied" -o $BACKFILE -r 5 > `pwd`/$BACKFILE.log 2>&1 &

	set +x
    done


if [[ -e $PWD/Sherpa_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background.env ]];then
    RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80/shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal.root -c Sherpa_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background.env -D "PseudoData" -T "TrueB_varied,TrueC_varied,TrueL_varied,Background_varied" -o Sherpa_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background -r 5 > `pwd`/Sherpa_shapeIP3DSV1_80_allJets_sumSV12mass_AltSignal_3norm_background.log 2>&1 &
fi