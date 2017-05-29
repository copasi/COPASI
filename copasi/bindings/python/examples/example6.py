
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
# This is an example on how to run an parameter fitting task.
# The example creates a simple model and runs a time course simulation on it.
# The timecourse data is written to file with some noise added to it.
# This data is used to fit the original parameters.
# 

from COPASI import *
import sys
from random import random

MODEL_STRING="""<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<!-- Created by COPASI version 4.5.30 (Debug) on 2009-03-30 08:01 with libSBML version 3.3.2. -->
<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">
  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"Model\">
    <listOfUnitDefinitions>
      <unitDefinition id=\"volume\">
        <listOfUnits>
          <unit kind=\"litre\" scale=\"-3\"/>
        </listOfUnits>
      </unitDefinition>
      <unitDefinition id=\"substance\">
        <listOfUnits>
          <unit kind=\"mole\" scale=\"-3\"/>
        </listOfUnits>
      </unitDefinition>
    </listOfUnitDefinitions>
    <listOfCompartments>
      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"5\"/>
      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"0\"/>
      <species id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"0\"/>
    </listOfSpecies>
    <listOfReactions>
      <reaction id=\"reaction_1\" name=\"reaction\" reversible=\"false\">
        <listOfReactants>
          <speciesReference species=\"species_1\"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species=\"species_2\"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">
            <apply>
              <times/>
              <ci> compartment_1 </ci>
              <ci> k1 </ci>
              <ci> species_1 </ci>
            </apply>
          </math>
          <listOfParameters>
            <parameter id=\"k1\" name=\"k1\" value=\"0.03\"/>
          </listOfParameters>
        </kineticLaw>
      </reaction>
      <reaction id=\"reaction_2\" name=\"reaction_1\" reversible=\"false\">
        <listOfReactants>
          <speciesReference species=\"species_2\"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species=\"species_3\"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">
            <apply>
              <times/>
              <ci> compartment_1 </ci>
              <ci> k1 </ci>
              <ci> species_2 </ci>
            </apply>
          </math>
          <listOfParameters>
            <parameter id=\"k1\" name=\"k1\" value=\"0.004\"/>
          </listOfParameters>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>"""

