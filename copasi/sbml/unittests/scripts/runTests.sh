#!/bin/bash

COPASIDIR=${HOME}/workspace/copasi_build25
SBMLDIR=${HOME}/Downloads/libsbml-COPASI-24
BIOMODELSDIR=${HOME}/Downloads/biomodels_25September2007_sbmls

LD_LIBRARY_PATH=$SBMLDIR/src/

VALIDATE=${SBMLDIR}/examples/c++/validateSBML
PRINT=${SBMLDIR}/examples/c++/printSBML

SYSTEM=`uname`

if [ "${SYSTEM}" == "Darwin" ];then
  COPASISE=${COPASIDIR}/copasi/CopasiSE/CopasiSE.app/Contents/MacOS/CopasiSE;
#else
#  COPASISE=${COPASIDIR}/copasi/CopasiSE/CopasiSE;
fi


# import all biomodels models and save them as cps files
# and reexport them to SBML
if [ -e ${BIOMODELSDIR} ];then
  if [ -e ${COPASISE} ];then
    if [ -r statistics ];then
      rm -rf statistics;
    fi
    mkdir statistics;
    if [ -r validation ];then
      rm -rf validation;
    fi
    mkdir validation;
    if [ -e result_import ];then
      rm -rf result_import;
    fi
    mkdir result_import;
    if [ -e result_reexport ];then
      rm -rf result_reexport;
    fi
    mkdir result_reexport;
    if [ -e result_export ];then
      rm -rf result_export;
    fi
    mkdir result_export;
    for SBMLMODEL in ${BIOMODELSDIR}/curated/*.xml;do
      FILENAME=${SBMLMODEL##*/};
      echo $FILENAME
      CPSFILE=result_import/${FILENAME%%.xml}.cps;
      LOGFILE=result_import/${FILENAME%%.xml}.s2clog
      ./convertSBMLToCPS.sh $COPASISE $SBMLMODEL ${CPSFILE} $LOGFILE;
      if [ ! -s $LOGFILE ];then
        rm $LOGFILE
      fi
      if [ -e ${CPSFILE} ];then
        LOGFILE=result_export/${FILENAME%%.xml}.c2slog;
        ./convertCPSToSBML.sh $COPASISE $CPSFILE result_export/${FILENAME} $LOGFILE;
        if [ ! -s $LOGFILE ];then
          rm $LOGFILE
        fi
        if [ -e result_export/${FILENAME} ];then
          if [ -e ${PRINT} ];then
            LOGFILE=statistics/${FILENAME%%.xml}.orig.print;
            $PRINT result_export/${FILENAME} &> ${LOGFILE};
          else
            echo "Error. $PRINT does not exist.";
          fi
          if [ -e ${VALIDATE} ];then
            LOGFILE=validation/${FILENAME%%.xml}.exported.valid;
            $VALIDATE result_export/${FILENAME} &> $LOGFILE;
            # remove some of the warnings
            ./filterSBMLWarnings.sh ${LOGFILE}; 
          else
            echo "Error. $VALIDATE does not exist.";
          fi
        else
          echo "Could not create $FILENAME from $CPSFILE."
        fi
      else
        echo "$CPSFILE could not be created."
      fi
      LOGFILE=result_reexport/${FILENAME%%.xml}.s2slog;
      ./convertSBMLToSBML.sh $COPASISE $SBMLMODEL result_reexport/${FILENAME} $LOGFILE;
      if [ ! -s $LOGFILE ];then
        rm $LOGFILE
      fi
      if [ ! -e result_reexport/${FILENAME} ];then
        echo "$FILENAME could not be reexported."
      fi
      if [ -e ${PRINT} ];then
        LOGFILE=statistics/${FILENAME%%.xml}.orig.print;
        $PRINT $SBMLMODEL &> ${LOGFILE};
        if [ -e result_reexport/${FILENAME} ];then
          LOGFILE=statistics/${FILENAME%%.xml}.reexported.print;
          $PRINT result_reexport/${FILENAME} &> ${LOGFILE};
        fi
      else
        echo "Error. $PRINT does not exist.";
      fi
      if [ -e ${VALIDATE} ];then
        LOGFILE=validation/${FILENAME%%.xml}.orig.valid;
        $VALIDATE $SBMLMODEL &> $LOGFILE;
        if [ -s $LOGFILE ];then
          ./filterSBMLWarnings.sh $LOGFILE; 
        fi
        if [ -e result_reexport/${FILENAME} ];then
          LOGFILE=validation/${FILENAME%%.xml}.reexported.valid;
          $VALIDATE result_reexport/${FILENAME} &> ${LOGFILE};
          ./filterSBMLWarnings.sh ${LOGFILE}; 
        fi
      else
        echo "Error. $VALIDATE does not exist.";
      fi
    done
  else
    echo "Error. $COPASISE does not exists.";
  fi
else
  echo "Error. $BIOMODELSDIR does not exist.";
fi

