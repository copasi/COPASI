# The character # (hex 23) can not be escaped we therefore create a variable containing it
HASH = $$system(echo "\\043")
contains(HASH, \\043){
  HASH = $$system(echo -e "\\043")
}

myLex = \
        $(LEX) -t $< | \
        sed -e 's/class istream;/$${HASH}include "copasi.h"/' \
            -e 's/<FlexLexer.h>/"FlexLexer.h"/' \
            -e 's/$${HASH}include <unistd.h>/using namespace std;/' > $@

contains(OS, Darwin) {
  INCLUDEPATH += /System/Library/Frameworks/vecLib.framework/Headers
}

win32{
  OS = win32
} else {
  OS = $$system(uname)
}

contains(OS, SunOS) {
  !isEmpty(CLAPACK_PATH) {
    INCLUDEPATH += $${CLAPACK_PATH}/include
    LIBS += -llapack -lblas -lF77 -lfl
    LIBS +=  $${CLAPACK_PATH}/lib
  } else {
    error( "CLAPACK_PATH must be specified )
  }
}
 
contains(OS, Linux) {
  !isEmpty(MKL_PATH) {
    INCLUDEPATH += $${MKL_PATH}/include
    LIBS += -lmkl_lapack -lmkl_p3 -lg2c -lpthread
    LIBS +=  $${MKL_PATH}/lib/32
  } else !isEmpty(CLAPACK_PATH) {
    INCLUDEPATH += $${CLAPACK_PATH}/include
    LIBS += -llapack -lblas -lF77 -lfl
    LIBS +=  $${CLAPACK_PATH}/lib
  } else {
    error( "Either MKL_PATH or CLAPACK_PATH must be specified )
  }
}
