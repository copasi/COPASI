# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CCopasiProblem.py,v $ 
#   $Revision: 1.8 $ 
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


class Test_CCopasiProblem(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.problem=self.datamodel.getTask(0).getProblem()


  def test_getType(self):
    t=self.problem.getType()
    self.assert_(type(t)==IntType)


  def test_getModel(self):
    model=self.problem.getModel()
    self.assert_(model.__class__==COPASI.CModel)
    self.assert_(model.getKey()==self.datamodel.getModel().getKey())

def suite():
  tests=[
          'test_getType'
         ,'test_getModel'
        ]
  return unittest.TestSuite(map(Test_CCopasiProblem,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


