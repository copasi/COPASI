######################################################################
# $Revision: 1.3 $ $Author: shoops $ $Date: 2003/05/20 16:24:37 $  
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
