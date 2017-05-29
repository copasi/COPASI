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
# This is an example on how to import an sbml file
# create a report for a time course simulation 
# and run a scan for a stochastic time course simulation
# 

from COPASI import *
import sys

MODEL_STRING="""<?xml version="1.0" encoding="UTF-8"?>
<!-- Created by COPASI version 4.4.29 (Debug) on 2009-03-05 14:41 with libSBML version 3.3.0. -->
<sbml xmlns="http://www.sbml.org/sbml/level2/version3" level="2" version="3">
  <model metaid="COPASI1" id="Model_1" name="New Model">
    <listOfUnitDefinitions>
      <unitDefinition id="volume">
        <listOfUnits>
          <unit kind="litre" scale="-6"/>
        </listOfUnits>
      </unitDefinition>
      <unitDefinition id="substance">
        <listOfUnits>
          <unit kind="mole" scale="-9"/>
        </listOfUnits>
      </unitDefinition>
    </listOfUnitDefinitions>
    <listOfCompartments>
      <compartment id="compartment_1" name="compartment" size="1"/>
    </listOfCompartments>
    <listOfSpecies>
      <species metaid="COPASI2" id="species_1" name="A" compartment="compartment_1" initialConcentration="1e-10">
      </species>
      <species metaid="COPASI3" id="species_2" name="B" compartment="compartment_1" initialConcentration="0">
      </species>
      <species metaid="COPASI4" id="species_3" name="C" compartment="compartment_1" initialConcentration="0">
      </species>
    </listOfSpecies>
    <listOfReactions>
      <reaction id="reaction_1" name="reaction" reversible="false">
        <listOfReactants>
          <speciesReference species="species_1"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="species_2"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> compartment_1 </ci>
              <ci> k1 </ci>
              <ci> species_1 </ci>
            </apply>
          </math>
          <listOfParameters>
            <parameter id="k1" value="0.1"/>
          </listOfParameters>
        </kineticLaw>
      </reaction>
      <reaction id="reaction_2" name="reaction_1" reversible="false">
        <listOfReactants>
          <speciesReference species="species_2"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="species_3"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> compartment_1 </ci>
              <ci> k1 </ci>
              <ci> species_2 </ci>
            </apply>
          </math>
          <listOfParameters>
            <parameter id="k1" value="0.1"/>
          </listOfParameters>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>
"""


def main(args):
   assert CRootContainer.getRoot() != None
   # create a datamodel
   dataModel = CRootContainer.addDatamodel()
   assert CRootContainer.getDatamodelList().size() == 1
   # the only argument to the main routine should be the name of an SBML file
   try:
       # load the model
       dataModel.importSBMLFromString(MODEL_STRING)
   except:
       sys.stderr.write("Error while importing the model from given string.\n")
       return 1
   model = dataModel.getModel()
   assert model != None
   # create a report with the correct filename and all the species against
   # time.
   reports = dataModel.getReportDefinitionList()
   # create a report definition object
   report = reports.createReportDefinition("Report", "Output for timecourse")
   # set the task type for the report definition to timecourse
   report.setTaskType(CTaskEnum.Task_timeCourse)
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
   body.push_back(CRegisteredCommonName(CCommonName(dataModel.getModel().getCN().getString() + ",Reference=Time").getString()))
   body.push_back(CRegisteredCommonName(report.getSeparator().getCN().getString()))
   header.push_back(CRegisteredCommonName(CDataString("time").getCN().getString()))
   header.push_back(CRegisteredCommonName(report.getSeparator().getCN().getString()))

   iMax = model.getMetabolites().size()
   for i in range(0,iMax):
       metab = model.getMetabolite(i)
       assert metab != None
       # we don't want output for FIXED metabolites right now
       if metab.getStatus() != CModelEntity.Status_FIXED:
           # we want the concentration in the output
           # alternatively, we could use "Reference=Amount" to get the
           # particle number
           body.push_back(CRegisteredCommonName(metab.getObject(CCommonName("Reference=Concentration")).getCN().getString()))
           # add the corresponding id to the header
           header.push_back(CRegisteredCommonName(CDataString(metab.getSBMLId()).getCN().getString()))
           
           if i!=iMax-1:
             # after each entry, we need a seperator
             body.push_back(CRegisteredCommonName(report.getSeparator().getCN().getString()))

             # and a seperator
             header.push_back(CRegisteredCommonName(report.getSeparator().getCN().getString()))

   # get the trajectory task object
   trajectoryTask = dataModel.getTask("Time-Course")
   assert trajectoryTask != None

   # run a stochastic time course
   trajectoryTask.setMethodType(CTaskEnum.Method_stochastic)

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
   scanTask = dataModel.getTask("Scan")
   assert scanTask != None

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
   scanProblem.setSubtask(CTaskEnum.Task_timeCourse)

   # we just want to run the timecourse task a number of times, so we
   # create a repeat item with 100 repeats
   scanProblem.addScanItem(CScanProblem.SCAN_REPEAT, 100)
   

   # we want the output from the trajectory task
   scanProblem.setOutputInSubtask(True)

   # we don't want to set the initial conditions of the model to the end
   # state of the last run
   scanProblem.setContinueFromCurrentState(False)

   try:
       # now we run the actual trajectory
       if not scanTask.process(True): 
         sys.stderr.write("Error. Running the scan failed.\n")
         # check if there are additional error messages
         sys.stderr.write(CCopasiMessage.getAllMessageText(True))
         
   except:
       sys.stderr.write("Error. Running the scan failed.\n")
       # check if there are additional error messages
       if (CCopasiMessage.size() > 0):
           # print the messages in chronological order
           sys.stderr.write(CCopasiMessage.getAllMessageText(True))
       return 1


if(__name__ == '__main__'):
   main(sys.argv[1:]) 

