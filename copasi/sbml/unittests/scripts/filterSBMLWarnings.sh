#!/bin/sh

# the script uses sed to remove some warnings
# from validation results
# the validation result ihas to be in the file passed as the only ocommandline
# argument
# which warnings will be filtered is determined by the file
# filteredSBMLWarnings.sed
FILENAME=$1
if [ -s $FILENAME ];then
  sed -f ./filteredSBMLWarnings.sed $FILENAME > ${FILENAME}.tmp && mv ${FILENAME}.tmp ${FILENAME}
fi
