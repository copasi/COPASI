// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/unittests/Test_RunScan.java,v $ 
//   $Revision: 1.4 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2008/01/15 17:53:26 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

package org.COPASI.unittests;

import java.lang.Math;
import java.util.HashMap;
import java.util.Set;
import java.util.Vector;
import java.util.Iterator;
import org.COPASI.*;
import junit.framework.*;


public class Test_RunScan extends TestCase
{

    CModel mModel;

   public Test_RunScan(String name)
   {
    super(name);
   }

   public CModel createModel()
   {
     try
     {
    CCopasiDataModel.getGlobal().newModel();
    }
    catch(Exception e)
    {
        return null;
    }
    CModel model=CCopasiDataModel.getGlobal().getModel();
    model.setVolumeUnit(CModel.fl);
    model.setTimeUnit(CModel.s);
    model.setQuantityUnit(CModel.fMol);
    CModelValue fixedModelValue=model.createModelValue("R",4.0);
    CModelValue variableModelValue=model.createModelValue("K");
    variableModelValue.setStatus(CModelEntity.ASSIGNMENT);
    String s=fixedModelValue.getObject(new CCopasiObjectName("Reference=Value")).getCN().getString();
    s="<"+s+">^2";
    variableModelValue.setExpression(s);
    model.compileIfNecessary();
    ObjectStdVector changedObjects=new ObjectStdVector();
    changedObjects.add(fixedModelValue.getObject(new CCopasiObjectName("Reference=InitialValue")));
    changedObjects.add(variableModelValue.getObject(new CCopasiObjectName("Reference=InitialValue")));
    model.updateInitialValues(changedObjects);
    return model;
   }
    
    public void setUp()
    {
        this.mModel=createModel();
    }

    public static CScanTask runScan(int subTask,Vector<CCopasiParameterGroup> scanItems,boolean adjustInitialValues)
    {
        CScanTask scanTask=(CScanTask)CCopasiDataModel.getGlobal().addTask(CCopasiTask.scan);
        if(scanTask==null) return null;
        CScanProblem scanProblem=(CScanProblem)scanTask.getProblem();
        scanProblem.setSubtask(subTask);
        if(scanProblem==null) return null;
        CCopasiParameterGroup problemScanItems=scanProblem.getGroup("ScanItems");
        if(problemScanItems==null) return null;
        for(Iterator<CCopasiParameterGroup> it=scanItems.iterator();it.hasNext();)
        {
           CCopasiParameterGroup scanItem=(CCopasiParameterGroup)it.next();
           problemScanItems.addParameter(scanItem);
        }
        boolean result=false;
        try
        {
            if(scanTask.initialize(CCopasiTask.NO_OUTPUT,null)!=false)
            {
              result=scanTask.process(true);
            }
        }
        catch(Exception e)
        {
            System.err.println("ERROR: "+e.getMessage());
        }
        if(!result)
        {
            return null;
        }
        return scanTask;
    }

    public void test_Scan_Repeat()
    {
        Vector<CCopasiParameterGroup> scanItems=new Vector<CCopasiParameterGroup>();
        boolean adjustInitialConditions=false;
        CCopasiParameterGroup parameterGroup=new CCopasiParameterGroup("scanItems");
        parameterGroup.addParameter("Number of steps", CCopasiParameter.UINT);
        parameterGroup.getParameter("Number of steps").setUIntValue(10);
        parameterGroup.addParameter("Type", CCopasiParameter.UINT);
        parameterGroup.getParameter("Type").setUIntValue(CScanProblem.SCAN_REPEAT);
        parameterGroup.addParameter("Object", CCopasiParameter.CN);
        parameterGroup.getParameter("Object").setStringValue("");
        scanItems.add(parameterGroup);
        CScanTask optTask=runScan(CCopasiTask.timeCourse,scanItems,adjustInitialConditions);
        assertFalse(optTask==null);
    }

  public static void main(String[] args) {
    junit.textui.TestRunner.run(Test_RunScan.class);
  }

}
