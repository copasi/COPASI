######################################################################
# $Revision: 1.5 $ $Author: ssahle $ $Date: 2003/10/29 10:35:14 $  
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
SUBDIRS += output
SUBDIRS += plot
SUBDIRS += randomGenerator
SUBDIRS += report
SUBDIRS += scan
SUBDIRS += steadystate
SUBDIRS += trajectory
SUBDIRS += utilities
SUBDIRS += xml

# Now the excecutables
SUBDIRS += CopasiUI
SUBDIRS += CopasiSE
SUBDIRS += test
