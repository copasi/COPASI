#!/usr/bin/env bash
# Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the 
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


YACC="$1"
PATH=$PATH:/bin:/usr/bin:/usr/local/bin

for arg in $@; do
  SOURCE_FILE=$arg
done

cd "$(dirname "${SOURCE_FILE}")"

SOURCE_FILE="$(basename "${SOURCE_FILE}")"
FILE_PREFIX="${SOURCE_FILE/%.*/}"

TARGET_FILE_C=${SOURCE_FILE/%.*/_yacc.cpp}
TARGET_FILE_H=${SOURCE_FILE/%.*/_yacc.hpp}

echo compiling $SOURCE_FILE '==>' $TARGET_FILE_C, $TARGET_FILE_H

echo ${YACC} -dt -b $FILE_PREFIX -p $FILE_PREFIX $SOURCE_FILE
${YACC} -dt -b $FILE_PREFIX -p $FILE_PREFIX $SOURCE_FILE

# We make sure that the file have the expected endings.
[ -e $FILE_PREFIX.tab.cpp ] && mv $FILE_PREFIX.tab.cpp ${TARGET_FILE_C}
[ -e $FILE_PREFIX.tab.hpp ] && mv $FILE_PREFIX.tab.hpp ${TARGET_FILE_H}

sed -e 's/'$FILE_PREFIX'parse/yyparse/g' \
    -e '/#define yylex/d' \
    -e '/int yyparse (.*);/d' \
    -e 's/'$FILE_PREFIX'.tab.cpp/'$TARGET_FILE_C'/g' \
    -e 's/'$FILE_PREFIX'.tab.hpp/'$TARGET_FILE_H'/g' \
    -e 's/int yydebug;/int yydebug = YYDEBUG;/' \
    -e '/getenv()/d' \
    ${TARGET_FILE_C} > $$.tmp && \
mv $$.tmp ${TARGET_FILE_C}

if [ x`uname -a | grep -ic cygwin` = x"1" ]; then
  unix2dos ${TARGET_FILE_C}
  unix2dos ${TARGET_FILE_H}
fi
