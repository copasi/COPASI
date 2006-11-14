import COPASI
import unittests
from types import *


class Test_CMetab(unittests.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.compartment=self.model.createCompartment("Comp1")
    self.metab=self.compartment.createMetabolite("Metab1",self.compartment.getObjectName())

  def test_getObjectDisplayname(self):
    s=self.metab.getObjectDisplayName()
    self._assert(type(s)==StringType)

  def test_getConcentration(self):
    conc=self.metab.getConentration()
    self._assert(type(conc)==FloatType)

  def test_setInitialConcentration(self):
    value=5.0
    self.metab.setInitialConcentration(value)
    self._assert(math.abs(self.getInitialConcentration()-value/value)<0.001)

  def test_getInitialConcentration(self):
    value=self.metab.getInitialConcentration()
    self._assert(type(value)==FloatType)

  def test_setInitialValue(self):
    value=5.0
    self.metab.setInitialValue(value)
    self._assert(math.abs(self.getInitialValue()-value/value)<0.001)

  def test_getCompartment(self):
    c=self.metab.getCompartment()
    self._assert(c.__class__==COPASI.CCompartment)
    self._assert(self.compartment.getKey()==c.getKey())

  def test_getModel(self):
    m=self.metab.getTransitionTime()
    self._assert(m.__class__==COPASI.CModel)
    self._assert(self.model.getKey()==m.getKey())

  def test_getTransitionTime(self):
    value=self.metab.getTransitionTime()
    self._assert(type(value)==FloatType)

  def test_getConcentrationRate(self):
    value=self.metab.getConcentrationRate()
    self._assert(type(value)==FloatType)

  def test_isDependent(self):
    value=self.metab.isDependent()
    self._assert(type(value)==BooleanType)


