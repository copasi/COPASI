######################################################################
# $Revision: 1.17.2.1 $ $Author: shoops $ $Date: 2006/05/16 20:44:57 $  
######################################################################

include(common.pri)

TEMPLATE = subdirs

# First build the libs
SUBDIRS =  commandline
SUBDIRS += CopasiDataModel
SUBDIRS += elementaryFluxModes
SUBDIRS += function
SUBDIRS += lyap
#SUBDIRS += mathmodel
SUBDIRS += model
SUBDIRS += mml
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
SUBDIRS += wizard

# Now the excecutables
SUBDIRS += CopasiSE
SUBDIRS += CopasiUI
#SUBDIRS += test2
#SUBDIRS += test


src_distribution.commands = \
  $$join(SUBDIRS, "; make src_distribution; cd ..; cd ", "cd ", "; make src_distribution; cd ..;")

QMAKE_EXTRA_UNIX_TARGETS += src_distribution
