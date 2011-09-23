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

stopifnot(!is.null(CCopasiRootContainer_getRoot()))
# create a new datamodel
dataModel <- CCopasiRootContainer_addDatamodel()
stopifnot(DataModelVector_size(CCopasiRootContainer_getDatamodelList()) == 1)
# get the model from the datamodel
model <- CCopasiDataModel_getModel(dataModel)
stopifnot(!is.null(model))
CModel_setVolumeUnit(model,"fl")
CModel_setTimeUnit(model,"s")
CModel_setQuantityUnit(model,"fMol")
fixedModelValue <- CModel_createModelValue(model,"F")
stopifnot(!is.null(fixedModelValue))
CModelEntity_setStatus(fixedModelValue,"FIXED")
CModelEntity_setInitialValue(fixedModelValue,3.0);   
variableModelValue <- CModel_createModelValue(model,"V")
stopifnot(!is.null(variableModelValue))
CModelEntity_setStatus(variableModelValue,"ASSIGNMENT")
# we create a very simple assignment that is easy on the optimization
# a parabole with the minimum at x=6 should do just fine
s <- CCopasiContainer_getObject(fixedModelValue,CCopasiObjectName("Reference=Value"))
s <- paste("(<", s, "> - 6.0)^2")
CModelEntity_setExpression(variableModelValue,s)
# now we compile the model and tell COPASI which values have changed so
# that COPASI can update the values that depend on those
CModel_compileIfNecessary(model)
changedObjects <- ObjectStdVector()
ObjectStdVector_push_back(changedObjects,CCopasiContainer_getObject(fixedModelValue,CCopasiObjectName("Reference=InitialValue")))
ObjectStdVector_push_back(changedObjects,CCopasiContainer_getObject(variableModelValue,CCopasiObjectName("Reference=InitialValue")))
CModel_updateInitialValues(model,changedObjects)

# now we set up the optimization

# we want to do an optimization for the time course
# so we have to set up the time course task first
timeCourseTask <- CCopasiDataModel_getTask(dataModel,"Time-Course")
stopifnot(!is.null(timeCourseTask))
# since for this example it really doesn't matter how long we run the time course 
# we run for 1 second and calculate 10 steps
# run a deterministic time course
CTrajectoryTask_setMethodType(timeCourseTask,"deterministic")

# get the problem for the task to set some parameters
problem <- timeCourseTask_getProblem(timeCourseTask)
# pass a pointer of the model to the problem
CTrajectoryProblem_setModel(problem,model)
stopifnot(!is.null(problem))

# simulate 10 steps
CTrajectoryProblem_setStepNumber(problem,10)
# start at time 0
CModel_setInitialTime(model, 0.0)
# simulate a duration of 1 time units
CTrajectoryProblem_setDuration(problem,1)
# tell the problem to actually generate time series data
CTrajectoryProblem_setTimeSeriesRequested(problem,TRUE)

# get the optimization task
optTask <- CCopasiDataModel_getTask(dataModel,"Optimization")
stopifnot(!is.null(optTask))
# we want to use Levenberg-Marquardt as the optimization method
COptTask_setMethodType(optTask,"LevenbergMarquardt")

# next we need to set subtask type on the problem
optProblem <- COptTask_getProblem(optTask)
stopifnot(!is.null(optProblem))
COptProblem_setSubtaskType(optProblem,"timeCourse")

# we create the objective function
# we want to minimize the value of the variable model value at the end of
# the simulation
# the objective function is normally minimized
objectiveFunction <- CCopasiContainer_getObject(variableModelValue,CCopasiObjectName("Reference=Value"))
# we need to put the angled brackets around the common name of the object
objectiveFunction <- paste("<", objectiveFunction ,">")
# now we set the objective function in the problem
COptProblem_setObjectiveFunction(optProblem,objectiveFunction)

