#!/bin/bash
# Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

CopasiSE=${1:-../../build/copasi/CopasiSE/CopasiSE}
shift

function runTest () {
  echo Test: ${1}
  rm ${1}.1.txt > /dev/null 3>&1 2>&1 
  ${CopasiSE} --nologo ${1}.cps > /dev/null
  head -n 1 ${1}.1.txt.tgt > ${1}.1.csv
  ndiff -sbml -abserr 1e-5 ${1}.1.txt ${1}.1.txt.tgt >> ${1}.1.csv || echo ${1} failed
}

SCHEDULED="$@"

if [ _${SCHEDULED} == _ ]; then
  SCHEDULED=$(ls -1 *.cps)
fi

for f in ${SCHEDULED}; do
  runTest $(basename $f .cps)
done
