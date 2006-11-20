import COPASI
import unittest
from types import *
import Test_CreateSimpleModel

def runSimulation(taskType,problemParameters,methodParameters):
    task=None
    for x in range(0,COPASI.CCopasiDataModel.GLOBAL.getTaskList().size()):
        if(COPASI.CCopasiDataModel.GLOBAL.getTask(x).getType()==COPASI.CCopasiTask.timeCourse):
            task=COPASI.CCopasiDataModel.GLOBAL.getTask(x)
    if(task==None):
        return False
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
    task.process(True)
    return task

def runDeterministicSimulation():
   problemParameters={"StepNumber":10000,"Duration":100.0,"TimeSeriesRequested":True,"OutputStartTime":0.0}
   methodParameters={"Absolute Tolerance":1.0e-20}
   return runSimulation(COPASI.CCopasiMethod.deterministic,problemParameters,methodParameters)

def runStochasticSimulation():
   problemParameters={"StepNumber":10000,"Duration":100.0,"TimeSeriesRequested":True,"OutputStartTime":0.0}
   methodParameters={}
   return runSimulation(COPASI.CCopasiMethod.stochastic,problemParameters,methodParameters)

def runHybridSimulation():
   problemParameters={"StepNumber":10000,"Duration":100.0,"TimeSeriesRequested":True,"OutputStartTime":0.0}
   methodParameters={}
   return runSimulation(COPASI.CCopasiMethod.hybrid,problemParameters,methodParameters)

class Test_RunSimulations(unittest.TestCase):
   def setUp(self):
    self.model=Test_CreateSimpleModel.createModel()

   def test_runStochasticSimulationOnSimpleModel(self):
    task=runStochasticSimulation()
    self.assert_(task!=None)
    self.assert_(task.__class__==COPASI.CTrajectoryTask)
    timeseries=task.getTimeSeries()
    self.assert_(timeseries!=None)
    self.assert_(timeseries.__class__==COPASI.CTimeSeries)
    self.assert_(timeseries.getNumSteps()==10001)
    self.assert_(timeseries.getNumVariables()==3)

   def test_runHybridSimulationOnSimpleModel(self):
    task=runHybridSimulation()
    self.assert_(task!=None)
    self.assert_(task.__class__==COPASI.CTrajectoryTask)
    timeseries=task.getTimeSeries()
    self.assert_(timeseries!=None)
    self.assert_(timeseries.__class__==COPASI.CTimeSeries)
    self.assert_(timeseries.getNumSteps()==10001)
    self.assert_(timeseries.getNumVariables()==3)

   def test_runDeterministicSimulationOnSimpleModel(self):
    task=runDeterministicSimulation()
    self.assert_(task!=None)
    self.assert_(task.__class__==COPASI.CTrajectoryTask)
    timeseries=task.getTimeSeries()
    self.assert_(timeseries!=None)
    self.assert_(timeseries.__class__==COPASI.CTimeSeries)
    self.assert_(timeseries.getNumSteps()==10001)
    self.assert_(timeseries.getNumVariables()==3)

   def test_runStochasticSimulationOnExtendedModel(self):
    Test_CreateSimpleModel.extendModel(self.model)
    task=runStochasticSimulation()
    self.assert_(task!=None)
    self.assert_(task.__class__==COPASI.CTrajectoryTask)
    timeseries=task.getTimeSeries()
    self.assert_(timeseries!=None)
    self.assert_(timeseries.__class__==COPASI.CTimeSeries)
    self.assert_(timeseries.getNumSteps()==10001)
    self.assert_(timeseries.getNumVariables()==4)

   def test_runHybridSimulationOnExtendedModel(self):
    Test_CreateSimpleModel.extendModel(self.model)
    task=runHybridSimulation()
    self.assert_(task!=None)
    self.assert_(task.__class__==COPASI.CTrajectoryTask)
    timeseries=task.getTimeSeries()
    self.assert_(timeseries!=None)
    self.assert_(timeseries.__class__==COPASI.CTimeSeries)
    self.assert_(timeseries.getNumSteps()==10001)
    self.assert_(timeseries.getNumVariables()==4)

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


def suite():
  tests=[
          'test_runDeterministicSimulationOnSimpleModel'
         ,'test_runDeterministicSimulationOnExtendedModel'
         ,'test_runStochasticSimulationOnSimpleModel'
         ,'test_runStochasticSimulationOnExtendedModel'
         ,'test_runHybridSimulationOnSimpleModel'
         ,'test_runHybridSimulationOnExtendedModel'
        ]
  return unittest.TestSuite(map(Test_RunSimulations,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


