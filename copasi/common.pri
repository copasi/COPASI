######################################################################
# $Revision: 1.43 $ $Author: shoops $ $Date: 2005/03/01 19:24:34 $  
######################################################################

# In the case the BUILD_OS is not specified we make a guess.
isEmpty(BUILD_OS) {
  win32 {
    BUILD_OS = WIN32
  } else {
    BUILD_OS = $$system(uname)
  }
}
DEFINES += $$BUILD_OS
message("Configuring for $${BUILD_OS}.")

TARGETDEPS += Makefile
DEFINES+=XML_STATIC
DEFINES+=LIBSBML_STATIC

# Common configuration settings
CONFIG += exceptions
CONFIG += rtti

debug {
  DEFINES += COPASI_DEBUG
}

!contains(BUILD_OS, WIN32) {
  QMAKE_QMAKE = $(QTDIR)/bin/qmake
  
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
  release {
    contains(TEMPLATE, app) {
      QMAKE_POST_LINK = strip $(TARGET)
    }
  }
 
  INCLUDEPATH += /System/Library/Frameworks/vecLib.framework/Headers
  INCLUDEPATH += /System/Library/Frameworks/Carbon.framework/Headers

  !isEmpty(SBML_PATH){
    LIBS +=  $${SBML_PATH}/lib/libsbml.a
    INCLUDEPATH += $${SBML_PATH}/include
  } else {
    LIBS += -lsbml
  }

  !isEmpty(EXPAT_PATH){
    LIBS+=  $${EXPAT_PATH}/lib/libexpat.a
    INCLUDEPATH += $${EXPAT_PATH}/include
  } else {
    LIBS += -lexpat
  }

  contains(CONFIG, qt) {
    !isEmpty(QWT_PATH){
       LIBS+=  $${QWT_PATH}/lib/libqwt.a
       INCLUDEPATH += $${QWT_PATH}/include
    } else {
      LIBS += -lqwt
    }
    
    LIBS += $(QTDIR)/lib/libqt-mt.a
  
    QMAKE_LIBS_QT =
    QMAKE_LIBS_QT_THREAD = 
  }

  LIBS += -framework vecLib
  LIBS += -framework Carbon
  LIBS += -framework QuickTime
  LIBS += -lz
}

contains(BUILD_OS, WIN32) {
  QMAKE_QMAKE = $(QTDIR)\bin\qmake.exe
  DEFINES -= UNICODE 
  debug {
    QMAKE_LFLAGS_WINDOWS += /NODEFAULTLIB:"msvcrt.lib"
    QMAKE_LFLAGS_CONSOLE += /NODEFAULTLIB:"msvcrt.lib"
  }

  !isEmpty(MKL_PATH) {
    DEFINES += USE_MKL
    QMAKE_CXXFLAGS_DEBUG   += -I"$${MKL_PATH}\include"
    QMAKE_CXXFLAGS_RELEASE += -I"$${MKL_PATH}\include"
    QMAKE_LFLAGS_WINDOWS += /LIBPATH:"$${MKL_PATH}\ia32\lib"
    QMAKE_LFLAGS_CONSOLE += /LIBPATH:"$${MKL_PATH}\ia32\lib"
    LIBS += mkl_lapack.lib mkl_p3.lib mkl_c.lib
  } else {
    !isEmpty(CLAPACK_PATH) {
      DEFINES += USE_CLAPACK
      QMAKE_CXXFLAGS_DEBUG   += -I"$${CLAPACK_PATH}\include"
      QMAKE_CXXFLAGS_RELEASE += -I"$${CLAPACK_PATH}\include"
      QMAKE_LFLAGS_WINDOWS += /LIBPATH:"$${CLAPACK_PATH}\lib"
      QMAKE_LFLAGS_CONSOLE += /LIBPATH:"$${CLAPACK_PATH}\lib"
      LIBS += clapack.lib
    } else {
      error( "Either MKL_PATH or CLAPACK_PATH must be specified" )
    }
  }

  !isEmpty(EXPAT_PATH) {
    QMAKE_CXXFLAGS_DEBUG   += -I"$${EXPAT_PATH}\Source\lib"
    QMAKE_CXXFLAGS_RELEASE += -I"$${EXPAT_PATH}\Source\lib"
    QMAKE_LFLAGS_WINDOWS += /LIBPATH:"$${EXPAT_PATH}\StaticLibs"
    QMAKE_LFLAGS_CONSOLE += /LIBPATH:"$${EXPAT_PATH}\StaticLibs"
    LIBS += libexpatMT.lib
  } else {
    error( "EXPAT_PATH must be specified" )
  }

  !isEmpty(SBML_PATH) {
    QMAKE_CXXFLAGS_DEBUG   += -I"$${SBML_PATH}\include"
    QMAKE_CXXFLAGS_RELEASE += -I"$${SBML_PATH}\include"
    QMAKE_LFLAGS_WINDOWS += /LIBPATH:"$${SBML_PATH}\lib"
    QMAKE_LFLAGS_CONSOLE += /LIBPATH:"$${SBML_PATH}\lib"
    LIBS += libsbml.lib
  } else {
    error( "SBML_PATH must be specified" )
  }

  contains(CONFIG, qt) {
    LIBS += -lqwt
  }
} 

