
NUM_REPEATS=10000
RELATIVE_TOLERANCE=0.001   # 0.1%

HEAD=/usr/bin/head
CUT=/usr/bin/cut

WRAPPER=./stochastic-testsuite

# go over all models in tests/model-list
MODELS=`cat tests/model-list`

function getSpecies()
{
    $HEAD -n1 $1 | $CUT -d ',' -f 2- --output-delimiter=" ";
}


for MODEL in $MODELS;do
  # set parameters 
  ENDTIME=50
  STEPNUMBER=50
  INFILE=${MODEL}.xml
  OUTFILE=${MODEL}.RESULT
  MEAN_OUTFILE=${MODEL}-mean.RESULT
  SD_OUTFILE=${MODEL}-sd.RESULT
  SPECIESLIST=`getSpecies tests/${MODEL}-mean.csv`
  # run simulation 
  echo "$WRAPPER $INFILE $ENDTIME $STEPNUMBER $NUM_REPEATS $SPECIESLIST"
  # calculate mean and standard deviation
  echo "./calculate_statistics.py $OUTFILE $MEAN_OUTFILE $SD_OUTFILE $STEPNUMBER $NUM_REPEATS"
  # compare results
  echo "./compare_results.sh ${MODEL}-mean.csv ${MODEL}-mean.RESULT $RELATIVE_TOLERANCE"
  echo "./compare_results.sh ${MODEL}-sd.csv ${MODEL}-sd.RESULT $RELATIVE_TOLERANCE"

done
