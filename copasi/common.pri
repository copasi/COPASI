# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/common.pri,v $ 
#   $Revision: 1.93.2.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/10/09 18:10:00 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# $Revision: 1.93.2.1 $ $Author: shoops $ $Date: 2008/10/09 18:10:00 $  
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
message("Configuring for $${BUILD_OS} with QTDIR=$(QTDIR).")

TARGETDEPS += Makefile

# Common configuration settings
CONFIG += exceptions
CONFIG += rtti
CONFIG += thread

#ifdef COPASI_LICENSE_COM
# COPASI License to use
DEFINES -= COPASI_LICENSE_US
DEFINES -= COPASI_LICENSE_DE
DEFINES -= COPASI_LICENSE_COM
DEFINES += COPASI_LICENSE_$$USE_LICENSE
#endif // COPASI_LICENSE_COM

INCLUDEPATH += ../..
QMAKE_CFLAGS   += $$(CFLAGS)
QMAKE_CXXFLAGS += $$(CXXFLAGS)
QMAKE_LFLAGS  += $$(LDFLAGS)

DEFINES += COPASI_TSSA

debug {
  DEFINES += COPASI_DEBUG
    
  isEmpty(COPASI_SRC_PACKAGE) {
    # DEFINES += COPASI_TSS
    #  stoichiometric stability analysis:
    # DEFINES += COPASI_SSA
  }
}

isEmpty(COPASI_SRC_PACKAGE) {
  DEFINES += HAVE_MML
}

contains(STATIC_LINKAGE, yes) {
  DEFINES+=XML_STATIC
  DEFINES+=LIBSBML_STATIC
}

!contains(BUILD_OS, WIN32) {
  #Release code optimization
  QMAKE_CFLAGS_RELEASE -= -O1
  QMAKE_CFLAGS_RELEASE -= -O2
  QMAKE_CFLAGS_RELEASE -= -O4
  QMAKE_CFLAGS_RELEASE += -O3

  QMAKE_CXXFLAGS_RELEASE -= -O1
  QMAKE_CXXFLAGS_RELEASE -= -O2
  QMAKE_CXXFLAGS_RELEASE -= -O4
  QMAKE_CXXFLAGS_RELEASE += -O3

  QMAKE_QMAKE = $(QTDIR)/bin/qmake
  QMAKE_LEX = ../../admin/flex.sh
  QMAKE_YACC = ../../admin/yacc.sh
  
  # The character # (hex 23) can not be escaped we therefore create 
  # a variable containing it
  HASH = $$system(echo "\\043")
  contains(HASH, \\043){
    HASH = $$system(echo -e "\\043")
  }
}


contains(BUILD_OS, Darwin) {  
  release {
    contains(TEMPLATE, app) {
      QMAKE_POST_LINK = strip $(TARGET)
    }
  }
 
  INCLUDEPATH += /System/Library/Frameworks/Accelerate.framework/Headers
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

  !isEmpty(RAPTOR_PATH){
    LIBS+=  $${RAPTOR_PATH}/lib/libraptor.a
    INCLUDEPATH += $${RAPTOR_PATH}/include
  } else {
    LIBS += -lraptor
  }

  contains(CONFIG, qt) {
    !isEmpty(SBW_PATH){
      LIBS+=  $${SBW_PATH}/lib/libSBW.a
      INCLUDEPATH += $${SBW_PATH}/include
      DEFINES += COPASI_SBW_INTEGRATION
      DEFINES += LINUX DARWIN 
    } 
  
    !isEmpty(QWT_PATH){
       LIBS+=  $${QWT_PATH}/lib/libqwt.a
       INCLUDEPATH += $${QWT_PATH}/include
    } else {
      LIBS += -lqwt
    }
    
    !isEmpty(QWT3D_PATH){
      LIBS +=  $${QWT3D_PATH}/lib/libqwtplot3d.a
      INCLUDEPATH += $${QWT3D_PATH}/include
    } else {
      LIBS += -lqwtplot3d
    }
 
    LIBS += $(QTDIR)/lib/libqt-mt.a
    
    
    QMAKE_LIBS_QT =
    QMAKE_LIBS_QT_THREAD = 
  }

  LIBS += -framework Accelerate
  LIBS += -framework Carbon
  LIBS += -framework QuickTime
  LIBS += -lz
}

