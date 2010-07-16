#!/bin/bash


if [ -x /bin/uname ];then
  UNAME=/bin/uname
else
  UNAME=/usr/bin/uname
fi

SYSTEM=`${UNAME} -s`

VALGRIND_NUMCALLERS=30
VALGRIND=/usr/bin/valgrind
TPUT=/usr/bin/tput
HEAD=/usr/bin/head
CUT=/usr/bin/cut
PYTHON=/usr/bin/python
DATE=/bin/date

if [ ${SYSTEM} == "Darwin" ];then
  GREP=/usr/bin/grep
  SED=/usr/bin/sed
else
  GREP=/bin/grep
  SED=/bin/sed
fi

if [ -z ${STOCH_METHOD} ];then
  STOCH_METHOD="stochastic"
fi

if [ -z ${NUM_ITERATIONS} ];then
  NUM_ITERATIONS=10000
fi


if [ -z $TMP_DIR ];then
  TMP_DIR=/tmp/
fi

if [ -z $USE_VALGRIND ];then
  USE_VALGRIND=no
fi

if [ -z $DO_LEAKCHECK ];then
  DO_LEAKCHECK=no
fi

if [ -z $STOCHASTIC_TESTSUITE_WRAPPER ];then
  if [ "$SYSTEM" == "Darwin" ];then
    STOCHASTIC_TESTSUITE_WRAPPER=../../../../stochastic-testsuite/stochastic-testsuite.app/Contents/MacOS/stochastic-testsuite
  else
    STOCHASTIC_TESTSUITE_WRAPPER=../../../../stochastic-testsuite/stochastic-testsuite
  fi
fi

if [ -z ${STOCHASTIC_TESTSUITE_DIR} ];then
 STOCHASTIC_TESTSUITE_DIR=../../../../stochastic-testsuite/dsmts23-20080307
fi

if [ -z ${ANALYSIS_SCRIPTS_DIR} ];then
  ANALYSIS_SCRIPTS_DIR=../../../../stochastic-testsuite
fi

if [ -z ${STOCHASTIC_TESTSUITE_LIST} ];then
    STOCHASTIC_TESTSUITE_LIST=../../../../stochastic-testsuite/copasi-model-list
fi

VALGRIND_OPTIONS="--num-callers=${VALGRIND_NUMCALLERS} ${VALGRIND_OPTIONS}"

source ./utilities.sh

