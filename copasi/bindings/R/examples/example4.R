#options(echo = FALSE) # disable echoing of input

# 
# This is an example on how to import an sbml file
# create a report for a time course simulation 
# and run a scan for a stochastic time course simulation
# 


# First we load the COPASI package
dyn.load(paste("COPASI", .Platform$dynlib.ext, sep=""))
source("COPASI.R")
# I Don't know exactly what the next line does, but this is what the SWIG
# documentation has to say about it:
# The cacheMetaData(1) will cause R to refresh its object tables. Without it, inheritance of wrapped objects may fail.
cacheMetaData(1)

MODEL_STRING <- '<?xml version="1.0" encoding="UTF-8"?><!-- Created by COPASI version 4.4.29 (Debug) on 2009-03-05 14:41 with libSBML version 3.3.0. --><sbml xmlns="http://www.sbml.org/sbml/level2/version3" level="2" version="3"><model metaid="COPASI1" id="Model_1" name="New Model"> <listOfUnitDefinitions><unitDefinition id="volume"><listOfUnits><unit kind="litre" scale="-6"/></listOfUnits></unitDefinition><unitDefinition id="substance"><listOfUnits><unit kind="mole" scale="-9"/></listOfUnits></unitDefinition></listOfUnitDefinitions><listOfCompartments><compartment id="compartment_1" name="compartment" size="1"/></listOfCompartments><listOfSpecies><species metaid="COPASI2" id="species_1" name="A" compartment="compartment_1" initialConcentration="1e-10"></species><species metaid="COPASI3" id="species_2" name="B" compartment="compartment_1" initialConcentration="0"></species><species metaid="COPASI4" id="species_3" name="C" compartment="compartment_1" initialConcentration="0"></species></listOfSpecies><listOfReactions><reaction id="reaction_1" name="reaction" reversible="false"><listOfReactants><speciesReference species="species_1"/></listOfReactants><listOfProducts><speciesReference species="species_2"/></listOfProducts><kineticLaw><math xmlns="http://www.w3.org/1998/Math/MathML"><apply><times/><ci> compartment_1 </ci><ci> k1 </ci><ci> species_1 </ci></apply></math><listOfParameters><parameter id="k1" value="0.1"/></listOfParameters></kineticLaw></reaction><reaction id="reaction_2" name="reaction_1" reversible="false"><listOfReactants><speciesReference species="species_2"/></listOfReactants><listOfProducts><speciesReference species="species_3"/></listOfProducts><kineticLaw><math xmlns="http://www.w3.org/1998/Math/MathML"><apply><times/><ci> compartment_1 </ci><ci> k1 </ci><ci> species_2 </ci></apply></math><listOfParameters><parameter id="k1" value="0.1"/></listOfParameters></kineticLaw></reaction></listOfReactions></model></sbml>'


stopifnot(!is.null(CCopasiRootContainer_getRoot()))
# create a datamodel
dataModel <- CCopasiRootContainer_addDatamodel()
stopifnot(DataModelVector_size(CCopasiRootContainer_getDatamodelList()) == 1)
# the only argument to the main routine should be the name of an SBML file
tryCatch(CCopasiDataModel_importSBMLFromString(dataModel,MODEL_STRING), error = function(e) {
  write("Error while importing the model from given string.", stderr())
  quit(save = "default", status = 1, runLast = TRUE)
} )

model <- CCopasiDataModel_getModel(dataModel)
stopifnot(!is.null(model))
# create a report with the correct filename and all the species against
# time.
reports <- CCopasiDataModel_getReportDefinitionList(dataModel)
# create a report definition object
report <- CReportDefinitionVector_createReportDefinition(reports,"Report", "Output for timecourse")
# set the task type for the report definition to timecourse
invisible(CReportDefinition_setTaskType(report,"timeCourse"))
# we don't want a table
invisible(CReportDefinition_setIsTable(report,FALSE))
# the entries in the output should be seperated by a ", "
invisible(CReportDefinition_setSeparator(report,CCopasiReportSeparator(", ")))

# we need a handle to the header and the body
# the header will display the ids of the metabolites and "time" for
# the first column
# the body will contain the actual timecourse data
sep <- CReportDefinition_getSeparator(report)
sep_string <- CCopasiObjectName_getString(CCopasiObject_getCN(sep))
header <- CReportDefinition_getHeaderAddr(report)
body <- CReportDefinition_getBodyAddr(report)
time_string <- CCopasiObjectName_getString(CCopasiObjectName(paste(CCopasiObjectName_getString(CCopasiObject_getCN(model)), ",Reference=Time", sep = "")))
invisible(ReportItemVector_push_back(body,CRegisteredObjectName(time_string)))
invisible(ReportItemVector_push_back(body,CRegisteredObjectName(sep_string)))
time_string <- CCopasiObjectName_getString(CCopasiObject_getCN(CCopasiStaticString("time")))
invisible(ReportItemVector_push_back(header,CRegisteredObjectName(time_string)))
invisible(ReportItemVector_push_back(header,CRegisteredObjectName(sep_string)))

