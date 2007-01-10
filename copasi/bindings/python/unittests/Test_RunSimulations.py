# Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

import COPASI
import unittest
from types import *
import Test_CreateSimpleModel
import math

def runSimulation(methodType,problemParameters,methodParameters):
    task=None
    for x in range(0,COPASI.CCopasiDataModel.GLOBAL.getTaskList().size()):
        if(COPASI.CCopasiDataModel.GLOBAL.getTask(x).getType()==COPASI.CCopasiTask.timeCourse):
            task=COPASI.CCopasiDataModel.GLOBAL.getTask(x)
    if(task==None):
        return False
    task.setMethodType(methodType)
    problem=task.getProblem()
    if(problem == None):
        return None
    for key in problemParameters.keys():
        param=problem.getParameter(key)
        if(param == None):
            return None
        param.setValue(problemParameters[key])
    method=task.getMethod()
    if(method == None):
        return None
    for key in methodParameters.keys():
        param=method.getParameter(key)
        if(param == None):
            return None
        param.setValue(methodParameters[key])
    if(not task.process(True)):
        return None
    return task

def runDeterministicSimulation():
   problemParameters={"StepSize":0.001,"Duration":10.0,"TimeSeriesRequested":True,"OutputStartTime":0.0}
   methodParameters={"Absolute Tolerance":1.0e-20}
   return runSimulation(COPASI.CCopasiMethod.deterministic,problemParameters,methodParameters)

def runStochasticSimulation():
   problemParameters={"StepSize":0.001,"Duration":10.0,"TimeSeriesRequested":True,"OutputStartTime":0.0}
   methodParameters={}
   return runSimulation(COPASI.CCopasiMethod.stochastic,problemParameters,methodParameters)

def runHybridSimulation():
   problemParameters={"StepSize":0.001,"Duration":10.0,"TimeSeriesRequested":True,"OutputStartTime":0.0}
   methodParameters={}
   return runSimulation(COPASI.CCopasiMethod.hybrid,problemParameters,methodParameters)

