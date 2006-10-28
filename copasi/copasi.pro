######################################################################
# $Revision: 1.20 $ $Author: shoops $ $Date: 2006/10/28 00:32:13 $  
######################################################################

TEMPLATE = subdirs

include(common.pri)

# First build the SE libs
SUBDIRS =  commandline
SUBDIRS += CopasiDataModel
SUBDIRS += elementaryFluxModes
SUBDIRS += function
SUBDIRS += lyap
SUBDIRS += model
contains(DEFINES, HAVE_MML) {
  SUBDIRS += mml
}
SUBDIRS += odepack++
SUBDIRS += optimization
SUBDIRS += parameterFitting
SUBDIRS += plot
SUBDIRS += randomGenerator
SUBDIRS += report
SUBDIRS += sbml
SUBDIRS += scan
contains(DEFINES, COPASI_SENS) {
  SUBDIRS += sensitivities
}
SUBDIRS += steadystate
SUBDIRS += trajectory
SUBDIRS += tss
SUBDIRS += utilities
SUBDIRS += xml
SUBDIRS += wizard

# Now the UI libraries
SUBDIRS += plotUI
SUBDIRS += UI

# Now build the libs
SUBDIRS += libs

# Now the excecutables
SUBDIRS += CopasiSE
SUBDIRS += CopasiUI

# Finally the bindings
SUBDIRS += bindings

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