# now we create the optimization items
# i.e. the model elements that have to be changed during the optimization
# in order to get to the optimal solution
optItem <- COptProblem_addOptItem(optProblem,CCopasiObjectName_getCN((CCopasiObject_getObject(fixedModelValue,CCopasiObjectName("Reference=InitialValue")))))
# we want to change the fixed model value from -100 to +100 with a start
# value of 50
COptItem_setStartValue(optItem,50.0)
COptItem_setLowerBound(optItem,CCopasiObjectName("-100"))
COptItem_setUpperBound(optItem,CCopasiObjectName("100"))

# now we set some parameters on the method
# these parameters are specific to the method type we set above
# (in this case Levenberg-Marquardt)
COptMethod <- COptTask_getMethod(optTask)
stopifnot(!is.null(optMethod))

# now we set some method parameters for the optimization method
# iteration limit
parameter <- CCopasiParameterGroup_getParameter(optMethod,"Iteration Limit")
stopifnot(!is.null(parameter))
CCopasiParameter_setIntValue(parameter,2000)
# tolerance
parameter <- CCopasiParameterGroup_getParameter(optMethod,"Tolerance")
stopifnot(!is.null(parameter))
CCopasiParameter_setDblValue(parameter,1.0e-5)

# create a report with the correct filename and all the species against
# time.
reports <- CCopasiDataModel_getReportDefinitionList(dataModel)
# create a report definition object
report <- ReportDefinitionVector_createReportDefinition(reports,"Report", "Output for optimization")
# set the task type for the report definition to timecourse
CReportDefinition_setTaskType(report,"optimization")
# we don't want a table
CReportDefinition_setIsTable(report,FALSE)
# the entries in the output should be seperated by a ", "
CReportDefinition_setSeparator(report,CCopasiReportSeparator(", "))

# we need a handle to the header and the body
# the header will display the ids of the metabolites and "time" for
# the first column
# the body will contain the actual timecourse data
header <- CReportDefinition_getHeaderAddr(report)
body <- CReportDefinition_getBodyAddr(report)

sep <- CReportDefinition_getSeparator(report)
sep_string <- CCopasiObjectName_getString(CCopasiObject_getCN(sep))
# in the report header we write two strings and a separator
s <- CCopasiObjectName_getString(CCopasiObject_getCN(CCopasiStaticString("best value of objective function")))
header.push_back(CRegisteredObjectName(s))
header.push_back(CRegisteredObjectName(sep_string))
s <- CCopasiObjectName_getString(CCopasiObject_getCN(CCopasiStaticString("initial value of F")))
header.push_back(CRegisteredObjectName(s))
# in the report body we write the best value of the objective function and
# the initial value of the fixed parameter separated by a komma
o <- COptProblem_getObject(optProblem,CCopasiObjectName("Reference=Best Value"))
s <- CCopasiObjectName_getString(CCopasiObject_getCN(o))
body.push_back(CRegisteredObjectName(s))
body.push_back(CRegisteredObjectName(sep_string))
o <- CCopasiContainer_getObject(fixedModelValue,CCopasiObjectName("Reference=InitialValue"))
s <- CCopasiObjectName_getString(CCopasiObject_getCN(o))
body.push_back(CRegisteredObjectName(s))


# set the report for the task
rep <- COptTask_getReport(optTask)
CReport_setReportDefinition(rep,report)
# set the output filename
CReport_setTarget(rep, "example5.txt")
# don't append output if the file exists, but overwrite the file
CReport_setAppend(rep, FALSE)

result <- FALSE
tryCatch(result <- COptTask_process(optTask,TRUE), error = function(e) {
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
bestValue <- COptProblem_getSolutionValue(optProblem)
stopifnot(abs(bestValue) < 1e-3)
# we should only have one solution variable since we only have one
# optimization item
stopifnot(FloatVectorCore_size(COptProblem_getSolutionVariables(optProblem)) == 1)
solution <- FloatVectorCore_get(COptProblem_getSolutionVariables(optProblem),0)
stopifnot(abs((solution-6.0)/6.0) < 1e-3)

