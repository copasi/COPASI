#!/bin/bash

PATH=$PATH:/bin:/usr/bin:/usr/local/bin

for arg in $@; do
  SOURCE_FILE=$arg
done

if [ x`uname -a | grep -ic cygwin` = x"1" ]; then
  FILE_PREFIX=y
else
  FILE_PREFIX=${SOURCE_FILE/%.*/}
fi

TARGET_FILE_C=${SOURCE_FILE/%.*/_yacc.cpp}
TARGET_FILE_H=${SOURCE_FILE/%.*/_yacc.h}

echo compiling $SOURCE_FILE '==>' $TARGET_FILE_C, $TARGET_FILE_H

echo byacc -dt -b $FILE_PREFIX $SOURCE_FILE
byacc -dt -b $FILE_PREFIX $SOURCE_FILE
sed -e 's/yyparse/yyYaccParser::yyparse/g' \
    -e 's/'$FILE_PREFIX'.tab.c/'$TARGET_FILE_C'/g' \
    -e 's/int yydebug;/int yydebug = 1;/' \
    -e '/getenv()/d' \
    $FILE_PREFIX.tab.c > $$.tmp && \
mv $$.tmp $FILE_PREFIX.tab.c

if [ x`uname -a | grep -ic cygwin` = x"1" ]; then
  unix2dos $FILE_PREFIX.tab.c
  unix2dos $FILE_PREFIX.tab.h
fi
