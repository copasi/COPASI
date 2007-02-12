# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/copasi.pro,v $ 
#   $Revision: 1.28 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2007/02/12 00:06:47 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.28 $ $Author: ssahle $ $Date: 2007/02/12 00:06:47 $  
######################################################################

TEMPLATE = subdirs

include(common.pri)

# First build the SE libs

#ifdef COPASI_LICENSE_COM
SUBDIRS =  commandline
contains(USE_LICENSE, COM) {
  SUBDIRS += commercial
}
#endif // COPASI_LICENSE_COM

SUBDIRS += CopasiDataModel
SUBDIRS += elementaryFluxModes
SUBDIRS += function
SUBDIRS += lyap
SUBDIRS += model
SUBDIRS += odepack++
SUBDIRS += optimization
SUBDIRS += parameterFitting
SUBDIRS += plot
SUBDIRS += randomGenerator
SUBDIRS += report
SUBDIRS += sbml
SUBDIRS += scan
SUBDIRS += sensitivities
SUBDIRS += steadystate
SUBDIRS += trajectory
SUBDIRS += tss
SUBDIRS += utilities
SUBDIRS += xml

contains(DEFINES, WITH_LAYOUT) {
  SUBDIRS += layout
}

# Now the UI libraries
!contains(BUILD_GUI, no) {
  contains(DEFINES, HAVE_MML) {
    SUBDIRS += mml
  }
  SUBDIRS += plotUI
  SUBDIRS += UI
  SUBDIRS += wizard
}

# Now build the libs
SUBDIRS += libs

# Now the excecutables
SUBDIRS += CopasiSE
!contains(BUILD_GUI, no) {
  SUBDIRS += CopasiUI
}

# Finally the bindings
isEmpty(COPASI_SRC_PACKAGE) {
  SUBDIRS += bindings
}

DISTDIRS = $${SUBDIRS}
DISTDIRS -= mml

DISTFILES += \
        1_configure.dsp \
        FlexLexer.h \
        LicenseUS.txt.h \
        LicenseDE.txt.h \
        blas.h \
        blaswrap.h \
        clapackwrap.h \
        copasi.dsp \
        copasi.dsw \
        copasi.h \
        copasilicense.h \
        copasiversion.h \
        copasi.pro \
        lapack.h \
        mathematics.h

src_distribution.commands = \
  rm -rf ../copasi_src/copasi; \
  $(CHK_DIR_EXISTS) ../copasi_src || $(MKDIR) ../copasi_src; \
  $(CHK_DIR_EXISTS) ../copasi_src/copasi || $(MKDIR) ../copasi_src/copasi; \
  cp $$DISTFILES ../copasi_src/copasi/; \
  $$join(DISTDIRS, "; $(MAKE) -f $(MAKEFILE) $@; cd ..; cd ", "cd ", "; $(MAKE) -f $(MAKEFILE) $@; cd ..;")

QMAKE_EXTRA_UNIX_TARGETS += src_distribution
