#!/usr/bin/env bash
# Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 


FLEX="$1"
PATH=$PATH:/bin:/usr/bin:/usr/local/bin
SED=${COPASI_SED:-sed}

for arg in $@; do
  SOURCE_FILE=$arg
done

cd "$(dirname "${SOURCE_FILE}")"

SOURCE_FILE="$(basename "${SOURCE_FILE}")"
TARGET_FILE=${SOURCE_FILE/%.*/_lex.cpp}

echo compiling $SOURCE_FILE '==>' $TARGET_FILE

echo ${FLEX} -o $TARGET_FILE $SOURCE_FILE
${FLEX} -o $TARGET_FILE $SOURCE_FILE

${SED} -e 's?<FlexLexer.h>?"copasi/FlexLexer.h"?' \
       -e 's/include <fstream>/include <iostream>/' \
       -e 's/using std::istream;/using namespace std;/' \
       -e 's/FLEX_STD /std::/g' \
       -e '/using std::ostream;/d' \
       -e '/#define yy_current_buffer YY_CURRENT_BUFFER/d' \
       -e '/#include <unistd.h>/d' \
       $TARGET_FILE > $$.tmp && \
mv $$.tmp $TARGET_FILE

if [ x`uname -a | grep -ic cygwin` = x"1" ]; then
  unix2dos $TARGET_FILE
fi
