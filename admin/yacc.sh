#!/bin/bash

PATH=$PATH:/bin:/usr/bin:/usr/local/bin

SOURCE_FILE=$4
TARGET_FILE_C=${SOURCE_FILE/%.*/_yacc.cpp}
TARGET_FILE_H=${SOURCE_FILE/%.*/_yacc.h}

echo compiling $SOURCE_FILE '==>' $TARGET_FILE_C, $TARGET_FILE_H

byacc -dt $SOURCE_FILE
sed -e 's/yyparse /yyYaccParser::yyparse /g' \
    -e 's/y.tab.c/'$TARGET_FILE_C'/g' \
    -e 's/int yydebug;/int yydebug = 1;/' \
    y.tab.c > $$.tmp && \
mv $$.tmp y.tab.c

if [ x`uname -a | grep -ic cygwin` = x"1" ]; then
  unix2dos y.tab.c
  unix2dos y.tab.h
fi
