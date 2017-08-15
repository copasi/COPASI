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

stopifnot(!is.null(CRootContainer_getRoot()))
# create a datamodel
dataModel <- CRootContainer_addDatamodel()
stopifnot(CRootContainer_getDatamodelList()$size() == 1)
# first we load a simple model
tryCatch(invisible(dataModel$importSBMLFromString(MODEL_STRING)), error = function(e) {
  write("Error while importing the model.", stderr())
  quit(save = "default", status = 1, runLast = TRUE)
} )

model <- dataModel$getModel()
# now we need to run some time course simulation to get data to fit
# against

# get the trajectory task object
trajectoryTask <- as(dataModel$getTask("Time-Course"), "_p_CTrajectoryTask")
stopifnot(!is.null(trajectoryTask))
# if there isn't one
if (is.null(trajectoryTask)) {
    # create a one
    trajectoryTask <- CTrajectoryTask()

    # add the time course task to the task list
    # this method makes sure that the object is now owned 
    # by the list and that it does not get deleted by SWIG
    invisible(dataModel$getTaskList()$addAndOwn(trajectoryTask))
}

# run a deterministic time course
invisible(trajectoryTask$setMethodType("deterministic"))

# pass a pointer of the model to the problem
problem <- as(trajectoryTask$getProblem(), "_p_CTrajectoryProblem")
invisible(problem$setModel(model))

# activate the task so that it will be run when the model is saved
# and passed to CopasiSE
invisible(trajectoryTask$setScheduled(TRUE))

# simulate 4000 steps
invisible(problem$setStepNumber(4000))
# start at time 0
invisible(model$setInitialTime(0.0))
# simulate a duration of 400 time units
invisible(problem$setDuration(400))
# tell the problem to actually generate time series data
invisible(problem$setTimeSeriesRequested(TRUE))

# set some parameters for the LSODA method through the method
method <- trajectoryTask$getMethod()

result <- TRUE
invisible(CCopasiMessage_clearDeque())
tryCatch(result <- trajectoryTask$process(TRUE), error = function(e) {
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
        write(CCopasiMessage$getAllMessageText(TRUE), stderr())
    }
    quit(save = "default", status = 1, runLast = TRUE)
}

# we write the data to a file and add some noise to it
# This is necessary since COPASI can only read experimental data from
# file.
timeSeries <- trajectoryTask$getTimeSeries()
# we simulated 100 steps, including the initial state, this should be
# 101 step in the timeseries
stopifnot(timeSeries$getRecordedSteps() == 4001)
iMax <- timeSeries$getNumVariables()
# there should be four variables, the three metabolites and time
stopifnot(iMax == 4)
lastIndex <- timeSeries$getRecordedSteps() - 1
# open the file
# we need to remember in which order the variables are written to file
# since we need to specify this later in the parameter fitting task
indexSet <- c()
metabVector <- list()

# write the header
# the first variable in a time series is a always time, for the rest
# of the variables, we use the SBML id in the header
rand <- 0.0

# redirect output to file
sink("fakedata_example6.txt", append=FALSE, split=FALSE)
cat("# time ")
keyFactory <- CRootContainer_getKeyFactory()
stopifnot(!is.null(keyFactory))
i <- 1
while (i < iMax) {
  key <- timeSeries$getKey(i)
  object <- keyFactory$get(key)
  stopifnot(!is.null(object))
  # only write header data for metabolites
  # Since I don't know yet how to determine the real underlying class
  # in R, I changed the example to use the getObjectType method
  if (object$getObjectType() == "Metabolite") {
    cat(", ")
    cat(timeSeries$getSBMLId(i,dataModel))
    indexSet <- c(indexSet,i)
    metabVector[[length(metabVector)+1]] <- object
  }
  i <- i + 1
}
cat("\n")
data <- 0.0
i <- 0
while(i < lastIndex) {
  s <- ""
  j <- 0
  while(j < iMax) {
    # we only want to  write the data for metabolites
    # the compartment does not interest us here
    if (j==0 || any(indexSet == j)) {
      # write the data with some noise (+-5% max)
      rand <- runif(1, -0.05, 0.05)
      data <- timeSeries$getConcentrationData(i, j)
      # don't add noise to the time
      if (j != 0) {
        data <- data + data * rand 
      }
      s <- paste(s, data, ", ", sep = "")
    }
    j <- j + 1
  }
  # remove the last two characters again
  cat(substr(s,1,nchar(s)-2), "\n", sep = "")
  #cat(substr(s,1,length(s)-1))
  i <- i + 1
}
# redirect output to default destination
sink()