class Test_RunSimulations(unittest.TestCase):
   def setUp(self):
    self.model=Test_CreateSimpleModel.createModel()
    self.NUM_REPEATS=20

   def test_runStochasticSimulationOnSimpleModel(self):
    values=[]
    for x in range(0,self.NUM_REPEATS):
      task=runStochasticSimulation()
      self.assert_(task!=None)
      self.assert_(task.__class__==COPASI.CTrajectoryTask)
      timeseries=task.getTimeSeries()
      self.assert_(timeseries!=None)
      self.assert_(timeseries.__class__==COPASI.CTimeSeries)
      self.assert_(timeseries.getNumSteps()==10001)
      self.assert_(timeseries.getNumVariables()==3)
      values.append([timeseries.getConcentrationData(1386,0),timeseries.getConcentrationData(1386,1),timeseries.getConcentrationData(1386,2)])
    average=[0.0,0.0,0.0]
    for x in range(0,len(values)):
      average[0]+=values[x][0]
      average[1]+=values[x][1]
      average[2]+=values[x][2]
    average[0]=average[0]/len(values)
    average[1]=average[1]/len(values)
    average[2]=average[2]/len(values)
    self.assert_(math.fabs((average[0]-1.386)/1.386)<0.001)
    self.assert_(math.fabs((average[1]-0.0001)/0.0001)<0.01)
    self.assert_(math.fabs((average[2]-0.0001)/0.0001)<0.01)

   def test_runHybridSimulationOnSimpleModel(self):
    values=[]
    for x in range(0,self.NUM_REPEATS):
      task=runHybridSimulation()
      self.assert_(task!=None)
      self.assert_(task.__class__==COPASI.CTrajectoryTask)
      timeseries=task.getTimeSeries()
      self.assert_(timeseries!=None)
      self.assert_(timeseries.__class__==COPASI.CTimeSeries)
      self.assert_(timeseries.getNumSteps()==10001)
      self.assert_(timeseries.getNumVariables()==3)
      values.append([timeseries.getConcentrationData(1386,0),timeseries.getConcentrationData(1386,1),timeseries.getConcentrationData(1386,2)])
    average=[0.0,0.0,0.0]
    for x in range(0,len(values)):
      average[0]+=values[x][0]
      average[1]+=values[x][1]
      average[2]+=values[x][2]
    average[0]=average[0]/len(values)
    average[1]=average[1]/len(values)
    average[2]=average[2]/len(values)
    self.assert_(math.fabs((average[0]-1.386)/1.386)<0.001)
    self.assert_(math.fabs((average[1]-0.0001)/0.0001)<0.01)
    self.assert_(math.fabs((average[2]-0.0001)/0.0001)<0.01)


   def test_runDeterministicSimulationOnSimpleModel(self):
    task=runDeterministicSimulation()
    self.assert_(task!=None)
    self.assert_(task.__class__==COPASI.CTrajectoryTask)
    timeseries=task.getTimeSeries()
    self.assert_(timeseries!=None)
    self.assert_(timeseries.__class__==COPASI.CTimeSeries)
    self.assert_(timeseries.getNumSteps()==10001)
    self.assert_(timeseries.getNumVariables()==3)
    value=timeseries.getConcentrationData(1386,0)
    self.assert_(math.fabs((value-1.386)/1.386)<0.001)
    value=timeseries.getConcentrationData(1386,1)
    self.assert_(math.fabs((value-0.0001)/0.0001)<0.001)
    value=timeseries.getConcentrationData(1386,2)
    self.assert_(math.fabs((value-0.0001)/0.0001)<0.001)


   def test_runStochasticSimulationOnExtendedModel(self):
    Test_CreateSimpleModel.extendModel(self.model)
    values=[]
    for x in range(0,self.NUM_REPEATS):
      task=runStochasticSimulation()
      self.assert_(task!=None)
      self.assert_(task.__class__==COPASI.CTrajectoryTask)
      timeseries=task.getTimeSeries()
      self.assert_(timeseries!=None)
      self.assert_(timeseries.__class__==COPASI.CTimeSeries)
      self.assert_(timeseries.getNumSteps()==10001)
      self.assert_(timeseries.getNumVariables()==4)
      values.append([timeseries.getConcentrationData(3574,0),timeseries.getConcentrationData(3574,1),timeseries.getConcentrationData(3574,3)])
    average=[0.0,0.0,0.0]
    for x in range(0,len(values)):
      average[0]+=values[x][0]
      average[1]+=values[x][1]
      average[2]+=values[x][2]
    average[0]=average[0]/len(values)
    average[1]=average[1]/len(values)
    average[2]=average[2]/len(values)
    self.assert_(math.fabs((average[0]-3.574)/3.574)<0.001)
    self.assert_(math.fabs((average[1]-average[2])/average[1])<0.01)


   def test_runHybridSimulationOnExtendedModel(self):
    Test_CreateSimpleModel.extendModel(self.model)
    values=[]
    for x in range(0,self.NUM_REPEATS):
      task=runHybridSimulation()
      self.assert_(task!=None)
      self.assert_(task.__class__==COPASI.CTrajectoryTask)
      timeseries=task.getTimeSeries()
      self.assert_(timeseries!=None)
      self.assert_(timeseries.__class__==COPASI.CTimeSeries)
      self.assert_(timeseries.getNumSteps()==10001)
      self.assert_(timeseries.getNumVariables()==4)
      values.append([timeseries.getConcentrationData(3574,0),timeseries.getConcentrationData(3574,1),timeseries.getConcentrationData(3574,3)])
    average=[0.0,0.0,0.0]
    for x in range(0,len(values)):
      average[0]+=values[x][0]
      average[1]+=values[x][1]
      average[2]+=values[x][2]
    average[0]=average[0]/len(values)
    average[1]=average[1]/len(values)
    average[2]=average[2]/len(values)
    self.assert_(math.fabs((average[0]-3.574)/3.574)<0.001)
    self.assert_(math.fabs((average[1]-average[2])/average[1])<0.01)


   def test_runDeterministicSimulationOnExtendedModel(self):
    Test_CreateSimpleModel.extendModel(self.model)
    task=runDeterministicSimulation()
    self.assert_(task!=None)
    self.assert_(task.__class__==COPASI.CTrajectoryTask)
    timeseries=task.getTimeSeries()
    self.assert_(timeseries!=None)
    self.assert_(timeseries.__class__==COPASI.CTimeSeries)
    self.assert_(timeseries.getNumSteps()==10001)
    self.assert_(timeseries.getNumVariables()==4)
    value=timeseries.getConcentrationData(3574,0)
    self.assert_(math.fabs((value-3.574)/3.574)<0.001)
    value=timeseries.getConcentrationData(3574,1)
    value2=timeseries.getConcentrationData(3574,3)
    self.assert_(math.fabs((value-value2)/value)<0.001)


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

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


