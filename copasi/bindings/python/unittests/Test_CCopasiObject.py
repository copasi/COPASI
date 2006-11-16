import COPASI
import unittest
from types import *

class Test_CCopasiObject(unittest.TestCase):
    def setUp(self):
      self.model=COPASI.CModel()
      self.compartment=self.model.createCompartment("Comp1")
      self.object=self.model.createMetabolite("Metab1","Comp1")
      self.model.compileIfNecessary()

    def test_getObjectName(self):
      t=self.object.getObjectName()
      self.assert_(type(t)==StringType)

    def test_setObjectName(self):
      NAME="MyObject"
      self.object.setObjectName(NAME)
      self.assert_(self.object.getObjectName()==NAME)

    def test_getObjectDisplayName(self):
      t=self.object.getObjectDisplayName()
      self.assert_(type(t)==StringType)

    def test_getObjectType(self):
      t=self.object.getObjectType()
      self.assert_(type(t)==StringType)

    def test_getObjectParent(self):
      parent=self.object.getObjectParent()  
      self.assert_(parent!=None)
      self.assert_(parent.__class__==COPASI.CCopasiContainer)
      self.assert_(parent.getKey()==self.compartment.getMetabolites().getKey())

    def test_getCN(self):
      cn=self.object.getCN()
      self.assert_(cn.__class__==COPASI.CCopasiObjectName)

    def test_isContainer(self):
      result=self.object.isContainer()
      self.assert_(type(result)==BooleanType)

    def test_isVector(self):
      result=self.object.isVector()
      self.assert_(type(result)==BooleanType)

    def test_isMatrix(self):
      result=self.object.isMatrix()
      self.assert_(type(result)==BooleanType)

    def test_isNameVector(self):
      result=self.object.isNameVector()
      self.assert_(type(result)==BooleanType)

    def test_isReference(self):
      result=self.object.isReference()
      self.assert_(type(result)==BooleanType)

    def test_isValueBool(self):
      result=self.object.isValueBool()
      self.assert_(type(result)==BooleanType)

    def test_isValueInt(self):
      result=self.object.isValueInt()
      self.assert_(type(result)==BooleanType)

    def test_isValueDbl(self):
      result=self.object.isValueDbl()
      self.assert_(type(result)==BooleanType)

    def test_isNonUniqueName(self):
      result=self.object.isNonUniqueName()
      self.assert_(type(result)==BooleanType)

    def test_isStaticString(self):
      result=self.object.isStaticString()
      self.assert_(type(result)==BooleanType)

    def test_isValueString(self):
      result=self.object.isValueString()
      self.assert_(type(result)==BooleanType)

    def test_isSeparator(self):
      result=self.object.isSeparator()
      self.assert_(type(result)==BooleanType)

    def test_getKey(self):
      key=self.object.getKey()
      self.assert_(type(key)==StringType) 

def suite():
  tests=[
          'test_getObjectName'
         ,'test_setObjectName'
         ,'test_getObjectDisplayName'
         ,'test_getObjectType'
         ,'test_getObjectParent'
         ,'test_getCN'
         ,'test_isContainer'
         ,'test_isVector'
         ,'test_isMatrix'
         ,'test_isNameVector'
         ,'test_isReference'
         ,'test_isValueBool'
         ,'test_isValueInt'
         ,'test_isValueDbl'
         ,'test_isNonUniqueName'
         ,'test_isStaticString'
         ,'test_isValueString'
         ,'test_isSeparator'
         ,'test_getKey'
        ]
  return unittest.TestSuite(map(Test_CCopasiObject,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


