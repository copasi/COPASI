import COPASI
import unittest
from types import *


class Test_CCopasiObjectName(unittest.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.compartment=self.model.createCompartment("Comp1")
    self.metab=self.model.createMetabolite("metab3","Comp1")
    self.cn=self.metab.getCN()
    self.model.compileIfNecessary()

  def test_getPrimary(self):
    prim=self.cn.getPrimary()
    self.assert_(prim.__class__==COPASI.CCopasiObjectName)
    self.assert_(prim.getString()=="CN=Root") 

  def test_getRemainder(self):
    prim=self.cn.getRemainder()
    self.assert_(prim.__class__==COPASI.CCopasiObjectName)
    self.assert_(prim.getString()=='Model=New Model,Vector=Compartments[Comp1],Vector=Metabolites[metab3]')

  def test_getObjectType(self):
    prim=self.cn.getObjectType()
    self.assert_(type(prim)==StringType)
    self.assert_(prim=="CN")

  def test_getObjectName(self):
    prim=self.cn.getObjectName()
    self.assert_(type(prim)==StringType)
    self.assert_(prim=="Root")


  def test_escape(self):
    a="This- \ \ is a test--!"
    o=COPASI.CCopasiObjectName.escape(a)
    self.assert_(type(o)==StringType)
    self.assert_(len(o)==len(a)+2)


  def test_unescape(self):
    a="This- \\ \\ is a test--!"
    o=COPASI.CCopasiObjectName.unescape(a)
    self.assert_(type(o)==StringType)
    self.assert_(len(o)==len(a)-2)
                                  

def suite():
  tests=[
          'test_getPrimary'
         ,'test_getRemainder'
         ,'test_getObjectType'
         ,'test_getObjectName'
         ,'test_escape'
         ,'test_unescape'
        ]
  return unittest.TestSuite(map(Test_CCopasiObjectName,tests))


if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


