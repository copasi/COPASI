# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CCompartment.py,v $ 
#   $Revision: 1.9 $ 
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
import math

class Test_CCompartment(unittest.TestCase):
  def setUp(self):
    COPASI.CCopasiDataModel.GLOBAL.newModel()
    self.model=COPASI.CCopasiDataModel.GLOBAL.getModel()
    self.compartment=self.model.createCompartment("Comp1")
    self.model.createMetabolite("metab1","Comp1")
    self.model.createMetabolite("metab2","Comp1")
    self.metab=self.model.createMetabolite("metab3","Comp1")
    self.model.createMetabolite("metab4","Comp1")
    self.model.createMetabolite("metab5","Comp1")

  def test_getMetabolites(self):
    metabolites=self.compartment.getMetabolites()
    self.assert_(metabolites.__class__==COPASI.MetabVectorNS)

  def test_removeMetabolite(self):
    size=self.compartment.getMetabolites().size()
    self.compartment.removeMetabolite(self.metab)
    self.assert_(self.compartment.getMetabolites().size()==size-1)

  def test_setInitialValue(self):
    value=5.0
    self.compartment.setInitialValue(value)
    self.assert_(math.fabs((self.compartment.getInitialValue()-value)/value)<0.001)
    

def suite():
  tests=[
          'test_getMetabolites'
         ,'test_removeMetabolite'
         ,'test_setInitialValue'
        ]
  return unittest.TestSuite(map(Test_CCompartment,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


