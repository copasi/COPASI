import COPASI
import unittest
from types import *


class Test_CModelValue(unittest.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.mv=self.model.createModelValue("mv")

  def test_getKey(self):
    key=self.mv.getKey();
    self._assert(type(key)==StringType)

  def test_getStatus(self):
    status=self.mv.getStatus();
    self._assert(type(status)==IntType)

  def test_isFixed(self):
    fixed=self.mv.isFixed()
    self._assert(type(fixed)==BooleanType)

  def test_getValue(self):
    value=self.mv.getValue()
    self._assert(type(value)==FloatType)

  def test_getInitialValue(self):
    value=self.mv.getInitialValue()
    self._assert(type(value)==FloatType)

  def test_getRate(self):
    value=self.mv.getRate()
    self._assert(type(value)==FloatType)

  def test_setStatus(self):
    status=COPASI.CModelEntity.ASSIGNMENT
    self.mv.setStatus(status)
    self._assert(self.getStatus()==status)

  def test_setInitialValue(self):
    v=3.14159
    self.mv.setInitialValue(v)
    self._assert(self.mv.getInitialValue()==v)

  def test_setSBMLId(self):
    id="TESTtestTEST"
    self.mv.setSBMLId(id)
    self._assert(self.mv.getSBMLId()==id)

  def test_getSBMLId(self):
    id=self.mv.getSBMLId()
    self._assert(type(id)==StringType)

  def test_getExpression(self):
    ex=self.mv.getExpression()
    self._assert(type(ex)==StringType)

  def test_getInitialExpression(self):
    ex=self.mv.getInitialExpression()
    self._assert(type(ex)==StringType)

  def test_setUsed(self):
    v=true
    self.mv.setUsed(value)
    self._assert(v==self.mv.getIsUsedOnce())
    v=false
    self.mv.setUsed(value)
    self._assert(v==self.mv.getIsUsedOnce())

  def test_isUsed(self):
    value=self.mv.isUsed()
    self._assert(type(value)==BooleanType)

  def test_setUsedOnce(self):
    v=true
    self.mv.setUsedOnce(value)
    self._assert(v==self.mv.getIsUsedOnce())
    v=false
    self.mv.setUsedOnce(value)
    self._assert(v==self.mv.getIsUsedOnce())

  def test_isUsedOnce(self):
    value=self.mv.isUsedOnce()
    self._assert(type(value)==BooleanType)

  def test_setExpression(self):
    # that test will be implemented later
    self._assert(false)

  def test_setInitialExpression(self):
    # that test will be implemented later
    self._assert(false)



def suite():
  tests=[
          'test_getKey'
         ,'test_getStatus'
         ,'test_isFixed'
         ,'test_getValue'
         ,'test_getInitialValue'
         ,'test_getRate'
         ,'test_setStatus'
         ,'test_setInitialValue'
         ,'test_getSBMLId'
         ,'test_setSBMLId'
         ,'test_getExpression'
         ,'test_getInitialExpression'
         ,'test_isUsed'
         ,'test_setUsed'
         ,'test_isUsedOnce'
         ,'test_setUsedOnce'
         ,'test_setExpression'
         ,'test_setInitialExpression'
        ]
  return unittest.TestSuite(map(Test_CModelValue,tests))