# now we change the parameter values to see if the parameter fitting
# can really find the original values
rand <- runif(1,0.0,10.0)
reaction <- model$getReaction(0)
# we know that it is an irreversible mass action, so there is one
# parameter
stopifnot(reaction$getParameters()$size() == 1)
stopifnot(reaction$isLocalParameter(0))
# the parameter of a irreversible mass action is called k1
invisible(reaction$setParameterValue("k1",rand))

reaction <- model$getReaction(1)
# we know that it is an irreversible mass action, so there is one
# parameter
stopifnot(reaction$getParameters()$size() == 1)
stopifnot(reaction$isLocalParameter(0))
invisible(reaction$setParameterValue("k1",rand))

fitTask <- dataModel$addTask("parameterFitting")
stopifnot(!is.null(fitTask))
# the method in a fit task is an instance of COptMethod or a subclass of
# it.
fitMethod <- fitTask$getMethod()
stopifnot(!is.null(fitMethod))
# the object must be an instance of COptMethod or a subclass thereof
# (CFitMethod)
fitProblem <- as(fitTask$getProblem(), "_p_CFitProblem")
invisible(as(fitProblem, '_p_CFitProblem'))
stopifnot(!is.null(fitProblem))

experimentSet <- fitProblem$getParameter("Experiment Set")
invisible(experimentSet <- as(experimentSet, '_p_CExperimentSet'))
stopifnot(!is.null(experimentSet))

# first experiment (we only have one here)
experiment <- CExperiment(dataModel)
stopifnot(!is.null(experiment))
# tell COPASI where to find the data
# reading data from string is not possible with the current C++ API
invisible(experiment$setFileName("fakedata_example6.txt"))
# we have to tell COPASI that the data for the experiment is a komma
# separated list (the default is TAB separated)
invisible(experiment$setSeparator(","))
# the data start in row 1 and goes to row 4001
invisible(experiment$setFirstRow(1))
stopifnot(experiment$getFirstRow() == 1)
invisible(experiment$setLastRow(4001))
stopifnot(experiment$getLastRow() == 4001)
invisible(experiment$setHeaderRow(1))
stopifnot(experiment$getHeaderRow() == 1)
invisible(experiment$setExperimentType("timeCourse"))
stopifnot(experiment$getExperimentType() == "timeCourse")
invisible(experiment$setNumColumns(4))
stopifnot(experiment$getNumColumns() == 4)
objectMap <- experiment$getObjectMap()
stopifnot(!is.null(objectMap))
result <- objectMap$setNumCols(4)
stopifnot(result == TRUE)
result <- objectMap$setRole(0,"time")
stopifnot(result == TRUE)
stopifnot(objectMap$getRole(0) == "time")

stopifnot(!is.null(model))
timeReference <- model$getObject(CCommonName("Reference=Time"))
stopifnot(!is.null(timeReference))
invisible(objectMap$setObjectCN(0,timeReference$getCN()$getString()))

# now we tell COPASI which column contain the concentrations of
# metabolites and belong to dependent variables
invisible(objectMap$setRole(1,"dependent"))
metab <- metabVector[[1]]
stopifnot(!is.null(metab))
particleReference <- metab$getObject(CCommonName("Reference=Concentration"))
stopifnot(!is.null(particleReference))
invisible(objectMap$setObjectCN(1,particleReference$getCN()$getString()))

invisible(objectMap$setRole(2,"dependent"))

