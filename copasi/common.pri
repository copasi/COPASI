# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/common.pri,v $ 
#   $Revision: 1.132 $ 
#   $Name:  $ 
# End CVS Header 

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# $Revision: 1.132 $ $Author: shoops $ $Date: 2011/11/10 15:49:44 $  
######################################################################

# In the case the BUILD_OS is not specified we make a guess.
isEmpty(BUILD_OS) {
  win32 {
    BUILD_OS = WIN32

    MY_QT4DIR = $$system(echo %QT4DIR%)
    contains(MY_QT4DIR, %QT4DIR%) {
      MY_QTDIR = $$system(echo %QTDIR%)
      contains(MY_QTDIR, %QTDIR%) {
        QMAKE_QMAKE = qmake.exe
        !build_pass: message("Configuring for $${BUILD_OS} with QTDIR=???.")
      } else {
        QMAKE_QMAKE = $(QTDIR)/bin/qmake.exe
        !build_pass: message("Configuring for $${BUILD_OS} with QTDIR=$(QTDIR).")
      }
	} else {
      QMAKE_QMAKE = $(QT4DIR)/bin/qmake.exe
      !build_pass: message("Configuring for $${BUILD_OS} with QTDIR=$(QT4DIR).")
	}

  } else {
    BUILD_OS = $$system(uname)
    message("Configuring for $${BUILD_OS} with QTDIR=$(QTDIR).")
  }
}
DEFINES += $$BUILD_OS

POST_TARGETDEPS += Makefile

# Common configuration settings
CONFIG += exceptions
CONFIG += rtti
CONFIG += thread

contains(CONFIG, qt) {
    QT += webkit
}

INCLUDEPATH += ../..
QMAKE_CFLAGS   += $$(CFLAGS)
QMAKE_CXXFLAGS += $$(CXXFLAGS)
QMAKE_LFLAGS  += $$(LDFLAGS)

DEFINES += WITH_CSPMETHOD

# the following flag enables Svens unit indentification code
# right now this still has some bugs and has to be disabled
# for releases
# DEFINES += USE_SBMLUNIT

# enable this to build support for the render extension
# DEFINES += USE_CRENDER_EXTENSION

# enable this to build with Svens layout generation code.
# This allows users to create new layouts for their models.
# This is not finished yet and should not be enabled per default 
# DEFINES += COPASI_AUTOLAYOUT
#
# This enables the code for displaying elementary mode analysis results 
# in the graph.
# This needs some more testing, but it should be quite stable.
# Since this depends heavily on the existence of layouts, I would only enable it
# once the autolayout has been finished.
#DEFINES += ELEMENTARY_MODE_DISPLAY

# This enables the code for the animation of flux data
# When this is enabled, the time course task will collect data
# on species concentrations or amounts as well as concentration
# or particle fluxes when a time course simulation is run.
# This data can be used by the layout windows to display animations
# of changing species concentrations and/or changing fluxes.
#DEFINES += FLUX_ANIMATION

# this flag enables new code to import layout information from 
# CellDesigner annotations
# Right now this is pretty much limited to the bare layout stuff.
#DEFINES += CELLDESIGNER_IMPORT

# enable this to get screenshots from the OpenGL 
# framebuffer. These should provide higher quality 
# anitaliasing and they should work on more systems
#DEFINES += FRAMEBUFFER_SCREENSHOTS

# flag to use Svens SBML unit identification framework
#define USE_SBMLUNIT

debug {
  DEFINES += COPASI_DEBUG
  DEFINES += COPASI_EXTUNIT
  # DEFINES += WITH_MERGEMODEL
  DEFINES += COPASI_NONLIN_DYN
  }

!contains(COPASI_SRC_PACKAGE, true)  {
  DEFINES += HAVE_MML
}

win32: STATIC_LINKAGE = yes

contains(STATIC_LINKAGE, yes) {
  DEFINES += XML_STATIC
  DEFINES += LIBSBML_STATIC
  DEFINES += LIBLAX_STATIC
  DEFINES += RAPTOR_STATIC
  DEFINES += SBW_STATIC
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

    MY_UNIVERSAL = $$system(echo $UNIVERSAL)
    contains(MY_UNIVERSAL, yes) {
       message("Creating universal 32 bit binaries.")
       CONFIG += x86 ppc
       QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.4u.sdk
    }
  }
  # on Mac OS X 10.6 x86 has to be added to config to make sure COPASI is build
  # as a 32 bit version, gcc on 10.6 builds 64 bit binaries by default
  #CONFIG += x86
 
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
  }

  LIBS += -framework Accelerate
  LIBS += -framework Carbon
  LIBS += -framework QuickTime
  LIBS += -lz

