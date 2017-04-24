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

import java.lang.Math;
import java.util.HashMap;
import java.util.Set;
import java.util.Iterator;
import org.COPASI.*;
import junit.framework.*;

public class Test_RunSimulations extends TestCase
{


   protected CDataModel mDataModel;
   protected CModel model;
   protected int NUM_REPEATS;

   public Test_RunSimulations(String name)
   {
    super(name);
   }

   public static CTrajectoryTask runSimulation(CDataModel dataModel,int methodType,HashMap<String,Object> problemParameters,HashMap<String,Object> methodParameters)
   {
    CTrajectoryTask task=null;
    for(int  x=0;x < dataModel.getTaskList().size();x++)
    {
        if(dataModel.getTask(x).getType()==CCopasiTask.timeCourse)
        {
          task=(CTrajectoryTask)dataModel.getTask(x);
        }
    }
    if(task==null)
    {
      return task;
    }
    task.setMethodType(methodType);
    CCopasiProblem problem=task.getProblem();
    if(problem==null)
    {
      return null;
    }
    Set<String> keySet=problemParameters.keySet();
    for(Iterator<String> it=keySet.iterator();it.hasNext();)
    {
      String key=(String)it.next();
      CCopasiParameter param=problem.getParameter(key);
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
      else
      {
        System.err.println("Error. Unknown parameter type.");
      }
    }
    CCopasiMethod method=task.getMethod();
    if(method==null)
    {
      return null;
    }
    keySet=methodParameters.keySet();
    for(Iterator<String> it=keySet.iterator();it.hasNext();)
    {
      String key=(String)it.next();
      CCopasiParameter param=method.getParameter(key);
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
      else
      {
        System.err.println("Error. Unknown parameter type.");
      }
    }
    boolean result=false;
    try
    {
       result=task.process(true);
    }
    catch(Exception e)
    {
       System.err.println("ERROR: "+e.getMessage());
    }
    if(!result)
    {
      return null;
    }
    return task;
   }

  public static CTrajectoryTask runDeterministicSimulation(CDataModel dataModel)
  {
   HashMap<String,Object> problemParameters=new HashMap<String,Object>();
   problemParameters.put("StepSize",new Double(0.001));
   problemParameters.put("StepNumber",new Integer(10000));
   problemParameters.put("Duration",new Double(10.0));
   problemParameters.put("TimeSeriesRequested",new Boolean(true));
   problemParameters.put("OutputStartTime",new Double(0.0));
   HashMap<String,Object> methodParameters=new HashMap<String,Object>();
   methodParameters.put("Absolute Tolerance",new Double(1.0e-20));
   return runSimulation(dataModel,CCopasiMethod.deterministic,problemParameters,methodParameters);
  }

  public static CTrajectoryTask runStochasticSimulation(CDataModel dataModel)
  {
   HashMap<String,Object> problemParameters=new HashMap<String,Object>();
   problemParameters.put("StepSize",new Double(0.001));
   problemParameters.put("StepNumber",new Integer(10000));
   problemParameters.put("Duration",new Double(10.0));
   problemParameters.put("TimeSeriesRequested",new Boolean(true));
   problemParameters.put("OutputStartTime",new Double(0.0));
   HashMap<String,Object> methodParameters=new HashMap<String,Object>();
   return runSimulation(dataModel,CCopasiMethod.stochastic,problemParameters,methodParameters);
  }

  public static CTrajectoryTask runHybridSimulation(CDataModel dataModel)
  {
   HashMap<String,Object> problemParameters=new HashMap<String,Object>();
   problemParameters.put("StepSize",new Double(0.001));
   problemParameters.put("StepNumber",new Integer(10000));
   problemParameters.put("Duration",new Double(10.0));
   problemParameters.put("TimeSeriesRequested",new Boolean(true));
   problemParameters.put("OutputStartTime",new Double(0.0));
   HashMap<String,Object> methodParameters=new HashMap<String,Object>();
   return runSimulation(dataModel,CCopasiMethod.hybrid,problemParameters,methodParameters);
  }