contains(BUILD_OS, WIN32) {
  QMAKE_QMAKE = $(QTDIR)\bin\qmake.exe
  QMAKE_LEX = C:\cygwin\bin\bash ../../admin/flex.sh
  QMAKE_YACC = C:\cygwin\bin\bash ../../admin/yacc.sh

  DEFINES -= UNICODE
   
  debug {
    !win32-msvc2005 {
      QMAKE_LFLAGS += /NODEFAULTLIB:"libcmt.lib"
    }

    QMAKE_LFLAGS += /NODEFAULTLIB:"msvcrt.lib"
  }
  
  #Release code optimization
  QMAKE_CFLAGS_RELEASE -= -O1
  QMAKE_CFLAGS_RELEASE += -O2

  QMAKE_CXXFLAGS_RELEASE -= -O1
  QMAKE_CXXFLAGS_RELEASE += -O2

  !isEmpty(MKL_PATH) {
    DEFINES += USE_MKL
    QMAKE_CXXFLAGS += -I"$${MKL_PATH}\include"
    QMAKE_LFLAGS += /LIBPATH:"$${MKL_PATH}\ia32\lib"
    QMAKE_LFLAGS += /LIBPATH:"$${MKL_PATH}\..\Compiler\C++\9.0\IA32\Lib"
    LIBS += mkl_c.lib
  } else {
    !isEmpty(CLAPACK_PATH) {
      DEFINES += USE_CLAPACK
      QMAKE_CXXFLAGS   += -I"$${CLAPACK_PATH}\include"
      QMAKE_LFLAGS += /LIBPATH:"$${CLAPACK_PATH}\lib"
      LIBS += clapack.lib
    } else {
      error( "Either MKL_PATH or CLAPACK_PATH must be specified" )
    }
  }

  !isEmpty(EXPAT_PATH) {
    QMAKE_CXXFLAGS   += -I"$${EXPAT_PATH}\Source\lib"
    QMAKE_CXXFLAGS   += -I"$${EXPAT_PATH}\include"
    QMAKE_LFLAGS += /LIBPATH:"$${EXPAT_PATH}\StaticLibs"
    QMAKE_LFLAGS += /LIBPATH:"$${EXPAT_PATH}\bin"
    QMAKE_LFLAGS += /LIBPATH:"$${EXPAT_PATH}\lib"
    contains(STATIC_LINKAGE, yes) {
      LIBS += libexpatMT.lib
    } else {
      LIBS += libexpat.lib
    }
  } else {
    error( "EXPAT_PATH must be specified" )
  }

  # Add libsbml
  win32-msvc2005 {
    release {
      LIBS += libsbml.lib
    }
    debug {
      LIBS += libsbmlD.lib
    }
  } else {
    LIBS += libsbml.lib
  }
  
  !isEmpty(SBML_PATH) {
    QMAKE_CXXFLAGS   += -I"$${SBML_PATH}\include"
    QMAKE_LFLAGS += /LIBPATH:"$${SBML_PATH}\lib"
    QMAKE_LFLAGS += /LIBPATH:"$${SBML_PATH}\bin"
  } else {
    error( "SBML_PATH must be specified" )
  }

# The raptor library
  release {
    LIBS += raptor.lib
  }
  debug {
    LIBS += raptorD.lib
  }
    
  !isEmpty(RAPTOR_PATH) {
    QMAKE_CXXFLAGS   += -I"$${RAPTOR_PATH}\include"
    QMAKE_LFLAGS += /LIBPATH:"$${RAPTOR_PATH}\lib"
  } else {
    error( "RAPTOR_PATH must be specified" )
  }
  
  contains(CONFIG, qt) {
    !isEmpty(SBW_PATH){
      release: LIBS += $${SBW_PATH}/lib/SBW.lib
      debug: LIBS += $${SBW_PATH}/lib/SBWD.lib
      
      INCLUDEPATH += $${SBW_PATH}/include
      DEFINES += COPASI_SBW_INTEGRATION
      DEFINES += WIN32
    }
     
    LIBS += -lqwt
    
    release: LIBS += -lqwtplot3d
    debug: LIBS += -lqwtplot3dD
  }
} 

