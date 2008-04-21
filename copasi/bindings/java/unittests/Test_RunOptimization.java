// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/unittests/Test_RunOptimization.java,v $ 
//   $Revision: 1.2.4.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/04/02 07:50:04 $ 
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
import java.util.Iterator;
import org.COPASI.*;
import junit.framework.*;


public class Test_RunOptimization extends TestCase
{

    CModel mModel;
    CModelValue mVariableModelValue;
    CModelValue mFixedModelValue;

   public Test_RunOptimization(String name)
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
    this.mFixedModelValue=model.createModelValue("R",4.0);
    this.mVariableModelValue=model.createModelValue("K");
    this.mVariableModelValue.setStatus(CModelEntity.ASSIGNMENT);
    String s=this.mFixedModelValue.getObject(new CCopasiObjectName("Reference=Value")).getCN().getString();
    s="<"+s+">^2";
    this.mVariableModelValue.setExpression(s);
    model.compileIfNecessary();
    return model;
   }
    
    public void setUp()
    {
        this.mModel=createModel();
    }

    public static COptTask runOptimization(int methodType,HashMap<String,Object> problemParameters,HashMap<String,Object> methodParameters,String objectiveFunction,COptItem optItem)
    {
        COptTask optTask=(COptTask)CCopasiDataModel.getGlobal().addTask(CCopasiTask.optimization);
        if(optTask==null) return null;
        optTask.setMethodType(CCopasiMethod.LevenbergMarquardt);
        COptProblem optProblem=(COptProblem)optTask.getProblem();
        if(optProblem==null) return null;
        Set<String> keySet=problemParameters.keySet();
        for(Iterator<String> it=keySet.iterator();it.hasNext();)
        {
            String key=(String)it.next();
            CCopasiParameter param=optProblem.getParameter(key);
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
        COptMethod optMethod=(COptMethod)optTask.getMethod();
        if(optMethod==null)
        {
            return null;
        }
        keySet=methodParameters.keySet();
        for(Iterator<String> it=keySet.iterator();it.hasNext();)
        {
            String key=(String)it.next();
            CCopasiParameter param=optMethod.getParameter(key);
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
        optProblem.setObjectiveFunction(objectiveFunction);
        COptItem optItem2=optProblem.addOptItem(optItem.getObjectCN());
        optItem2.setStartValue(optItem.getStartValue());
        optItem2.setLowerBound(new CCopasiObjectName(optItem.getLowerBound()));
        optItem2.setUpperBound(new CCopasiObjectName(optItem.getUpperBound()));
        boolean result=false;
        try
        {
            if(optTask.initialize(CCopasiTask.NO_OUTPUT,CCopasiDataModel.getGlobal(),null)!=false)
            {
              result=optTask.process(true);
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
        return optTask;
    }

    public void test_RunOptimization_LevenbergMarquardt()
    {
        String timeCourseKey="";
        for(int  x=0;x < CCopasiDataModel.getGlobal().getTaskList().size();x++)
        {
            if(CCopasiDataModel.getGlobal().getTask(x).getType()==CCopasiTask.timeCourse)
            {
                timeCourseKey=CCopasiDataModel.getGlobal().getTask(x).getKey();
                break;
            }
        }
        assertFalse(timeCourseKey=="");
        HashMap<String,Object> problemParameters=new HashMap<String,Object>();
        // steady state or time-course
        problemParameters.put("Steady-State","");
        problemParameters.put("Time-Course",timeCourseKey);
        // opt_items 
        COptItem optItem=new COptItem();
        optItem.setObjectCN(new CCopasiObjectName(this.mFixedModelValue.getObject(new CCopasiObjectName("Reference=InitialValue")).getCN()));
        optItem.setStartValue(4.0);
        optItem.setLowerBound(new CCopasiObjectName("-100"));
        optItem.setUpperBound(new CCopasiObjectName("100"));
        HashMap<String,Object> methodParameters=new HashMap<String,Object>();
        // iteration limit
        // tolerance
        methodParameters.put("Iteration Limit",new Integer(2000));
        methodParameters.put("Tolerance",new Double(1.0e-5));
        // objective function
        String objectiveFunction=this.mVariableModelValue.getObject(new CCopasiObjectName("Reference=Value")).getCN().getString();
        objectiveFunction="<"+objectiveFunction+">";
        COptTask optTask=runOptimization(CCopasiMethod.LevenbergMarquardt,problemParameters,methodParameters,objectiveFunction,optItem);
        assertFalse(optTask==null);
        COptProblem optProblem=(COptProblem)optTask.getProblem();
        assertFalse(optProblem==null);
        assertTrue(optProblem.getSolutionVariables().size()==optProblem.getOptItemList().size());
        assertTrue(optProblem.getSolutionVariables().size()==1);
        assertTrue(optProblem.getSolutionVariables().get(0) < 1e-6);
        assertTrue(optProblem.getSolutionValue() < 1e-6);
    }

  public static void main(String[] args) {
    junit.textui.TestRunner.run(Test_RunOptimization.class);
  }

}
