import COPASI
import unittests
from types import *


class Test_CCopasiObjectName(unittests.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.compartment=self.model.createCompartment("Comp1")
    self.metab=self.model.createMetabolite("metab3","Comp1")
    self.cn=self.metab.getCN()

  def test_getPrimary(self):
    prim=self.cn.getPrimary()
    self._assert(type(prim)==StringType)
    self._assert(false)

  def test_getRemainder(self):
    prim=self.cn.getRemainder()
    self._assert(type(prim)==StringType)
    self._assert(false)

  def test_getObjectType(self):
    prim=self.cn.getObjectType()
    self._assert(type(prim)==StringType)
    self._assert(false)

  def test_getObjectName(self):
    prim=self.cn.getObjectName()
    self._assert(type(prim)==StringType)
    self._assert(false)

  def test_getElementName(self):
    prim=self.cn.getElementName(1)
    self._assert(type(prim)==StringType)
    self._assert(false)

  def test_escape(self):
    a="This- \ \ is a test--!"
    o=COPASI.CCopasiObjectName.escape(a)
    self._assert(type(o)==StringType)
    self._assert(len(o)==len(a)+2)


  def test_unescape(self):
    a="This- \\ \\ is a test--!"
    o=COPASI.CCopasiObjectName.unescape(a)
    self._assert(type(o)==StringType)
    self._assert(len(o)==len(a)-2)
                                  

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
  return unittests.TestSuite(map(Test_CCopasiObjectName,tests))


