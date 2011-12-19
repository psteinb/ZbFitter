
echo "using input files from $SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_70"

if [[ $# > 0 ]];then
    
    for file in $*;done
    ENVFILE=`basename $file`
    ENVFILE=${ENVFILE/Sherpa_/}
    ENVFILE=${ENVFILE/_3norm_top.env/}
    DATAFILE=$SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_70/*${ENVFILE}
    if [[ -f $DATAFILE ]];then
	echo "using "
	echo -e "\tinput:\t $DATAFILE"
	echo -e "\tenv:  \t $ENVFILE"
	RunFitter.exe -M Migrad -d $DATAFILE  -c $ENVFILE -D "Data" -T "TrueB_varied,TrueC_varied,TrueL_varied,Top_varied" -o Inclusive_${ENVFILE/.env/} -r 5 > `pwd`/${ENVFILE/.env/.log} 2>&1 &
    else
	echo "inputfile not found $DATAFILE"
    fi
    done

else
    echo "not input file given"
fi


