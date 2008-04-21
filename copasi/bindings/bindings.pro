# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/bindings.pro,v $ 
#   $Revision: 1.4 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/21 10:27:06 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

TEMPLATE = subdirs

include(../common.pri)

contains(ENABLE_JAVA,yes){
  SUBDIRS += java
  !isEmpty(JUNIT_PATH){
    SUBDIRS += java/unittests
  }
}

contains(ENABLE_PYTHON,yes){
SUBDIRS += python
}


