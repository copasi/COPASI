#!/bin/bash

if [ x"$#" = x1 ]; then
  scp calvin.bioinformatics.vt.edu:/usr/local/apache/htdocs/calvin/copasi/alpha-test/index.html $$.index.html
  sed -e 's/COPASI 4.0 Build [0-9]*/COPASI 4.0 Build '$1'/' \
      -e 's/CopasiUI-[0-9]*/CopasiUI-'$1'/' \
      -e 's/Last modified: .*/Last modified: '"`date`"'/' $$.index.html > $$.tmp && \
  scp $$.tmp calvin.bioinformatics.vt.edu:/usr/local/apache/htdocs/calvin/copasi/alpha-test/index.html
  rm $$.tmp $$.index.html
else
  echo usage: newbuild build
fi
