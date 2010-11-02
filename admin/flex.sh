#!/bin/bash

PATH=$PATH:/bin:/usr/bin:/usr/local/bin
AWK=${COPASI_AWK:-gawk}

for arg in $@; do
  SOURCE_FILE=$arg
done

PREFIX=`$AWK -- '$0 ~ "%option prefix=" {split($2, out, "\""); print out[2]}' $SOURCE_FILE`

TARGET_FILE=lex.${SOURCE_FILE/%.*/.c}

echo compiling $SOURCE_FILE '==>' ${SOURCE_FILE/%.*/_lex.cpp}

flex  -t $SOURCE_FILE | \
     sed -e 's?<FlexLexer.h>?"copasi/FlexLexer.h"?' \
         -e 's/include <fstream>/include <iostream>/' \
         -e 's/using std::istream;/using namespace std;/' \
         -e '/using std::ostream;/d' \
         -e '/#include <unistd.h>/d' \
         -e '/yy_delete_buffer *( *YY_CURRENT_BUFFER *) *;/a \
  '${PREFIX}'free((yy_buffer_stack));
' \
         > $TARGET_FILE

if [ x`uname -a | grep -ic cygwin` = x"1" ]; then
  unix2dos $TARGET_FILE
fi
