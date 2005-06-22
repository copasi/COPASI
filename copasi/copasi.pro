######################################################################
# $Revision: 1.12 $ $Author: ssahle $ $Date: 2005/06/22 09:26:52 $  
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
#SUBDIRS += output
SUBDIRS += plot
SUBDIRS += randomGenerator
SUBDIRS += report
SUBDIRS += sbml
SUBDIRS += scan
SUBDIRS += steadystate
SUBDIRS += trajectory
SUBDIRS += tss
SUBDIRS += utilities
SUBDIRS += xml
SUBDIRS += wizard

# Now the excecutables
SUBDIRS += CopasiSE
SUBDIRS += CopasiUI
#SUBDIRS += test
