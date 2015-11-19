#!/bin/bash 
# Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 


HEAD=head
CUT=cut
SED=sed

if [ $# != 5 ] ; then
  echo -e "\nUsage: run.sh WRAPPER TESTSDIR [MODEL_LIST_FILE|MODEL] METHOD NUM_REPEATS\n";
  exit 1;
fi  

WRAPPER="$1"
TESTSDIR="$2"
MODELFILE=$3
METHOD=$4
NUM_REPEATS=$5

if [ -e $MODELFILE ]; then
  MODELS=`cat $MODELFILE` 
else
  MODELS=$MODELFILE
fi

function getSpecies()
{
    $HEAD -n1 "$1" | $CUT -d ',' -f 2- | $SED -e ' s/,/ /g; s/[ \t\r\n]*$//';
}

TOTALTIME=0.0

for MODEL in $MODELS;do
  # set parameters 
  RESULT="passed"
  ENDTIME=50
  STEPNUMBER=50
  INFILE="${TESTSDIR}"/${MODEL}.xml
  OUTFILE="${TESTSDIR}"/${MODEL}.RESULT
  OUTFILEWAP=${MODEL}.RESULT
  MEAN_OUTFILE="${TESTSDIR}"/${MODEL}-mean.RESULT
  SD_OUTFILE="${TESTSDIR}"/${MODEL}-sd.RESULT
  SPECIESLIST=`getSpecies "${TESTSDIR}"/${MODEL}-mean.csv`
  MEAN_REFERENCE_FILE="${TESTSDIR}"/${MODEL}-mean.csv
  SD_REFERENCE_FILE="${TESTSDIR}"/${MODEL}-sd.csv
  # run simulation 
  if [ -e "${INFILE}" ] ; then
    echo "$WRAPPER $METHOD \"${INFILE}\" $ENDTIME $STEPNUMBER $NUM_REPEATS \"${OUTFILE}\" $SPECIESLIST"
    rm -f "${OUTFILE}"
    exec 3>&1 4>&2
    TIME=$( { time -p "${WRAPPER}" $METHOD "${INFILE}" $ENDTIME $STEPNUMBER $NUM_REPEATS "${OUTFILEWAP}" $SPECIESLIST > /dev/null || RESULT="failed"  1>&3 2>&4; } 2>&1 )  # Captures time only.
    exec 3>&- 4>&-
    TIME=`echo $TIME |  /usr/bin/awk '{print $4}'` 
    echo "time: $TIME seconds"
    TOTALTIME=`echo "$TIME + $TOTALTIME" | /usr/bin/bc` 
    if [ "e$RESULT" == "efailed" ] ; then
      echo "ERROR: Simulation failed.";
      rm -f "${OUTFILE}";
    fi  
    if [ -e "${OUTFILE}" ] ; then
      # calculate mean and standard deviation
      rm -f "${MEAN_OUTFILE}" "${SD_OUTFILE}"
      ./calculate_statistics.py "${OUTFILE}" "${MEAN_OUTFILE}" "${SD_OUTFILE}" $STEPNUMBER $NUM_REPEATS || RESULT="failed" ;
      if [ "e$RESULT" == "efailed" ] ; then
        echo "ERROR: Statistical calculation failed.";
        rm -f "${MEAN_OUTFILE}" "${SD_OUTFILE}";
      fi  
      # compare results
      if [ -e "${MEAN_OUTFILE}" ] ; then
        if [ -e "${SD_REFERENCE_FILE}" ] ; then 
          if [ -e "${MEAN_REFERENCE_FILE}" ] ; then
             rm -f "${TESTSDIR}"/${MODEL}-mean-compare.RESULT 
             ./compare_mean.py "${MEAN_OUTFILE}" "${MEAN_REFERENCE_FILE}" "${SD_REFERENCE_FILE}" $NUM_REPEATS "${TESTSDIR}"/${MODEL}-mean-compare.RESULT || RESULT="failed"; 
             rm -f "${TESTSDIR}"/${MODEL}-sd-compare.RESULT 
             ./compare_sd.py "${SD_OUTFILE}" "${SD_REFERENCE_FILE}" $NUM_REPEATS "${TESTSDIR}"/${MODEL}-sd-compare.RESULT || RESULT="failed";
          else
            echo "Error. Could not find file \"${MEAN_REFERENCE_FILE}\"";
            RESULT="failed"
          fi     
        else
          echo "Error. Could not find file \"${SD_REFERENCE_FILE}\"";
          RESULT="failed"
        fi
      else
        echo "Error. Could not find file \"${MEAN_OUTFILE}\"";
        RESULT="failed"
      fi  
    else
      echo "Error. Could not find file \"${OUTFILE}\"";
      RESULT="failed"
    fi
  else
    echo "Error. Could not  find file \"${INFILE}\"";
    RESULT="failed"
  fi
  echo "$MODEL $RESULT"
done
echo "Time used for simulations: $TOTALTIME seconds";
