#!/bin/bash

if [ -x /bin/uname ];then
  UNAME=/bin/uname
else
  UNAME=/usr/bin/uname
fi

SYSTEM=`${UNAME} -s`

TARGET_SBML_VERSION=${TARGET_SBML_VERSION:=""}

VALGRIND_NUMCALLERS=30
if [ "${SYSTEM}" == "Darwin" ];then
  GREP=/usr/bin/grep
else
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

if [ -z "$COPASISE" ];then
  if [ "$SYSTEM" == "Darwin" ];then
    COPASISE=../../../CopasiSE/CopasiSE.app/Contents/MacOS/CopasiSE
  else
    COPASISE=../../../CopasiSE/CopasiSE
  fi
fi

if [ -z "$COPASISE_OPTIONS" ];then
  COPASISE_OPTIONS="--nologo --verbose"
fi

VALGRIND_OPTIONS="--num-callers=${VALGRIND_NUMCALLERS} ${VALGRIND_OPTIONS}"

source ./utilities.sh

function test_export_single_file
{
    # we pass all the commands as parameters so we don't have to check
    # for their existence in each call. Thoses checks have to be done by the
    # caller
    if [ $# != 2 ];then
        echo "Error. test_import_single_file expects exactly two arguments.";
        return 1;
    fi
    CPS_FILE=$1
    OUTPUT_DIR=$2
    NAME=${CPS_FILE##*/};
    NAME=${NAME%%.cps};
    SBML_FILE=${NAME}.xml
    OUTPUT_FILE=${NAME}.export.out
    ERROR_FILE=${NAME}.export.err
    VALGRIND_LOG=${NAME}.export.log
    COMMAND_FILE=${NAME}.export.sh
    if [ -z "$TARGET_SBML_VERSION" ];then
      COMMAND="${COPASISE} ${COPASISE_OPTIONS} --exportSBML ${OUTPUT_DIR}/${SBML_FILE} ${CPS_FILE}"
    else  
      SBML_FILE=${NAME}.${TARGET_SBML_VERSION}.xml
      COMMAND="${COPASISE} ${COPASISE_OPTIONS} --SBMLSchema ${TARGET_SBML_VERSION} --exportSBML ${OUTPUT_DIR}/${SBML_FILE} ${CPS_FILE}"
    fi
    if [ "$USE_VALGRIND" == "yes" ];then
       COMMAND="${VALGRIND} ${VALGRIND_OPTIONS} --log-file-exactly=${OUTPUT_DIR}/${VALGRIND_LOG} ${COMMAND}"
    fi
    echo "$COMMAND" > ${OUTPUT_DIR}/${COMMAND_FILE}
    $COMMAND > ${OUTPUT_DIR}/${OUTPUT_FILE} 2> ${OUTPUT_DIR}/${ERROR_FILE} || return 1;
    # check if the CPS file has been generated and has a size different from 0
    if [ ! -s ${OUTPUT_DIR}/${SBML_FILE} ];then
        return 1;
    fi
    # check if the output file has a size different from 0
    if [ -s ${OUTPUT_DIR}/$ERROR_FILE ];then
        if [ "$USE_VALGRIND" == "yes" ];then
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

function test_export_files
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
        COUNT=$(($COUNT + 1))
        echo -n "Exporting $FILENAME ... ";
        NAME=${FILENAME##*/};
        NAME=${NAME%%.cps};
        test_export_single_file ${FILENAME} ${OUTPUT_DIR}
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
            echo -e "\nThere was additional output from COPASI. Check ${OUTPUT_DIR}/${NAME}.export.err for details.";
            NUM_SUCCEEDED=$(($NUM_SUCCEEDED + 1));
            ;;
        102 ) 
            echo -n -e '\E[33;47mSUCCEDED';
            ${TPUT} sgr0;
            echo -e "\nValgrind reported errors. Check ${OUTPUT_DIR}/${NAME}.export.log for details.";
            NUM_SUCCEEDED=$(($NUM_SUCCEEDED + 1));
            ;;
        103 ) 
            echo -n -e '\E[33;47mSUCCEDED';
            ${TPUT} sgr0;
            echo -e "\nValgrind reported errors and memory leaks. Check ${OUTPUT_DIR}/${NAME}.export.log.";
            NUM_SUCCEEDED=$(($NUM_SUCCEEDED + 1));
            ;;
        104 ) 
            echo -e -n '\E[33;47mSUCCEDED';
            ${TPUT} sgr0;
            echo -e "\nValgrind reported memory leaks. Check ${OUTPUT_DIR}/${NAME}.export.log for details.";
            NUM_SUCCEEDED=$(($NUM_SUCCEEDED + 1));
            ;;
        * )
            echo -n -e '\E[31;47mFAILED';
            ${TPUT} sgr0;
            echo -e ".\nAn unknown error code was reported from test_export_single_file.";
            NUM_FAILED=$(($NUM_FAILED + 1));
            ;;
        esac
      fi
      shift
      FILENAME=$1
    done
    echo -e "\nOut of ${COUNT} exports ${NUM_PASSED} PASSED, ${NUM_SUCCEEDED} SUCCEEDED and ${NUM_FAILED} FAILED.\n\n" 
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

# check if CopasiSE is there
check_executable $COPASISE || exit 1;

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

test_export_files $*

