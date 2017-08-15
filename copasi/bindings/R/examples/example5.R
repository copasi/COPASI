#options(echo = FALSE) # disable echoing of input

# 
# This is an example on how to run an optimization task.
# And how to access the result of an optimization.
# 


# First we load the COPASI package
dyn.load(paste("COPASI", .Platform$dynlib.ext, sep=""))
source("COPASI.R")
# I Don't know exactly what the next line does, but this is what the SWIG
# documentation has to say about it:
# The cacheMetaData(1) will cause R to refresh its object tables. Without it, inheritance of wrapped objects may fail.
cacheMetaData(1)

stopifnot(!is.null(CRootContainer_getRoot()))
# create a new datamodel
dataModel <- CRootContainer_addDatamodel()
stopifnot(CRootContainer_getDatamodelList()$size() == 1)
# get the model from the datamodel
model <- dataModel$getModel()
stopifnot(!is.null(model))
invisible(model$setVolumeUnit("fl"))
invisible(model$setTimeUnit("s"))
invisible(model$setQuantityUnit("fMol"))
fixedModelValue <- model$createModelValue("F")
stopifnot(!is.null(fixedModelValue))
invisible(fixedModelValue$setStatus("FIXED"))
invisible(fixedModelValue$setInitialValue(3.0))
variableModelValue <- model$createModelValue("V")
stopifnot(!is.null(variableModelValue))
invisible(variableModelValue$setStatus("ASSIGNMENT"))
# we create a very simple assignment that is easy on the optimization
# a parabole with the minimum at x=6 should do just fine
s <- fixedModelValue$getObject(CCommonName("Reference=Value"))
s <- paste("(<", s$getCN()$getString(), "> - 6.0)^2", sep = "")
invisible(variableModelValue$setExpression(s))
# now we compile the model and tell COPASI which values have changed so
# that COPASI can update the values that depend on those
invisible(model$compileIfNecessary())
changedObjects <- ObjectStdVector()
invisible(changedObjects$push_back(fixedModelValue$getObject(CCommonName("Reference=InitialValue"))))
invisible(changedObjects$push_back(variableModelValue$getObject(CCommonName("Reference=InitialValue"))))
invisible(model$updateInitialValues(changedObjects))

# now we set up the optimization

# we want to do an optimization for the time course
# so we have to set up the time course task first
timeCourseTask <- dataModel$getTask("Time-Course")
stopifnot(!is.null(timeCourseTask))
# since for this example it really doesn't matter how long we run the time course 
# we run for 1 second and calculate 10 steps
# run a deterministic time course
invisible(timeCourseTask$setMethodType("deterministic"))

# get the problem for the task to set some parameters
problem <- as(timeCourseTask$getProblem(), "_p_CTrajectoryProblem")
# pass a pointer of the model to the problem
invisible(problem$setModel(model))
stopifnot(!is.null(problem))

# simulate 10 steps
invisible(problem$setStepNumber(10))
# start at time 0
invisible(model$setInitialTime(0.0))
# simulate a duration of 1 time units
invisible(problem$setDuration(1))
# tell the problem to actually generate time series data
invisible(problem$setTimeSeriesRequested(TRUE))

# get the optimization task
optTask <- dataModel$getTask("Optimization")
stopifnot(!is.null(optTask))
# we want to use Levenberg-Marquardt as the optimization method
invisible(optTask$setMethodType("LevenbergMarquardt"))

# next we need to set subtask type on the problem
optProblem <- as(optTask$getProblem(), "_p_COptProblem")
stopifnot(!is.null(optProblem))
invisible(optProblem$setSubtaskType("timeCourse"))

# we create the objective function
# we want to minimize the value of the variable model value at the end of
# the simulation
# the objective function is normally minimized
objectiveFunction <- variableModelValue$getObject(CCommonName("Reference=Value"))
# we need to put the angled brackets around the common name of the object
objectiveFunction <- paste("<", objectiveFunction$getCN()$getString() ,">", sep = "")
# now we set the objective function in the problem
invisible(optProblem$setObjectiveFunction(objectiveFunction))