  public void setUp()
  {
    mDataModel=CRootContainer.addDatamodel();
    this.model=Test_CreateSimpleModel.createModel(mDataModel);
    this.NUM_REPEATS=20;
  }

  
  public void test_runStochasticSimulationOnSimpleModel()
  {
    double[][] values=new double[this.NUM_REPEATS][4];
    for(int x=0;x < this.NUM_REPEATS;x++)
    {
      CTrajectoryTask task=runStochasticSimulation(mDataModel);
      assertTrue(task!=null);
      assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
      CTimeSeries timeseries=task.getTimeSeries();
      assertTrue(timeseries!=null);
      assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
      assertTrue(timeseries.getRecordedSteps()==10001);
      assertTrue(timeseries.getNumVariables()==4);
      values[x][0]=timeseries.getConcentrationData(10000,0);
      values[x][1]=timeseries.getConcentrationData(10000,1);
      values[x][2]=timeseries.getConcentrationData(10000,2);
      values[x][3]=timeseries.getConcentrationData(10000,3);
    }
    double[] average={0.0,0.0,0.0,0.0};
    for(int x=0;x < values.length;x++)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
      average[3]+=values[x][3];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    average[3]=average[3]/values.length;
    assertTrue(Math.abs((average[0]-10.0)/10.0)<0.0001);
    double difference=2e-4-average[1];
    assertTrue(difference > 0.0);
    assertTrue(Math.abs((average[2]-difference)/difference)<0.001);
    assertTrue(Math.abs((average[3]-1.0)/1.0)<0.0001);
   }

   public void test_runHybridSimulationOnSimpleModel()
   {
    double[][] values=new double[this.NUM_REPEATS][4];
    for(int x=0;x < this.NUM_REPEATS; x++)
    {
      CTrajectoryTask task=runHybridSimulation(mDataModel);
      assertTrue(task!=null);
      assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
      CTimeSeries timeseries=task.getTimeSeries();
      assertTrue(timeseries!=null);
      assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
      assertTrue(timeseries.getRecordedSteps()==10001);
      assertTrue(timeseries.getNumVariables()==4);
      values[x][0]=timeseries.getConcentrationData(10000,0);
      values[x][1]=timeseries.getConcentrationData(10000,1);
      values[x][2]=timeseries.getConcentrationData(10000,2);
      values[x][3]=timeseries.getConcentrationData(10000,3);
    }
    double[] average={0.0,0.0,0.0,0.0};
    for(int x=0; x < values.length;x++)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
      average[3]+=values[x][3];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    average[3]=average[3]/values.length;
    assertTrue(Math.abs((average[0]-10.0)/10.0)<0.0001);
    double difference=2e-4-average[1];
    assertTrue(difference > 0.0);
    assertTrue(Math.abs((average[2]-difference)/difference)<0.001);
    assertTrue(Math.abs((average[3]-1.0)/1.0)<0.0001);
   }
   
   public void test_runDeterministicSimulationOnSimpleModel()
   {
    CTrajectoryTask task=runDeterministicSimulation(mDataModel);
    assertTrue(task!=null);
    assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
    CTimeSeries timeseries=task.getTimeSeries();
    assertTrue(timeseries!=null);
    assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
    assertTrue(timeseries.getRecordedSteps()==10001);
    assertTrue(timeseries.getNumVariables()==4);
    double value=timeseries.getConcentrationData(10000,0);
    assertTrue(Math.abs((value-10.0)/10.0)<0.001);
    double difference=2e-4-timeseries.getConcentrationData(10000,1);
    assertTrue(difference > 0.0);
    value=timeseries.getConcentrationData(10000,2);
    assertTrue(Math.abs((value-difference)/difference)<0.0001);
    value=timeseries.getConcentrationData(10000,3);
    assertTrue(Math.abs((value-1.0)/1.0)<0.001);
   }
   
