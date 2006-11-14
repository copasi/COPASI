import COPASI
import unittests
from types import *


class Test_CModel(unittests.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.model.createCompartment("comp1",1.0)
    self.model.createCompartment("comp2",2.0)
    m1=self.model.createMetabolite("A","comp1")
    m2=self.model.createMetabolite("B","comp1")
    m3=self.model.createMetabolite("C","comp1")
    m4=self.model.createMetabolite("D","comp1")
    m5=self.model.createMetabolite("E","comp2")
    m6=self.model.createMetabolite("F","comp2")
    m7=self.model.createMetabolite("G","comp2")
    r=self.createReaction("react1")
    r.addSubstrate(m1)
    r.addProduct(m2)
    r=self.createReaction("react2")
    r.addSubstrate(m3)
    r.addProduct(m5)
    r=self.createReaction("react3")
    r.addSubstrate(m6)
    r.addProduct(m2)
    self.model.buildStoi()
    self.model.buildRedStoi()
    self.model.buildMoieties()

  def test_getMetabolites(self):
    v=self.model.getMetabolites()
    self._assert(v.__class__==COPASI.MetabVector)
    self._assert(v.size()==7)

  def test_getMetabolitesX(self):
    v=self.model.getMetabolites()
    self._assert(v.__class__==COPASI.MetabVector)
    self._assert(v.size()==7)

  def test_getNumMetabs(self):
    n=self.model.getNumMetabs()
    self._assert(type(n)==IntType)
    self._assert(n==7)

  def test_getNumVariableMetabs(self):
    n=self.model.getNumVeriableMetabs()
    self._assert(type(n)==IntType)
    self._assert(n==7)

  def test_getNumODEMetabs(self):
    n=self.model.getNumODEMetabs()
    self._assert(type(n)==IntType)
    self._assert(n==6)

  def test_getNumIndependentMetabs(self):
    n=self.model.getNumODEMetabs()
    self._assert(type(n)==IntType)
    self._assert(n==4)

  def test_getNumDependentMetabs(self):
    n=self.model.getNumODEMetabs()
    self._assert(type(n)==IntType)
    self._assert(n==3)

  def test_getModelValues(self):
    v=self.model.getModelValues()
    self._assert(v.__class__=COPASI.ModelValueVector)
    self._assert(v.size()==0)

  def test_getNumModelValues(self):
    n=self.model.getNumModelValues()
    self._assert(type(n)==IntType)
    self._assert(n==0)

  def test_getReactions(self):
    v=self.model.getReactions()
    self._assert(v.__class__=COPASI.ReactionVector)
    self._assert(v.size()==3)

  def test_getTotSteps(self):
    n=self.model.getTotSteps()
    self._assert(type(n)==IntType)
    self._assert(n==3)

  def test_getComments(self):
    comments=self.model.getComments()
    self._assert(type(comments)==StringType)


  def test_getKey(self):
    key=self.model.getKey()
    self._assert(type(key)==StringType)

  def test_setTitle(self):
    title="MyTitle"
    self.model.setTitle(title)
    self._assert(self.model.getTitle()==title)

  def test_setComments(self):
    comment="MyComment"
    self.model.setComments(comment)
    self._assert(self.model.getComments()==comment)

  def test_setInitialTime(self):
    d=12.4
    self.model.setInitialTime(d)
    self._assert(math.abs((self.model.getInitialTime()-d)/d)<0.001)

  def test_getInitialTime(self):
    d=self.model.getInitialTime()
    self._assert(type(d)==FloatType)

  def test_getTime(self):
    d=self.model.getTime()
    self._assert(type(d)==FloatType)

  def test_getCompartments(self):
    v=self.model.getCompartments()
    self._assert(v.__class__==COPASI.CompartmentVector)
    self._assert(v.size()==2)

  def test_getStoi(self):
    m=self.model.getStoi()
    self._assert(m.__class__==COPASI.FloatMatrix)

  def test_getRedStoi(self):
    m=self.model.getRedStoi()
    self._assert(m.__class__==COPASI.FloatMatrix)

  def test_getStoiReordered(self):
    m=self.model.getStoiReordered()
    self._assert(m.__class__==COPASI.FloatMatrix)

  def test_getMoieties(self):
    v=self.model.getMoieties()
    self._assert(v.__class__==COPASI.MoietyVector)
    self._assert(v.size()==3)

  def test_findMetabByName(self):
    index=self.model.findMetabByName("D")
    self._assert(type(index)==IntType)
    self._assert(index==3) 

  def test_findMoiety(self):
    v=self.model.getMoieties()
    moiety=v.get(1)
    index=self.model.findMoiety(moiety.getObjectName()) 
    self._assert(type(index)==IntType)
    self._assert(index==1)

  def test_getInitialState(self):
    state=self.model.getInitialState()
    self._assert(state.__class__=COPASI.CState)

  def test_getState(self):
    state=self.model.getInitialState()
    self._assert(state.__class__=COPASI.CState)

  def test_setInitialState(self):
    # this can not be tested yet since there is no way to manipulate a CState object
    self._assert(false)


  def test_setVolumeUnit(self):
    u=COPASI.CModel.l
    self.setQuantityUnit(u)
    self._assert(self.getQuantityUnitEnum()==u)
    self.model.setQuantityUnit("nl")
    self._assert(self.model.getQuantityUnitEnum()==COPASI.CModel.nl)

  def test_getVolumeUnitName(self):
    n=self.model.getVolumeUnitName()
    self._assert(type(e)==StringType)

  def test_getVolumeUnitEnum(self):
    e=self.model.getVolumeUnitEnum()
    self._assert(type(e)==IntType)

  def test_setTimeUnit(self):
    u=COPASI.CModel.micros
    self.setQuantityUnit(u)
    self._assert(self.getQuantityUnitEnum()==u)
    self.model.setQuantityUnit("ms")
    self._assert(self.model.getQuantityUnitEnum()==COPASI.CModel.ms)

  def test_getTimeUnitName(self):
    n=self.model.getTimeUnitName()
    self._assert(type(e)==StringType)

  def test_getTimeUnitEnum(self):
    e=self.model.getTimeUnitEnum()
    self._assert(type(e)==IntType)

  def test_setQuantityUnit(self):
    u=COPASI.CModel.microMol
    self.setQuantityUnit(u)
    self._assert(self.getQuantityUnitEnum()==u)
    self.model.setQuantityUnit("nMol")
    self._assert(self.model.getQuantityUnitEnum()==COPASI.CModel.nMol)

  def test_getQuantityUnitName(self):
    n=self.model.getQuantityUnitName()
    self._assert(type(e)==StringType)

  def test_getQuantityUnitEnum(self):
    e=self.model.getQuantityUnitEnum()
    self._assert(type(e)==IntType)

  def test_setModelType(self):
    t=COPASI.CModel.deterministic
    self.model.setModelType(t)
    self._assert(self.model.getModelType()==t)
    t=COPASI.CModel.stochastic
    self.model.setModelType(t)
    self._assert(self.model.getModelType()==t)

  def test_getModelType(self):
    t=self.model.getModelType()
    self._assert(type(t)==IntType)

  def test_getQunatity2NumberFactor(self):
    v=self.model.getQuantity2NumberFactor()
    self._assert(type(v)==FloatType)

  def test_getNumber2QuantityFactor(self):
    v=self.model.getNumber2QuantityFactor()
    self._assert(type(v)==FloatType)

  def test_getConcentrationUnitName(self):
    name=self.model.getConcentrationUnitName()
    self._assert(type(name)==StringType)

  def getConcentrationRateUnitName(self):
    name=self.model.getConcentrationRateUnitName()
    self._assert(type(name)==StringType)

  def getQuantityRateUnitName(self):
    name=self.model.getQuantityRateUnitName()
    self._assert(type(name)==StringType)

  def test_createMetabolite(self):
    c=self.model.createCompartment("testCompartment")
    size=self.model.getNumMetabolites()
    m=self.model.createMetabolite("testMetabolite","testCompartment")
    self._assert(self.model.getNumMetabolites()==size+1)
    self._assert(m.__class__==COPASI.CMetab)
    self._assert(m.getObjectName()=="testMetabolite")
    self._assert(m.getCompartment().getObjectName()=="testCompartment")

  def test_removeMetabolite(self):
    c=self.model.createCompartment("testCompartment")
    size=self.model.getNumMetabolites()
    m=self.model.createMetabolite("testMetabolite","testCompartment")
    self._assert(self.model.getNumMetabolites()==size+1)
    self.model.removeMetabolite(m.getKey())
    self._assert(self.model.getNumMetabolites()==size)

  def test_createCompartment(self):
    size=self.model.getNumCompartments()
    c=self.model.createCompartment("testCompartment")
    self._assert(self.model.getNumCompartments()==size+1)
    self._assert(c.__class__==COPASI.CCompartment)
    self._assert(c.getObjectName()=="testCompartment")

  def test_removeCompartment(self):
    size=self.model.getNumCompartments()
    c=self.model.createCompartment("testCompartment")
    self._assert(self.model.getNumCompartments()==size+1)
    self.model.removeCompartment(c.getKey())
    self._assert(self.model.getCompartments()==size)

  def test_createReaction(self):
    size=self.model.getNumReactions()
    r=self.model.createReaction("testReaction")
    self._assert(self.model.getNumReactions()==size+1)
    self._assert(r.__class__==COPASI.CReaction)
    self._assert(r.getObjectName()=="testReaction")

  def test_removeReaction(self):
    size=self.model.getNumReactions()
    r=self.model.createReaction("testReaction")
    self._assert(self.model.getNumReactions()==size+1)
    self.model.removeReaction(r.getKey())
    self._assert(self.model.getNumReactions()==size)

  def test_createModelValue(self):
    size=self.model.getNumModelValues()
    mv=self.model.createModelValue("testModelValue")
    self._assert(self.model.getNumModelValues()==size+1)
    self._assert(mv.__class__==COPASI.CModelValue)
    self._assert(mv.getObjectName()=="testModelValue")

  def test_removeModelValue(self):
    size=self.model.getNumModelValues()
    mv=self.model.createModelValue("testModelValue")
    self._assert(self.model.getNumModelValues()==size+1)
    self.model.removeModelValue(mv.getKey())
    self._assert(self.model.getNumModelValues()==size)

  def test_hasReversibleReaction(self):
    v=self.model.hasReversibleReaction()
    self._assert(type(v)==BooleanType)

  def test_suitableForStochasticSimulation(self):
    v=self.model.suitableForStochasticSimulation()
    self._assert(type(v)==BooleanType)

  def test_isAutonomous(self):
    v=self.model.isAutonomous()
    self._assert(type(v)==BooleanType)


