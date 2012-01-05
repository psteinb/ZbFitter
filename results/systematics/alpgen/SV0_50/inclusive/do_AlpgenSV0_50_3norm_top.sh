
echo "using input files from $SRC/bundles/sherpa/inclusive/systematics/SV0_50"

if [[ -n ${1} ]];then
    
    for file in {AllFlavorsBTagEffDown,AllFlavorsBTagEffUp,HeavyFlavorBTagEffDown,HeavyFlavorBTagEffUp,JER,JESDOWN,JESUP,LightBTagEffDown,LightBTagEffUp,MuonEff,MuonPt};
    do
	ENVFILE=Alpgen_bundleSV0_50_allJets_sumSV12mass_${file}_3norm_top.env
	RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/systematics/SV0_50/bundleSV0_50_allJets_sumSV12mass_${file}.root -c  -D "Data" -T "TrueB_varied,TrueC_varied,TrueL_varied,Top_varied" -o Inclusive_${ENVFILE/.env/} -r 5 > `pwd`/${ENVFILE/.env/.log} 2>&1 &
    else
	echo "inputfile not found $DATAFILE"
    fi
    done

else
    echo "not input file given"
fi