   public void test_runStochasticSimulationOnExtendedModel()
   {
    Test_CreateSimpleModel.extendModel(this.model);
    double[][] values=new double[this.NUM_REPEATS][5];
    for(int x=0;x < this.NUM_REPEATS;x++)
    {
      CTrajectoryTask task=runStochasticSimulation(mDataModel);
      assertTrue(task!=null);
      assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
      CTimeSeries timeseries=task.getTimeSeries();
      assertTrue(timeseries!=null);
      assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
      assertTrue(timeseries.getRecordedSteps()==10001);
      assertTrue(timeseries.getNumVariables()==5);
      values[x][0]=timeseries.getConcentrationData(10000,0);
      values[x][1]=timeseries.getConcentrationData(10000,1);
      values[x][2]=timeseries.getConcentrationData(10000,2);
      values[x][3]=timeseries.getConcentrationData(10000,3);
      values[x][4]=timeseries.getConcentrationData(10000,4);
    }
    double[] average={0.0,0.0,0.0,0.0,0.0};
    for(int x=0;x < values.length;x++)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
      average[3]+=values[x][3];
      average[4]+=values[x][4];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    average[3]=average[3]/values.length;
    average[4]=average[4]/values.length;
    assertTrue(Math.abs((average[0]-10.0)/10.0)<0.0001);
    assertTrue(Math.abs((average[1] + average[2] + average[3] - 2e-4)/2e-4) < 0.0001);
    assertTrue(Math.abs((average[4]-1.0)/1.0) < 0.001);
   }

   public void test_runHybridSimulationOnExtendedModel()
   {
    Test_CreateSimpleModel.extendModel(this.model);
    double[][] values=new double[this.NUM_REPEATS][5];
    for(int x=0;x < this.NUM_REPEATS;x++)
    {
      CTrajectoryTask task=runHybridSimulation(mDataModel);
      assertTrue(task!=null);
      assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
      CTimeSeries timeseries=task.getTimeSeries();
      assertTrue(timeseries!=null);
      assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
      assertTrue(timeseries.getRecordedSteps()==10001);
      assertTrue(timeseries.getNumVariables()==5);
      values[x][0]=timeseries.getConcentrationData(10000,0);
      values[x][1]=timeseries.getConcentrationData(10000,1);
      values[x][2]=timeseries.getConcentrationData(10000,2);
      values[x][3]=timeseries.getConcentrationData(10000,3);
      values[x][4]=timeseries.getConcentrationData(10000,4);
    }
    double[] average={0.0,0.0,0.0,0.0,0.0};
    for(int x=0;x < values.length;x++)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
      average[3]+=values[x][3];
      average[4]+=values[x][4];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    average[3]=average[3]/values.length;
    average[4]=average[4]/values.length;
    assertTrue(Math.abs((average[0]-10.0)/10.0)<0.0001);
    assertTrue(Math.abs((average[1] + average[2] + average[3] - 2e-4)/2e-4) < 0.0001);
    assertTrue(Math.abs((average[4]-1.0)/1.0) < 0.0001);
   }

   public void test_runDeterministicSimulationOnExtendedModel()
   {
    Test_CreateSimpleModel.extendModel(this.model);
    CTrajectoryTask task=runDeterministicSimulation(mDataModel);
    assertTrue(task!=null);
    assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
    CTimeSeries timeseries=task.getTimeSeries();
    assertTrue(timeseries!=null);
    assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
    assertTrue(timeseries.getRecordedSteps()==10001);
    assertTrue(timeseries.getNumVariables()==5);
    double value=timeseries.getConcentrationData(10000,0);
    assertTrue(Math.abs((value-10.0)/10.0)<0.0001);
    value=timeseries.getConcentrationData(10000,1);
    double value2=timeseries.getConcentrationData(10000,2);
    double value3=timeseries.getConcentrationData(10000,3);
    assertTrue(Math.abs((value + value2 + value3 - 2e-4)/2e-4) < 0.0001);
    value3=timeseries.getConcentrationData(10000,4);
    assertTrue(Math.abs((value3-1.0)/1.0)<0.0001);
   }
   

  public static void main(String[] args) {
    junit.textui.TestRunner.run(Test_RunSimulations.class);
  }


}
