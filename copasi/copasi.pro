# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/copasi.pro,v $ 
#   $Revision: 1.45 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/01/17 13:04:57 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.45 $ $Author: shoops $ $Date: 2008/01/17 13:04:57 $  
######################################################################

TEMPLATE = subdirs

include(common.pri)

# First build the SE libs

COPASISE_DIRS =  commandline

#ifdef COPASI_LICENSE_COM
contains(USE_LICENSE, COM) {
  COPASISE_DIRS += commercial
}
#endif // COPASI_LICENSE_COM

COPASISE_DIRS += CopasiDataModel
COPASISE_DIRS += compareExpressions
COPASISE_DIRS += elementaryFluxModes
COPASISE_DIRS += function
COPASISE_DIRS += lyap
COPASISE_DIRS += model
COPASISE_DIRS += MIRIAM
COPASISE_DIRS += odepack++
COPASISE_DIRS += optimization
COPASISE_DIRS += parameterFitting
COPASISE_DIRS += plot
COPASISE_DIRS += randomGenerator
COPASISE_DIRS += report
COPASISE_DIRS += sbml
COPASISE_DIRS += scan
COPASISE_DIRS += sensitivities
COPASISE_DIRS += steadystate
COPASISE_DIRS += trajectory
COPASISE_DIRS += tss
COPASISE_DIRS += utilities
COPASISE_DIRS += xml


!isEmpty(CPPUNIT_PATH) {
  COPASISE_DIRS += compareExpressions/unittests
}

contains(DEFINES, COPASI_TSSA) {
  COPASISE_DIRS += tssanalysis
}

contains(DEFINES, WITH_LAYOUT) {
  COPASISE_DIRS += layout
  COPASIUI_DIRS += layoutUI
}

# Now the UI libraries

COPASIUI_DIRS += plotUI
COPASIUI_DIRS += UI
COPASIUI_DIRS += wizard
  
contains(DEFINES, HAVE_MML) {
  COPASIUI_DIRS += mml
}

contains(DEFINES, WITH_QWT3D) {
  COPASIUI_DIRS += barChart
}

SUBDIRS = $${COPASISE_DIRS}

!contains(BUILD_GUI, no) {
  SUBDIRS += $${COPASIUI_DIRS}
}

# Now build the libs
SUBDIRS += libs
sub-libs.depends = $$join(COPASISE_DIRS, " sub-", "sub-") 
sub-libs.depends += $$join(COPASIUI_DIRS, " sub-", "sub-")
QMAKE_EXTRA_UNIX_TARGETS += sub-libs

# Now the excecutables
SUBDIRS += CopasiSE
sub-CopasiSE.depends = sub-libs
QMAKE_EXTRA_UNIX_TARGETS += sub-CopasiSE

!contains(BUILD_GUI, no) {
  SUBDIRS += CopasiUI
  sub-CopasiUI.depends = sub-libs
  QMAKE_EXTRA_UNIX_TARGETS += sub-CopasiUI
}

#SUBDIRS += test3

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
