#!/bin/bash

PATH=$PATH:/bin:/usr/bin:/usr/local/bin

SOURCE_FILE=${1/%.*/.cpp}
HEADER_FILE=${1/%.*/.h}

echo clo++ $1 '==>' $SOURCE_FILE, $HEADER_FILE

# Remove old files
[ -e $SOURCE_FILE ] && rm $SOURCE_FILE
[ -e $HEADER_FILE ] && rm $HEADER_FILE

# Compile and post process
clo++ -o c++ $1 && \
sed -e 's/compare([^,]*,[^,]*, *\([^,]*\) *,[^)]*)/compare(\1)/g' $SOURCE_FILE \
> $$ && \
mv $$ $SOURCE_FILE; 

# Apply formating style
[ -e $SOURCE_FILE ] && ../../cvs_admin/c++style $SOURCE_FILE
[ -e $HEADER_FILE ] && ../../cvs_admin/c++style $HEADER_FILE

# Make sure the file is dos formated
if [ x`uname -a | grep -ic cygwin` = x"1" ]; then
  [ -e $SOURCE_FILE ] && unix2dos $SOURCE_FILE
  [ -e $HEADER_FILE ] && unix2dos $HEADER_FILE
fi
