######################################################################
# $Revision: 1.8 $ $Author: shoops $ $Date: 2004/12/29 15:07:44 $  
######################################################################

include(common.pri)

TEMPLATE = subdirs

# First build the libs
SUBDIRS =  commandline
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
SUBDIRS += utilities
SUBDIRS += xml
SUBDIRS += wizard
# Now the excecutables
SUBDIRS += CopasiUI
#SUBDIRS += CopasiSE
#SUBDIRS += test