metab <- metabVector[[2]]
stopifnot(!is.null(metab))
particleReference <- metab$getObject(CCommonName("Reference=Concentration"))
stopifnot(!is.null(particleReference))
invisible(objectMap$setObjectCN(2,particleReference$getCN()$getString()))

invisible(objectMap$setRole(3,"dependent"))

metab <- metabVector[[3]]
stopifnot(!is.null(metab))
particleReference <- metab$getObject(CCommonName("Reference=Concentration"))
stopifnot(!is.null(particleReference))
invisible(objectMap$setObjectCN(3,particleReference$getCN()$getString()))

invisible(experimentSet$addExperiment(experiment))
stopifnot(experimentSet$getExperimentCount() == 1)
# addExperiment makes a copy, so we need to get the added experiment
# again
experiment <- experimentSet$getExperiment(0)
stopifnot(!is.null(experiment))

# now we have to define the two fit items for the two local parameters
# of the two reactions
reaction <- model$getReaction(0)
stopifnot(!is.null(reaction))
stopifnot(reaction$isLocalParameter(0) == TRUE)
parameter <- reaction$getParameters()$getParameter(0)
stopifnot(!is.null(parameter))

# define a CFitItem
parameterReference <- parameter$getObject(CCommonName("Reference=Value"))
stopifnot(!is.null(parameterReference))
fitItem1 <- fitProblem$addFitItem(parameterReference$getCN())
stopifnot(!is.null(fitItem1))
#invisible(fitItem1$setObjectCN(parameterReference$getCN()))
invisible(fitItem1$setStartValue(4.0))
invisible(fitItem1$setLowerBound(CCommonName("0.00001")))
invisible(fitItem1$setUpperBound(CCommonName("10")))
# add the fit item to the correct parameter group
optimizationItemGroup <- fitProblem$getParameter("OptimizationItemList")
stopifnot(!is.null(optimizationItemGroup))

reaction <- model$getReaction(1)
stopifnot(!is.null(reaction))
stopifnot(reaction$isLocalParameter(0)==TRUE)
parameter <- reaction$getParameters()$getParameter(0)
stopifnot(!is.null(parameter))

# define a CFitItem
parameterReference <- parameter$getObject(CCommonName("Reference=Value"))
stopifnot(!is.null(parameterReference))
fitItem2 <- fitProblem$addFitItem(parameterReference$getCN())
stopifnot(!is.null(fitItem2))
invisible(fitItem2$setStartValue(4.0))
invisible(fitItem2$setLowerBound(CCommonName("0.00001")))
invisible(fitItem2$setUpperBound(CCommonName("10")))

result <- TRUE
# running the task for this example will probably take some time
cat("This can take some time...\n")
tryCatch(result <- fitTask$process(TRUE), error = function(e) {
  write("Error. Parameter fitting failed.", stderr())
  quit(save = "default", status = 1, runLast = TRUE)
} )

  
stopifnot(result == TRUE)
# stopifnot(that there are two optimization items)
optItemList <- fitProblem$getOptItemList();
stopifnot(optItemList$size() == 2)
# the order should be the order in whih we added the items above
optItem1 <- fitProblem$getOptItem(0)
optItem2 <- fitProblem$getOptItem(1)
# the actual results are stored in the fit problem
solutionVariables <- fitProblem$getSolutionVariables();
stopifnot(solutionVariables$size() == 2)

cat("value for " , CCommonName_getString(optItem1$getObject()$getCN()) , ": " , solutionVariables$get(0), "\n", sep = "")
cat("value for " , CCommonName_getString(optItem2$getObject()$getCN()) , ": " , solutionVariables$get(1), "\n", sep = "")
# depending on the noise, the fit can be quite bad, so we are a litle
# relaxed here (we should be within 3% of the original values)
stopifnot((abs(solutionVariables$get(0) - 0.03) / 0.03) < 3e-2)
stopifnot((abs(solutionVariables$get(1) - 0.004) / 0.004) < 3e-2)

