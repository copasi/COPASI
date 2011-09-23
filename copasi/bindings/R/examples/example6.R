#options(echo = FALSE) # disable echoing of input

# 
# This is an example on how to run an parameter fitting task.
# The example creates a simple model and runs a time course simulation on it.
# The timecourse data is written to file with some noise added to it.
# This data is used to fit the original parameters.
# 


# First we load the COPASI package
dyn.load(paste("COPASI", .Platform$dynlib.ext, sep=""))
source("COPASI.R")
# I Don't know exactly what the next line does, but this is what the SWIG
# documentation has to say about it:
# The cacheMetaData(1) will cause R to refresh its object tables. Without it, inheritance of wrapped objects may fail.
cacheMetaData(1)

MODEL_STRING <- '<?xml version="1.0" encoding="UTF-8"?>\n<!-- Created by COPASI version 4.5.30 (Debug) on 2009-03-30 08:01 with libSBML version 3.3.2. -->\n<sbml xmlns="http://www.sbml.org/sbml/level2" level="2" version="1">\n<model metaid="COPASI1" id="Model_1" name="Model">\n<listOfUnitDefinitions>\n<unitDefinition id="volume">\n<listOfUnits>\n<unit kind="litre" scale="-3"/>\n</listOfUnits>\n</unitDefinition>\n<unitDefinition id="substance">\n<listOfUnits>\n<unit kind="mole" scale="-3"/>\n</listOfUnits>\n</unitDefinition>\n</listOfUnitDefinitions>\n<listOfCompartments>\n<compartment id="compartment_1" name="compartment" size="1"/>\n</listOfCompartments>\n<listOfSpecies>\n<species id="species_1" name="A" compartment="compartment_1" initialConcentration="5"/>\n<species id="species_2" name="B" compartment="compartment_1" initialConcentration="0"/>\n<species id="species_3" name="C" compartment="compartment_1" initialConcentration="0"/>\n</listOfSpecies>\n<listOfReactions>\n<reaction id="reaction_1" name="reaction" reversible="false">\n<listOfReactants>\n<speciesReference species="species_1"/>\n</listOfReactants>\n<listOfProducts>\n<speciesReference species="species_2"/>\n</listOfProducts>\n<kineticLaw>\n<math xmlns="http://www.w3.org/1998/Math/MathML">\n<apply>\n<times/>\n<ci> compartment_1 </ci>\n<ci> k1 </ci>\n<ci> species_1 </ci>\n</apply>\n</math>\n<listOfParameters>\n<parameter id="k1" name="k1" value="0.03"/>\n</listOfParameters>\n</kineticLaw>\n</reaction>\n<reaction id="reaction_2" name="reaction_1" reversible="false">\n<listOfReactants>\n<speciesReference species="species_2"/>\n</listOfReactants>\n<listOfProducts>\n<speciesReference species="species_3"/>\n</listOfProducts>\n<kineticLaw>\n<math xmlns="http://www.w3.org/1998/Math/MathML">\n<apply>\n<times/>\n<ci> compartment_1 </ci>\n<ci> k1 </ci>\n<ci> species_2 </ci>\n</apply>\n</math>\n<listOfParameters>\n<parameter id="k1" name="k1" value="0.004"/>\n</listOfParameters>\n</kineticLaw>\n</reaction>\n</listOfReactions>\n</model>\n</sbml>'

stopifnot(!is.null(CCopasiRootContainer_getRoot()))
# create a datamodel
dataModel <- CCopasiRootContainer_addDatamodel()
stopifnot(DataModelVector_size(CCopasiRootContainer_getDatamodelList()) == 1)
# first we load a simple model
tryCatch(CCopasiDataModel_importSBMLFromString(dataModel,MODEL_STRING), error = function(e) {
  write("Error while importing the model.", stderr())
  quit(save = "default", status = 1, runLast = TRUE)
} )

model <- CCopasiDataModel_getModel(dataModel)
# now we need to run some time course simulation to get data to fit
# against

# get the trajectory task object
trajectoryTask <- CCopasiDataModel_getTask(dataModel,"Time-Course")
stopifnot(!is.null(trajectoryTask))
# if there isn't one
if (is.null(trajectoryTask)) {
    # create a one
    trajectoryTask <- CTrajectoryTask()

    # add the time course task to the task list
    # this method makes sure that the object is now owned 
    # by the list and that it does not get deleted by SWIG
    invisible(CCopasiTaskList_addAndOwn(CCopasiDataModel_getTaskList(dataModel), trajectoryTask))
}

