package org.eml.COPASI.unittests;

import java.lang.Math;
import java.util.HashMap;
import org.eml.COPASI.*;
import junit.framework.*;

class Test_RunSimulations extends TestCase
{
   protected CCopasiDataModel model;
   protected int NUM_REPEATS;

   public Test_RunSimulations(String name)
   {
    super(name);
   }

   public static CCopasiTask runSimulation(CCopasiTask.type methodType,HashMap<String,Object> problemParameters,HashMap<String,Object> methodParameters)
   {
    CCopasiTask task=null;
    for(int  x=0;x < CCopasiDataModel.GLOBAL.getTaskList().size();x++)
    {
        if(CCopasiDataModel.GLOBAL.getTask(x).getType()==CCopasiTask.timeCourse)
        {
          task=CCopasiDataModel.GLOBAL.getTask(x);
        }
    }
    if(task.equals(null))
    {
      return task;
    }
    task.setMethodType(methodType);
    CCopasiProblem problem=task.getProblem();
    if(problem.equals(null))
    {
      return null;
    }
    Set<String> keySet=problemParameters.keySet();
    keySet=methodParameters.keySet();
    for(Iterator<String> it=keySet.iterator();it.hasNext;)
    {
      key=(String)it.next();
      CCopasiParameter param=problem.getParameter(key);
      if(param.equals(null))
      {
        return null;
      }
      Object o=problemParameters.get(key);
      if(o.getClass()==Double)
      {
        param.setValue(((Double)o).doubleValue());
      }
      else if(o.getClass()==Boolean)
      {
        param.setValue(((Boolean)o).boolValue());
      }
      else
      {
        System.err.println("Error. Unknown parameter type.");
      }
    }
    CCopasiMethod method=task.getMethod();
    if(method.equals(null))
    {
      return null;
    }
    keySet=methodParameters.keySet();
    for(Iterator<String> it=keySet.iterator();it.hasNext;)
    {
      key=(String)it.next();
      CCopasiParameter param=method.getParameter(key);
      if(param.equals(null))
      {
        return null;
      }
      Object o=methodParameters.get(key);
      if(o.getClass()==Double)
      {
        param.setValue(((Double)o).doubleValue());
      }
      else if(o.getClass()==Boolean)
      {
        param.setValue(((Boolean)o).boolValue());
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

  public static CCopasiTask runDeterministicSimulation()
  {
   HashMap<String,Object> problemParameters;
   problemParameters.put("StepSize",Double(0.001));
   problemParameters.put("Duration",Double(10.0));
   problemParameters.put("TimeSeriesRequested",Boolean(true));
   problemParameters.put("OutputStartTime",Double(0.0));
   HashMap<String,Object> methodParameters;
   methodParameters.put("Absolute Tolerance",Double(1.0e-20));
   return runSimulation(CCopasiMethod.deterministic,problemParameters,methodParameters);
  }

  public static CCopasiTask runStochasticSimulation()
  {
   HashMap<String,Object> problemParameters;
   problemParameters.put("StepSize",Double(0.001));
   problemParameters.put("Duration",Double(10.0));
   problemParameters.put("TimeSeriesRequested",Boolean(true));
   problemParameters.put("OutputStartTime",Double(0.0));
   HashMap<String,Object> methodParameters;
   return runSimulation(CCopasiMethod.stochastic,problemParameters,methodParameters);
  }

  public static CCopasiTask runHybridSimulation()
  {
   HashMap<String,Object> problemParameters;
   problemParameters.put("StepSize",Double(0.001));
   problemParameters.put("Duration",Double(10.0));
   problemParameters.put("TimeSeriesRequested",Boolean(true));
   problemParameters.put("OutputStartTime",Double(0.0));
   HashMap<String,Object> methodParameters;
   return runSimulation(CCopasiMethod.hybrid,problemParameters,methodParameters);
  }

  public void setUp(self)
  {
    this.model=Test_CreateSimpleModel.createModel();
    this.NUM_REPEATS=20;
  }

  public void test_runStochasticSimulationOnSimpleModel()
  {
    values=[];
    for(int x=0;x < this.NUM_REPEATS;x++)
    {
      CCopasiTask task=runStochasticSimulation();
      Assert.assertTrue(!task.equals(null));
      Assert.assertTrue(task.getClass()==CTrajectoryTask);
      timeseries=task.getTimeSeries();
      Assert.assertTrue(!timeseries.equals(null));
      Assert.assertTrue(timeseries.getClass()==CTimeSeries);
      Assert.assertTrue(timeseries.getNumSteps()==10001);
      Assert.assertTrue(timeseries.getNumVariables()==3);
      values.append([timeseries.getConcentrationData(1386,0),timeseries.getConcentrationData(1386,1),timeseries.getConcentrationData(1386,2)]);
    }
    average=[0.0,0.0,0.0];
    for(int x=0;x < values.length;x++)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    Assert.assertTrue(Math.abs((average[0]-1.386)/1.386)<0.001)
    Assert.assertTrue(Math.abs((average[1]-0.0001)/0.0001)<0.01)
    Assert.assertTrue(Math.abs((average[2]-0.0001)/0.0001)<0.01)
   }

   public void test_runHybridSimulationOnSimpleModel()
   {
    values=[];
    for(int x=0;x < this.NUM_REPEATS; x++)
    {
      CCopasiTask task=runHybridSimulation();
      Assert.assertTrue(!task.equals(null));
      Assert.assertTrue(task.getClass()==CTrajectoryTask);
      timeseries=task.getTimeSeries();
      Assert.assertTrue(!timeseries.equals(null));
      Assert.assertTrue(timeseries.getClass()==CTimeSeries);
      Assert.assertTrue(timeseries.getNumSteps()==10001);
      Assert.assertTrue(timeseries.getNumVariables()==3)
      values.append([timeseries.getConcentrationData(1386,0),timeseries.getConcentrationData(1386,1),timeseries.getConcentrationData(1386,2)]);
    }
    average=[0.0,0.0,0.0];
    for(int x=0 x < values.length;x++)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    Assert.assertTrue(Math.abs((average[0]-1.386)/1.386)<0.001);
    Assert.assertTrue(Math.abs((average[1]-0.0001)/0.0001)<0.01);
    Assert.assertTrue(Math.abs((average[2]-0.0001)/0.0001)<0.01);
   }

   public void test_runDeterministicSimulationOnSimpleModel()
   {
    CCopasiTask task=runDeterministicSimulation();
    Assert.assertTrue(!task.equals(null));
    Assert.assertTrue(task.getClass()==CTrajectoryTask);
    timeseries=task.getTimeSeries();
    Assert.assertTrue(!timeseries.equals(null));
    Assert.assertTrue(timeseries.getClass()==CTimeSeries);
    Assert.assertTrue(timeseries.getNumSteps()==10001);
    Assert.assertTrue(timeseries.getNumVariables()==3);
    value=timeseries.getConcentrationData(1386,0);
    Assert.assertTrue(Math.abs((value-1.386)/1.386)<0.001);
    value=timeseries.getConcentrationData(1386,1);
    Assert.assertTrue(Math.abs((value-0.0001)/0.0001)<0.001)
    value=timeseries.getConcentrationData(1386,2);
    Assert.assertTrue(Math.abs((value-0.0001)/0.0001)<0.001);
   }

   public void test_runStochasticSimulationOnExtendedModel()
   {
    Test_CreateSimpleModel.extendModel(this.model);
    values=[];
    for(int x=0;x < this.NUM_REPEATS;x++)
    {
      CCopasiTask task=runStochasticSimulation();
      Assert.assertTrue(!task.equals(null));
      Assert.assertTrue(task.getClass()==CTrajectoryTask);
      timeseries=task.getTimeSeries();
      Assert.assertTrue(!timeseries.equals(null));
      Assert.assertTrue(timeseries.getClass()==CTimeSeries);
      Assert.assertTrue(timeseries.getNumSteps()==10001);
      Assert.assertTrue(timeseries.getNumVariables()==4);
      values.append([timeseries.getConcentrationData(3574,0),timeseries.getConcentrationData(3574,1),timeseries.getConcentrationData(3574,3)]);
    }
    average=[0.0,0.0,0.0];
    for(int x=0;x < values.length)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    Assert.assertTrue(Math.abs((average[0]-3.574)/3.574)<0.001);
    Assert.assertTrue(Math.abs((average[1]-average[2])/average[1])<0.01);
   }

   public void test_runHybridSimulationOnExtendedModel()
   {
    Test_CreateSimpleModel.extendModel(this.model);
    values=[];
    for(int x=0;x < this.NUM_REPEATS;x++)
    {
      CCopasiTask task=runHybridSimulation();
      Assert.assertTrue(!task.equals(null));
      Assert.assertTrue(task.getClass()==CTrajectoryTask);
      timeseries=task.getTimeSeries();
      Assert.assertTrue(!timeseries.equals(null));
      Assert.assertTrue(timeseries.getClass()==CTimeSeries);
      Assert.assertTrue(timeseries.getNumSteps()==10001);
      Assert.assertTrue(timeseries.getNumVariables()==4);
      values.append([timeseries.getConcentrationData(3574,0),timeseries.getConcentrationData(3574,1),timeseries.getConcentrationData(3574,3)]);
    }
    average=[0.0,0.0,0.0];
    for(int x=0;x < values.length;x++)
    {
      average[0]+=values[x][0];
      average[1]+=values[x][1];
      average[2]+=values[x][2];
    }
    average[0]=average[0]/values.length;
    average[1]=average[1]/values.length;
    average[2]=average[2]/values.length;
    Assert.assertTrue(Math.abs((average[0]-3.574)/3.574)<0.001);
    Assert.assertTrue(Math.abs((average[1]-average[2])/average[1])<0.01);
   }

   public void test_runDeterministicSimulationOnExtendedModel()
   {
    Test_CreateSimpleModel.extendModel(this.model);
    CCopasiTask task=runDeterministicSimulation();
    Assert.assertTrue(!task.equals(null));
    Assert.assertTrue(task.getClass()==CTrajectoryTask);
    timeseries=task.getTimeSeries();
    Assert.assertTrue(!timeseries.equals(null));
    Assert.assertTrue(timeseries.getClass()==CTimeSeries);
    Assert.assertTrue(timeseries.getNumSteps()==10001);
    Assert.assertTrue(timeseries.getNumVariables()==4);
    value=timeseries.getConcentrationData(3574,0);
    Assert.assertTrue(Math.abs((value-3.574)/3.574)<0.001);
    value=timeseries.getConcentrationData(3574,1);
    value2=timeseries.getConcentrationData(3574,3);
    Assert.assertTrue(Math.abs((value-value2)/value)<0.001);
   }

/*
def suite():
  tests=[
          'test_runDeterministicSimulationOnSimpleModel'
         ,'test_runStochasticSimulationOnSimpleModel'
         ,'test_runHybridSimulationOnSimpleModel'
         ,'test_runDeterministicSimulationOnExtendedModel'
         ,'test_runStochasticSimulationOnExtendedModel'
         ,'test_runHybridSimulationOnExtendedModel'
        ]
  return unittest.TestSuite(map(Test_RunSimulations,tests))
*/

  public static void main(String[] args) {
    junit.swingui.TestRunner.run(Test_RunSimulations.class);
  }


}
