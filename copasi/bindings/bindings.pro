# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/bindings.pro,v $ 
#   $Revision: 1.1.16.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/16 20:08:01 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

TEMPLATE = subdirs

include(../common.pri)

contains(ENABLE_JAVA,yes){
SUBDIRS += java
}

contains(ENABLE_PYTHON,yes){
SUBDIRS += python
}