# run a deterministic time course
invisible(CTrajectoryTask_setMethodType(trajectoryTask,"deterministic"))

# pass a pointer of the model to the problem
problem <- CCopasiTask_getProblem(trajectoryTask)
invisible(CCopasiProblem_setModel(problem,model))

# activate the task so that it will be run when the model is saved
# and passed to CopasiSE
invisible(CCopasiTask_setScheduled(trajectoryTask,TRUE))

# simulate 4000 steps
invisible(CTrajectoryProblem_setStepNumber(problem,4000))
# start at time 0
invisible(CModel_setInitialTime(model, 0.0))
# simulate a duration of 400 time units
invisible(CTrajectoryProblem_setDuration(problem,400))
# tell the problem to actually generate time series data
invisible(CTrajectoryProblem_setTimeSeriesRequested(problem,TRUE))

# set some parameters for the LSODA method through the method
method <- CCopasiTask_getMethod(trajectoryTask)

result <- TRUE
invisible(CCopasiMessage_clearDeque())
tryCatch(result <- CTrajectoryTask_process(trajectoryTask,TRUE), error = function(e) {
  write("Error. Running the time course simulation failed.", stderr()) 
  # check if there are additional error messages
  if (CCopasiMessage_size() > 0) {
      # print the messages in chronological order
      write(CCopasiMessage_getAllMessageText(TRUE), stderr())
  }
  quit(save = "default", status = 1, runLast = TRUE)
} )

if (result == FALSE) {
    write("An error occured while running the time course simulation." , stderr())
    # check if there are additional error messages
    if (CCopasiMessage_size() > 0) {
        # print the messages in chronological order
        write(CCopasiMessage_getAllMessageText(CCopasiMessage,TRUE), stderr())
    }
    quit(save = "default", status = 1, runLast = TRUE)
}

# we write the data to a file and add some noise to it
# This is necessary since COPASI can only read experimental data from
# file.
timeSeries <- CTrajectoryTask_getTimeSeries(trajectoryTask)
# we simulated 100 steps, including the initial state, this should be
# 101 step in the timeseries
stopifnot(CTimeSeries_getRecordedSteps(timeSeries) == 4001)
iMax <- CTimeSeries_getNumVariables(timeSeries)
# there should be four variables, the three metabolites and time
stopifnot(iMax == 5)
lastIndex <- CTimeSeries_getRecordedSteps(timeSeries) - 1
# open the file
# we need to remember in which order the variables are written to file
# since we need to specify this later in the parameter fitting task
indexSet <-[]
metabVector <-[]

# write the header
# the first variable in a time series is a always time, for the rest
# of the variables, we use the SBML id in the header
rand <- 0.0

# redirect output to file
sink("fakedata_example6.txt", append=FALSE, split=FALSE)
write("# time ")
keyFactory <- CCopasiRootContainer_getKeyFactory()
stopifnot(!is.null(keyFactory))
i <- 1
while (i < iMax) {
  key <- CTimeSeries_getKey(timeSeries,i)
  object <- CCopasiKeyFactory_get(keyFactory,key)
  stopifnot(!is.null(object))
  # only write header data or metabolites
  if (object.__class__ == CMetab) {
    write(", ")
    write(CTimeSeries_getSBMLId(timeSeries,i,dataModel))
    indexSet_append(indexSet,i)
    metabVector_append(metabVector,object)
  }
}
write("\n")
data <- 0.0
i <- 0
while(i < lastIndex) {
  s <- ""
  j <- 0
  while(j < iMax) {
    # we only want to  write the data for metabolites
    # the compartment does not interest us here
    if (j==0 || (j in indexSet)) {
      # write the data with some noise (+-5% max)
      rand <- runif(1, -0.05, 0.05)
      data <- CTimeSeries_getConcentrationData(timeSeries,i, j)
      # don't add noise to the time
      if (j != 0) {
        data = data + data * rand 
      }
      s <- paste(s, data, ", ")
    }
  }
  # remove the last two characters again
  write(s[0:-2])
  write("\n")
}
# redirect output to default destination
sink()

# now we change the parameter values to see if the parameter fitting
# can really find the original values
rand <- runif(1,0.0,10.0)
reaction <- CModel_getReaction(model,0)
# we know that it is an irreversible mass action, so there is one
# parameter
stopifnot(CCopasiParameterGroup_size(CReaction_getParameters(reaction)) == 1)
stopifnot(CReaction_isLocalParameter(reaction,0))
# the parameter of a irreversible mass action is called k1
invisible(CReaction_setParameterValue(reaction,"k1",rand))

