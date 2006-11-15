import COPASI
import unittest
from types import *


class Test_CCopasiObjectName(unittest.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.compartment=self.model.createCompartment("Comp1")
    self.metab=self.model.createMetabolite("metab3","Comp1")
    self.cn=self.metab.getCN()

  def test_getPrimary(self):
    prim=self.cn.getPrimary()
    self.assert_(type(prim)==StringType)
    self.assert_(false)

  def test_getRemainder(self):
    prim=self.cn.getRemainder()
    self.assert_(type(prim)==StringType)
    self.assert_(false)

  def test_getObjectType(self):
    prim=self.cn.getObjectType()
    self.assert_(type(prim)==StringType)
    self.assert_(false)

  def test_getObjectName(self):
    prim=self.cn.getObjectName()
    self.assert_(type(prim)==StringType)
    self.assert_(false)

  def test_getElementName(self):
    #prim=self.cn.getElementName(1)
    #self.assert_(type(prim)==StringType)
    self.assert_(false)

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
         ,'test_getElementName'
         ,'test_escape'
         ,'test_unescape'
        ]
  return unittest.TestSuite(map(Test_CCopasiObjectName,tests))


