######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2003/05/19 12:45:53 $  
######################################################################

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