# only needed for the class CLSimpleImageTexturizer which is only
# needed if we want to create bitmaps from layouts in the backend
#  contains(DEFINES, USE_CRENDER_EXTENSION){
#    INCLUDEPATH += /opt/local/include
#    LIBS += -L/opt/local/lib -lpng
#    LIBS += -ljpeg
#  }  
}

contains(BUILD_OS, WIN32) {
  CONFIG += debug_and_release

  win32-icc: {
    !build_pass: message("Using Intel Compiler.")
  }

  !contains(QMAKE_HOST.arch, x86_64) {
    !build_pass: message("x86 build")
    COPASI_ARCH = 32
    QMAKE_LFLAGS += /MACHINE:X86
  } else {
    !build_pass: message("x86_64 build")
    COPASI_ARCH = 64
    QMAKE_CFLAGS += /Wp64
    QMAKE_LFLAGS += /MACHINE:X64
  }

  !isEmpty(INTELRD_PATH) {
    QMAKE_LFLAGS   += /LIBPATH:\""$${INTELRD_PATH}"\"
  }
  
  QMAKE_LEX = C:/cygwin/bin/bash ../../admin/flex.sh
  QMAKE_YACC = C:/cygwin/bin/bash ../../admin/yacc.sh

  DEFINES -= UNICODE
  DEFINES += _CRT_SECURE_NO_WARNINGS
  
  #Release code optimization
  QMAKE_CFLAGS_RELEASE   -= -O1
  QMAKE_CFLAGS_RELEASE   *= -O2

  QMAKE_CXXFLAGS_RELEASE -= -O1
  QMAKE_CXXFLAGS_RELEASE *= -O2
  
  contains(RUNTIME, MT) {
    release: RUNTIME = MT
    debug:   RUNTIME = MTd
    
    QMAKE_CFLAGS_RELEASE   -= -MD
    QMAKE_CFLAGS_RELEASE   *= -MT
    QMAKE_CFLAGS_DEBUG     -= -MDd
    QMAKE_CFLAGS_DEBUG     *= -MTd
	
    QMAKE_CXXFLAGS_RELEASE -= -MD
    QMAKE_CXXFLAGS_RELEASE *= -MT
    QMAKE_CXXFLAGS_DEBUG   -= -MDd
    QMAKE_CXXFLAGS_DEBUG   *= -MTd
	
    QMAKE_LFLAGS *= /NODEFAULTLIB:"msvcrt.lib"
    QMAKE_LFLAGS *= /NODEFAULTLIB:"msvcrtd.lib"
    QMAKE_LFLAGS *= /NODEFAULTLIB:"msvcprt.lib"
    QMAKE_LFLAGS *= /NODEFAULTLIB:"msvcprtd.lib"
    
    release: QMAKE_LFLAGS *= /NODEFAULTLIB:"libcmtd.lib"
    
    debug: QMAKE_LFLAGS *= /NODEFAULTLIB:"libcmt.lib"
  } else {
    release: RUNTIME = MD
    debug:   RUNTIME = MDd
    
    QMAKE_CFLAGS_RELEASE   -= -MT
    QMAKE_CFLAGS_RELEASE   *= -MD
    QMAKE_CFLAGS_DEBUG     -= -MTd
    QMAKE_CFLAGS_DEBUG     *= -MDd
       
    QMAKE_CXXFLAGS_RELEASE -= -MT
    QMAKE_CXXFLAGS_RELEASE *= -MD
    QMAKE_CXXFLAGS_DEBUG   -= -MTd
    QMAKE_CXXFLAGS_DEBUG   *= -MDd
	
    QMAKE_LFLAGS *= /NODEFAULTLIB:"libcmt.lib"
    QMAKE_LFLAGS *= /NODEFAULTLIB:"libcmtd.lib"
    
    release {
      QMAKE_LFLAGS *= /NODEFAULTLIB:"msvcrtd.lib"
      QMAKE_LFLAGS *= /NODEFAULTLIB:"msvcprtd.lib"
    }
    
    debug {
      QMAKE_LFLAGS *= /NODEFAULTLIB:"msvcrt.lib"
      QMAKE_LFLAGS *= /NODEFAULTLIB:"msvcprt.lib"
    }
  }    

  LIBS += shell32.lib

  !isEmpty(MKL_PATH) {
    DEFINES += USE_MKL
    QMAKE_CXXFLAGS += -I\""$${MKL_PATH}"/include\"

    contains(COPASI_ARCH, 32) {
      QMAKE_LFLAGS += /LIBPATH:\""$${MKL_PATH}"/ia32/lib\"
      QMAKE_LFLAGS += /LIBPATH:\""$${MKL_PATH}"/../lib/ia32\"
      LIBS += mkl_intel_c.lib mkl_intel_thread.lib mkl_core.lib -Qopenmp libguide.lib
    } else {
      QMAKE_LFLAGS += /LIBPATH:\""$${MKL_PATH}"/em64t/lib\"
      QMAKE_LFLAGS += /LIBPATH:\""$${MKL_PATH}"/../lib/intel64\"
      LIBS += mkl_intel_lp64.lib mkl_intel_thread.lib mkl_core.lib -Qopenmp libguide.lib
    }
  } else {
    !isEmpty(LAPACK_PATH) {
      DEFINES += USE_LAPACK
      QMAKE_CXXFLAGS   += -I\""$${LAPACK_PATH}"/include\"
      QMAKE_LFLAGS += /LIBPATH:\""$${LAPACK_PATH}/lib/$${COPASI_ARCH}"\"
      debug {
        LIBS += blasD.lib lapackD.lib
      }
      release {
        LIBS += blas.lib lapack.lib ifconsol.lib libifcoremt.lib libifport.lib libirc.lib libmmt.lib svml_dispmt.lib
      }
      LIBS += ifconsol.lib libifcoremt.lib libifport.lib libirc.lib libmmt.lib svml_dispmt.lib
    } else {
      !isEmpty(CLAPACK_PATH) {
        DEFINES += USE_CLAPACK
        QMAKE_CXXFLAGS   += -I\""$${CLAPACK_PATH}"/include\"
        QMAKE_LFLAGS += /LIBPATH:\""$${CLAPACK_PATH}"/lib\"
        QMAKE_LFLAGS += /LIBPATH:\""$${CLAPACK_PATH}/lib/$${COPASI_ARCH}"\"
        LIBS += clapack.lib
      } else {
        error( "Either MKL_PATH, LPACK_PATH, or CLAPACK_PATH must be specified" )
      }
    }
  }


#expat library
  LIBS += libexpat$${RUNTIME}.lib

  !isEmpty(EXPAT_PATH) {
    QMAKE_CXXFLAGS += -I\""$${EXPAT_PATH}"/Source/lib\"
    QMAKE_CXXFLAGS += -I\""$${EXPAT_PATH}"/include\"
    QMAKE_LFLAGS   += /LIBPATH:\""$${EXPAT_PATH}"/StaticLibs\"
    QMAKE_LFLAGS   += /LIBPATH:\""$${EXPAT_PATH}"/bin\"
    QMAKE_LFLAGS   += /LIBPATH:\""$${EXPAT_PATH}"/lib\"
    QMAKE_LFLAGS   += /LIBPATH:\""$${EXPAT_PATH}/lib/$${COPASI_ARCH}"\"
  } else {
    error( "EXPAT_PATH must be specified" )
  }

  LIBS += libsbml$${RUNTIME}.lib
  
  !isEmpty(SBML_PATH) {
    QMAKE_CXXFLAGS += -I\""$${SBML_PATH}"/include\"
    QMAKE_LFLAGS   += /LIBPATH:\""$${SBML_PATH}"/lib\"
    QMAKE_LFLAGS   += /LIBPATH:\""$${SBML_PATH}/lib/$${COPASI_ARCH}"\"
    QMAKE_LFLAGS   += /LIBPATH:\""$${SBML_PATH}"/bin\"
  } else {
    error( "SBML_PATH must be specified" )
  }

# The raptor library
  LIBS += raptor$${RUNTIME}.lib
    
  !isEmpty(RAPTOR_PATH) {
    QMAKE_CXXFLAGS += -I\""$${RAPTOR_PATH}"/include\"
    QMAKE_LFLAGS   += /LIBPATH:\""$${RAPTOR_PATH}"/lib\"
    QMAKE_LFLAGS   += /LIBPATH:\""$${RAPTOR_PATH}/lib/$${COPASI_ARCH}"\"
  } else {
    error( "RAPTOR_PATH must be specified" )
  }
  
  contains(CONFIG, qt) {
    LIBS    += SBW$${RUNTIME}.lib ws2_32.lib

    !isEmpty(SBW_PATH){
      QMAKE_CXXFLAGS += -I\""$${SBW_PATH}"/include\"
      QMAKE_LFLAGS   += /LIBPATH:\""$${SBW_PATH}"/lib\"
      QMAKE_LFLAGS   += /LIBPATH:\""$${SBW_PATH}/lib/$${COPASI_ARCH}"\"
      
      DEFINES += COPASI_SBW_INTEGRATION
      DEFINES *= WIN32
    }
     
    !isEmpty(QWT_PATH){
       LIBS+=  -L\""$${QWT_PATH}"/lib\"
       INCLUDEPATH += \""$${QWT_PATH}"/include\"
    }
    
    release: LIBS += -lqwt
    debug: LIBS += -lqwtD
    
    !isEmpty(QWT3D_PATH){
      LIBS += -L\""$${QWT3D_PATH}"/lib\"
      INCLUDEPATH += \""$${QWT3D_PATH}"/include\"
    } 

#    DEFINES        += QWT3D_NODLL

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
    }
    LIBS += -lqwtplot3d
    
    LIBS += -lSM
  } else {
    QMAKE_LIBS_THREAD -= -lpthread
    QMAKE_LIBS_THREAD -= -lrt
  }
}
 
