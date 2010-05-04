# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CCopasiContainer.py,v $ 
#   $Revision: 1.10.12.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2010/05/04 15:56:15 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *

class Test_CCopasiContainer(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiRootContainer.addDatamodel()
    self.datamodel.loadModel("calcium_juergen.cps")


  def  test_ObjectFromName(self):
    metab=self.datamodel.getModel().getMetabolite(1)
    v=COPASI.ContainerStdVector()
    v.push_back(self.datamodel.getModel())
    object=self.datamodel.ObjectFromName(v,metab.getCN())
    self.assert_(object!=None)
    self.assert_(object.__class__==COPASI.CMetab)
    self.assert_(metab.getCN().getString()==object.getCN().getString())


def suite():
  tests=[
          'test_ObjectFromName'
        ]
  return unittest.TestSuite(map(Test_CCopasiContainer,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


