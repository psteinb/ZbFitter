#!/bin/bash
if [[ -n $1 ]];then
    BASEDIR=`dirname $1`
    BASEFILE=$BASEDIR/collect.cfg
    for file in $*;
    do 
	if [[ -f $file && $file == *root ]];then
	    FILEID=`echo $file|sed -e 's/.*custom\(.*\)_Means.*/\1/g'`
	    XVALUE="1."
	    if [[ -n $FILEID ]];then
		XVALUE=`echo ${FILEID/_/}|sed -e 's/d/./g'`
	    fi
	    echo -e "[Scaled${FILEID}]\nhist = ${file}:mean_par0\nextractor=MeanExtractor()\nxvalue=${XVALUE}\n\n"
	else
	    continue
	fi
    done > $BASEFILE

    cp $BASEFILE ${BASEFILE/.cfg/MeanAndMeanRMS.cfg}
    cp $BASEFILE ${BASEFILE/.cfg/MeanAndSigmaMean.cfg}
    sed -i -e 's/MeanExtractor/MeanUncFromHiddenExtractor/g' ${BASEFILE/.cfg/MeanAndSigmaMean.cfg}
    
    for cfg in ${BASEDIR}/*{AndMeanRMS,AndSigmaMean}.cfg;
    do
	python /home/psteinb/development/sandbox/fitter/python/collectNumbersToTGraph.py -f $cfg -o ${cfg/cfg/root} > ${cfg/cfg/log} 2>&1 &
    done
    
else
    echo "usage: $0 <root files to process>"
    echo "dumps collect.cfg in path of first file"
fi