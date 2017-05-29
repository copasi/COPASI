# -*- coding: utf-8 -*-
# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# 
# This is an example on how to run an optimization task.
# And how to access the result of an optimization.
# 

from COPASI import *
import sys

def main():
   assert CRootContainer.getRoot() != None
   # create a new datamodel
   dataModel = CRootContainer.addDatamodel()
   assert CRootContainer.getDatamodelList().size() == 1
   # get the model from the datamodel
   model = dataModel.getModel()
   assert model != None
   model.setVolumeUnit(CUnit.fl)
   model.setTimeUnit(CUnit.s)
   model.setQuantityUnit(CUnit.fMol)
   fixedModelValue=model.createModelValue("F")
   assert fixedModelValue != None
   fixedModelValue.setStatus(CModelEntity.Status_FIXED)
   fixedModelValue.setInitialValue(3.0);   
   variableModelValue=model.createModelValue("V")
   assert variableModelValue != None
   variableModelValue.setStatus(CModelEntity.Status_ASSIGNMENT)
   # we create a very simple assignment that is easy on the optimization
   # a parabole with the minimum at x=6 should do just fine
   s=fixedModelValue.getObject(CCommonName("Reference=Value")).getCN().getString()
   s="(<"+s+"> - 6.0)^2"
   variableModelValue.setExpression(s)
   # now we compile the model and tell COPASI which values have changed so
   # that COPASI can update the values that depend on those
   model.compileIfNecessary()
   changedObjects=ObjectStdVector()
   changedObjects.push_back(fixedModelValue.getObject(CCommonName("Reference=InitialValue")))
   changedObjects.push_back(variableModelValue.getObject(CCommonName("Reference=InitialValue")))
   model.updateInitialValues(changedObjects)
   
   # now we set up the optimization

   # we want to do an optimization for the time course
   # so we have to set up the time course task first
   timeCourseTask = dataModel.getTask("Time-Course")
   assert timeCourseTask != None
   # since for this example it really doesn't matter how long we run the time course 
   # we run for 1 second and calculate 10 steps
   # run a deterministic time course
   timeCourseTask.setMethodType(CTaskEnum.Method_deterministic)

   # pass a pointer of the model to the problem
   timeCourseTask.getProblem().setModel(dataModel.getModel())

   # get the problem for the task to set some parameters
   problem = timeCourseTask.getProblem()
   assert problem != None

   # simulate 10 steps
   problem.setStepNumber(10)
   # start at time 0
   dataModel.getModel().setInitialTime(0.0)
   # simulate a duration of 1 time units
   problem.setDuration(1)
   # tell the problem to actually generate time series data
   problem.setTimeSeriesRequested(True)
  
   # get the optimization task
   optTask=dataModel.getTask("Optimization")
   assert optTask != None
   # we want to use Levenberg-Marquardt as the optimization method
   optTask.setMethodType(CTaskEnum.Method_LevenbergMarquardt)
   
   # next we need to set subtask type on the problem
   optProblem=optTask.getProblem()
   assert optProblem != None
   optProblem.setSubtaskType(CTaskEnum.Task_timeCourse)
   
   # we create the objective function
   # we want to minimize the value of the variable model value at the end of
   # the simulation
   # the objective function is normally minimized
   objectiveFunction=variableModelValue.getObject(CCommonName("Reference=Value")).getCN().getString()
   # we need to put the angled brackets around the common name of the object
   objectiveFunction="<"+objectiveFunction+">"
   # now we set the objective function in the problem
   optProblem.setObjectiveFunction(objectiveFunction)

   # now we create the optimization items
   # i.e. the model elements that have to be changed during the optimization
   # in order to get to the optimal solution
   optItem=optProblem.addOptItem(CCommonName(fixedModelValue.getObject(CCommonName("Reference=InitialValue")).getCN()))
   # we want to change the fixed model value from -100 to +100 with a start
   # value of 50
   optItem.setStartValue(50.0)
   optItem.setLowerBound(CCommonName("-100"))
   optItem.setUpperBound(CCommonName("100"))
   
   # now we set some parameters on the method
   # these parameters are specific to the method type we set above
   # (in this case Levenberg-Marquardt)
   optMethod=optTask.getMethod()
   assert optMethod != None
   
   # now we set some method parameters for the optimization method
   # iteration limit
   parameter=optMethod.getParameter("Iteration Limit")
   assert parameter != None
   parameter.setIntValue(2000)
   # tolerance
   parameter=optMethod.getParameter("Tolerance")
   assert parameter != None
   parameter.setDblValue(1.0e-5)

   # create a report with the correct filename and all the species against
   # time.
   reports = dataModel.getReportDefinitionList()
   # create a report definition object
   report = reports.createReportDefinition("Report", "Output for optimization")
   # set the task type for the report definition to timecourse
   report.setTaskType(CTaskEnum.Task_optimization)
   # we don't want a table
   report.setIsTable(False)
   # the entries in the output should be seperated by a ", "
   report.setSeparator(CCopasiReportSeparator(", "))

   # we need a handle to the header and the body
   # the header will display the ids of the metabolites and "time" for
   # the first column
   # the body will contain the actual timecourse data
   header = report.getHeaderAddr()
   body = report.getBodyAddr()
   
   # in the report header we write two strings and a separator
   header.push_back(CRegisteredCommonName(CDataString("best value of objective function").getCN().getString()))
   header.push_back(CRegisteredCommonName(report.getSeparator().getCN().getString()))
   header.push_back(CRegisteredCommonName(CDataString("initial value of F").getCN().getString()))
   # in the report body we write the best value of the objective function and
   # the initial value of the fixed parameter separated by a komma
   body.push_back(CRegisteredCommonName(optProblem.getObject(CCommonName("Reference=Best Value")).getCN().getString()))
   body.push_back(CRegisteredCommonName(report.getSeparator().getCN().getString()))
   body.push_back(CRegisteredCommonName(fixedModelValue.getObject(CCommonName("Reference=InitialValue")).getCN().getString()))

   
   # set the report for the task
   optTask.getReport().setReportDefinition(report)
   # set the output filename
   optTask.getReport().setTarget("example5.txt")
   # don't append output if the file exists, but overwrite the file
   optTask.getReport().setAppend(False)

   result=False
   try:
     result=optTask.process(True)
   except:
       sys.stderr.write("Running the optimization failed.\n" )
       return 1
   if(not result):
       sys.stderr.write("Running the optimization failed.\n" )
       return 1
   # now we check if the optimization actually got the correct result
   # the best value it should have is 0 and the best parameter value for
   # that result should be 6 for the initial value of the fixed parameter
   bestValue=optProblem.getSolutionValue()
   assert abs(bestValue) < 1e-3
   # we should only have one solution variable since we only have one
   # optimization item
   assert optProblem.getSolutionVariables().size() == 1
   solution=optProblem.getSolutionVariables().get(0)
   assert abs((solution-6.0)/6.0) < 1e-3


if(__name__ == '__main__'):
   main() 

