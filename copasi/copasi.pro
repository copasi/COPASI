######################################################################
# $Revision: 1.4 $ $Author: shoops $ $Date: 2003/06/03 17:23:09 $  
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