iMax <- MetabVector_size(CModel_getMetabolites(model))
i <- 0
while (i < iMax) {
    metab <- CModel_getMetabolite(model,i)
    stopifnot(!is.null(metab))
    # we don't want output for FIXED metabolites right now
    if (CModelEntity_getStatus(metab) != "FIXED") {
        # we want the concentration in the output
        # alternatively, we could use "Reference=Amount" to get the
        # particle number
        conc <- CCopasiContainer_getObject(metab, CCopasiObjectName("Reference=Concentration"))
        conc_string <- CCopasiObjectName_getString(CCopasiObject_getCN(conc))
        invisible(ReportItemVector_push_back(body,CRegisteredObjectName(conc_string)))
        # add the corresponding id to the header
        sbml_id <- CModelEntity_getSBMLId(metab)
        sbml_string <- CCopasiObjectName_getString(CCopasiObject_getCN(CCopasiStaticString(sbml_id)))
        invisible(ReportItemVector_push_back(header,CRegisteredObjectName(sbml_string)))
        
        if (i != iMax-1) {
          # after each entry, we need a seperator
          invisible(ReportItemVector_push_back(body,CRegisteredObjectName(sep_string)))

          # and a seperator
          invisible(ReportItemVector_push_back(header,CRegisteredObjectName(sep_string)))
        }
    }
    i <- i + 1
}

# get the trajectory task object
trajectoryTask <- CCopasiDataModel_getTask(dataModel,"Time-Course")
stopifnot(!is.null(trajectoryTask))
# if there isn't one
if (is.null(trajectoryTask)) {
    # create a one
    trajectoryTask <- CTrajectoryTask()
    # add the time course task to the task list
    # this method makes sure the object is now owned by the list
    # and that SWIG does not delete it
    invisible(CCopasiTaskList_addAndOwn(CCopasiDataModel_getTaskList(dataModel), trajectoryTask))
}


# run a stochastic time course
invisible(CTrajectoryTask_setMethodType(trajectoryTask,"stochastic"))

# get the problem for the task to set some parameters
problem <- CCopasiTask_getProblem(trajectoryTask)

# pass a pointer of the model to the problem
invisible(CCopasiProblem_setModel(problem,model))

# we don't want the trajectory task to run by itself, but we want to
# run it from a scan, so we deactivate the standalone trajectory task
invisible(CCopasiTask_setScheduled(trajectoryTask,FALSE))

# simulate 100 steps
invisible(CTrajectoryProblem_setStepNumber(problem,100))
# start at time 0
invisible(CModel_setInitialTime(model,0.0))
# simulate a duration of 10 time units
invisible(CTrajectoryProblem_setDuration(problem,10))
# tell the problem to actually generate time series data
invisible(CTrajectoryProblem_setTimeSeriesRequested(problem,TRUE))

# now we set up the scan
scanTask <- CCopasiDataModel_getTask(dataModel,"Scan")
stopifnot(!is.null(scanTask))
if (is.null(scanTask)) {
    # create a scan task
    scanTask <- CScanTask()
    # add the scan task
    # this method makes sure the object is now owned by the list
    # and that SWIG does not delete it
    invisible(CCopasiTaskList_addAndOwn(CCopasiDataModel_getTaskList(dataModel),scanTask))
}

# get the problem
scanProblem <- CCopasiTask_getProblem(scanTask)
stopifnot(!is.null(scanProblem))

# set the model for the problem
invisible(CCopasiProblem_setModel(scanProblem,model))

# activate the task so that is is run
# if the model is saved and passed to CopasiSE
invisible(CCopasiTask_setScheduled(scanTask,TRUE))

# set the report for the task
invisible(CReport_setReportDefinition(CCopasiTask_getReport(scanTask), report))

# set the output file for the report
invisible(CReport_setTarget(CCopasiTask_getReport(scanTask), "example4.txt"))
# don't append to an existing file, but overwrite
invisible(CReport_setAppend(CCopasiTask_getReport(scanTask,),FALSE))

# tell the scan that we want to make a scan over a trajectory task
invisible(CScanProblem_setSubtask(scanProblem,"timeCourse"))

# we just want to run the timecourse task a number of times, so we
# create a repeat item with 100 repeats
invisible(CScanProblem_createScanItem(scanProblem,"SCAN_REPEAT", 100))

# we want the output from the trajectory task
invisible(CScanProblem_setOutputInSubtask(scanProblem,TRUE))

# we don't want to set the initial conditions of the model to the end
# state of the last run
invisible(CScanProblem_setAdjustInitialConditions(scanProblem,FALSE))

tryCatch(CScanTask_process(scanTask,TRUE), error = function(e) {
  write("Error. Running the scan failed.", stderr())
  # check if there are additional error messages
  if (CCopasiMessage_size() > 0) {
      # print the messages in chronological order
      write(CCopasiMessage_getAllMessageText(TRUE), stderr())
  }
  quit(save = "default", status = 1, runLast = TRUE)
} )


