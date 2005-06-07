#!/bin/bash

PATH=$PATH:/bin:/usr/bin:/usr/local/bin

SOURCE_FILE=$4
TARGET_FILE_C=y.tab.c

echo $SOURCE_FILE
echo $TARGET_FILE

byacc -dt $SOURCE_FILE
sed -e 's/yyparse /yyYaccParser::yyparse /g' \
    -e 's/int yydebug;/int yydebug = 1;/' \
    $TARGET_FILE_C > $$.tmp && \
mv $$.tmp $TARGET_FILE_C

if [ x`uname -a | grep -ic cygwin` = x"1" ]; then
  unix2dos $TARGET_FILE_C $TARGET_FILE_H
fi
