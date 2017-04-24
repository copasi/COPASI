// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

package org.COPASI.unittests;

import org.COPASI.*;
import junit.framework.*;

public class Test_CreateSimpleModel extends TestCase
{

   CDataModel mDataModel;
   CModel model;

   public Test_CreateSimpleModel(String name)
   {
    super(name);
   }

   public static CModel createModel(CDataModel dataModel)
   {
    try
    {
      dataModel.newModel();
    }
    catch(Exception e)
    {
        return null;
    }
    CModel model=dataModel.getModel();
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
    StringStdVector mapping=new StringStdVector();
    mapping.add(react.getChemEq().getSubstrate(0).getMetabolite().getKey());
    react.setParameterMappingVector(react.getFunction().getVariables().getParameter(1).getObjectName(),mapping);
    model.compileIfNecessary();
    ObjectStdVector changedObjects=new ObjectStdVector();
    changedObjects.add(comp.getObject(new CCommonName("Reference=InitialVolume")));
    changedObjects.add(A.getObject(new CCommonName("Reference=InitialConcentration")));
    changedObjects.add(B.getObject(new CCommonName("Reference=InitialConcentration")));
    changedObjects.add(react.getParameters().getParameter(0).getObject(new CCommonName("Reference=Value")));
    model.updateInitialValues(changedObjects);
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
      StringStdVector mapping=new StringStdVector();
      mapping.add(react.getChemEq().getSubstrate(0).getMetabolite().getKey());
      react.setParameterMappingVector(react.getFunction().getVariables().getParameter(1).getObjectName(),mapping);;
      model.compileIfNecessary();
      ObjectStdVector changedObjects=new ObjectStdVector();
      changedObjects.add(metab.getObject(new CCommonName("Reference=InitialConcentration")));
      changedObjects.add(react.getParameters().getParameter(0).getObject(new CCommonName("Reference=Value")));
      model.updateInitialValues(changedObjects);
  }

   
  public void setUp()
  {
    mDataModel=CRootContainer.addDatamodel();
    this.model=this.createModel(mDataModel);
  }

  public void test_createModel()
  {
     assertFalse(this.model==null);
     assertTrue(this.model.getClass().getName().equals("org.COPASI.CModel"));
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
