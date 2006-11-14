import COPASI
import unittests
from types import *


class Test_CMoiety(unittests.TestCase):
  def setUp(self):
    self.moiety=COPASI.CMoiety()

  def test_getDescription(self):
    desc=self.moiety.getDescription()
    self._assert(type(desc)==StringType)

  def test_dependentNumber(self):
    v=self.moiety.dependentNumber()
    self._assert(type(v)==FloatType)

  def test_getNumber(self):
    v=self.moiety.getNumber()
    self._assert(type(v)==FloatType)

  def test_getKey(self):
    key=self.moiety.getKey()
    self._assert(type(key)==StringType)

  def test_getDependentRate(self):
    v=self.moiety.getDependentRate()
    self._assert(type(v)==FloatType)

  def test_getDependentNumber(self):
    v=self.moiety.getDependentNumber()
    self._assert(type(v)==FloatType)


