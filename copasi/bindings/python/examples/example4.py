# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/examples/example4.py,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2009/03/05 11:12:46 $ 
# End CVS Header 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# 
# This is an example on how to import an sbml file
# create a report for a time course simulation 
# and run a scan for a stochastic time course simulation
# 

from COPASI import *
import sys

def main(args):
   assert CCopasiRootContainer.getRoot() != None
   # create a datamodel
   dataModel = CCopasiRootContainer.addDatamodel()
   assert CCopasiRootContainer.getDatamodelList().size() == 1
   # the only argument to the main routine should be the name of an SBML file
   if len(args) == 1:
       filename = args[0]
       try:
           # load the model
           dataModel.importSBML(filename)
       except:
           print >> sys.stderr,  "Error while importing the model from file named \"" + filename + "\"."
           return 1
       model = dataModel.getModel()
       assert model != None
       # create a report with the correct filename and all the species against
       # time.
       reports = dataModel.getReportDefinitionList()
       # create a report definition object
       report = reports.createReportDefinition("Report", "Output for timecourse")
       # set the task type for the report definition to timecourse
       report.setTaskType(CCopasiTask.timeCourse)
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
       body.push_back(CRegisteredObjectName(CCopasiObjectName(dataModel.getModel().getCN().getString() + ",Reference=Time").getString()))
       body.push_back(CRegisteredObjectName(report.getSeparator().getCN().getString()))
       header.push_back(CRegisteredObjectName(CCopasiStaticString("time").getCN().getString()))
       header.push_back(CRegisteredObjectName(report.getSeparator().getCN().getString()))

       iMax = model.getMetabolites().size()
       for i in range(0,iMax):
           metab = model.getMetabolite(i)
           assert metab != None
           # we don't want output for FIXED metabolites right now
           if metab.getStatus() != CModelEntity.FIXED:
               # we want the concentration oin the output
               # alternatively, we could use "Reference=Amount" to get the
               # particle number
               body.push_back(CRegisteredObjectName(metab.getObject(CCopasiObjectName("Reference=Concentration")).getCN().getString()))
               # add the corresponding id to the header
               header.push_back(CRegisteredObjectName(CCopasiStaticString(metab.getSBMLId()).getCN().getString()))
               
               if i!=iMax-1:
                 # after each entry, we need a seperator
                 body.push_back(CRegisteredObjectName(report.getSeparator().getCN().getString()))

                 # and a seperator
                 header.push_back(CRegisteredObjectName(report.getSeparator().getCN().getString()))
       # get the task list
       taskList = dataModel.getTaskList()

       # get the trajectory task object
       trajectoryTask = taskList.getObject(CCopasiObjectName("Time-Course"))
       # if there isn't one
       if trajectoryTask == None:
           # create a one
           trajectoryTask = CTrajectoryTask()
           # remove any existing trajectory task just to be sure since in
           # theory only the cast might have failed above
           taskList.removeByName("Time-Course")

           # add the time course task to the task list
           taskList.add(trajectoryTask, True)

       # run a stochastic time course
       trajectoryTask.setMethodType(CCopasiMethod.stochastic)

       # pass a pointer of the model to the problem
       trajectoryTask.getProblem().setModel(dataModel.getModel())

       # we don't want the trajectory task to run by itself, but we want to
       # run it from a scan, so we deactivate the standalone trajectory task
       trajectoryTask.setScheduled(False)

       # get the problem for the task to set some parameters
       problem = trajectoryTask.getProblem()

       # simulate 100 steps
       problem.setStepNumber(100)
       # start at time 0
       dataModel.getModel().setInitialTime(0.0)
       # simulate a duration of 10 time units
       problem.setDuration(10)
       # tell the problem to actually generate time series data
       problem.setTimeSeriesRequested(True)

       # now we set up the scan
       scanTask = taskList.getObject(CCopasiObjectName("Scan"))
       if scanTask == None:
           # create a scan task
           scanTask = CScanTask()
           # just to be on the save side, delete any existing scan task
           taskList.removeByName("Scan")
           # add the scan task
           taskList.add(scanTask, True)

       # get the problem
       scanProblem = scanTask.getProblem()
       assert scanProblem != None

       # set the model for the problem
       scanProblem.setModel(dataModel.getModel())

       # activate the task so that is is run
       # if the model is saved and passed to CopasiSE
       scanTask.setScheduled(True)

       # set the report for the task
       scanTask.getReport().setReportDefinition(report)

       # set the output file for the report
       scanTask.getReport().setTarget("example4.txt")
       # don't append to an existing file, but overwrite
       scanTask.getReport().setAppend(False)

       # tell the scan that we want to make a scan over a trajectory task
       scanProblem.setSubtask(CCopasiTask.timeCourse)

       # we just want to run the timecourse task a number of times, so we
       # create a repeat item with 100 repeats
       scanProblem.createScanItem(CScanProblem.SCAN_REPEAT, 100)

       # we want the output from the trajectory task
       scanProblem.setOutputInSubtask(True)

       # we don't want to set the initial conditions of the model to the end
       # state of the last run
       scanProblem.setAdjustInitialConditions(False)

       try:
           # now we run the actual trajectory
           scanTask.process(True)
       except:
           print >> sys.stderr,  "Error. Running the scan failed."
           # check if there are additional error messages
           if (CCopasiMessage.size() > 0):
               # print the messages in chronological order
               print >> sys.stderr,  CCopasiMessage.getAllMessageText(True)
           return 1
   else:
       print >> sys.stderr,  "Usage: example4 SBMLFILE"
       return 1

if(__name__ == '__main__'):
   main(sys.argv[1:]) 