reaction <- CModel_getReaction(model, 1)
# we know that it is an irreversible mass action, so there is one
# parameter
stopifnot(CCopasiParameterGroup_size(reaction_getParameters(reaction,)) == 1)
stopifnot(CReaction_isLocalParameter(reaction,0))
invisible(CReaction_setParameterValue(reaction,"k1",rand))

fitTask <- CCopasiDataModel_addTask(dataModel,"parameterFitting")
stopifnot(!is.null(fitTask))
# the method in a fit task is an instance of COptMethod or a subclass of
# it.
fitMethod <- CFitTask_getMethod(fitTask)
stopifnot(!is.null(fitMethod))
# the object must be an instance of COptMethod or a subclass thereof
# (CFitMethod)
fitProblem <- CFitTask_getProblem(fitTask)
stopifnot(!is.null(fitProblem))

experimentSet <- fitProblem_getParameter(fitProblem,"Experiment Set")
stopifnot(!is.null(experimentSet))

# first experiment (we only have one here)
experiment <- CExperiment(dataModel)
stopifnot(!is.null(experiment))
# tell COPASI where to find the data
# reading data from string is not possible with the current C++ API
invisible(CExperiment_setFileName(experiment,"fakedata_example6.txt"))
# we have to tell COPASI that the data for the experiment is a komma
# separated list (the default is TAB separated)
invisible(CExperiment_setSeparator(experiment,","))
# the data start in row 1 and goes to row 4001
invisible(CExperiment_setFirstRow(experiment,1))
stopifnot(CExperiment_getFirstRow(experiment) == 1)
invisible(CExperiment_setLastRow(experiment,4001))
stopifnot(CExperiment_getLastRow(experiment) == 4001)
invisible(CExperiment_setHeaderRow(experiment,1))
stopifnot(CExperiment_getHeaderRow(experiment) == 1)
invisible(CExperiment_setExperimentType(experiment,"timeCourse"))
stopifnot(CExperiment_getExperimentType(experiment) == "timeCourse")
invisible(CExperiment_setNumColumns(experiment,4))
stopifnot(CExperiment_getNumColumns(experiment) == 4)
objectMap <- CExperiment_getObjectMap(experiment)
stopifnot(!is.null(objectMap))
result <- CExperimentObjectMap_setNumCols(objectMap,4)
stopifnot(result == TRUE)
result <- CExperimentObjectMap_setRole(objectMap,0,"time")
stopifnot(result == TRUE)
stopifnot(CExperimentObjectMap_getRole(objectMap,0) == "time")

stopifnot(!is.null(model))
timeReference <- CModel_getObject(model,CCopasiObjectName("Reference=Time"))
stopifnot(!is.null(timeReference))
invisible(CExperimentObjectMap_setObjectCN(objectMap,0,CCopasiObjectName_getString(CCopasiObject_getCN(timeReference))))

# now we tell COPASI which column contain the concentrations of
# metabolites and belong to dependent variables
invisible(CExperimentObjectMap_setRole(objectMap,1,"dependent"))
metab <- metabVector[0]
stopifnot(!is.null(metab))
particleReference <- CCopasiContainer_getObject(metab,CCopasiObjectName("Reference=Concentration"))
stopifnot(!is.null(particleReference))
invisible(CExperimentObjectMap_setObjectCN(objectMap,1,CCopasiObjectName_getString(CCopasiObject_getCN(particleReference))))

invisible(CExperimentObjectMap_setRole(objectMap,2,"dependent"))
metab <- metabVector[1]
stopifnot(!is.null(metab))
particleReference <- CCopasiCOntainer_getObject(metab,CCopasiObjectName("Reference=Concentration"))
stopifnot(!is.null(particleReference))
invisible(CExperimentObjectMap_setObjectCN(objectMap,2,CCopasiObjectName_getString(CCopasiObject_getCN(particleReference))))

invisible(CExperimentObjectMap_setRole(objectMap,3,"dependent"))
metab <- metabVector[2]
stopifnot(!is.null(metab))
particleReference <- CCopasiContainer_getObject(metab,CCopasiObjectName("Reference=Concentration"))
stopifnot(!is.null(particleReference))
invisible(CExperimentObjectMap_setObjectCN(objectMap,3,CCopasiObjectName_getString(CCopasiObject_getCN(particleReference))))

