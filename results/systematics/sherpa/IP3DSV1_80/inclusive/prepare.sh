
TARGETS=0
DEFAULTPATH=$SRC/bundles/sherpa/inclusive/systematics/IP3DSV1_80/
if [[ -z $1 ]];then
    echo "no input given, using files from $DEFAULTPATH"
    TARGETS=`find $DEFAULTPATH/ -iname "custom*root"`
    TARGETS="${TARGETS} `find $DEFAULTPATH/ -iname "shape*root"`"
else
    TARGETS=$*
fi

echo "running on"
echo $TARGETS
echo 


for file in $TARGETS;do
    FILENAME=`basename $file`
    # echo "python $SRC/python/printEnvFile.py -f $file -3 -N 'TrueB_varied,TrueC_varied,TrueL_varied,Top_varied'"
    # python $SRC/python/printEnvFile.py -f $file -3 -N "TrueB_varied,TrueC_varied,TrueL_varied,Top_varied"|egrep "^[A-Za-z]" > Sherpa_${FILENAME/.root/}_3norm_top.env
    echo "python $SRC/python/printEnvFile.py -f $file -3 -N 'TrueB_varied,TrueC_varied,TrueL_varied,Background_varied'"
    python $SRC/python/printEnvFile.py -f $file -3 -N "TrueB_varied,TrueC_varied,TrueL_varied,Background_varied"|egrep "^[A-Za-z]" > Sherpa_${FILENAME/.root/}_3norm_background.env
    
done

