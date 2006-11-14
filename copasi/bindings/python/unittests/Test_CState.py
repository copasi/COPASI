import COPASI
import unittest
from types import *

class Test_CState(unittest.TestCase):
  def setUp(self):
    self.cstate=CState()

  def test_getTime(self):
    time=self.cstate.getTime()
    self.assert_(type(time)==DoubleType)

  def test_setTime(self):
    TIME=27.96
    self.cstate.setTime(TIME)
    self.assert_(self.cstate.getTime()==TIME)

  def test_getNumIndependent(self):
    result=self.cstate.getNumIndependent()
    self.assert_(type(result)==IntType)

  def test_getNumDependent(self):
    result=self.cstate.getNumDependent()
    self.assert_(type(result)==IntType)

  def test_getNumVariable(self):
    result=self.cstate.getNumVariable()
    self.assert_(type(result)==IntType)

  def test_getNumFixed(self):
    result=self.cstate.getNumFixed()
    self.assert_(type(result)==IntType)

  def test_isUpdateDependentRequired(self):
    result=self.cstate.isUpdateDependentRequired()
    self.assert_(type(result)==BooleanType)

  def test_setUpdateDependentRequired(self):
    UPDATE_REQUIRED=false
    self.cstate.setUpdateDependentRequired(UPDATE_REQUIRED)
    self.assert_(self.cstate.isUpdateDependentRequired()==UPDATE_REQUIRED)
    UPDATE_REQUIRED=true
    self.cstate.setUpdateDependentRequired(UPDATE_REQUIRED)
    self.assert_(self.cstate.isUpdateDependentRequired()==UPDATE_REQUIRED)

    
