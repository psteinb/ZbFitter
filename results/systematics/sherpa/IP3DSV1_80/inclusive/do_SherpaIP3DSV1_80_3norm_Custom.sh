
echo "using input files from $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80"

    for file in {AllFlavorsBTagEffDown,AllFlavorsBTagEffUp,HeavyFlavorBTagEffDown,HeavyFlavorBTagEffUp,JER,JESDOWN,JESUP,LightBTagEffDown,LightBTagEffUp,MuonEff,MuonPt};
    do
	ENVFILE=Sherpa_customIP3DSV1_80_allJets_sumSV12mass_${file}_3norm_background.env
	set -x
	TOPFILE=InclusivePseudoData_${ENVFILE/.env/}
	#RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80/bundleIP3DSV1_80_allJets_sumSV12mass_${file}.root -c ${ENVFILE} -D "PseudoData" -T "TrueB_varied,TrueC_varied,TrueL_varied,Top_varied" -o $TOPFILE -r 5 > `pwd`/$TOPFILE.log 2>&1 &
	BACKFILE=${TOPFILE//top/background}
	RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80/customIP3DSV1_80_allJets_sumSV12mass_${file}.root -c ${ENVFILE/top/background} -D "PseudoData" -T "TrueB_varied,TrueC_varied,TrueL_varied,Background_varied" -o $BACKFILE -r 5 > `pwd`/$BACKFILE.log 2>&1 &

	set +x
    done