contains(BUILD_OS, SunOS) {
# :TODO: This should be set through configure.
  LIBS += -L/export/home/shoops/copasi/gcc/lib

  release { 
    contains(TEMPLATE, app) {
# Note: This must be the SunOS strip command.
      QMAKE_POST_LINK = /usr/ccs/bin/strip $(TARGET)
    }
  }
 
  !isEmpty(CLAPACK_PATH) {
    DEFINES += USE_CLAPACK
    INCLUDEPATH += $${CLAPACK_PATH}/include
    LIBS += -llapack -lblas -lF77 -lfl
    LIBS += -L$${CLAPACK_PATH}/lib
  } else {
    !isEmpty(LAPACK_PATH) {
      message("Using lapack.")
      DEFINES += USE_CLAPACK
      INCLUDEPATH += $${LAPACK_PATH}/include
      LIBS += -llapack -lblas  -lg2c
      LIBS += -L$${LAPACK_PATH}/lib
    } else {
      error( "Either CLAPACK_PATH or LAPACK_PATH must be specified" )
    }
  }
  !isEmpty(EXPAT_PATH){
      LIBS+=  -L$${EXPAT_PATH}/lib
      INCLUDEPATH += $${EXPAT_PATH}/include
  }
  !isEmpty(SBML_PATH){
      LIBS+=  -L$${SBML_PATH}/lib
      INCLUDEPATH += $${SBML_PATH}/include
  }

  LIBS += -lsbml -lexpat

  contains(CONFIG, qt) {
    !isEmpty(QWT_PATH){
       LIBS+=  -L$${QWT_PATH}/lib
       INCLUDEPATH += $${QWT_PATH}/include
    }
    LIBS += -lqwt
  }

  LIBS += -lSM
}
 
contains(BUILD_OS, Linux) {
  release {
    contains(TEMPLATE, app) {
      QMAKE_POST_LINK = strip $(TARGET)
    }
  }
 
  QMAKE_LFLAGS += -static

  !isEmpty(SBML_PATH){
    LIBS+=  -L$${SBML_PATH}/lib
    INCLUDEPATH += $${SBML_PATH}/include
    LIBS += -lsbml
  }

  !isEmpty(EXPAT_PATH){
    LIBS+=  -L$${EXPAT_PATH}/lib
    INCLUDEPATH += $${EXPAT_PATH}/include
    LIBS += -lexpat
  }

  !isEmpty(MKL_PATH) {
    DEFINES += USE_MKL
    INCLUDEPATH += $${MKL_PATH}/include
    LIBS += -lmkl_lapack -lmkl_p3 -lg2c -lpthread
    LIBS +=  -L$${MKL_PATH}/lib/32
  } else {
    !isEmpty(CLAPACK_PATH) {
      DEFINES += USE_CLAPACK
      INCLUDEPATH += $${CLAPACK_PATH}/include
      INCLUDEPATH += /usr/include/qt3
      LIBS += -llapack -lblas -lF77 -lfl
      LIBS += -L$${CLAPACK_PATH}/lib 
    } else {
      !isEmpty(LAPACK_PATH) {
        message("Using lapack.")
        DEFINES += USE_CLAPACK
        INCLUDEPATH += $${LAPACK_PATH}/include
        LIBS += -llapack -lblas  -lg2c
        LIBS += -L$${LAPACK_PATH}/lib
      } else {
        error( "Either MKL_PATH, CLAPACK_PATH, or LAPACK_PATH must be specified" )
      }
    }
  }

  contains(CONFIG, qt) {
    !isEmpty(QWT_PATH){
       LIBS+=  -L$${QWT_PATH}/lib
       INCLUDEPATH += $${QWT_PATH}/include
    }
    LIBS += -lqwt
  }
}

DEP1.target   = depend
DEP1.depends  = qmake

QMAKE_EXTRA_UNIX_TARGETS += DEP1
