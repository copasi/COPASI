# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/copasi.pro,v $
#   $Revision: 1.58 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2009/04/21 16:12:03 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# $Revision: 1.58 $ $Author: shoops $ $Date: 2009/04/21 16:12:03 $
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
COPASISE_DIRS += layout
COPASISE_DIRS += lyap
COPASISE_DIRS += model
COPASISE_DIRS += moieties
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


contains(DEFINES, COPASI_TSSA) {
  COPASISE_DIRS += tssanalysis
}

addSubdirs($${COPASISE_DIRS})

!contains(BUILD_GUI, no) {
  # Now the UI libraries
  COPASIUI_DIRS += barChart
  COPASIUI_DIRS += layoutUI
  COPASIUI_DIRS += MIRIAMUI
  COPASIUI_DIRS += plotUI
  COPASIUI_DIRS += wizard

  contains(DEFINES, HAVE_MML) {
    COPASIUI_DIRS += mml
    COPASIUI_DIRS += tex
  }

  addSubdirs($${COPASIUI_DIRS})

  COPASIUI_DIRS += UI
  addSubdirs(UI, wizard)
}

# Now build the libs

addSubdirs(libs, $${COPASISE_DIRS} $${COPASIUI_DIRS})

# Now the excecutables
addSubdirs(CopasiSE, libs)

!contains(BUILD_GUI, no) {
  addSubdirs(CopasiUI, libs)
}

isEmpty(COPASI_SRC_PACKAGE) {
  # The bindings
  !contains(BUILD_BINDINGS, no) {
    addSubdirs(bindings, libs)
  }

  # unit tests
  !isEmpty(CPPUNIT_PATH) {
    SUBDIRS += compareExpressions/unittests
    SUBDIRS += compareExpressions/stresstest
    SUBDIRS += sbml/unittests
  }
}


DISTDIRS = $${SUBDIRS}
DISTDIRS -= mml

DISTFILES += \
        1_configure.vcproj \
        FlexLexer.h \
        LicenseUS.txt.h \
        LicenseDE.txt.h \
        blas.h \
        blaswrap.h \
        clapackwrap.h \
        copasi.vcproj \
        copasi.sln \
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
