// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/unittests/Test_RunScan.java,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/01/12 21:20:44 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
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

    public static COptTask runScan(int subTask,Vector<CCopasiParameterGroup> scanItems,bool adjustInitialValues)
    {
        CScanTask scanTask=(CScanTask)CCopasiDataModel.getGlobal().addTask(CCopasiTask.scan);
        if(scanTask==null) return null;
        CScanProblem scanProblem=(CScanProblem)scanTask.getProblem();
        scanProblem.setSubtask(subTask);
        if(scanProblem==null) return null;
        Set<String> keySet=problemParameters.keySet();
        for(Iterator<String> it=keySet.iterator();it.hasNext();)
        {
            String key=(String)it.next();
            CCopasiParameter param=scanProblem.getParameter(key);
            if(param==null)
            {
                return null;
            }
            Object o=problemParameters.get(key);
            if(o instanceof Double)
            {
                param.setDblValue(((Double)o).doubleValue());
            }
            else if(o instanceof Integer)
            {
                param.setIntValue(((Integer)o).intValue());
            }
            else if(o instanceof Boolean)
            {
                param.setBoolValue(((Boolean)o).booleanValue());
            }
            else if(o instanceof String)
            {
                param.setStringValue(((String)o));
            }
            else
            {
                System.err.println("Error. Unknown parameter type.");
            }
        }
        CScanMethod scanMethod=(CScanMethod)scanTask.getMethod();
        if(scanMethod==null)
        {
            return null;
        }
        keySet=methodParameters.keySet();
        for(Iterator<String> it=keySet.iterator();it.hasNext();)
        {
            String key=(String)it.next();
            CCopasiParameter param=scanMethod.getParameter(key);
            if(param==null)
            {
                return null;
            }
            Object o=methodParameters.get(key);
            if(o instanceof Double)
            {
                param.setDblValue(((Double)o).doubleValue());
            }
            else if(o instanceof Integer)
            {
                param.setIntValue(((Integer)o).intValue());
            }
            else if(o instanceof Boolean)
            {
                param.setBoolValue(((Boolean)o).booleanValue());
            }
            else if(o instanceof String)
            {
                param.setStringValue(((String)o));
            }
            else
            {
                System.err.println("Error. Unknown parameter type.");
            }
        }
        for(Iterator<CCopasiParameterGroup> it=scanItems.iterator();it.hasNext();)
        {
           CCopasiParameterGroup scanItem=(CCopasiParameterGroup)it.next();
           CCopasiParameter type=scanItem.getParameter("Type");
           CCopasiParameterGroup newScanItem=scanProblem.createScanItem(type.getUIntValue());
           for(int i=0;i<scanItem.size(),++i)
           {
              CCopasiParameter para=scanItem.getParameter(i);
              newScanItem.addParameter(para);
           }
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
        bool adjustInitialConditions=false;
        CCopasiParameterGroup parameterGroup=new CCopasiParameterGroup();
        parameterGroup.addParameter("Number of steps", CCopasiParameter.UINT, 10);
        parameterGroup.addParameter("Type", CCopasiParameter.UINT, CScanProblem.SCAN_REPEAT);
        parameterGroup.addParameter("Object", CCopasiParameter.CN, "");
        scanIems.add(parameterGroup);
        COptTask optTask=runScan(CCopasiTask.timeCourse,scanItems,adjustInitialConditions);
        assertFalse(optTask==null);
    }

  public static void main(String[] args) {
    junit.textui.TestRunner.run(Test_RunScan.class);
  }

}
