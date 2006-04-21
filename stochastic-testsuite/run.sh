
NUM_REPEATS=10

HEAD=/usr/bin/head
CUT=/usr/bin/cut

#HEAD=/sw/bin/head
#CUT=/sw/bin/cut

WRAPPER=./stochastic-testsuite

#WRAPPER=`pwd`/stochastic-testsuite.app/Contents/MacOS/stochastic-testsuite

# go over all models in tests/model-list
#MODELS=`cat tests/model-list`

MODELS=`cat $1` 

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
  $WRAPPER $INFILE $ENDTIME $STEPNUMBER $NUM_REPEATS $OUTFILE $SPECIESLIST
  # calculate mean and standard deviation
  ./calculate_statistics.py $OUTFILE $MEAN_OUTFILE $SD_OUTFILE $STEPNUMBER $NUM_REPEATS
  # compare results
  ./compare_mean.py ${MODEL}-mean.RESULT ${MODEL}-mean.csv ${MODEL}-sd.csv $NUM_REPEATS ${MODEL}-mean-compare.RESULT 
  ./compare_sd.py ${MODEL}-sd.RESULT {MODEL}-sd.csv $NUM_REPEATS ${MODEL}-sd-compare.RESULT
done
