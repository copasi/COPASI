# -*- coding: utf-8 -*-
# Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
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


  def test_getMathContainer(self):
    container=self.problem.getMathContainer()
    self.assert_(container.__class__==COPASI.CMathContainer)
    self.assert_(container.getModel().getKey()==self.datamodel.getModel().getKey())

def suite():
  tests=[
          'test_getType'
         ,'test_getMathContainer'
        ]
  return unittest.TestSuite(map(Test_CCopasiProblem,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


