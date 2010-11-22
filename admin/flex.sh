#!/bin/bash

PATH=$PATH:/bin:/usr/bin:/usr/local/bin
AWK=${COPASI_AWK:-gawk}
SED=${COPASI_SED:-sed}

for arg in $@; do
  SOURCE_FILE=$arg
done

PREFIX=`$AWK -- '$0 ~ "%option prefix=" {split($2, out, "\""); print out[2]}' $SOURCE_FILE`

TARGET_FILE=lex.${SOURCE_FILE/%.*/.c}

echo compiling $SOURCE_FILE '==>' ${SOURCE_FILE/%.*/_lex.cpp}

flex  -t $SOURCE_FILE | \
  ${SED} -e 's?<FlexLexer.h>?"copasi/FlexLexer.h"?' \
         -e 's/include <fstream>/include <iostream>/' \
         -e 's/using std::istream;/using namespace std;/' \
         -e '/using std::ostream;/d' \
         -e '/#include <unistd.h>/d' \
         -e '/'${PREFIX}'free *( *yy_start_stack *);/,/yy_delete_buffer *( *YY_CURRENT_BUFFER *) *;/c \
  '${PREFIX}'free(yy_start_stack); \n  yy_delete_buffer(YY_CURRENT_BUFFER); \n  '${PREFIX}'free((yy_buffer_stack));
' \
         > $TARGET_FILE

if [ x`uname -a | grep -ic cygwin` = x"1" ]; then
  unix2dos $TARGET_FILE
fi