function analyse_testrun
{
    if [ $# != 3 ];then
        echo "Error. analyse_testrun expects exactly three arguments.";
        return 1;
    fi
    MODEL=$1
    OUTPUT_DIR=$2
    STEPNUMBER=$3
    OUTPUT_FILE=${MODEL}.stochastic.out
    ERROR_FILE=${MODEL}.stochastic.err
    RESULT_FILE=${MODEL}.stochastic.RESULT
    MEAN_OUTFILE=${MODEL}-mean.stochastic.RESULT
    SD_OUTFILE=${MODEL}-sd.stochastic.RESULT
    MEAN_REFERENCE_FILE=${MODEL}-mean.csv
    SD_REFERENCE_FILE=${MODEL}-sd.csv
    CALCULATION_OUTPUT=${MODEL}-calc.out
    SD_COMPARE_OUTPUT=${MODEL}-sd-compare.out
    MEAN_COMPARE_OUTPUT=${MODEL}-mean-compare.out
    # check if the result file is there
    if [ ! -f ${OUTPUT_DIR}/${RESULT_FILE} ];then
      echo "Error. Could not find result file at \"${OUTPUT_DIR}/${RESULT_FILE}\""
      return 1;
    fi
    # get a summary from the result file
    ${PYTHON} ${ANALYSIS_SCRIPTS_DIR}/calculate_statistics.py ${OUTPUT_DIR}/${RESULT_FILE} ${OUTPUT_DIR}/${MEAN_OUTFILE} ${OUTPUT_DIR}/${SD_OUTFILE} ${STEPNUMBER} ${NUM_ITERATIONS} &> ${OUTPUT_DIR}/${CALCULATION_OUTPUT} || return 3;
   
    if [ -f ${OUTPUT_DIR}/${MEAN_OUTFILE} ] ; then
      if [ -f ${STOCHASTIC_TESTSUITE_DIR}/${SD_REFERENCE_FILE} ] ; then 
        if [ -f ${STOCHASTIC_TESTSUITE_DIR}/${MEAN_REFERENCE_FILE} ] ; then
           ${PYTHON} ${ANALYSIS_SCRIPTS_DIR}/compare_mean.py ${OUTPUT_DIR}/${MEAN_OUTFILE} ${STOCHASTIC_TESTSUITE_DIR}/${MEAN_REFERENCE_FILE} ${STOCHASTIC_TESTSUITE_DIR}/${SD_REFERENCE_FILE} ${NUM_ITERATIONS} ${OUTPUT_DIR}/${MODEL}-mean-compare.RESULT &> ${OUTPUT_DIR}/${MEAN_COMPARE_OUTPUT}|| return 4; 
           #${PYTHON} ${ANALYSIS_SCRIPTS_DIR}/compare_mean.py ${OUTPUT_DIR}/${MEAN_OUTFILE} ${STOCHASTIC_TESTSUITE_DIR}/${MEAN_REFERENCE_FILE} ${STOCHASTIC_TESTSUITE_DIR}/${SD_REFERENCE_FILE} ${NUM_ITERATIONS} ${OUTPUT_DIR}/${MODEL}-mean-compare.RESULT || return 4; 
           ${PYTHON} ${ANALYSIS_SCRIPTS_DIR}/compare_sd.py ${OUTPUT_DIR}/${SD_OUTFILE} ${STOCHASTIC_TESTSUITE_DIR}/${SD_REFERENCE_FILE} ${NUM_ITERATIONS} ${OUTPUT_DIR}/${MODEL}-sd-compare.RESULT &> ${OUTPUT_DIR}/${SD_COMPARE_OUTPUT} || return 5;
           #${PYTHON} ${ANALYSIS_SCRIPTS_DIR}/compare_sd.py ${OUTPUT_DIR}/${SD_OUTFILE} ${STOCHASTIC_TESTSUITE_DIR}/${SD_REFERENCE_FILE} ${NUM_ITERATIONS} ${OUTPUT_DIR}/${MODEL}-sd-compare.RESULT || return 5;
        else
          echo "Error. Could not find file \"${STOCHASTIC_TESTSUITE_DIR}/${MEAN_REFERENCE_FILE}\"";
          return 6;
        fi     
      else
        echo "Error. Could not find file \"${STOCHASTIC_TESTSUITE_DIR}/${SD_REFERENCE_FILE}\"";
        return 6;
      fi
    else
      echo "Error. Could not find file \"${OUTPUT_DIR}/${MEAN_OUTFILE}\"";
      return 6;
    fi  

    if [ "$USE_VALGRIND" == "yes" ];then
      # additional valgrind checks
      check_valgrind_errors ${OUTPUT_DIR}/${VALGRIND_LOG}
      return $?
    fi
}

function getSpecies
{
    $HEAD -n1 $1 | $CUT -d ',' -f 2- | $SED -e 's/[ \t\r\n]*$//; s/,/ /g';
}


function run-single-stochastic-test
{
    if [ $# != 2 ];then
        echo "Error. run-single-stochastic-test expects exactly two arguments.";
        return 1;
    fi
    MODEL=$1
    OUTPUT_DIR=$2
    ENDTIME=50
    STEPNUMBER=50
    INFILE=${STOCHASTIC_TESTSUITE_DIR}/${MODEL}.xml
    OUTPUT_FILE=${MODEL}.stochastic.out
    COMMAND_FILE=${MODEL}.stochastic.sh
    ERROR_FILE=${MODEL}.stochastic.err
    RESULT_FILE=${MODEL}.stochastic.RESULT
    MEAN_REFERENCE_FILE=${MODEL}-mean.csv
    # we only need one output file since we want to see to which test the
    # errors belong
    VALGRIND_LOG=${MODEL}.stochastic.log
    # create the species list from the reference mean result
    if [ ! -f ${STOCHASTIC_TESTSUITE_DIR}/${MEAN_REFERENCE_FILE} ];then
      echo "Error. Could not find file \"${STOCHASTIC_TESTSUITE_DIR}/${MEAN_REFERENE_FILE}\"."
      return 1;
    fi
    SPECIESLIST=`getSpecies ${STOCHASTIC_TESTSUITE_DIR}/${MEAN_REFERENCE_FILE}`
    if [ -z "${SPECIESLIST}" ];then
      echo "Error. Specieslist created from \"${STOCHASTIC_TESTSUITE_DIR}/${MEAN_REFERENCE_FILE}\" is empty.";
      return 1;
    fi
    # run the test
    COMMAND="${STOCHASTIC_TESTSUITE_WRAPPER} ${STOCH_METHOD} ${INFILE} ${ENDTIME} ${STEPNUMBER} ${NUM_ITERATIONS} ${OUTPUT_DIR}/${RESULT_FILE} ${SPECIESLIST}" || return 1;
    if [ "$USE_VALGRIND" == "yes" ];then
       COMMAND="${VALGRIND} ${VALGRIND_OPTIONS} --log-file-exactly=${OUTPUT_DIR}/${VALGRIND_LOG} ${COMMAND}"
    fi
    echo "${COMMAND}" > ${OUTPUT_DIR}/${COMMAND_FILE}
    $COMMAND > ${OUTPUT_DIR}/${OUTPUT_FILE} 2> ${OUTPUT_DIR}/${ERROR_FILE}
    analyse_testrun ${MODEL} ${OUTPUT_DIR} ${STEPNUMBER};
    return $?
}

function run-stochastic-testsuite
{
    if [ $# -lt 2 ];then
       echo "Error. No models specified.";
       return 1;
    fi
    OUTPUT_DIR=$1
    shift
    MODEL=$1
    COUNT=0;
    NUM_PASSED=0;
    NUM_FAILED=0;
    NUM_SUCCEED=0;
    while [ -n "$MODEL" ];do
      echo -n "Simulating ${MODEL} stochastically ${NUM_ITERATIONS} times ... ";
      COUNT=$(($COUNT + 1))
      run-single-stochastic-test ${MODEL} ${TMP_DIR}
      case $? in
      0 )
          echo -n -e '\E[32;47mOK';
          ${TPUT} sgr0;
          echo -n -e "\n";
          NUM_PASSED=$(($NUM_PASSED + 1));
          ;;
      1 )
          echo -n -e '\E[31;47mFAILED';
          ${TPUT} sgr0;
          echo -n -e "\n";
          NUM_FAILED=$(($NUM_FAILED + 1));
          ;;
      3 )
          echo -n -e '\E[31;47mFAILED';
          ${TPUT} sgr0;
          echo -e "\nCalculation of mean values and standard deviations failed. See ${OUTPUT_DIR}/${MODEL}-calc.out";
          NUM_FAILED=$(($NUM_FAILED + 1));
          ;;
      4 )
          echo -n -e '\E[31;47mFAILED';
          ${TPUT} sgr0;
          echo -e "\nComparison of mean values failed. See ${OUTPUT_DIR}/${MODEL}-mean-compare.out";
          NUM_FAILED=$(($NUM_FAILED + 1));
          ;;
      5 )
          echo -n -e '\E[31;47mFAILED';
          ${TPUT} sgr0;
          echo -e "\nComparison of standard deviations failed. See ${OUTPUT_DIR}/${MODEL}-sd-compare.out";
          NUM_FAILED=$(($NUM_FAILED + 1));
          ;;
      6 )
          echo -n -e '\E[31;47mFAILED';
          ${TPUT} sgr0;
          echo -e "\nSome result file was missing";
          NUM_FAILED=$(($NUM_FAILED + 1));
          ;;
      102 ) 
          echo -n -e '\E[33;47mSUCCEDED';
          ${TPUT} sgr0;
          echo -e -n "\nValgrind reported errors. Check ${OUTPUT_DIR}/${MODEL}.stochastic.log for details.";
          NUM_SUCCEEDED=$(($NUM_SUCCEEDED + 1));
          ;;
      103 ) 
          echo -n -e '\E[33;47mSUCCEDED';
          ${TPUT} sgr0;
          echo -e "\nValgrind reported errors and memory leaks. Check ${OUTPUT_DIR}/${MODEL}.stochastic.log.";
          NUM_SUCCEEDED=$(($NUM_SUCCEEDED + 1));
          ;;
      104 ) 
          echo -e -n '\E[33;47mSUCCEDED';
          ${TPUT} sgr0;
          echo -e "\nValgrind reported memory leaks. Check ${OUTPUT_DIR}/${MODEL}.stochastic.log for details.";
          NUM_SUCCEEDED=$(($NUM_SUCCEEDED + 1));
          ;;
      * )
          echo -n -e '\E[31;47mFAILED';
          ${TPUT} sgr0;
          echo -e "\nAn unknown error code \"$?\" was reported from run-single-stochastic-test.";
          NUM_FAILED=$(($NUM_FAILED + 1));
          ;;
      esac
      shift
      MODEL=$1
    done
    echo -e "\nOut of ${COUNT} tests ${NUM_PASSED} passed, ${NUM_SUCCEEDED} succeeded and ${NUM_FAILED} failed.\n\n"
}

