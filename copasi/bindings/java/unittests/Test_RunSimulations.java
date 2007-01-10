// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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


   protected CModel model;
   protected int NUM_REPEATS;

   public Test_RunSimulations(String name)
   {
    super(name);
   }

   public static CTrajectoryTask runSimulation(int methodType,HashMap<String,Object> problemParameters,HashMap<String,Object> methodParameters)
   {
    CTrajectoryTask task=null;
    for(int  x=0;x < CCopasiDataModel.getGlobal().getTaskList().size();x++)
    {
        if(CCopasiDataModel.getGlobal().getTask(x).getType()==CCopasiTask.timeCourse)
        {
          task=(CTrajectoryTask)CCopasiDataModel.getGlobal().getTask(x);
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
      else if(o instanceof Boolean)
      {
        param.setBoolValue(((Boolean)o).booleanValue());
      }
      else
      {
        System.err.println("Error. Unknown parameter type.");
      }
    }
    if(!task.process(true))
    {
      return null;
    }
    return task;
   }

  public static CTrajectoryTask runDeterministicSimulation()
  {
   HashMap<String,Object> problemParameters=new HashMap<String,Object>();
   problemParameters.put("StepSize",new Double(0.001));
   problemParameters.put("Duration",new Double(10.0));
   problemParameters.put("TimeSeriesRequested",new Boolean(true));
   problemParameters.put("OutputStartTime",new Double(0.0));
   HashMap<String,Object> methodParameters=new HashMap<String,Object>();
   methodParameters.put("Absolute Tolerance",new Double(1.0e-20));
   return runSimulation(CCopasiMethod.deterministic,problemParameters,methodParameters);
  }

  public static CTrajectoryTask runStochasticSimulation()
  {
   HashMap<String,Object> problemParameters=new HashMap<String,Object>();
   problemParameters.put("StepSize",new Double(0.001));
   problemParameters.put("Duration",new Double(10.0));
   problemParameters.put("TimeSeriesRequested",new Boolean(true));
   problemParameters.put("OutputStartTime",new Double(0.0));
   HashMap<String,Object> methodParameters=new HashMap<String,Object>();
   return runSimulation(CCopasiMethod.stochastic,problemParameters,methodParameters);
  }

  public static CTrajectoryTask runHybridSimulation()
  {
   HashMap<String,Object> problemParameters=new HashMap<String,Object>();
   problemParameters.put("StepSize",new Double(0.001));
   problemParameters.put("Duration",new Double(10.0));
   problemParameters.put("TimeSeriesRequested",new Boolean(true));
   problemParameters.put("OutputStartTime",new Double(0.0));
   HashMap<String,Object> methodParameters=new HashMap<String,Object>();
   return runSimulation(CCopasiMethod.hybrid,problemParameters,methodParameters);
  }

  public void setUp()
  {
    this.model=Test_CreateSimpleModel.createModel();
    this.NUM_REPEATS=20;
  }

  public void test_runStochasticSimulationOnSimpleModel()
  {
    double[][] values=new double[this.NUM_REPEATS][3];
    for(int x=0;x < this.NUM_REPEATS;x++)
    {
      CTrajectoryTask task=runStochasticSimulation();
      assertTrue(task!=null);
      assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
      CTimeSeries timeseries=task.getTimeSeries();
      assertTrue(timeseries!=null);
      assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
      assertTrue(timeseries.getNumSteps()==10001);
      assertTrue(timeseries.getNumVariables()==3);
      values[x][0]=timeseries.getConcentrationData(1386,0);
      values[x][1]=timeseries.getConcentrationData(1386,1);
      values[x][2]=timeseries.getConcentrationData(1386,2);
    }
    double[] average={0.0,0.0,0.0};
    for(int x=0;x < values.length;x++)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    assertTrue(Math.abs((average[0]-1.386)/1.386)<0.001);
    assertTrue(Math.abs((average[1]-0.0001)/0.0001)<0.01);
    assertTrue(Math.abs((average[2]-0.0001)/0.0001)<0.01);
   }

   public void test_runHybridSimulationOnSimpleModel()
   {
    double[][] values=new double[this.NUM_REPEATS][3];
    for(int x=0;x < this.NUM_REPEATS; x++)
    {
      CTrajectoryTask task=runHybridSimulation();
      assertTrue(task!=null);
      assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
      CTimeSeries timeseries=task.getTimeSeries();
      assertTrue(timeseries!=null);
      assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
      assertTrue(timeseries.getNumSteps()==10001);
      assertTrue(timeseries.getNumVariables()==3);
      values[x][0]=timeseries.getConcentrationData(1386,0);
      values[x][1]=timeseries.getConcentrationData(1386,1);
      values[x][2]=timeseries.getConcentrationData(1386,2);
    }
    double[] average={0.0,0.0,0.0};
    for(int x=0; x < values.length;x++)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    assertTrue(Math.abs((average[0]-1.386)/1.386)<0.001);
    assertTrue(Math.abs((average[1]-0.0001)/0.0001)<0.01);
    assertTrue(Math.abs((average[2]-0.0001)/0.0001)<0.01);
   }

   public void test_runDeterministicSimulationOnSimpleModel()
   {
    CTrajectoryTask task=runDeterministicSimulation();
    assertTrue(task!=null);
    assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
    CTimeSeries timeseries=task.getTimeSeries();
    assertTrue(timeseries!=null);
    assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
    assertTrue(timeseries.getNumSteps()==10001);
    assertTrue(timeseries.getNumVariables()==3);
    double value=timeseries.getConcentrationData(1386,0);
    assertTrue(Math.abs((value-1.386)/1.386)<0.001);
    value=timeseries.getConcentrationData(1386,1);
    assertTrue(Math.abs((value-0.0001)/0.0001)<0.001);
    value=timeseries.getConcentrationData(1386,2);
    assertTrue(Math.abs((value-0.0001)/0.0001)<0.001);
   }

   public void test_runStochasticSimulationOnExtendedModel()
   {
    Test_CreateSimpleModel.extendModel(this.model);
    double[][] values=new double[this.NUM_REPEATS][3];
    for(int x=0;x < this.NUM_REPEATS;x++)
    {
      CTrajectoryTask task=runStochasticSimulation();
      assertTrue(task!=null);
      assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
      CTimeSeries timeseries=task.getTimeSeries();
      assertTrue(timeseries!=null);
      assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
      assertTrue(timeseries.getNumSteps()==10001);
      assertTrue(timeseries.getNumVariables()==4);
      values[x][0]=timeseries.getConcentrationData(3574,0);
      values[x][1]=timeseries.getConcentrationData(3574,1);
      values[x][2]=timeseries.getConcentrationData(3574,3);
    }
    double[] average={0.0,0.0,0.0};
    for(int x=0;x < values.length;x++)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    assertTrue(Math.abs((average[0]-3.574)/3.574)<0.001);
    assertTrue(Math.abs((average[1]-average[2])/average[1])<0.01);
   }

   public void test_runHybridSimulationOnExtendedModel()
   {
    Test_CreateSimpleModel.extendModel(this.model);
    double[][] values=new double[this.NUM_REPEATS][3];
    for(int x=0;x < this.NUM_REPEATS;x++)
    {
      CTrajectoryTask task=runHybridSimulation();
      assertTrue(task!=null);
      assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
      CTimeSeries timeseries=task.getTimeSeries();
      assertTrue(timeseries!=null);
      assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
      assertTrue(timeseries.getNumSteps()==10001);
      assertTrue(timeseries.getNumVariables()==4);
      values[x][0]=timeseries.getConcentrationData(3574,0);
      values[x][1]=timeseries.getConcentrationData(3574,1);
      values[x][2]=timeseries.getConcentrationData(3574,3);
    }
    double[] average={0.0,0.0,0.0};
    for(int x=0;x < values.length;x++)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    assertTrue(Math.abs((average[0]-3.574)/3.574)<0.001);
    assertTrue(Math.abs((average[1]-average[2])/average[1])<0.01);
   }

   public void test_runDeterministicSimulationOnExtendedModel()
   {
    Test_CreateSimpleModel.extendModel(this.model);
    CTrajectoryTask task=runDeterministicSimulation();
    assertTrue(task!=null);
    assertTrue(task.getClass().getName().equals("org.COPASI.CTrajectoryTask"));
    CTimeSeries timeseries=task.getTimeSeries();
    assertTrue(timeseries!=null);
    assertTrue(timeseries.getClass().getName().equals("org.COPASI.CTimeSeries"));
    assertTrue(timeseries.getNumSteps()==10001);
    assertTrue(timeseries.getNumVariables()==4);
    double value=timeseries.getConcentrationData(3574,0);
    assertTrue(Math.abs((value-3.574)/3.574)<0.001);
    value=timeseries.getConcentrationData(3574,1);
    double value2=timeseries.getConcentrationData(3574,3);
    assertTrue(Math.abs((value-value2)/value)<0.001);
   }


  public static void main(String[] args) {
    junit.textui.TestRunner.run(Test_RunSimulations.class);
  }


}
