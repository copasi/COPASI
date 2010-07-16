#!/bin/bash

if [ -x /bin/uname ];then
  UNAME=/bin/uname
else
  UNAME=/usr/bin/uname
fi

SYSTEM=`${UNAME} -s`


VALGRIND_NUMCALLERS=30

if [ "${SYSTEM}" == "Darwin" ];then
  SED=/usr/bin/sed
  GREP=/usr/bin/grep
else
  SED=/bin/sed
  GREP=/bin/grep
fi  

VALGRIND=/usr/bin/valgrind
TPUT=/usr/bin/tput


if [ -z "$TMP_DIR" ];then
  TMP_DIR=/tmp/
fi

if [ -z "$USE_VALGRIND" ];then
  USE_VALGRIND=no
fi

if [ -z "$DO_LEAKCHECK" ];then
  DO_LEAKCHECK=no
fi

FILTER_SBML_INPUT_WARNINGS=${FILTER_SBML_IMPORT_WARNINGS:="yes"}
FILTER_RDF_MESSAGES=${FILTER_RDF_MESSAGES:="yes"}

if [ -z "$FRANKS_WRAPPER" ];then
  if [ "$SYSTEM" == "Darwin" ];then
    FRANKS_WRAPPER=../../../../franks_testsuite/franks_testsuite.app/Contents/MacOS/franks_testsuite
  else
    FRANKS_WRAPPER=../../../../franks_testsuite/franks_testsuite
  fi
fi

VALGRIND_OPTIONS="--num-callers=${VALGRIND_NUMCALLERS} ${VALGRIND_OPTIONS}"

source ./utilities.sh

function test_run_single_file
{
    # we pass all the commands as parameters so we don't have to check
    # for their existence in each call. Thoses checks have to be done by the
    # caller
    if [ $# != 2 ];then
        echo "Error. test_run_single_file expects exactly two arguments.";
        return 1;
    fi
    SBML_FILE=$1
    OUTPUT_DIR=$2
    NAME=${SBML_FILE##*/};
    NAME=${NAME%%.xml};
    RESULT_FILE=${OUTPUT_DIR}/${NAME}.CSV
    OUTPUT_FILE=${NAME}.franks.out
    ERROR_FILE=${NAME}.franks.err
    VALGRIND_LOG=${NAME}.franks.log
    COMMAND_FILE=${NAME}.franks.sh
    COMMAND="${FRANKS_WRAPPER} ${SBML_FILE} 0.0 10.0 1000 ${RESULT_FILE}"
    if [ "$USE_VALGRIND" == "yes" ];then
       COMMAND="${VALGRIND} ${VALGRIND_OPTIONS} --log-file-exactly=${OUTPUT_DIR}/${VALGRIND_LOG} ${COMMAND}"
    fi
    echo "$COMMAND" > ${OUTPUT_DIR}/${COMMAND_FILE}
    $COMMAND > ${OUTPUT_DIR}/${OUTPUT_FILE} 2> ${OUTPUT_DIR}/${ERROR_FILE} || return 1;
    # check if the CPS file has been generated and has a size different from 0
    if [ ! -s ${RESULT_FILE} ];then
        return 1;
    fi
    # check if filtering of warnings has been enabled and if yes,
    # do the filtering
    if [ "${FILTER_SBML_IMPORT_WARNINGS}" == "yes" ];then
      mv ${OUTPUT_DIR}/${ERROR_FILE} ${OUTPUT_DIR}/${ERROR_FILE}.unfiltered;
      ${SED} -e '/>.*(filtered)/,/^ *\. *$/d' ${OUTPUT_DIR}/${ERROR_FILE}.unfiltered > ${OUTPUT_DIR}/${ERROR_FILE}
    fi
    # check if the output file has a size different from 0
    if [ -s ${OUTPUT_DIR}/${ERROR_FILE} ];then
        if [ "${USE_VALGRIND}" == "yes" ];then
          # additional valgrind checks
          check_valgrind_errors ${OUTPUT_DIR}/${VALGRIND_LOG}
          return $?
        else
            return 2;
        fi
    fi
    # todo check if valgrind found an error
    if [ "$USE_VALGRIND" == "yes" ];then
      check_valgrind_errors ${OUTPUT_DIR}/${VALGRIND_LOG}
      return $?
    fi
    return 0
}

function test_run_files
{
    # create a direcory in TMP_DIR that holds all result files
    OUTPUT_DIR=$TMP_DIR
    FILENAME=$1
    COUNT=0;
    NUM_PASSED=0;
    NUM_FAILED=0;
    NUM_SUCCEEDED=0;
    while [ -n "$FILENAME" ];do
      # check if the file exists
      if [ ! -r $FILENAME ];then
          echo "$FILENAME does not exist, is not a regular file or is not readable."
      else
        COUNT=$(($COUNT + 1));
        echo -n "Simulating $FILENAME ... ";
        NAME=${FILENAME##*/};
        NAME=${NAME%%.xml};
        test_run_single_file ${FILENAME} ${OUTPUT_DIR}
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
        2 )
            echo -n -e '\E[33;47mSUCCEDED';
            ${TPUT} sgr0;
            echo -e "\nThere was additional output from COPASI. Check ${OUTPUT_DIR}/${NAME}.franks.err for details.";
            NUM_SUCCEEDED=$(($NUM_SUCCEEDED + 1));
            ;;
        102 ) 
            echo -n -e '\E[33;47mSUCCEDED';
            ${TPUT} sgr0;
            echo -e "\nValgrind reported errors. Check ${OUTPUT_DIR}/${NAME}.franks.log for details.";
            NUM_SUCCEEDED=$(($NUM_SUCCEEDED + 1));
            ;;
        103 ) 
            echo -n -e '\E[33;47mSUCCEDED';
            ${TPUT} sgr0;
            echo -e "\nValgrind reported errors and memory leaks. Check ${OUTPUT_DIR}/${NAME}.franks.log.";
            NUM_SUCCEEDED=$(($NUM_SUCCEEDED + 1));
            ;;
        104 ) 
            echo -e -n '\E[33;47mSUCCEDED';
            ${TPUT} sgr0;
            echo -e "\nValgrind reported memory leaks. Check ${OUTPUT_DIR}/${NAME}.franks.log for details.";
            NUM_SUCCEEDED=$(($NUM_SUCCEEDED + 1));
            ;;
        * )
            echo -n -e '\E[31;47mFAILED';
            ${TPUT} sgr0;
            echo -e ".\nAn unknown error code was reported from test_import_file.";
            NUM_FAILED=$(($NUM_FAILED + 1));
            ;;
        esac
      fi
      shift
      FILENAME=$1
    done
    echo -e "\nOut of ${COUNT} simulations ${NUM_PASSED} passed, ${NUM_SUCCEEDED} succeeded and ${NUM_FAILED} failed.\n\n";
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

# check if tput is there
check_executable $TPUT || exit 1;

# check if grep is there
check_executable $GREP || exit 1;

# check if sed is there
check_executable $SED || exit 1;

# check if wrapper is there
check_executable ${FRANKS_WRAPPER} || exit 1;

# check if TMP_DIR is present, a directry and writable
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

test_run_files $*