invisible(CExperimentSet_addExperiment(experimentSet,experiment))
stopifnot(CExperimentSet_getExperimentCount(experimentSet) == 1)
# addExperiment makes a copy, so we need to get the added experiment
# again
experiment <- CExperimentSet_getExperiment(experimentSet,0)
stopifnot(!is.null(experiment))

# now we have to define the two fit items for the two local parameters
# of the two reactions
reaction <- CModel_getReaction(model,0)
stopifnot(!is.null(reaction))
stopifnot(CReaction_isLocalParameter(reaction,0) == TRUE)
parameter <- CCopasiParameterGroup_getParameter(CReaction_getParameters(reaction),0)
stopifnot(!is.null(parameter))

# define a CFitItem
parameterReference <- CCopasiParameter_getObject(parameter,CCopasiObjectName("Reference=Value"))
stopifnot(!is.null(parameterReference))
fitItem1 <- CFitItem(dataModel)
stopifnot(!is.null(fitItem1))
invisible(CFitItem_setObjectCN(fitItem1,parameterReference.getCN()))
invisible(CFitItem_setStartValue(fitItem1,4.0))
invisible(CFitItem_setLowerBound(fitItem1,CCopasiObjectName("0.00001")))
invisible(CFitItem_setUpperBound(fitItem1,CCopasiObjectName("10")))
# add the fit item to the correct parameter group
optimizationItemGroup <- CFitProblem_getParameter(fitProblem,"OptimizationItemList")
stopifnot(!is.null(optimizationItemGroup))
invisible(CCopasiParameterGroup_addParameter(optimizationItemGroup,fitItem1))

reaction <- CModel_getReaction(model,1)
stopifnot(!is.null(reaction))
stopifnot(CReaction_isLocalParameter(reaction,0)==TRUE)
parameter <- CCopasiParameterGroup_getParameter(CReaction_getParameters(reaction),0)
stopifnot(!is.null(parameter))

# define a CFitItem
parameterReference <- CCopasiContainer_getObject(parameter,CCopasiObjectName("Reference=Value"))
stopifnot(!is.null(parameterReference))
fitItem2 <- CFitItem(dataModel)
stopifnot(!is.null(fitItem2))
invisible(CFitItem_setObjectCN(fitItem2,parameterReference.getCN()))
invisible(CFitItem_setStartValue(fitItem2,4.0))
invisible(CFitItem_setLowerBound(fitItem2,CCopasiObjectName("0.00001")))
invisible(CFitItem_setUpperBound(fitItem2,CCopasiObjectName("10")))
# add the fit item to the correct parameter group
invisible(CCopasiParameterGroup_addParameter(optimizationItemGroup,fitItem2))

result <- TRUE
# running the task for this example will probably take some time
cat("This can take some time...\n")
tryCatch(result <- fitTask_process(fitTask,TRUE), error = function(e) {
  write("Error. Parameter fitting failed.", stderr())
  quit(save = "default", status = 1, runLast = TRUE)
} )

  
stopifnot(result == TRUE)
# stopifnot(that there are two optimization items)
stopifnot(len(fitProblem_getOptItemList(fitProblem)) == 2)
# the order should be the order in whih we added the items above
optItem1 <- CFitProblem_getOptItemList(fitProblem)[0]
optItem2 <- CFitProblem_getOptItemList(fitProblem)[1]
# the actual results are stored in the fit problem
stopifnot(FloatVectorCore_size(CFitProblem_getSolutionVariables(fitProblem)) == 2)

cat("value for " , CCopasiObjectName_getString(CCopasiObject_getCN(COptItem_getObject(optItem1))) , ": " , FloatVectorCore_get(CFitProblem_getSolutionVariables(),0), "\n" sep = "")
cat("value for " , CCopasiObjectName_getString(CCopasiObject_getCN(COptItem_getObject(optItem2))) , ": " , FloatVectorCore_get(CFitProblem_getSolutionVariables(),1), "\n", sep = "")
# depending on the noise, the fit can be quite bad, so we are a litle
# relaxed here (we should be within 3% of the original values)
stopifnot((abs(FloatVectorCore(CFitProblem_getSolutionVariables(fitProblem),0) - 0.03) / 0.03) < 3e-2)
stopifnot((abs(FloatVectorCore(CFitProblem_getSolutionVariables(fitProblem),1) - 0.004) / 0.004) < 3e-2)

