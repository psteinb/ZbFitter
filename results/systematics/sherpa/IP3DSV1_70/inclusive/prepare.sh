

if [[ -n $1 ]];then
    for file in $*;do
	FILENAME=`basename $file`
	echo "python $SRC/python/printEnvFile.py -f $file -3 -N 'TrueB_varied,TrueC_varied,TrueL_varied,Top_varied'"
	python $SRC/python/printEnvFile.py -f $file -3 -N "TrueB_varied,TrueC_varied,TrueL_varied,Top_varied"|egrep "^[A-Za-z]" > Sherpa_${FILENAME/.cfg/}_3norm_top.env
    done
else
    echo "no input files given"
fi