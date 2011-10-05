CNT=0
TOTALCNT=`find $SRC/bundles/sherpa/inclusive/systematics/correlations/ -name "*root"|wc -l`
for file in $SRC/bundles/sherpa/inclusive/systematics/correlations/*root;do
    CNT=$((CNT + 1 ))
    FILECORE=`basename $file .root`
    ENVFILE=${file/.root/.env}
    OUTFILE=ThreeFit_$FILECORE
    LOGFILE=ThreeFit_${FILECORE}.log
    echo ">> processing fit ${CNT} / ${TOTALCNT}"
    (RunFitter.exe -M Migrad -d $file  -c $ENVFILE -D "PseudoData" -T "TrueB_varied,TrueC_varied,TrueL_varied,Top_varied" -o $OUTFILE -r 5 > $LOGFILE 2>&1)
done



