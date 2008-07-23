#!/bin/bash

# common parameters

if [ -x /bin/uname ];then
  UNAME=/bin/uname
else
  UNAME=/usr/bin/uname
fi

SYSTEM=`${UNAME} -s`

DATE=/bin/date
MKDIR=/bin/mkdir

# set TMP_DIR to HOME so that we don't fill up /tmp by accident
TMP_DIR=${TMP_DIR:="$HOME"}

USE_VALGRIND=${USE_VALGRIND:="no"}

DO_LEACKCHECK=${DO_LEAKCHECK:="no"}

DO_NONCURATED=${DO_NONCURATED:="no"}

if [ -z $COPASISE ];then
  if [ "$SYSTEM" == "Darwin" ];then
    COPASISE=../../../CopasiSE/CopasiSE.app/Contents/MacOS/CopasiSE
  else
    COPASISE=../../../CopasiSE/CopasiSE
  fi
fi

COPASISE_OPTIONS=${COPASISE_OPTIONS:="--nologo --verbose"}

# parameters for import test
BIOMODELS_DIR=${BIOMODELS_DIR:=${HOME}/Downloads/biomodels_25September2007_sbmls}

# parameters for export test
CPS_DIR=${CPS_DIR:=""}

# parameters for roundtripping test


# parameters for semantic testsuite test


# parameters for stochastic testsuite test
if [ -z $SBML_SEMANTIC_TESTSUITE_WRAPPER ];then
  if [ "$SYSTEM" == "Darwin" ];then
    SBML_SEMANTIC_TESTSUITE_WRAPPER=../../../../semantic-test-suite/semantic-test-suite.app/Contents/MacOS/semantic-test-suite
  else
    SBML_SEMANTIC_TESTSUITE_WRAPPER=../../../../semantic-test-suite/semantic-test-suite
  fi
fi

SBML_SEMANTIC_TESTSUITE_DIR=${SBML_SEMANTIC_TESTSUITE_DIR:="../../../../semantic-test-suite/semantic-test-suite"}

SBML_SEMANTIC_TESTSUITE_LIST=${SBML_SEMANTIC_TESTSUITE_LIST:="../../../../semantic-test-suite/copasitestlist.txt"}

# 10000 iterations is the recommended number by the testsuite authors
NUM_ITERATIONS=${NUM_ITERATIONS:=10000}

if [ -z $STOCHASTIC_TESTSUITE_WRAPPER ];then
  if [ "$SYSTEM" == "Darwin" ];then
    STOCHASTIC_TESTSUITE_WRAPPER=../../../../stochastic-testsuite/stochastic-testsuite.app/Contents/MacOS/stochastic-testsuite
  else
    STOCHASTIC_TESTSUITE_WRAPPER=../../../../stochastic-testsuite/stochastic-testsuite
  fi
fi

STOCHASTIC_TESTSUITE_DIR=${STOCHASTIC_TESTSUITE_DIR:="../../../../stochastic-testsuite/dsmts23-20080307"}

ANALYSIS_SCRIPTS_DIR=${ANALYSIS_SCRIPTS_DIR:="../../../../stochastic-testsuite"}

STOCHASTIC_TESTSUITE_LIST=${STOCHASTIC_TESTSUITE_LIST:="../../../../stochastic-testsuite/copasi-model-list"}

# parameters for franks testsuite
if [ -z "$FRANKS_WRAPPER" ];then
  if [ "$SYSTEM" == "Darwin" ];then
    FRANKS_WRAPPER=../../../../franks_testsuite/franks_testsuite.app/Contents/MacOS/franks_testsuite
  else
    FRANKS_WRAPPER=../../../../franks_testsuite/franks_testsuite
  fi
fi


# check if TMP_DIR is writable
if [ ! -d "${TMP_DIR}" ];then
  echo "Error. \"${TMP_DIR}\" does not exist or is not a directory.";
  exit 1;
fi
if [ ! -w "${TMP_DIR}" ];then
  echo "Error. \"${TMP_DIR}\" is not writable.";
  exit 1;
fi


# create a directory for the results in TMP_DIR
DATE_SECONDS=`$DATE "+%s"`
RESULT_DIR=${TMP_DIR}/results-${DATE_SECONDS}
$MKDIR ${RESULT_DIR} || exit 1 #{ echo "Error. Unable to create result directory \"${RESULT_DIR}\"."; exit 1 }



# run the import tests on all curated biomodels files
echo "Running import tests ..."
echo -e "\nImporting curated models ..."
# check if ${BIOMODELS_DIR}/curated exists
if [ ! -d ${BIOMODELS_DIR}/curated ];then
  echo "Error. \"${BIOMODELS_DIR}/curated\" does not exist or is not a directory."
  exit 1;
