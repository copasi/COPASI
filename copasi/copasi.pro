######################################################################
# $Revision: 1.14 $ $Author: ssahle $ $Date: 2005/10/11 16:28:05 $  
######################################################################

include(common.pri)

TEMPLATE = subdirs

# First build the libs
SUBDIRS =  commandline
SUBDIRS += CopasiDataModel
SUBDIRS += elementaryFluxModes
SUBDIRS += function
SUBDIRS += mathmodel
SUBDIRS += model
SUBDIRS += mml
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
