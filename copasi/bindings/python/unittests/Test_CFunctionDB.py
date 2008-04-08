# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CFunctionDB.py,v $ 
#   $Revision: 1.6.14.2 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/08 15:07:15 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *

class Test_CFunctionDB(unittest.TestCase):
  def setUp(self):
    self.functions=COPASI.CCopasiDataModel.GLOBAL.getFunctionList()
    self.assert_(self.functions!=None)
    self.assert_(self.functions.__class__==COPASI.CFunctionDB)

  def test_createFunction(self):
    size=self.functions.loadedFunctions().size()
    function=self.functions.createFunction("testFunction",COPASI.CEvaluationTree.Function)
    self.assert_(function!=None)
    self.assert_(function.__class__==COPASI.CFunction)
    self.assert_(self.functions.loadedFunctions().size()==size+1)

  def test_removeFunction(self):
    size=self.functions.loadedFunctions().size()
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
    self.assert_(loadedFunctions.__class__==COPASI.CEvaluationTreeVectorN)


  def test_suitableFunctions(self):
    sfs=self.functions.suitableFunctions(2,1,COPASI.TriFalse)
    self.assert_(sfs!=None)
    self.assert_(type(sfs)==TupleType) 
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


