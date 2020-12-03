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

class Test_CFunctionDB(unittest.TestCase):
  def setUp(self):
    self.functions=COPASI.CRootContainer.getFunctionList()
    self.assert_(self.functions!=None)
    self.assert_(self.functions.__class__==COPASI.CFunctionDB)

  def test_createFunction(self):
    size=len(self.functions.loadedFunctions())
    function=self.functions.createFunction("testFunction",COPASI.CEvaluationTree.Function)
    self.assert_(function!=None)
    self.assert_(function.__class__==COPASI.CFunction)
    self.assert_(self.functions.loadedFunctions().size()==size+1)

  def test_removeFunction(self):
    size=len(self.functions.loadedFunctions())
    function=self.functions.createFunction("testFunction2",COPASI.CEvaluationTree.Function)
    self.assert_(function!=None)
    self.assert_(function.__class__==COPASI.CFunction)
    size=self.functions.loadedFunctions().size()
    self.assert_(self.functions.removeFunction(function.getKey()))
    self.assert_(self.functions.loadedFunctions().size()==size-1)

  def test_findFunction(self):
    function=self.functions.findFunction("Iso Uni Uni")
    self.assert_(function!=None)
    self.assert_(function.__class__==COPASI.CFunction)
    self.assert_(function.getObjectName()=="Iso Uni Uni")

  def test_findLoadFunction(self):
    function=self.functions.findLoadFunction("Iso Uni Uni")
    self.assert_(function!=None)
    self.assert_(function.__class__==COPASI.CFunction)
    self.assert_(function.getObjectName()=="Iso Uni Uni")

  def test_loadedFunctions(self):
    loadedFunctions=self.functions.loadedFunctions()
    self.assert_(loadedFunctions!=None)
    self.assert_(loadedFunctions.__class__==COPASI.CFunctionVectorN)


  def test_suitableFunctions(self):
    sfs=self.functions.suitableFunctions(2,1,COPASI.TriFalse)
    self.assert_(sfs!=None)
    self.assert_(isinstance(sfs, COPASI.CFunctionStdVector)) 
    self.assert_(len(sfs)!=0)

def suite():
  tests=[
          "setUp"
         ,"test_createFunction"
         ,"test_removeFunction"
         ,"test_findFunction"
         ,"test_findLoadFunction"
         ,"test_loadedFunctions"
         ,"test_suitableFunctions"
        ]
  return unittest.TestSuite(map(Test_CFunctionDB,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


