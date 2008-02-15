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
else
  COPASISE=${COPASIDIR}/copasi/CopasiSE/CopasiSE;
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
        ./convertCPSToSBML.sh $COPASISE $CPSFILE result_export/${FILENAME%%.xml}.old.xml ${LOGFILE}.old;
        ./convertCPSToNewSBML.sh $COPASISE $CPSFILE result_export/${FILENAME%%.xml}.new.xml ${LOGFILE}.new;
        if [ ! -s ${LOGFILE}.old ];then
          rm ${LOGFILE}.old
        fi
        if [ ! -s ${LOGFILE}.new ];then
          rm ${LOGFILE}.new
        fi
        if [ -e result_export/${FILENAME%%.xml}.old.xml ];then
          /sw/bin/python ./rewriteXML.py result_export/${FILENAME%%.xml}.old.xml ./tmp.xml
          xmllint --format --noblanks ./tmp.xml > result_export/${FILENAME%%.xml}.old.xml 
          rm ./tmp.xml
          if [ -e ${PRINT} ];then
            LOGFILE=statistics/${FILENAME%%.xml}.old.print;
            $PRINT result_export/${FILENAME%%.xml}.old.xml &> ${LOGFILE};
          else
            echo "Error. $PRINT does not exist.";
          fi
          if [ -e ${VALIDATE} ];then
            LOGFILE=validation/${FILENAME%%.xml}.exported-old.valid;
            $VALIDATE result_export/${FILENAME%%.xml}.old.xml &> $LOGFILE;
            # remove some of the warnings
            ./filterSBMLWarnings.sh ${LOGFILE}; 
          else
            echo "Error. $VALIDATE does not exist.";
          fi
        else
          echo "Could not create ${FILENAME%%.xml}.old.xml from $CPSFILE."
        fi
        if [ -e result_export/${FILENAME%%.xml}.new.xml ];then
          /sw/bin/python ./compareSBMLFiles.py result_export/${FILENAME%%.xml}.old.xml result_export/${FILENAME%%.xml}.new.xml result_export/${FILENAME%%.xml}.new.reordered.xml 
          xmllint --noblanks --format result_export/${FILENAME%%.xml}.new.reordered.xml > ./tmp.xml 
          mv ./tmp.xml result_export/${FILENAME%%.xml}.new.reordered.xml
 if [ -e ${PRINT} ];then
            LOGFILE=statistics/${FILENAME%%.xml}.orig.new.print;
            $PRINT result_export/${FILENAME%%.xml}.new.xml &> ${LOGFILE};
          else
            echo "Error. $PRINT does not exist.";
          fi
          if [ -e ${VALIDATE} ];then
            LOGFILE=validation/${FILENAME%%.xml}.exported-new.valid;
            $VALIDATE result_export/${FILENAME%%.xml}.new.xml &> $LOGFILE;
            # remove some of the warnings
            ./filterSBMLWarnings.sh ${LOGFILE}; 
          else
            echo "Error. $VALIDATE does not exist.";
          fi
        else
          echo "Could not create ${FILENAME%%.xml}.new.xml from $CPSFILE."
        fi
      else
        echo "$CPSFILE could not be created."
      fi
      LOGFILE=result_reexport/${FILENAME%%.xml}.s2slog;
      ./convertSBMLToSBML.sh $COPASISE $SBMLMODEL result_reexport/${FILENAME%%.xml}.old.xml ${LOGFILE}.old;
      ./convertSBMLToNewSBML.sh $COPASISE $SBMLMODEL result_reexport/${FILENAME%%.xml}.new.xml ${LOGFILE}.new;
      if [ ! -s ${LOGFILE}.old ];then
        rm ${LOGFILE}.old
      fi
      if [ ! -e result_reexport/${FILENAME%%.xml}.old.xml ];then
        echo "${FILENAME%%.xml}.old.xml could not be reexported."
      fi
      if [ ! -s ${LOGFILE}.new ];then
        rm ${LOGFILE}.new
      fi
      if [ ! -e result_reexport/${FILENAME%%.xml}.new.xml ];then
        echo "${FILENAME%%.xml}.new.xml could not be reexported."
      fi
      #/sw/bin/python ./compareSBMLFiles.py result_reexport/${FILENAME%%.xml}.old.xml result_reexport/${FILENAME%%.xml}.new.xml result_reexport/${FILENAME%%.xml}.new.reordered.xml 
      if [ -e ${PRINT} ];then
        LOGFILE=statistics/${FILENAME%%.xml}.orig.print;
        $PRINT $SBMLMODEL &> ${LOGFILE};
        if [ -e result_reexport/${FILENAME%%.xml}-old.xml ];then
          LOGFILE=statistics/${FILENAME%%.xml}.reexported.old.print;
          $PRINT result_reexport/${FILENAME%%.xml}-old.xml &> ${LOGFILE};
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
        if [ -e result_reexport/${FILENAME%%.xml}-old.xml ];then
          LOGFILE=validation/${FILENAME%%.xml}.reexported.old.valid;
          $VALIDATE result_reexport/${FILENAME%%.xml}-old.xml &> ${LOGFILE};
          ./filterSBMLWarnings.sh ${LOGFILE}; 
        fi
      else
        echo "Error. $VALIDATE does not exist.";
      fi
      if [ -e ${PRINT} ];then
        if [ -e result_reexport/${FILENAME%%.xml}-new.xml ];then
          LOGFILE=statistics/${FILENAME%%.xml}.reexported.new.print;
          $PRINT result_reexport/${FILENAME%%.xml}-new.xml &> ${LOGFILE};
        fi
      else
        echo "Error. $PRINT does not exist.";
      fi
      if [ -e ${VALIDATE} ];then
        if [ -e result_reexport/${FILENAME%%.xml}-new.xml ];then
          LOGFILE=validation/${FILENAME%%.xml}.reexported.new.valid;
          $VALIDATE result_reexport/${FILENAME%%.xml}-new.xml &> ${LOGFILE};
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

