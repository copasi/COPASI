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
import string

class Test_CEvaluationTree(unittest.TestCase):
  def setUp(self):
    self.tree=COPASI.CEvaluationTree.create(COPASI.CEvaluationTree.Function)

  def test_create(self):
    self.assert_(self.tree!=None)
    self.assert_(self.tree.__class__==COPASI.CFunction)

  def test_copy(self):
    t=COPASI.CEvaluationTree.copy(self.tree)
    self.assert_(t!=None)
    self.assert_(t.__class__==COPASI.CFunction)

  def test_getType(self):
    t=self.tree.getType()
    self.assert_(type(t)==IntType)
    self.assert_(t==COPASI.CEvaluationTree.Function)

  def test_getKey(self):
    key=self.tree.getKey()
    self.assert_(type(key)==StringType)

  def test_getInfix(self):
    infix=self.tree.getInfix()
    self.assert_(type(infix)==StringType)

  def test_setInfix(self):
    expr="3 * A + 5.0"
    self.assert_(self.tree.setInfix(expr))
    infix=self.tree.getInfix()
    expr2=""
    for x in expr:
        if x not in string.whitespace:
            expr2+=x
    expr3=""
    for x in infix:
        if x not in string.whitespace:
            expr3+=x
    self.assert_(expr2==expr3)

  def test_getErrorLocation(self):
    badExpr="4 +* 3"
    self.assert_(self.tree.setInfix(badExpr).isError())
    pos=self.tree.getErrorLocation()
    self.assert_(type(pos)==IntType)
    self.assert_(pos==2 or pos==3)

  def test_getVariableIndex(self):
    expr="3 * A + 5.0"
    self.assert_(self.tree.setInfix(expr))
    index=self.tree.getVariableIndex("A")
    self.assert_(type(index)==IntType)
    self.assert_(index==0)

#  def test_getVariableValue(self):
#    expr="3 * A + 5.0"
#    self.assert_(self.tree.setInfix(expr))
#    v=self.tree.getVariableValue(0)    
#    self.assert_(type(v)==FloatType)
#    self.assert_(v!=v)

  def test_getSBMLId(self):
    id=self.tree.getSBMLId()
    self.assert_(type(id)==StringType)

  def test_setSBMLId(self):
    self.tree.setSBMLId("test_tree")
    self.assert_(self.tree.getSBMLId()=="test_tree")


def suite():
  tests=[
          "test_create"
         ,"test_copy"
         ,"test_getType"
         ,"test_getInfix"
         ,"test_getKey"
         ,"test_setInfix"
         ,"test_getErrorLocation"
         ,"test_getVariableIndex"
#         ,"test_getVariableValue"
         ,"test_getSBMLId"
         ,"test_setSBMLId"
        ]
  return unittest.TestSuite(map(Test_CEvaluationTree,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


