import COPASI
import unittest
from types import *

class Test_CCopasiObject(unittests.TestCase):
    def setUp(self):
      self.object=COPASI.CMoiety()

    def test_getObjectName(self):
      t=self.object.getObjectName()
      self.assert_(type(t)==StringType)

    def test_setObjectName(self):
      NAME="MyObject"
      self.object.setObjectName(NAME)
      self.assert_(self.getObjectName()==NAME)

    def test_getObjectDisplayName(self):
      t=self.object.getObjectDisplayName()
      self.assert_(type(t)==StringType)

    def test_getObjectType(self):
      t=self.object.getObjectType()
      self.assert_(type(t)==StringType)

    def test_getObjectParent(self):
      self._assert(false)

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
