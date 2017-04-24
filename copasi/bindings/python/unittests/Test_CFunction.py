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
import string


class Test_CFunction(unittest.TestCase):
  def setUp(self):
    self.functions=COPASI.CRootContainer.getFunctionList()
    self.function=self.functions.findFunction("Iso Uni Uni")

  def test_setUp(self):
    self.assert_(self.function!=None)
    self.assert_(self.function.__class__==COPASI.CFunction)
    self.assert_(self.function.getObjectName()=="Iso Uni Uni")

  def test_setInfix(self):
    function=COPASI.CEvaluationTree.create(COPASI.CEvaluationTree.Function)
    self.assert_(function!=None)
    self.assert_(function.__class__==COPASI.CFunction)
    expr="B + (7.0 / A)"
    self.assert_(function.setInfix(expr))
    infix=function.getInfix()
    expr2=""
    for x in expr:
        if x not in string.whitespace:
            expr2+=x
    expr3=""
    for x in infix:
        if x not in string.whitespace:
            expr3+=x
    self.assert_(expr2==expr3)

  def test_getVariableIndex(self):
    index=self.function.getVariableIndex("Kmp")
    self.assert_(type(index)==IntType)
    self.assert_(index==3)

#  def test_getVariableValue(self):
#    v=self.function.getVariableValue(3)
#    self.assert_(type(v)==FloatType)
#    self.assert_(v==1.0)

  def test_isReversible(self):
    b=self.function.isReversible()
    self.assert_(type(b)==IntType)

  def test_setReversible(self):
    function=COPASI.CEvaluationTree.create(COPASI.CEvaluationTree.Function)
    self.assert_(function!=None)
    self.assert_(function.__class__==COPASI.CFunction)
    v=True
    function.setReversible(v)
    self.assert_(function.isReversible()==v)
    v=False
    function.setReversible(v)
    self.assert_(function.isReversible()==v)

  def test_getVariables(self):
    params=self.function.getVariables()
    self.assert_(params!=None)
    self.assert_(params.__class__==COPASI.CFunctionParameters)

  def test_addVariable(self):
    params=self.function.getVariables()
    size=params.size()
    self.function.addVariable("testVar")
    self.assert_(params.size()==size+1)
    self.function.getVariables().remove("testVar")

  def test_isSuitable(self):
    b=self.function.isSuitable(1,1,COPASI.TriTrue)
    self.assert_(type(b)==BooleanType)
    self.assert_(b==True)
    b=self.function.isSuitable(0,1,COPASI.TriTrue)
    self.assert_(b==False)
    b=self.function.isSuitable(1,1,COPASI.TriFalse)
    self.assert_(b==False)

def suite():
  tests=[
          "test_setUp"
         ,"test_setInfix"
         ,"test_getVariableIndex"
#         ,"test_getVariableValue"
         ,"test_isReversible"
         ,"test_setReversible"
         ,"test_getVariables"
         ,"test_addVariable"
         ,"test_isSuitable"                     
        ]
  return unittest.TestSuite(map(Test_CFunction,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


