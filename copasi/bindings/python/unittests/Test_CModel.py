import COPASI
import unittest
from types import *


class Test_CModel(unittest.TestCase):
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
    r=self.model.createReaction("react1")
    r.addSubstrate(m1.getKey())
    r.addProduct(m2.getKey())
    r=self.model.createReaction("react2")
    r.addSubstrate(m3.getKey())
    r.addProduct(m5.getKey())
    r=self.model.createReaction("react3")
    r.addSubstrate(m6.getKey())
    r.addProduct(m2.getKey())
    self.model.buildStoi()
    self.model.buildMoieties()
    #self.model.buildRedStoi()

  def test_getMetabolites(self):
    v=self.model.getMetabolites()
    self.assert_(v.__class__==COPASI.MetabVector)
    self.assert_(v.size()==7)

  def test_getMetabolitesX(self):
    v=self.model.getMetabolites()
    self.assert_(v.__class__==COPASI.MetabVector)
    self.assert_(v.size()==7)

  def test_getNumMetabs(self):
    n=self.model.getNumMetabs()
    self.assert_(type(n)==IntType)
    self.assert_(n==7)

  def test_getNumVariableMetabs(self):
    n=self.model.getNumVeriableMetabs()
    self.assert_(type(n)==IntType)
    self.assert_(n==7)

  def test_getNumODEMetabs(self):
    n=self.model.getNumODEMetabs()
    self.assert_(type(n)==IntType)
    self.assert_(n==6)

  def test_getNumIndependentMetabs(self):
    n=self.model.getNumODEMetabs()
    self.assert_(type(n)==IntType)
    self.assert_(n==4)

  def test_getNumDependentMetabs(self):
    n=self.model.getNumODEMetabs()
    self.assert_(type(n)==IntType)
    self.assert_(n==3)

  def test_getModelValues(self):
    v=self.model.getModelValues()
    self.assert_(v.__class__==COPASI.ModelValueVector)
    self.assert_(v.size()==0)

  def test_getNumModelValues(self):
    n=self.model.getNumModelValues()
    self.assert_(type(n)==IntType)
    self.assert_(n==0)

  def test_getReactions(self):
    v=self.model.getReactions()
    self.assert_(v.__class__==COPASI.ReactionVector)
    self.assert_(v.size()==3)

  def test_getTotSteps(self):
    n=self.model.getTotSteps()
    self.assert_(type(n)==IntType)
    self.assert_(n==3)

  def test_getComments(self):
    comments=self.model.getComments()
    self.assert_(type(comments)==StringType)


  def test_getKey(self):
    key=self.model.getKey()
    self.assert_(type(key)==StringType)

  def test_setTitle(self):
    title="MyTitle"
    self.model.setTitle(title)
    self.assert_(self.model.getTitle()==title)

  def test_setComments(self):
    comment="MyComment"
    self.model.setComments(comment)
    self.assert_(self.model.getComments()==comment)

  def test_setInitialTime(self):
    d=12.4
    self.model.setInitialTime(d)
    self.assert_(math.abs((self.model.getInitialTime()-d)/d)<0.001)

  def test_getInitialTime(self):
    d=self.model.getInitialTime()
    self.assert_(type(d)==FloatType)

  def test_getTime(self):
    d=self.model.getTime()
    self.assert_(type(d)==FloatType)

  def test_getCompartments(self):
    v=self.model.getCompartments()
    self.assert_(v.__class__==COPASI.CompartmentVector)
    self.assert_(v.size()==2)

  def test_getStoi(self):
    m=self.model.getStoi()
    self.assert_(m.__class__==COPASI.FloatMatrix)

  def test_getRedStoi(self):
    m=self.model.getRedStoi()
    self.assert_(m.__class__==COPASI.FloatMatrix)

  def test_getStoiReordered(self):
    m=self.model.getStoiReordered()
    self.assert_(m.__class__==COPASI.FloatMatrix)

  def test_getMoieties(self):
    v=self.model.getMoieties()
    self.assert_(v.__class__==COPASI.MoietyVector)
    self.assert_(v.size()==3)

  def test_findMetabByName(self):
    index=self.model.findMetabByName("D")
    self.assert_(type(index)==IntType)
    self.assert_(index==3) 

  def test_findMoiety(self):
    v=self.model.getMoieties()
    moiety=v.get(1)
    index=self.model.findMoiety(moiety.getObjectName()) 
    self.assert_(type(index)==IntType)
    self.assert_(index==1)

  def test_getInitialState(self):
    state=self.model.getInitialState()
    self.assert_(state.__class__==COPASI.CState)

  def test_getState(self):
    state=self.model.getInitialState()
    self.assert_(state.__class__==COPASI.CState)

  def test_setInitialState(self):
    # this can not be tested yet since there is no way to manipulate a CState object
    self.assert_(0)


  def test_setVolumeUnit(self):
    u=COPASI.CModel.l
    self.setQuantityUnit(u)
    self.assert_(self.getQuantityUnitEnum()==u)
    self.model.setQuantityUnit("nl")
    self.assert_(self.model.getQuantityUnitEnum()==COPASI.CModel.nl)

  def test_getVolumeUnitName(self):
    n=self.model.getVolumeUnitName()
    self.assert_(type(e)==StringType)

  def test_getVolumeUnitEnum(self):
    e=self.model.getVolumeUnitEnum()
    self.assert_(type(e)==IntType)

  def test_setTimeUnit(self):
    u=COPASI.CModel.micros
    self.setQuantityUnit(u)
    self.assert_(self.getQuantityUnitEnum()==u)
    self.model.setQuantityUnit("ms")
    self.assert_(self.model.getQuantityUnitEnum()==COPASI.CModel.ms)

  def test_getTimeUnitName(self):
    n=self.model.getTimeUnitName()
    self.assert_(type(e)==StringType)

  def test_getTimeUnitEnum(self):
    e=self.model.getTimeUnitEnum()
    self.assert_(type(e)==IntType)

  def test_setQuantityUnit(self):
    u=COPASI.CModel.microMol
    self.setQuantityUnit(u)
    self.assert_(self.getQuantityUnitEnum()==u)
    self.model.setQuantityUnit("nMol")
    self.assert_(self.model.getQuantityUnitEnum()==COPASI.CModel.nMol)

  def test_getQuantityUnitName(self):
    n=self.model.getQuantityUnitName()
    self.assert_(type(e)==StringType)

  def test_getQuantityUnitEnum(self):
    e=self.model.getQuantityUnitEnum()
    self.assert_(type(e)==IntType)

  def test_setModelType(self):
    t=COPASI.CModel.deterministic
    self.model.setModelType(t)
    self.assert_(self.model.getModelType()==t)
    t=COPASI.CModel.stochastic
    self.model.setModelType(t)
    self.assert_(self.model.getModelType()==t)

  def test_getModelType(self):
    t=self.model.getModelType()
    self.assert_(type(t)==IntType)

  def test_getQuantity2NumberFactor(self):
    v=self.model.getQuantity2NumberFactor()
    self.assert_(type(v)==FloatType)

  def test_getNumber2QuantityFactor(self):
    v=self.model.getNumber2QuantityFactor()
    self.assert_(type(v)==FloatType)

  def test_getConcentrationUnitName(self):
    name=self.model.getConcentrationUnitName()
    self.assert_(type(name)==StringType)

  def test_getConcentrationRateUnitName(self):
    name=self.model.getConcentrationRateUnitName()
    self.assert_(type(name)==StringType)

  def test_getQuantityRateUnitName(self):
    name=self.model.getQuantityRateUnitName()
    self.assert_(type(name)==StringType)

  def test_createMetabolite(self):
    c=self.model.createCompartment("testCompartment")
    size=self.model.getNumMetabolites()
    m=self.model.createMetabolite("testMetabolite","testCompartment")
    self.assert_(self.model.getNumMetabolites()==size+1)
    self.assert_(m.__class__==COPASI.CMetab)
    self.assert_(m.getObjectName()=="testMetabolite")
    self.assert_(m.getCompartment().getObjectName()=="testCompartment")

  def test_removeMetabolite(self):
    c=self.model.createCompartment("testCompartment")
    size=self.model.getNumMetabolites()
    m=self.model.createMetabolite("testMetabolite","testCompartment")
    self.assert_(self.model.getNumMetabolites()==size+1)
    self.model.removeMetabolite(m.getKey())
    self.assert_(self.model.getNumMetabolites()==size)

  def test_createCompartment(self):
    size=self.model.getNumCompartments()
    c=self.model.createCompartment("testCompartment")
    self.assert_(self.model.getNumCompartments()==size+1)
    self.assert_(c.__class__==COPASI.CCompartment)
    self.assert_(c.getObjectName()=="testCompartment")

  def test_removeCompartment(self):
    size=self.model.getNumCompartments()
    c=self.model.createCompartment("testCompartment")
    self.assert_(self.model.getNumCompartments()==size+1)
    self.model.removeCompartment(c.getKey())
    self.assert_(self.model.getCompartments()==size)

  def test_createReaction(self):
    size=self.model.getNumReactions()
    r=self.model.createReaction("testReaction")
    self.assert_(self.model.getNumReactions()==size+1)
    self.assert_(r.__class__==COPASI.CReaction)
    self.assert_(r.getObjectName()=="testReaction")

  def test_removeReaction(self):
    size=self.model.getNumReactions()
    r=self.model.createReaction("testReaction")
    self.assert_(self.model.getNumReactions()==size+1)
    self.model.removeReaction(r.getKey())
    self.assert_(self.model.getNumReactions()==size)

  def test_createModelValue(self):
    size=self.model.getNumModelValues()
    mv=self.model.createModelValue("testModelValue")
    self.assert_(self.model.getNumModelValues()==size+1)
    self.assert_(mv.__class__==COPASI.CModelValue)
    self.assert_(mv.getObjectName()=="testModelValue")

  def test_removeModelValue(self):
    size=self.model.getNumModelValues()
    mv=self.model.createModelValue("testModelValue")
    self.assert_(self.model.getNumModelValues()==size+1)
    self.model.removeModelValue(mv.getKey())
    self.assert_(self.model.getNumModelValues()==size)

  def test_hasReversibleReaction(self):
    v=self.model.hasReversibleReaction()
    self.assert_(type(v)==BooleanType)

  def test_suitableForStochasticSimulation(self):
    v=self.model.suitableForStochasticSimulation()
    self.assert_(type(v)==BooleanType)

  def test_isAutonomous(self):
    v=self.model.isAutonomous()
    self.assert_(type(v)==BooleanType)