contains(BUILD_OS, Linux) {

  TARGET_64 = $$system($CC -dM -E - < /dev/null | grep -q __x86_64__ && echo true)

  contains(TARGET_64, true) {
    message("Creating 64 bit binaries.")
  }

  INTEL_COMPILER = $$system($CC -dM -E - < /dev/null | grep -q __INTEL_COMPILER && echo true)

  contains(INTEL_COMPILER, true) {
    message("Linking statically against Intel libraries.")
    QMAKE_LFLAGS *= -static-intel
  }
  
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
      QMAKE_LFLAGS *= -static
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

    contains(TARGET_64, true) {
      LIBS += -Wl,--start-group \
                $${MKL_PATH}/lib/em64t/libmkl_intel_lp64.a \
                $${MKL_PATH}/lib/em64t/libmkl_sequential.a \
                $${MKL_PATH}/lib/em64t/libmkl_core.a \
              -Wl,--end-group \
              -lpthread
    } else {
      LIBS += $${MKL_PATH}/lib/32/libmkl_solver.a \
              -Wl,--start-group \
                $${MKL_PATH}/lib/32/libmkl_intel.a \
                $${MKL_PATH}/lib/32/libmkl_sequential.a \
                $${MKL_PATH}/lib/32/libmkl_core.a \
              -Wl,--end-group \
              -lpthread
    }

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
          HAVE_G2C = $$system(locate libg2c)
          !isEmpty(HAVE_G2C) LIBS += -lg2c
        }
      } else {
        error( "Either MKL_PATH, CLAPACK_PATH, or LAPACK_PATH must be specified" )
      }
    }
  }

  contains(CONFIG, qt) {
    !isEmpty(SBW_PATH){
      contains(SBW_PATH, yes) {
        LIBS += -lSBW
      } else {
        LIBS += $${SBW_PATH}/lib/libSBW.a
        INCLUDEPATH += $${SBW_PATH}/include
      }
      DEFINES += COPASI_SBW_INTEGRATION
      DEFINES += LINUX 
    }
     
    !isEmpty(QWT_PATH){
       LIBS +=  -L$${QWT_PATH}/lib
       INCLUDEPATH += $${QWT_PATH}/include
       INCLUDEPATH += $${QWT_PATH}/include/qwt-qt4
    }
    LIBS += -lqwt

    !isEmpty(QWT3D_PATH){
      LIBS += -L$${QWT3D_PATH}/lib/
      INCLUDEPATH += $${QWT3D_PATH}/include
      INCLUDEPATH += $${QWT3D_PATH}/include/qwtplot3d-qt4
    }
    LIBS += -lqwtplot3d

# only needed for the class CLSimpleImageTexturizer which is only
# needed if we want to create bitmaps from layouts in the backend
#contains(DEFINES,USE_CRENDER_EXTENSION) {           
#	LIBS += -lpng
#       LIBS += -ljpeg
#}
  }
}

DEP1.target   = depend
DEP1.depends  = qmake

QMAKE_EXTRA_TARGETS += DEP1

# addSubdirs(subdirs,deps): Adds directories to the project that depend on
# other directories
defineTest(addSubdirs) {
    for(subdirs, 1) {
        entries = $$files($$subdirs)
        for(entry, entries) {
            name = $$replace(entry, [/\\\\], _)
            SUBDIRS += $$name
            eval ($${name}.subdir = $$entry)
            for(dep, 2):eval ($${name}.depends += $$replace(dep, [/\\\\], _))
            export ($${name}.subdir)
            export ($${name}.depends)
        }
    }
    export (SUBDIRS)
}
