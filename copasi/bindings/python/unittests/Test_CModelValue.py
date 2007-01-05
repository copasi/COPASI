import COPASI
import unittest
from types import *


class Test_CModelValue(unittest.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.mv=self.model.createModelValue("mv")

  def test_getKey(self):
    key=self.mv.getKey();
    self.assert_(type(key)==StringType)

  def test_getStatus(self):
    status=self.mv.getStatus();
    self.assert_(type(status)==IntType)

  def test_isFixed(self):
    fixed=self.mv.isFixed()
    self.assert_(type(fixed)==BooleanType)

  def test_getValue(self):
    value=self.mv.getValue()
    self.assert_(type(value)==FloatType)

  def test_getInitialValue(self):
    value=self.mv.getInitialValue()
    self.assert_(type(value)==FloatType)

  def test_getRate(self):
    value=self.mv.getRate()
    self.assert_(type(value)==FloatType)

  def test_setStatus(self):
    status=COPASI.CModelEntity.ASSIGNMENT
    self.mv.setStatus(status)
    self.assert_(self.mv.getStatus()==status)

  def test_setInitialValue(self):
    v=3.14159
    self.mv.setInitialValue(v)
    self.assert_(self.mv.getInitialValue()==v)

  def test_setSBMLId(self):
    id="TESTtestTEST"
    self.mv.setSBMLId(id)
    self.assert_(self.mv.getSBMLId()==id)

  def test_getSBMLId(self):
    id=self.mv.getSBMLId()
    self.assert_(type(id)==StringType)

  def test_getExpression(self):
    ex=self.mv.getExpression()
    self.assert_(type(ex)==StringType)

  def test_getInitialExpression(self):
    ex=self.mv.getInitialExpression()
    self.assert_(type(ex)==StringType)

  def test_setUsed(self):
    v=True
    self.mv.setUsed(v)
    self.assert_(v==self.mv.isUsed())
    v=False
    self.mv.setUsed(v)
    self.assert_(v==self.mv.isUsed())

  def test_isUsed(self):
    value=self.mv.isUsed()
    self.assert_(type(value)==BooleanType)

  def test_setUsedOnce(self):
    v=True
    self.mv.setUsedOnce(v)
    self.assert_(v==self.mv.isUsedOnce())
    v=False
    self.mv.setUsedOnce(v)
    self.assert_(v==self.mv.isUsedOnce())

  def test_isUsedOnce(self):
    value=self.mv.isUsedOnce()
    self.assert_(type(value)==BooleanType)

  def test_setExpression(self):
    self.mv.setStatus(COPASI.CModelEntity.ASSIGNMENT)
    expr="17"
    self.assert_(self.mv.setExpression(expr))
    self.assert_(self.mv.getExpression()==expr)


  def test_setInitialExpression(self):
    expr="42.6"
    self.assert_(self.mv.setInitialExpression(expr))
    self.assert_(self.mv.getInitialExpression()==expr)



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

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