def suite():
  tests=[
          'test_getMetabolites'
         ,'test_getMetabolitesX'
         ,'test_getNumMetabs'
         ,'test_getNumVariableMetabs'
         ,'test_getNumODEMetabs'
         ,'test_getNumIndependentMetabs'
         ,'test_getNumDependentMetabs'
         ,'test_getModelValues'
         ,'test_getNumModelValues'
         ,'test_getReactions'
         ,'test_getTotSteps'
         ,'test_getComments'
         ,'test_getKey'
         ,'test_setTitle'
         ,'test_setComments'
         ,'test_getInitialTime'
         ,'test_setInitialTime'
         ,'test_getTime'
         ,'test_getCompartments'
         ,'test_getStoi'
         ,'test_getRedStoi'
         ,'test_getStoiReordered'
         ,'test_getMoieties'
         ,'test_findMetabByName'
         ,'test_findMoiety'
         ,'test_getInitialState'
         ,'test_getState'
         ,'test_setInitialState'
         ,'test_getVolumeUnitEnum'
         ,'test_getVolumeUnitName'
         ,'test_setVolumeUnit'
         ,'test_getTimeUnitEnum'
         ,'test_getTimeUnitName'
         ,'test_setTimeUnit'
         ,'test_getQuantityUnitEnum'
         ,'test_getQuantityUnitName'
         ,'test_setQuantityUnit'
         ,'test_getModelType'
         ,'test_setModelType'
         ,'test_getQuantity2NumberFactor'
         ,'test_getNumber2QuantityFactor'
         ,'test_getConcentrationUnitName'
         ,'test_getConcentrationRateUnitName'
         ,'test_getQuantityRateUnitName'
         ,'test_createMetabolite'
         ,'test_removeMetabolite'
         ,'test_createCompartment'
         ,'test_removeCompartment'
         ,'test_createReaction'
         ,'test_removeReaction'
         ,'test_createModelValue'
         ,'test_removeModelValue'
         ,'test_hasReversibleReaction'
         ,'test_suitableForStochasticSimulation'
         ,'test_isAutonomous'
        ]
  return unittest.TestSuite(map(Test_CModel,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


