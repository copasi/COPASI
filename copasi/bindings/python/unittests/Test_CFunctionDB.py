import COPASI
import unittest
from types import *


class Test_CFunctionDB(unittest.TestCase):
  def setUp(self):
    self.functions=COPASI.CCopasiDataModel.GLOBAL.getFunctionList()
    self.assert_(self.functions!=None)
    self.assert_(self.functions.__class__==COPASI.CFunctionDB)

  def test_add(self):
    function=COPASI.CFunction("testFunction")
    size=self.functions.loadedFunctions().size()
    function.this.disown()
    result=self.functions.add(function,True)
    if(result==False):
      function.this.own()
    self.assert_(result==True)
    self.assert_(self.functions.loadedFunctions().size()==size+1)

  def test_removeFunction(self):
    function=COPASI.CFunction("testFunction2")
    self.assert_(function!=None)
    self.assert_(function.__class__==COPASI.CFunction)
    size=self.functions.loadedFunctions().size()
    function.this.disown()
    result=self.functions.add(function,True)
    if(result==False):
      function.this.own()
    self.assert_(result==True)
    self.assert_(self.functions.loadedFunctions().size()==size+1)
    self.assert_(self.functions.removeFunction(function.getKey()))
    self.assert_(self.functions.loadedFunctions().size()==size)


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
    self.assert_(sfs.__class__==COPASI.CFunctionStdVector)
    self.assert_(sfs.size()!=0)

def suite():
  tests=[
          "setUp"
         ,"test_add"
         ,"test_removeFunction"
         ,"test_findFunction"
         ,"test_findLoadFunction"
         ,"test_loadedFunctions"
         ,"test_suitableFunctions"
        ]
  return unittest.TestSuite(map(Test_CFunctionDB,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


