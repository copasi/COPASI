#!/bin/bash 

NUM_REPEATS=1000

TESTSDIR=./tests

#HEAD=/usr/bin/head
#CUT=/usr/bin/cut
#SED=/usr/bin/sed

HEAD=/sw/bin/head
CUT=/sw/bin/cut
SED=/sw/bin/sed

#WRAPPER=./stochastic-testsuite

WRAPPER=`pwd`/stochastic-testsuite.app/Contents/MacOS/stochastic-testsuite

# go over all models in tests/model-list
#MODELS=`cat tests/model-list`

MODELS=`cat $1` 

function getSpecies()
{
    $HEAD -n1 $1 | $CUT -d ',' -f 2- --output-delimiter=" " | $SED 's/[ \t\r\n]*$//';
}


for MODEL in $MODELS;do
  # set parameters 
  ENDTIME=50
  STEPNUMBER=50
  INFILE=${TESTSDIR}/${MODEL}.xml
  OUTFILE=${TESTSDIR}/${MODEL}.RESULT
  MEAN_OUTFILE=${TESTSDIR}/${MODEL}-mean.RESULT
  SD_OUTFILE=${TESTSDIR}/${MODEL}-sd.RESULT
  SPECIESLIST=`getSpecies ${TESTSDIR}/${MODEL}-mean.csv`
  # run simulation 
  #echo "$WRAPPER $INFILE $ENDTIME $STEPNUMBER $NUM_REPEATS $OUTFILE $SPECIESLIST"
  $WRAPPER $INFILE $ENDTIME $STEPNUMBER $NUM_REPEATS $OUTFILE $SPECIESLIST
  # calculate mean and standard deviation
  ./calculate_statistics.py $OUTFILE $MEAN_OUTFILE $SD_OUTFILE $STEPNUMBER $NUM_REPEATS
  # compare results
  ./compare_mean.py ${MEAN_OUTFILE} ${TESTSDIR}/${MODEL}-mean.csv ${TESTSDIR}/${MODEL}-sd.csv $NUM_REPEATS ${TESTSDIR}/${MODEL}-mean-compare.RESULT 
  ./compare_sd.py ${SD_OUTFILE} ${TESTSDIR}/${MODEL}-sd.csv $NUM_REPEATS ${TESTSDIR}/${MODEL}-sd-compare.RESULT
done
