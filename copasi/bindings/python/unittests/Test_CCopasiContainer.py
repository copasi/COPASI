# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CCopasiContainer.py,v $ 
#   $Revision: 1.10 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/21 10:27:07 $ 
# End CVS Header 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *

class Test_CCopasiContainer(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.datamodel.loadModel("calcium_juergen.cps")


  def  test_ObjectFromName(self):
    metab=self.datamodel.getModel().getMetabolite(1)
    object=COPASI.CCopasiContainer.ObjectFromName(metab.getCN())
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