# now we create the optimization items
# i.e. the model elements that have to be changed during the optimization
# in order to get to the optimal solution
optItem <- optProblem$addOptItem(fixedModelValue$getObject(CCommonName("Reference=InitialValue"))$getCN())
# we want to change the fixed model value from -100 to +100 with a start
# value of 50
invisible(optItem$setStartValue(50.0))
invisible(optItem$setLowerBound(CCommonName("-100")))
invisible(optItem$setUpperBound(CCommonName("100")))

# now we set some parameters on the method
# these parameters are specific to the method type we set above
# (in this case Levenberg-Marquardt)
optMethod <- optTask$getMethod()
stopifnot(!is.null(optMethod))

# now we set some method parameters for the optimization method
# iteration limit
parameter <- optMethod$getParameter("Iteration Limit")
stopifnot(!is.null(parameter))
invisible(parameter$setIntValue(2000))
# tolerance
parameter <- optMethod$getParameter("Tolerance")
stopifnot(!is.null(parameter))
invisible(parameter$setDblValue(1.0e-5))

# create a report with the correct filename and all the species against
# time.
reports <- dataModel$getReportDefinitionList()
# create a report definition object
report <- reports$createReportDefinition("Report", "Output for optimization")
# set the task type for the report definition to timecourse
invisible(report$setTaskType("optimization"))
# we don't want a table
invisible(report$setIsTable(FALSE))
# the entries in the output should be seperated by a ", "
invisible(report$setSeparator(CCopasiReportSeparator(", ")))

# we need a handle to the header and the body
# the header will display the ids of the metabolites and "time" for
# the first column
# the body will contain the actual timecourse data
header <- report$getHeaderAddr()
body <- report$getBodyAddr()

sep <- report$getSeparator()
sep_string <- sep$getCN()$getString()
# in the report header we write two strings and a separator
s <- CDataString("best value of objective function")$getCN()$getString()
invisible(header$push_back(CRegisteredCommonName(s)))
invisible(header$push_back(CRegisteredCommonName(sep_string)))
s <- CDataString("initial value of F")$getCN()$getString()
invisible(header$push_back(CRegisteredCommonName(s)))
# in the report body we write the best value of the objective function and
# the initial value of the fixed parameter separated by a komma
o <- optProblem$getObject(CCommonName("Reference=Best Value"))
s <- o$getCN()$getString()
invisible(body$push_back(CRegisteredCommonName(s)))
invisible(body$push_back(CRegisteredCommonName(sep_string)))
o <- fixedModelValue$getObject(CCommonName("Reference=InitialValue"))
s <- o$getCN()$getString()
invisible(body$push_back(CRegisteredCommonName(s)))


# set the report for the task
rep <- optTask$getReport()
invisible(rep$setReportDefinition(report))
# set the output filename
invisible(rep$setTarget("example5.txt"))
# don't append output if the file exists, but overwrite the file
invisible(rep$setAppend(FALSE))

result <- FALSE
tryCatch(result <- optTask$process(TRUE), error = function(e) {
  write("Running the optimization failed." , stderr())
  quit(save = "default", status = 1, runLast = TRUE)
} )

if(!result) {
    write("Running the optimization failed." , stderr())
    quit(save = "default", status = 1, runLast = TRUE)
}
# now we check if the optimization actually got the correct result
# the best value it should have is 0 and the best parameter value for
# that result should be 6 for the initial value of the fixed parameter
bestValue <- optProblem$getSolutionValue()
stopifnot(abs(bestValue) < 1e-3)
# we should only have one solution variable since we only have one
# optimization item
stopifnot(optProblem$getSolutionVariables()$size() == 1)
solution <- optProblem$getSolutionVariables()$get(0)
stopifnot(abs((solution-6.0)/6.0) < 1e-3)

