package org.eml.COPASI.unittests;

import org.eml.COPASI.*;
import junit.framework.*;

public class Test_CreateSimpleModel extends TestCase
{

   CModel model;

   public Test_CreateSimpleModel(String name)
   {
    super(name);
   }

   public static CModel createModel()
   {
    CCopasiDataModel.getGlobal().newModel();
    CModel model=CCopasiDataModel.getGlobal().getModel();
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
    react.setReversible(false);
    react.setFunction("Mass action (irreversible)");
    react.setParameterValue("k1",0.5);
    ParameterMapping mapping=new ParameterMapping();
    mapping.add(react.getChemEq().getSubstrate(0).getMetabolite().getKey());
    react.setParameterMappingVector(react.getFunction().getVariables().getParameter(1).getObjectName(),mapping);;
    model.compileIfNecessary();
    return model;
   }

  public static void extendModel(CModel model)
  {
      CMetab metab=model.createMetabolite("C",model.getCompartment(0).getObjectName());
      metab.setInitialConcentration(0.0);
      CReaction react=model.createReaction("Decay_2");
      react.addSubstrate(model.getMetabolite(1).getKey());
      react.addProduct(metab.getKey());
      react.setReversible(false);
      react.setFunction("Mass action (irreversible)");
      react.getParameters().getParameter(0).setDblValue(0.1);
      ParameterMapping mapping=new ParameterMapping();
      mapping.add(react.getChemEq().getSubstrate(0).getMetabolite().getKey());
      react.setParameterMappingVector(react.getFunction().getVariables().getParameter(1).getObjectName(),mapping);;
      model.compileIfNecessary();
  }

   
  public void setUp()
  {
    this.model=this.createModel();
  }

  public void test_createModel()
  {
     assertFalse(this.model==null);
     assertTrue(this.model.getClass().getName().equals("org.eml.COPASI.CModel"));
     assertTrue(this.model.getCompartments().size()==1);
     assertTrue(this.model.getCompartment(0).getObjectName().equals("CompartmentA"));
     assertTrue(this.model.getMetabolites().size()==2);
     assertTrue(this.model.getMetabolite(0).getObjectName().equals("A"));
     assertTrue(this.model.getMetabolite(0).getInitialConcentration()==2.0e-4);
     assertTrue(this.model.getMetabolite(1).getObjectName().equals("B"));
     assertTrue(this.model.getMetabolite(1).getInitialValue()==0.0);
     assertTrue(this.model.getReactions().size()==1);
     assertTrue(this.model.getReaction(0).getObjectName().equals("Decay_1"));
     assertTrue(this.model.getReaction(0).isReversible()==false);
     assertTrue(this.model.getReaction(0).getChemEq().getSubstrates().size()==1);
     assertTrue(this.model.getReaction(0).getChemEq().getSubstrate(0).getMetabolite().getObjectName().equals("A"));
     assertTrue(this.model.getReaction(0).getChemEq().getSubstrate(0).getMultiplicity()==1.0);
     assertTrue(this.model.getReaction(0).getChemEq().getProducts().size()==1);
     assertTrue(this.model.getReaction(0).getChemEq().getProduct(0).getMetabolite().getObjectName().equals("B"));
     assertTrue(this.model.getReaction(0).getChemEq().getProduct(0).getMultiplicity()==1.0);
     assertTrue(this.model.getReaction(0).getChemEq().getModifiers().size()==0);
     assertFalse(this.model.getReaction(0).getFunction()==null);
     assertTrue(this.model.getReaction(0).getFunction().getObjectName().equals("Mass action (irreversible)"));
     assertTrue(this.model.getReaction(0).getParameters().size()==1);
     assertTrue(this.model.getReaction(0).getParameters().getParameter(0).getObjectName().equals("k1"));
     assertTrue(this.model.getReaction(0).getParameters().getParameter(0).getDblValue()==0.5);
  }

  public void test_extendModel()
  {
     this.extendModel(this.model); ;
     assertTrue(this.model.getMetabolites().size()==3);
     assertTrue(this.model.getMetabolite(2).getObjectName().equals("C"));
     assertTrue(this.model.getMetabolite(2).getInitialValue()==0.0);
     assertTrue(this.model.getReactions().size()==2);
     assertTrue(this.model.getReaction(1).getObjectName().equals("Decay_2"));
     assertTrue(this.model.getReaction(1).isReversible()==false);
     assertTrue(this.model.getReaction(1).getChemEq().getSubstrates().size()==1);
     assertTrue(this.model.getReaction(1).getChemEq().getSubstrate(0).getMetabolite().getObjectName().equals("B"));
     assertTrue(this.model.getReaction(1).getChemEq().getSubstrate(0).getMultiplicity()==1.0);
     assertTrue(this.model.getReaction(1).getChemEq().getProducts().size()==1);
     assertTrue(this.model.getReaction(1).getChemEq().getProduct(0).getMetabolite().getObjectName().equals("C"));
     assertTrue(this.model.getReaction(1).getChemEq().getProduct(0).getMultiplicity()==1.0);
     assertTrue(this.model.getReaction(1).getChemEq().getModifiers().size()==0);
     assertFalse(this.model.getReaction(1).getFunction()==null);
     assertTrue(this.model.getReaction(1).getFunction().getObjectName().equals("Mass action (irreversible)"));
     assertTrue(this.model.getReaction(1).getParameters().size()==1);
     assertTrue(this.model.getReaction(1).getParameters().getParameter(0).getObjectName().equals("k1"));
     assertTrue(this.model.getReaction(1).getParameters().getParameter(0).getDblValue()==0.1);
  }
  

  public static void main(String[] args) {
    junit.textui.TestRunner.run(Test_CreateSimpleModel.class);
  }

}