# enable leak checking in valgrind if requested
if [ "${DO_LEAKCHECK}" == "yes" ];then
    VALGRIND_OPTIONS="${VALGRIND_OPTIONS} --leak-check=full"
fi

# check if valgrind is there if needed
if [ ${USE_VALGRIND} == "yes" ]; then
   # todo check if the valgrind executable exists
   check_executable $VALGRIND || exit 1; 
fi

# check if head is there
check_executable $HEAD || exit 1;

# check if cut is there
check_executable $CUT || exit 1;

# check if sed is there
check_executable $SED || exit 1;

# if python is available
check_executable $PYTHON || exit 1;

# check if the testsuite wrapper is there
check_executable ${STOCHASTIC_TESTSUITE_WRAPPER} || exit 1;

# check if TMP_DIR is present, a directory and writable
if [ -d $TMP_DIR ];then
    touch ${TMP_DIR}/test.test
    if [ $? != 0 ];then
        echo "Error. Can not write to ${TMP_DIR}."
        exit 1
    else
      rm ${TMP_DIR}/test.test
    fi
else
    echo "Error. ${TMP_DIR} is not a directory."
    exit 1;
fi

# check if the testuite directory is there
if [ ! -d ${STOCHASTIC_TESTSUITE_DIR} ];then
    echo "Error. Stochastic testsuite directory not found at ${STOCHASTIC_TESTSUITE_DIR}.";
    return 1;
