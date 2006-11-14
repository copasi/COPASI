import COPASI
import unittests
from types import *


class Test_CReaction(unittests.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.comp=model.createCompartment("comp1",1.0)
    self.comp=model.createCompartment("comp2",2.0)
    self.substrate=model.createMetabolite("A","comp1")
    self.product=model.createMetabolite("B","comp2")
    self.reac=model.createReaction("testReaction");


  def test_getKey(self):
    key=self.reac.getKey()
    self._assert(type(key)==StringType)

  def test_getFlux(self):
    v=self.reac.getFlux()
    self._assert(type(v)==FloatType)

  def test_getParticleFlux(self):
    v=self.reac.getParticleFlux()
    self._assert(type(v)==FloatType)

  def test_isReversible(self):
    v=self.reac.getParticleFlux()
    self._assert(type(v)==BooleanType)

  def test_addSubstrate(self):
    self.reac.addSubstrate(self.substrate)

  def test_addProduct(self):
    self.reac.addProduct(self.product)

  def test_addModifier(self):
    self.reac.addModifier(self.product)

  def test_setReversible(self):
    v=false
    self.reac.setReversible(v)
    self._assert(self.reac.getReversible()==v)
    v=true
    self.reac.setReversible(v)
    self._assert(self.reac.getReversible()==v)

  def test_getCompartmentNumber(self):
    self.reac.addSubstrate(self.substrate)
    self.reac.addProduct(self.product)
    self.reac.addModifier(self.product)
    n=self.reac.getCompartmentNumber()
    self._assert(type(n)==IntType)
    self._assert(n==2)

  def test_getLargestCompartment(self):
    self.reac.addSubstrate(self.substrate)
    self.reac.addProduct(self.product)
    self.reac.addModifier(self.product)
    comp=self.reac.getLargestCompartment()
    self._assert(comp.__class__==COPASI.CCompartment)
    self._assert(comp.getObjectName()=="comp2")

  def test_getSmallestCompartment(self):
    self.reac.addSubstrate(self.substrate)
    self.reac.addProduct(self.product)
    self.reac.addModifier(self.product)
    comp=self.reac.getSmallestCompartment()
    self._assert(comp.__class__==COPASI.CCompartment)
    self._assert(comp.getObjectName()=="comp1")

  def test_setSBMLId(self):
    id="react_1"
    self.reac.setSBMLId(id)
    self._assert(self.reac.getSBMLid()==id)

  def test_getSBMLId(self):
    id=self.reac.getSBMLId()
    self._assert(type(id)==StringType)



