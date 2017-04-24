# -*- coding: utf-8 -*-
# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

import COPASI
import unittest
from types import *


class Test_CCopasiProblem(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CRootContainer.addDatamodel()
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


