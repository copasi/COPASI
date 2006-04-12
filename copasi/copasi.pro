######################################################################
# $Revision: 1.16 $ $Author: ssahle $ $Date: 2006/04/12 12:36:41 $  
######################################################################

include(common.pri)

TEMPLATE = subdirs

# First build the libs
SUBDIRS =  commandline
SUBDIRS += CopasiDataModel
SUBDIRS += elementaryFluxModes
SUBDIRS += function
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
