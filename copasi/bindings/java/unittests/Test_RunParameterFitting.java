// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

package org.COPASI.unittests;

import org.COPASI.*;
import junit.framework.*;


public class Test_RunParameterFitting extends TestCase
{

   CDataModel mDataModel;

   public Test_RunParameterFitting(String name)
   {
    super(name);
   }

    public void setUp()
    {
        mDataModel=CRootContainer.addDatamodel();
        Test_CreateSimpleModel.createModel(mDataModel);
    }


    public void test_RunParameterFitting_simple()
    {
        CFitTask fitTask=(CFitTask)mDataModel.addTask(CCopasiTask.parameterFitting);
        assertTrue(fitTask!=null);
        assertTrue(fitTask.getClass()==CFitTask.class);
        // the method in a fit task is an instance of COptMethod or a subclass of
        // it.
        COptMethod fitMethod=(COptMethod)fitTask.getMethod();
        assertTrue(fitMethod!=null);
        // the object must be an instance of COptMethod or a subclass thereof
        // (CFitMethod)
        assertTrue(fitMethod instanceof COptMethod);
        CFitProblem fitProblem=(CFitProblem)fitTask.getProblem();
        assertTrue(fitProblem!=null);
        assertTrue(fitProblem.getClass()==CFitProblem.class);
        CExperimentSet experimentSet=(CExperimentSet)fitProblem.getParameter("Experiment Set");
        assertTrue(experimentSet!=null);
        assertTrue(experimentSet.getClass() == CExperimentSet.class);
        assertTrue(experimentSet.getExperimentCount() == 0);
        // first experiment
        CExperiment experiment=new CExperiment(mDataModel);
        assertTrue(experiment!=null);
        assertTrue(experiment.getClass()==CExperiment.class);
        experiment.setFileName("parameter_fitting_data_simple.txt");
        experiment.setFirstRow(1);
        assertTrue(experiment.getFirstRow()==1);
        experiment.setLastRow(22);
        assertTrue(experiment.getLastRow()==22);
        experiment.setHeaderRow(1);
        assertTrue(experiment.getHeaderRow()==1);
        experiment.setExperimentType(CCopasiTask.timeCourse);
        assertTrue(experiment.getExperimentType()==CCopasiTask.timeCourse);
        experiment.setNumColumns(3);
        assertTrue(experiment.getNumColumns()==3);
        CExperimentObjectMap objectMap=experiment.getObjectMap();
        assertTrue(objectMap!=null);
        assertTrue(objectMap.getClass()==CExperimentObjectMap.class);
        boolean result=objectMap.setNumCols(3);
        assertTrue(result==true);
        result=objectMap.setRole(0,CExperiment.time);
        assertTrue(result==true);
        assertTrue(objectMap.getRole(0)==CExperiment.time);
        CModel model=mDataModel.getModel();
        assertTrue(model!=null);
        assertTrue(model.getClass()==CModel.class);
        CDataObject timeReference=model.getObject(new CCommonName("Reference=Time"));
        assertTrue(timeReference!=null);
        assertTrue(timeReference.getClass()==CDataObject.class);
        objectMap.setObjectCN(0,timeReference.getCN().getString());
        // getObjectCN returns a string whereas getCN returns a
        // CCommonName
        assertTrue(objectMap.getObjectCN(0).equals(timeReference.getCN().getString()));
        CMetab metabA=model.getMetabolite(0);
        assertTrue(metabA!=null);
        assertTrue(metabA.getClass()==CMetab.class);
        CMetab metabB=null;
        if(metabA.getObjectName()!="A")
        {
            metabB=metabA;
            metabA=model.getMetabolite(1);
            assertTrue(metabA!=null);
            assertTrue(metabA.getClass()==CMetab.class);
        }
        else
        {
            metabB=model.getMetabolite(1);
            assertTrue(metabB!=null);
            assertTrue(metabB.getClass()==CMetab.class);
        }
        objectMap.setRole(1,CExperiment.dependent);
        CDataObject particleReference=metabA.getObject(new CCommonName("Reference=ParticleNumber"));
        assertTrue(particleReference!=null);
        assertTrue(particleReference.getClass()==CDataObject.class);
        objectMap.setObjectCN(1,particleReference.getCN().getString());
        // getObjectCN returns a string whereas getCN returns a
        // CCommonName
        assertTrue(objectMap.getObjectCN(1).equals(particleReference.getCN().getString()));
        objectMap.setRole(2,CExperiment.dependent);
        particleReference=metabB.getObject(new CCommonName("Reference=ParticleNumber"));
        assertTrue(particleReference!=null);
        assertTrue(particleReference.getClass()==CDataObject.class);
        objectMap.setObjectCN(2,particleReference.getCN().getString());
        // getObjectCN returns a string whereas getCN returns a
        // CCommonName
        assertTrue(objectMap.getObjectCN(2).equals(particleReference.getCN().getString()));
        // reading from string is not possible with the current C++ API
        //result=experiment.read(TIME_COURSE_DATA,false)
        //assertTrue(result==true)
        experimentSet.addExperiment(experiment);
        assertTrue(experimentSet.getExperimentCount()==1);
        // addExperiment makes a copy, so we need to get the added experiment
        // again
        experiment=experimentSet.getExperiment(0);
        assertTrue(experiment!=null);
        assertTrue(experiment.getClass()==CExperiment.class);

        CReaction reaction=model.getReaction(0);
        assertTrue(reaction!=null);
        assertTrue(reaction.getClass()==CReaction.class);
        assertTrue(reaction.isLocalParameter(0)==true);
        CCopasiParameter parameter=reaction.getParameters().getParameter(0);
        assertTrue(parameter!=null);
        assertTrue(parameter.getClass()==CCopasiParameter.class);
        
        // define CFitItems
        assertTrue(fitProblem.getOptItemSize()==0);
        CDataObject parameterReference=parameter.getObject(new CCommonName("Reference=Value"));
        assertTrue(parameterReference!=null);
        assertTrue(parameterReference.getClass()==CDataObject.class);
        CFitItem fitItem=new CFitItem(mDataModel);
        assertTrue(fitItem!=null);
        assertTrue(fitItem.getClass()==CFitItem.class);
        fitItem.setObjectCN(parameterReference.getCN());
        fitItem.setStartValue(4.0);
        fitItem.setLowerBound(new CCommonName("0.0001"));
        fitItem.setUpperBound(new CCommonName("10"));
        // add the experiment to the fit item
        //fitItem.addExperiment(experiment.getKey())
        assertTrue(fitItem.getStartValue()==4.0);
        //assertTrue(fitItem.getExperimentCount()==1)
        // add the fit item to the correct parameter group
        CCopasiParameterGroup optimizationItemGroup=(CCopasiParameterGroup)fitProblem.getParameter("OptimizationItemList");
        assertTrue(optimizationItemGroup!=null);
        assertTrue(optimizationItemGroup.getClass()==CCopasiParameterGroup.class);
        assertTrue(optimizationItemGroup.size()==0);
        optimizationItemGroup.addParameter(fitItem);
        assertTrue(optimizationItemGroup.size()==1);
        // addParameter makes a copy of the fit item, so we have to get it back
        fitItem=(CFitItem)optimizationItemGroup.getParameter(0);
        assertTrue(fitItem!=null);
        assertTrue(fitItem.getClass()==CFitItem.class);
        result=true;
        try
        {
          result=fitTask.process(true);
        }
        catch(Exception e)
        {
          result=false;
        }
        assertTrue(result==true);
        // just check if the result is in the correct range. The actual value is
        // probably off since we use only one experiment to fit
        assertTrue((fitItem.getLocalValue()-0.5)/0.5 < 1.0);
    }

  public static void main(String[] args) {
    junit.textui.TestRunner.run(Test_RunParameterFitting.class);
  }

}
