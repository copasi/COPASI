######################################################################
# $Revision: 1.5 $ $Author: shoops $ $Date: 2003/05/20 01:53:58 $  
######################################################################

# In the case the BUILD_OS is not specified we make a guess.
isEmpty(BUILD_OS) {
  win32 {
    BUILD_OS = WIN32
  } else {
    BUILD_OS = $$system(uname)
  }
}
DEFINES += $${BUILD_OS}

# Common configuration settings
CONFIG += exceptions
CONFIG += rtti
CONFIG += thread

!contains(BUILD_OS, WIN32) {
  # The character # (hex 23) can not be escaped we therefore create 
  # a variable containing it
  HASH = $$system(echo "\\043")
  contains(HASH, \\043){
    HASH = $$system(echo -e "\\043")
  }

  myLex = \
          $(LEX) -t $< | \
          sed -e 's/class istream;/$${HASH}include "copasi.h"/' \
              -e 's/<FlexLexer.h>/"FlexLexer.h"/' \
              -e 's/$${HASH}include <unistd.h>/using namespace std;/' > $@
}

contains(BUILD_OS, Darwin) {
  INCLUDEPATH += /System/Library/Frameworks/vecLib.framework/Headers
  LIBS += -framework vecLib
  LIBS += -framework Carbon
  LIBS += -framework QuickTime
  LIBS += -lz
  CONFIG -= thread
}

contains(BUILD_OS, WIN32) {
  DEFINES -= UNICODE
  QMAKE_LFLAGS_WINDOWS += /NODEFAULTLIB:"msvcrt.lib"

  !isEmpty(MKL_PATH) {
    DEFINES += USE_MKL
    INCLUDEPATH += $${MKL_PATH}/include
    LIBS += # mkl_lapack.lib mkl_p3.lib
    LIBS += # -L$${MKL_PATH}/lib/32"
  } else {
    !isEmpty(CLAPACK_PATH) {
      DEFINES += USE_CLAPACK
      INCLUDEPATH += $${CLAPACK_PATH}/include
      LIBS += $${CLAPACK_PATH}/lib/clapack.lib
    } else {
      error( "Either MKL_PATH or CLAPACK_PATH must be specified )
    }
  }

  !isEmpty(EXPAT_PATH) {
      INCLUDEPATH += $${EXPAT_PATH}/Source/lib
      LIBS += $${EXPAT_PATH}/StaticLibs/libexpat.lib
    } else {
      error( "EXPAT_PATH must be specified )
    }
} 

contains(BUILD_OS, SunOS) {
  !isEmpty(CLAPACK_PATH) {
    DEFINES += USE_CLAPACK
    INCLUDEPATH += $${CLAPACK_PATH}/include
    LIBS += -llapack -lblas -lF77 -lfl
    LIBS += -L$${CLAPACK_PATH}/lib
  } else {
    error( "CLAPACK_PATH must be specified )
  }
}
 
contains(BUILD_OS, Linux) {
  !isEmpty(MKL_PATH) {
    DEFINES += USE_MKL
    INCLUDEPATH += $${MKL_PATH}/include
    LIBS += -lmkl_lapack -lmkl_p3 -lg2c -lpthread
    LIBS +=  -L$${MKL_PATH}/lib/32
  } else {
    !isEmpty(CLAPACK_PATH) {
      DEFINES += USE_CLAPACK
      INCLUDEPATH += $${CLAPACK_PATH}/include
      LIBS += -llapack -lblas -lF77 -lfl
      LIBS += -L$${CLAPACK_PATH}/lib
    } else {
      error( "Either MKL_PATH or CLAPACK_PATH must be specified )
    }
  }
}
