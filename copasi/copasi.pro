######################################################################
# $Revision: 1.6 $ $Author: ssahle $ $Date: 2004/06/15 09:24:22 $  
######################################################################

include(common.pri)

TEMPLATE = subdirs

# First build the libs
SUBDIRS =  commandline
SUBDIRS += elementaryFluxModes
SUBDIRS += function
SUBDIRS += mathmodel
SUBDIRS += model
SUBDIRS += optimization
#SUBDIRS += output
SUBDIRS += plot
SUBDIRS += randomGenerator
SUBDIRS += report
SUBDIRS += sbml
SUBDIRS += scan
SUBDIRS += steadystate
SUBDIRS += trajectory
SUBDIRS += utilities
SUBDIRS += xml

# Now the excecutables
SUBDIRS += CopasiUI
#SUBDIRS += CopasiSE
#SUBDIRS += test