fi
# check if the testlist is there and readable
if [ -f ${STOCHASTIC_TESTSUITE_LIST} ];then
    if [ -r ${STOCHASTIC_TESTSUITE_LIST} ];then
        if [ ! -s ${STOCHASTIC_TESTSUITE_LIST} ];then
            echo "Error. Stochastic testlist at ${STOCHASTIC_TESTSUITE_LIST} is empty.";
            return 1;
        fi
    else
      echo "Error. Stochastic testlist at ${STOCHASTIC_TESTSUITE_LIST} not readable.";
      return 1;
    fi
else
  echo "Error. Stochastic testlist not found at ${STOCHASTIC_TESTSUITE_LIST} or it is not a regular file."
  return 1
fi


# check if the analysis scrips are there
if [ -d ${ANALYSIS_SCRIPTS_DIR} ];then
    if [ ! -f ${ANALYSIS_SCRIPTS_DIR}/calculate_statistics.py ];then
      echo "Error. Could not find script \"${ANALYSIS_SCRIPTS_DIR}/compare_sd.py\"."
      exit 1;
    fi
    if [ ! -f ${ANALYSIS_SCRIPTS_DIR}/compare_sd.py ];then
      echo "Error. Could not find script \"${ANALYSIS_SCRIPTS_DIR}/compare_sd.py\"."
      exit 1;
    fi
    if [ ! -f ${ANALYSIS_SCRIPTS_DIR}/compare_mean.py ];then
      echo "Error. Could not find script \"${ANALYSIS_SCRIPTS_DIR}/compare_mean.py\"."
      exit 1;
    fi
else
  echo "Could not find directory for analysis scripts at \"${ANALYSIS_SCRIPTS_DIR}\"."
  exit 1;
fi

MODELS=`cat ${STOCHASTIC_TESTSUITE_LIST}`
if [ -z "$MODELS" ];then
  echo "Error. The model list cointains no models.";
  exit 1;
fi

check_executable $DATE
if [ $? -eq 0 ];then
  date=`${DATE}`
fi
echo -n "Running stochastic testsuite ";
if [ -n "$date" ];then
  echo "(${date})"
fi

run-stochastic-testsuite $MODELS
exit $?