def main():
   assert CRootContainer.getRoot() != None
   # create a datamodel
   dataModel = CRootContainer.addDatamodel()
   assert CRootContainer.getDatamodelList().size() == 1
   # first we load a simple model
   try:
     # load the model 
     dataModel.importSBMLFromString(MODEL_STRING)
   except:
     sys.stderr.write("Error while importing the model.\n")
     return 1
   
   # now we need to run some time course simulation to get data to fit
   # against

   # get the trajectory task object
   trajectoryTask = dataModel.getTask("Time-Course")
   assert trajectoryTask != None

   # run a deterministic time course
   trajectoryTask.setMethodType(CTaskEnum.Method_deterministic)

   # pass a pointer of the model to the problem
   trajectoryTask.getProblem().setModel(dataModel.getModel())

   # activate the task so that it will be run when the model is saved
   # and passed to CopasiSE
   trajectoryTask.setScheduled(True)

   # get the problem for the task to set some parameters
   problem = trajectoryTask.getProblem()

   # simulate 4000 steps
   problem.setStepNumber(4000)
   # start at time 0
   dataModel.getModel().setInitialTime(0.0)
   # simulate a duration of 400 time units
   problem.setDuration(400)
   # tell the problem to actually generate time series data
   problem.setTimeSeriesRequested(True)

   # set some parameters for the LSODA method through the method
   method = trajectoryTask.getMethod()

   result=True
   try:
       # now we run the actual trajectory
       result=trajectoryTask.processWithOutputFlags(True, CCopasiTask.ONLY_TIME_SERIES)
   except:
       sys.stderr.write("Error. Running the time course simulation failed.\n" )
       sys.stderr.write(trajectoryTask.getProcessWarning())
       sys.stderr.write(trajectoryTask.getProcessError())
       # check if there are additional error messages
       if CCopasiMessage.size() > 0:
           # print the messages in chronological order
           sys.stderr.write(CCopasiMessage.getAllMessageText(True))
       return 1
   if result==False:
       sys.stderr.write("An error occured while running the time course simulation.\n" )
       dataModel.saveModel('test.cps', True)
       sys.stderr.write(trajectoryTask.getProcessWarning())
       sys.stderr.write(trajectoryTask.getProcessError())
       # check if there are additional error messages
       if CCopasiMessage.size() > 0:
           # print the messages in chronological order
           sys.stderr.write(CCopasiMessage.getAllMessageText(True))
       return 1

   # we write the data to a file and add some noise to it
   # This is necessary since COPASI can only read experimental data from
   # file.
   timeSeries = trajectoryTask.getTimeSeries()
   # we simulated 100 steps, including the initial state, this should be
   # 101 step in the timeseries
   assert timeSeries.getRecordedSteps() == 4001
   iMax = timeSeries.getNumVariables()
   # there should be four variables, the three metabolites and time
   assert iMax == 4
   lastIndex = timeSeries.getRecordedSteps() - 1
   # open the file
   # we need to remember in which order the variables are written to file
   # since we need to specify this later in the parameter fitting task
   indexSet=[]
   metabVector=[]

   # write the header
   # the first variable in a time series is a always time, for the rest
   # of the variables, we use the SBML id in the header
   rand=0.0
   os=open("fakedata_example6.txt","w")
   os.write("# time ")
   keyFactory=CRootContainer.getKeyFactory()
   assert keyFactory != None
   for i in range(1,iMax):
     key=timeSeries.getKey(i)
     object=keyFactory.get(key)
     assert object != None
     # only write header data or metabolites
     if object.__class__==CMetab:
       os.write(", ")
       os.write(timeSeries.getSBMLId(i,dataModel))
       indexSet.append(i)
       metabVector.append(object)
   os.write("\n")
   data=0.0
   for i in range(0,lastIndex):
     s=""
     for j in range(0,iMax):
       # we only want to  write the data for metabolites
       # the compartment does not interest us here
       if j==0 or (j in indexSet):
         # write the data with some noise (+-5% max)
         rand=random()
         data=timeSeries.getConcentrationData(i, j)
         # don't add noise to the time
         if j!=0:
           data+=data*(rand*0.1-0.05)
         s=s+str(data)
         s=s+", "
     # remove the last two characters again
     os.write(s[0:-2])
     os.write("\n")
   os.close()
   
   # now we change the parameter values to see if the parameter fitting
   # can really find the original values
   rand=random()*10
   reaction=dataModel.getModel().getReaction(0)
   # we know that it is an irreversible mass action, so there is one
   # parameter
   assert reaction.getParameters().size() == 1
   assert reaction.isLocalParameter(0)
   # the parameter of a irreversible mass action is called k1
   reaction.setParameterValue("k1",rand)
   
   reaction=dataModel.getModel().getReaction(1)
   # we know that it is an irreversible mass action, so there is one
   # parameter
   assert reaction.getParameters().size() == 1
   assert reaction.isLocalParameter(0)
   reaction.setParameterValue("k1",rand)

   fitTask=dataModel.addTask(CTaskEnum.Task_parameterFitting)
   assert fitTask != None
   # the method in a fit task is an instance of COptMethod or a subclass of
   # it.
   fitMethod=fitTask.getMethod()
   assert fitMethod != None
   # the object must be an instance of COptMethod or a subclass thereof
   # (CFitMethod)
   fitProblem=fitTask.getProblem()
   assert fitProblem != None
   
   experimentSet=fitProblem.getParameter("Experiment Set")
   assert experimentSet != None
   
   # first experiment (we only have one here)
   experiment=CExperiment(dataModel)
   assert experiment != None
   # tell COPASI where to find the data
   # reading data from string is not possible with the current C++ API
   experiment.setFileName("fakedata_example6.txt")
   # we have to tell COPASI that the data for the experiment is a komma
   # separated list (the default is TAB separated)
   experiment.setSeparator(",")
   # the data start in row 1 and goes to row 4001
   experiment.setFirstRow(1)
   assert experiment.getFirstRow()==1
   experiment.setLastRow(4001)
   assert experiment.getLastRow()==4001
   experiment.setHeaderRow(1)
   assert experiment.getHeaderRow()==1
   experiment.setExperimentType(CTaskEnum.Task_timeCourse)
   assert experiment.getExperimentType()==CTaskEnum.Task_timeCourse
   experiment.setNumColumns(4)
   assert experiment.getNumColumns()==4
   objectMap=experiment.getObjectMap()
   assert objectMap != None
   result=objectMap.setNumCols(4)
   assert result == True
   result=objectMap.setRole(0,CExperiment.time)
   assert result == True
   assert objectMap.getRole(0) == CExperiment.time

   model=dataModel.getModel()
   assert model!=None
   timeReference=model.getValueReference()
   assert timeReference != None
   objectMap.setObjectCN(0,timeReference.getCN().getString())
  
   # now we tell COPASI which column contain the concentrations of
   # metabolites and belong to dependent variables
   objectMap.setRole(1,CExperiment.dependent)
   metab=metabVector[0]
   assert metab != None
   particleReference=metab.getConcentrationReference()
   assert particleReference != None
   objectMap.setObjectCN(1,particleReference.getCN().getString())

   objectMap.setRole(2,CExperiment.dependent)
   metab=metabVector[1]
   assert metab != None
   particleReference=metab.getConcentrationReference()
   assert particleReference != None
   objectMap.setObjectCN(2,particleReference.getCN().getString())

   objectMap.setRole(3,CExperiment.dependent)
   metab=metabVector[2]
   assert metab != None
   particleReference=metab.getConcentrationReference()
   assert particleReference != None
   objectMap.setObjectCN(3,particleReference.getCN().getString())
   
   experimentSet.addExperiment(experiment)
   assert experimentSet.getExperimentCount()==1
   # addExperiment makes a copy, so we need to get the added experiment
   # again
   experiment=experimentSet.getExperiment(0)
   assert experiment != None

   # now we have to define the two fit items for the two local parameters
   # of the two reactions
   reaction=model.getReaction(0)
   assert reaction != None
   assert reaction.isLocalParameter(0)==True
   parameter=reaction.getParameters().getParameter(0)
   assert parameter != None
   
   # define a CFitItem
   parameterReference=parameter.getValueReference()
   assert parameterReference != None
   fitItem1=CFitItem(dataModel)
   assert fitItem1 !=None
   fitItem1.setObjectCN(parameterReference.getCN())
   fitItem1.setStartValue(4.0)
   fitItem1.setLowerBound(CCommonName("0.00001"))
   fitItem1.setUpperBound(CCommonName("10"))
   # add the fit item to the correct parameter group
   optimizationItemGroup=fitProblem.getParameter("OptimizationItemList")
   assert optimizationItemGroup != None
   optimizationItemGroup.addParameter(fitItem1)
   
   reaction=model.getReaction(1)
   assert reaction != None
   assert reaction.isLocalParameter(0)==True
   parameter=reaction.getParameters().getParameter(0)
   assert parameter != None
   
   # define a CFitItem
   parameterReference=parameter.getValueReference()
   assert parameterReference != None
   fitItem2=CFitItem(dataModel)
   assert fitItem2 !=None
   fitItem2.setObjectCN(parameterReference.getCN())
   fitItem2.setStartValue(4.0)
   fitItem2.setLowerBound(CCommonName("0.00001"))
   fitItem2.setUpperBound(CCommonName("10"))
   # add the fit item to the correct parameter group
   optimizationItemGroup.addParameter(fitItem2)
   
   result=True
   try:
     # running the task for this example will probably take some time
     print ("This can take some time...")
     result=fitTask.processWithOutputFlags(True, CCopasiTask.ONLY_TIME_SERIES)
   except:
     sys.stderr.write("Error. Parameter fitting failed.\n")
     return 1
   if result==False:
       sys.stderr.write("An error occured while running the Parameter estimation.\n")
       dataModel.saveModel('test.cps', True)
       sys.stderr.write(fitTask.getProcessWarning())
       sys.stderr.write(fitTask.getProcessError())
       # check if there are additional error messages
       if CCopasiMessage.size() > 0:
           # print the messages in chronological order
           sys.stderr.write(CCopasiMessage.getAllMessageText(True))
       return 1
   assert result == True
   # assert that there are two optimization items
   assert len(fitProblem.getOptItemList()) == 2
   # the order should be the order in whih we added the items above
   optItem1 = fitProblem.getOptItemList()[0]
   optItem2 = fitProblem.getOptItemList()[1]
   # the actual results are stored in the fit problem
   assert fitProblem.getSolutionVariables().size() == 2
   print ("value for " , optItem1.getObject().getCN().getString() , ": " , fitProblem.getSolutionVariables().get(0))
   print ("value for " , optItem2.getObject().getCN().getString() , ": " , fitProblem.getSolutionVariables().get(1))
   # depending on the noise, the fit can be quite bad, so we are a litle
   # relaxed here (we should be within 3% of the original values)
   assert (abs(fitProblem.getSolutionVariables().get(0) - 0.03) / 0.03) < 3e-2
   assert (abs(fitProblem.getSolutionVariables().get(1) - 0.004) / 0.004) < 3e-2

if(__name__ == '__main__'):
   main() 