fi
${MKDIR} ${RESULT_DIR}/import/
${MKDIR} ${RESULT_DIR}/import/curated
COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/import/curated ./test_sbml_import.sh ${BIOMODELS_DIR}/curated/*.xml
if [ "${DO_NONCURATED}" == "yes" ];then
  echo -e "\nImporting noncurated models ..."
  # check if ${BIOMODELS_DIR}/noncurated exists
  if [ ! -d ${BIOMODELS_DIR}/noncurated ];then
    echo "Error. \"${BIOMODELS_DIR}/noncurated\" does not exist or is not a directory."
    exit 1;
  fi
  ${MKDIR} ${RESULT_DIR}/import/noncurated
  COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/import/noncurated ./test_sbml_import.sh ${BIOMODELS_DIR}/noncurated/*.xml
fi
echo -e "\n\n"



# run the export test
echo "Running export tests ..."
# if CPS_DIR is set, we try to export the CPS files in that directory instead
# of taking the ones created in the import test
if [ ! -z "${CPS_DIR}" ];then
  echo -e "\nExporting COPASI models in ${CPS_DIR} ..."
  ${MKDIR} ${RESULT_DIR}/export
  if [ ! -d ${CPS_DIR} ];then
    echo "Error. \"${CPS_DIR}\" does not exist or is not a directory."
    exit 1;
  fi
  COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/export ./test_sbml_export.sh ${CPS_DIR}/*.cps

else
  echo -e "\nExporting models created from curated biomodel files ..."
  ${MKDIR} ${RESULT_DIR}/export
  ${MKDIR} ${RESULT_DIR}/export/curated
  CPS_DIR=${RESULT_DIR}/import/curated
  if [ ! -d ${RESULT_DIR}/import/curated ];then
    echo "Error. \"${RESULT_DIR}/import/curated\" does not exist or is not a directory."
    exit 1;
  fi
  COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/export/curated ./test_sbml_export.sh ${CPS_DIR}/*.cps

  if [ "${DO_NONCURATED}" == "yes" ];then
    echo -e "\nExporting models created from noncurated biomodel files ..."
    ${MKDIR} ${RESULT_DIR}/export/noncurated
    CPS_DIR=${RESULT_DIR}/import/noncurated
    if [ ! -d ${RESULT_DIR}/import/noncurated ];then
      echo "Error. \"${RESULT_DIR}/import/noncurated\" does not exist or is not a directory."
      exit 1;
    fi
    COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/export/noncurated ./test_sbml_export.sh ${CPS_DIR}/*.cps
  fi
fi
echo -e "\n\n"



# run the roundtripping test
echo "Running roundtripping tests ..."
echo -e "\nRoundtripping curated models ..."
# check if ${BIOMODELS_DIR}/curated exists
if [ ! -d ${BIOMODELS_DIR}/curated ];then
  echo "Error. \"${BIOMODELS_DIR}/curated\" does not exist or is not a directory."
  exit 1;
fi
${MKDIR} ${RESULT_DIR}/roundtripping
${MKDIR} ${RESULT_DIR}/roundtripping/curated
COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/roundtripping/curated ./test_sbml_roundtripping.sh ${BIOMODELS_DIR}/curated/*.xml

if [ "${DO_NONCURATED}" == "yes" ];then
  echo -e "\nRoundtripping noncurated models ..."
  # check if ${BIOMODELS_DIR}/noncurated exists
  if [ ! -d ${BIOMODELS_DIR}/noncurated ];then
    echo "Error. \"${BIOMODELS_DIR}/noncurated\" does not exist or is not a directory."
    exit 1;
  fi
  ${MKDIR} ${RESULT_DIR}/roundtripping/noncurated
  COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/roundtripping/noncurated ./test_sbml_roundtripping.sh ${BIOMODELS_DIR}/noncurated/*.xml
fi
echo -e "\n\n"



# run the sbml_semantic_testsuite
echo "Running SBML semantic testsuite ..."
${MKDIR} ${RESULT_DIR}/semantic-testsuite
SBML_SEMANTIC_TESTSUITE_WRAPPER=${SBML_SEMANTIC_TESTSUITE_WRAPPER} SBML_SEMANTIC_TESTSUITE_DIR=${SBML_SEMANTIC_TESTSUITE_DIR} SBML_SEMANTIC_TESTSUITE_LIST=${SBML_SEMANTIC_TESTSUITE_LIST} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/semantic-testsuite ./run_sbml_semantic_testsuite.sh
echo -e "\n\n"



# run the stochastic testsuite
echo "Running stochastic testsuite ..."
${MKDIR} ${RESULT_DIR}/stochastic-testsuite
ANALYSIS_SCRIPTS_DIR=${ANALYSIS_SCRIPTS_DIR} STOCHASTIC_TESTSUITE_WRAPPER=${STOCHASTIC_TESTSUITE_WRAPPER} STOCHASTIC_TESTSUITE_DIR=${STOCHASTIC_TESTSUITE_DIR} STOCHASTIC_TESTSUITE_LIST=${STOCHASTIC_TESTSUITE_LIST} USE_VALGRIND="no" DO_LEAKCHECK="no" TMP_DIR=${RESULT_DIR}/stochastic-testsuite ./run_stochastic_testsuite.sh
echo -e "\n\n"



# run franks test
# not written yet.
echo "Running Franks simulation test ..."
${MKDIR} ${RESULT_DIR}/franks
${MKDIR} ${RESULT_DIR}/franks/curated
if [ ! -d ${BIOMODELS_DIR}/curated ];then
  echo "Error. \"${BIOMODELS_DIR}/curated\" does not exist or is not a directory."
  exit 1;
fi
USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/franks/curated ./run_franks_test.sh ${BIOMODELS_DIR}/curated/*.xml
if [ "${DO_NONCURATED}" == "yes" ];then
  echo -e "\nRoundtripping noncurated models ..."
  # check if ${BIOMODELS_DIR}/noncurated exists
  if [ ! -d ${BIOMODELS_DIR}/noncurated ];then
    echo "Error. \"${BIOMODELS_DIR}/noncurated\" does not exist or is not a directory."
    exit 1;
  fi
  ${MKDIR} ${RESULT_DIR}/franks/noncurated
  USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/franks/noncurated ./run_franks_test.sh ${BIOMODELS_DIR}/noncurated/*.xml
fi
echo -e "\n\n"