contains(BUILD_OS, SunOS) {
contains(STATIC_LINKAGE, yes) {
# :TODO: This should be set through configure.
  LIBS += -L/export/home/shoops/copasi/gcc/lib
}

  release { 
    contains(TEMPLATE, app) {
# Note: This must be the SunOS strip command.
      QMAKE_POST_LINK = /usr/ccs/bin/strip $(TARGET)
    }
  }
 
  !isEmpty(CLAPACK_PATH) {
    DEFINES += USE_CLAPACK
    INCLUDEPATH += $${CLAPACK_PATH}/include
#    LIBS += -llapack -lblas -lF77 -lfl
    LIBS += -llapack -lblas -lF77
    LIBS += -L$${CLAPACK_PATH}/lib
  } else {
    !isEmpty(LAPACK_PATH) {
      message("Using lapack.")
      DEFINES += USE_LAPACK
      INCLUDEPATH += $${LAPACK_PATH}/include
      LIBS += -llapack -lblas  -lg2c
      LIBS += -L$${LAPACK_PATH}/lib
    } else {
      message("Using sunperf.")
      DEFINES += USE_SUNPERF
      LIBS += -lsunperf
      QMAKE_CFLAGS   += -dalign
      QMAKE_CXXFLAGS   += -dalign
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

# The raptor library
  LIBS += -lraptor
  !isEmpty(RAPTOR_PATH){
      LIBS+=  -L$${RAPTOR_PATH}/lib
      INCLUDEPATH += $${RAPTOR_PATH}/include
  }
  
  contains(CONFIG, qt) {
    !isEmpty(SBW_PATH){
      LIBS+=  $${SBW_PATH}/lib/libSBW.a
      INCLUDEPATH += $${SBW_PATH}/include
      DEFINES += COPASI_SBW_INTEGRATION
      DEFINES += LINUX SOLARIS
    } 

    !isEmpty(QWT_PATH){
       LIBS+=  -L$${QWT_PATH}/lib
       INCLUDEPATH += $${QWT_PATH}/include
    }
    LIBS += -lqwt
    
    !isEmpty(QWT3D_PATH){
      LIBS += -L$${QWT3D_PATH}/lib/
      INCLUDEPATH += $${QWT3D_PATH}/include
    } else {
      LIBS += -lqwtplot3d
    }
    
    LIBS += -lSM
  } else {
    QMAKE_LIBS_THREAD -= -lpthread
    QMAKE_LIBS_THREAD -= -lrt
  }
}
 
contains(BUILD_OS, Linux) {
  release {
    contains(TEMPLATE, app) {
      QMAKE_POST_LINK = strip $(TARGET)
    }
  }

  contains(PACKAGE, yes) {
    QMAKE_LFLAGS -= -static
  }
  else {
    contains(STATIC_LINKAGE, yes) {
      QMAKE_LFLAGS += -static
    }
    else {
      QMAKE_LFLAGS -= -static
    }
  }

  !isEmpty(SBML_PATH){
    INCLUDEPATH += $${SBML_PATH}/include
    INCLUDEPATH += $${SBML_PATH}/include/sbml

    contains(PACKAGE, yes) {
      LIBS += $${SBML_PATH}/lib/libsbml.a
    }
    else {
      LIBS += -L$${SBML_PATH}/lib
      LIBS += -lsbml
    }
  }
  else { 
    contains(PACKAGE, yes) {
      error("SBML_PATH must be given.")
    }
    else {
      LIBS += -lsbml
    }
  }

  !isEmpty(EXPAT_PATH){
    INCLUDEPATH += $${EXPAT_PATH}/include

    contains(PACKAGE, yes) {
      LIBS += $${EXPAT_PATH}/lib/libexpat.a
    }
    else {
      LIBS += -L$${EXPAT_PATH}/lib
      LIBS += -lexpat
    }
  }
  else { 
    contains(PACKAGE, yes) {
      error("EXPAT_PATH must be given.")
    }
    else {
      LIBS += -lexpat
    }
  }

# The raptor library
  !isEmpty(RAPTOR_PATH){
      LIBS +=  -L$${RAPTOR_PATH}/lib
      INCLUDEPATH += $${RAPTOR_PATH}/include

    contains(PACKAGE, yes) {
      LIBS += $${RAPTOR_PATH}/lib/libraptor.a
    }
    else {
      LIBS += -L$${RAPTOR_PATH}/lib
      LIBS += -lraptor
    }
  }
  else { 
    contains(PACKAGE, yes) {
      error("RAPTOR_PATH must be given.")
    }
    else {
      LIBS += -lraptor
    }
  }
  
  !isEmpty(MKL_PATH) {
    DEFINES += USE_MKL
    INCLUDEPATH += $${MKL_PATH}/include
#    LIBS += -lmkl_lapack -lmkl_ia32 -lg2c -lpthread
    LIBS += -lmkl_lapack -lmkl_ia32 -lguide -lpthread
    LIBS  +=  -L$${MKL_PATH}/lib/32
  } else {
    !isEmpty(CLAPACK_PATH) {
      DEFINES += USE_CLAPACK
      INCLUDEPATH += $${CLAPACK_PATH}/include
#      LIBS += -llapack -lblas -lF77 -lfl
      LIBS += -llapack -lblas -lF77
      LIBS += -L$${CLAPACK_PATH}/lib 
    } else {
      !isEmpty(LAPACK_PATH) {
        message("Using lapack.")
        DEFINES += USE_LAPACK
        INCLUDEPATH += $${LAPACK_PATH}/include

        contains(PACKAGE, yes) {
          LIBS += $${LAPACK_PATH}/lib/liblapack.a 
          LIBS += $${LAPACK_PATH}/lib/libblas.a
          LIBS += $$system(locate libg2c.a)
        }
        else {
          LIBS += -L$${LAPACK_PATH}/lib
          LIBS += -llapack 
          LIBS += -lblas
          LIBS += -lg2c
        }
      } else {
        error( "Either MKL_PATH, CLAPACK_PATH, or LAPACK_PATH must be specified" )
      }
    }
  }

  contains(CONFIG, qt) {
    !isEmpty(SBW_PATH){
      LIBS+=  $${SBW_PATH}/lib/libSBW.a
      INCLUDEPATH += $${SBW_PATH}/include
      DEFINES += COPASI_SBW_INTEGRATION
      DEFINES += LINUX 
    }
     
    !isEmpty(QWT_PATH){
       LIBS +=  -L$${QWT_PATH}/lib
       INCLUDEPATH += $${QWT_PATH}/include
    }
    LIBS += -lqwt

    !isEmpty(QWT3D_PATH){
      LIBS += -L$${QWT3D_PATH}/lib/
      INCLUDEPATH += $${QWT3D_PATH}/include
    } else {
      LIBS += -lqwtplot3d
    }
  }
}

DEP1.target   = depend
DEP1.depends  = qmake

QMAKE_EXTRA_UNIX_TARGETS += DEP1

!equals(TEMPLATE, subdirs) {
  # Copy the sources for the tar ball
  src_distribution.depends = Makefile
  src_distribution.commands =   \
    $(CHK_DIR_EXISTS) ../../copasi_src || $(MKDIR) ../../copasi_src; \
    $(CHK_DIR_EXISTS) ../../copasi_src/copasi || \
      $(MKDIR) ../../copasi_src/copasi; \
    $(CHK_DIR_EXISTS) ../../copasi_src/copasi/$$SRC_TARGET || \
      $(MKDIR) ../../copasi_src/copasi/$$SRC_TARGET; \
    $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) \
      ../../copasi_src/copasi/$$SRC_TARGET/

  QMAKE_EXTRA_UNIX_TARGETS += src_distribution
}
