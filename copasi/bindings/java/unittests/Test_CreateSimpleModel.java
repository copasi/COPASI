package org.eml.COPASI.unittests;

import org.eml.COPASI.*;
import junit.framework.*;

class Test_CreateSimpleModel extends TestCase
{
   CCopasiDataModel model;

   public Test_CreateSimpleModel(String name)
   {
    super(name);
   }

   public static CCpasiDataModel createModel()
   {
    CCopasiDataModel.GLOBAL.newModel();
    CCopasiDataModel model=CCopasiDataModel.GLOBAL.getModel();
    model.setVolumeUnit(CModel.fl);
    model.setTimeUnit(CModel.s);
    model.setQuantityUnit(CModel.fMol);
    CCompartment comp=model.createCompartment("CompartmentA");
    CMetab A=model.createMetabolite("A",comp.getObjectName());
    A.setInitialConcentration(2.0e-4);
    CMetab B=model.createMetabolite("B",comp.getObjectName());
    B.setInitialConcentration(0.0);
    CReaction react=model.createReaction("Decay_1");
    react.addSubstrate(A.getKey());
    react.addProduct(B.getKey());
    react.setReversible(False);
    react.setFunction("Mass action (irreversible)");
    react.setParameterValue("k1",0.5);
    ParameterMapping mapping=ParameterMapping();
    mapping.append(react.getChemEq().getSubstrate(0).getMetabolite().getKey());
    react.setParameterMappingVector(react.getFunction().getVariables().getParameter(1).getObjectName(),mapping);;
    model.compileIfNecessary();
    return model;
   }

  public static void extendModel(CCopasiDataModel model)
  {
      CMetab metab=model.createMetabolite("C",model.getCompartment(0).getObjectName());
      metab.setInitialConcentration(0.0);
      CReaction react=model.createReaction("Decay_2");
      react.addSubstrate(model.getMetabolite(1).getKey());
      react.addProduct(metab.getKey());
      react.setReversible(False);
      react.setFunction("Mass action (irreversible)");
      react.getParameters().getParameter(0).setValue(0.1);
      ParameterMapping mapping=ParameterMapping();
      mapping.append(react.getChemEq().getSubstrate(0).getMetabolite().getKey());
      react.setParameterMappingVector(react.getFunction().getVariables().getParameter(1).getObjectName(),mapping);;
      model.compileIfNecessary();
  }

   
  public void setUp()
  {
    this.model=this.createModel();
  }

  public void test_createModel()
  {
     Assert.assertFalse(this.model.equals(null));
     Assert.assertTrue(this.model.getClass()==CModel);
     Assert.assertTrue(this.model.getCompartments().size()==1);
     Assert.assertTrue(this.model.getCompartment(0).getObjectName().equals("CompartmentA"));
     Assert.assertTrue(this.model.getMetabolites().size()==2);
     Assert.assertTrue(this.model.getMetabolite(0).getObjectName().equals("A"));
     Assert.assertTrue(this.model.getMetabolite(0).getInitialConcentration()==2.0e-4);
     Assert.assertTrue(this.model.getMetabolite(1).getObjectName().equals("B"));
     Assert.assertTrue(this.model.getMetabolite(1).getInitialValue()==0.0);
     Assert.assertTrue(this.model.getReactions().size()==1);
     Assert.assertTrue(this.model.getReaction(0).getObjectName().equals("Decay_1"));
     Assert.assertTrue(this.model.getReaction(0).isReversible()==False);
     Assert.assertTrue(this.model.getReaction(0).getChemEq().getSubstrates().size()==1);
     Assert.assertTrue(this.model.getReaction(0).getChemEq().getSubstrate(0).getMetabolite().getObjectName().equals("A"));
     Assert.assertTrue(this.model.getReaction(0).getChemEq().getSubstrate(0).getMultiplicity()==1.0);
     Assert.assertTrue(this.model.getReaction(0).getChemEq().getProducts().size()==1);
     Assert.assertTrue(this.model.getReaction(0).getChemEq().getProduct(0).getMetabolite().getObjectName().equals("B"));
     Assert.assertTrue(this.model.getReaction(0).getChemEq().getProduct(0).getMultiplicity()==1.0);
     Assert.assertTrue(this.model.getReaction(0).getChemEq().getModifiers().size()==0);
     Assert.assertFalse(this.model.getReaction(0).getFunction().equals(null));
     Assert.assertTrue(this.model.getReaction(0).getFunction().getObjectName().equals("Mass action (irreversible)"));
     Assert.assertTrue(this.model.getReaction(0).getParameters().size()==1);
     Assert.assertTrue(this.model.getReaction(0).getParameters().getParameter(0).getObjectName().equals("k1"));
     Assert.assertTrue(this.model.getReaction(0).getParameters().getParameter(0).getValue()==0.5);
  }

  public void test_extendModel()
  {
     this.extendModel(this.model); ;
     Assert.assertTrue(this.model.getMetabolites().size()==3);
     Assert.assertTrue(this.model.getMetabolite(2).getObjectName().equals("C"));
     Assert.assertTrue(this.model.getMetabolite(2).getInitialValue()==0.0);
     Assert.assertTrue(this.model.getReactions().size()==2);
     Assert.assertTrue(this.model.getReaction(1).getObjectName().equals("Decay_2"));
     Assert.assertTrue(this.model.getReaction(1).isReversible()==False);
     Assert.assertTrue(this.model.getReaction(1).getChemEq().getSubstrates().size()==1);
     Assert.assertTrue(this.model.getReaction(1).getChemEq().getSubstrate(0).getMetabolite().getObjectName().equals("B"));
     Assert.assertTrue(this.model.getReaction(1).getChemEq().getSubstrate(0).getMultiplicity()==1.0);
     Assert.assertTrue(this.model.getReaction(1).getChemEq().getProducts().size()==1);
     Assert.assertTrue(this.model.getReaction(1).getChemEq().getProduct(0).getMetabolite().getObjectName().equals("C"));
     Assert.assertTrue(this.model.getReaction(1).getChemEq().getProduct(0).getMultiplicity()==1.0);
     Assert.assertTrue(this.model.getReaction(1).getChemEq().getModifiers().size()==0);
     Assert.assertFalse(this.model.getReaction(1).getFunction().equals(null));
     Assert.assertTrue(this.model.getReaction(1).getFunction().getObjectName().equals("Mass action (irreversible)"));
     Assert.assertTrue(this.model.getReaction(1).getParameters().size()==1);
     Assert.assertTrue(this.model.getReaction(1).getParameters().getParameter(0).getObjectName().equals("k1"));
     Assert.assertTrue(this.model.getReaction(1).getParameters().getParameter(0).getValue()==0.1);
  }
  

  public static void main(String[] args) {
    junit.swingui.TestRunner.run(Test_CreateSimpleModel.class);
  }

/*
 def suite():
  tests=[
          'test_createModel'
         ,'test_extendModel'
        ]
  return unittest.TestSuite(map(Test_CreateSimpleModel,tests))
*/
}
