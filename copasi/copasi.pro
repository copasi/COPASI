######################################################################
# $Revision: 1.1.1.1 $ $Author: anuragr $ $Date: 2004/10/26 15:17:43 $  
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
SUBDIRS += wizard
# Now the excecutables
SUBDIRS += CopasiUI
#SUBDIRS += CopasiSE
#SUBDIRS += test
