#options(echo = FALSE) # disable echoing of input

# 
# This is an example on how to import an sbml file
# create a report for a time course simulation 
# and run a time course simulation
# 


# First we load the COPASI package
dyn.load(paste("COPASI", .Platform$dynlib.ext, sep=""))
source("COPASI.R")
# I Don't know exactly what the next line does, but this is what the SWIG
# documentation has to say about it:
# The cacheMetaData(1) will cause R to refresh its object tables. Without it, inheritance of wrapped objects may fail.
cacheMetaData(1)

stopifnot(!is.null(CCopasiRootContainer_getRoot()))
# create a datamodel
dataModel <- CCopasiRootContainer_addDatamodel()
stopifnot(DataModelVector_size(CCopasiRootContainer_getDatamodelList()) == 1)
# the only argument to the main routine should be the name of an SBML file
args <- commandArgs(trailingOnly = TRUE)
if (length(args) == 1) {
    filename <- args[1]
    tryCatch(CCopasiDataModel_importSBML(dataModel,filename), error = function(e) {
      write(paste("Error while importing the model from file named \"" , filename , "\"."), stderr())
      quit(save = "default", status = 1, runLast = TRUE)
    } )

    model <- CCopasiDataModel_getModel(dataModel)
    stopifnot(!is.null(model))
    # create a report with the correct filename and all the species against
    # time.
    reports <- CCopasiDataModel_getReportTemplateList(dataModel)
    # create a report template object
    report <- CReportTemplateVector_createReportTemplate(reports, "Report", "Output for timecourse")
    # set the task type for the report template to timecourse
    invisible(CReportTemplate_setTaskType(report,"timeCourse"))
    # we don't want a table
    invisible(CReportTemplate_setIsTable(report,FALSE))
    # the entries in the output should be seperated by a ", "
    invisible(CReportTemplate_setSeparator(report, CCopasiReportSeparator(", ")))

    # we need a handle to the header and the body
    # the header will display the ids of the metabolites and "time" for
    # the first column
    # the body will contain the actual timecourse data
    header <- CReportTemplate_getHeaderAddr(report)
    body <- CReportTemplate_getBodyAddr(report)

    cn <- CCopasiObject_getCN(model)
    stopifnot(!is.null(cn))
    cn_string <- CCopasiObjectName_getString(cn)
    stopifnot(!is.null(cn_string))
    
    cn_string <- paste(cn_string,",Reference=Time", sep = "")
    on <- CRegisteredObjectName(cn_string)
    stopifnot(!is.null(on))
    invisible(ReportItemVector_push_back(body, on))

    separator <- CReportTemplate_getSeparator(report)
    stopifnot(!is.null(separator))
    cn <- CCopasiObject_getCN(separator)
    stopifnot(!is.null(cn))
    cn_string <- CCopasiObjectName_getString(cn)
    sep_on <- CRegisteredObjectName(cn_string)
    stopifnot(!is.null(on))
    invisible(ReportItemVector_push_back(body, sep_on))

    s <- CCopasiStaticString("time")
    stopifnot(!is.null(s))
    cn <- CCopasiObject_getCN(s)
    stopifnot(!is.null(cn))
    cn_string <- CCopasiObjectName_getString(cn)
    on <- CRegisteredObjectName(cn_string)
    stopifnot(!is.null(on))

    invisible(ReportItemVector_push_back(header,on))
    invisible(ReportItemVector_push_back(header,sep_on))
   
    iMax <- MetabVector_size(CModel_getMetabolites(model))
    i <- 0
    while ( i < iMax ) {
        metab <- CModel_getMetabolite(model, i)
        stopifnot(!is.null(metab))
        # we don't want output for FIXED metabolites right now
        if (CModelEntity_getStatus(metab) != "FIXED") {
            # we want the concentration in the output
            # alternatively, we could use "Reference=Amount" to get the
            # particle number
            # We could probably just concatenate the string to get the common name for
            # the particle number, but in this case, we get the object and get its common name
            obj <- CCopasiContainer_getObject(metab , CCopasiObjectName("Reference=Concentration"))
            cn <- CCopasiObject_getCN(obj)
            cn_string <- CCopasiObjectName_getString(cn)
            on <- CRegisteredObjectName(cn_string)
            invisible(ReportItemVector_push_back(body,on))
            # add the corresponding id to the header
            s <- CCopasiStaticString(CModelEntity_getSBMLId(metab))
            cn <- CCopasiObject_getCN(s)
            cn_string <- CCopasiObjectName_getString(cn)
            on <- CRegisteredObjectName(cn_string)
            invisible(ReportItemVector_push_back(header, on))
            # after each entry, we need a seperator
            if( i != (iMax-1) ) {
              invisible(ReportItemVector_push_back(body, sep_on))
              invisible(ReportItemVector_push_back(header, sep_on))
            }
        }
        i <- i + 1
    }
    # get the trajectory task object
    trajectoryTask <- CCopasiDataModel_getTask(dataModel,"Time-Course")
    # if there isn't one
    if (is.null(trajectoryTask)) {
        # create a one
        trajectoryTask <- CTrajectoryTask()
        # add the time course task to the task list
        # this method makes sure the object is now owned by the list
        # and that SWIG does not delete it
        invisible(CCopasiTaskList_addAndOwn(CCopasiDataModel_getTaskList(dataModel),trajectoryTask))
    }

    # run a deterministic time course
    invisible(CTrajectoryTask_setMethodType(trajectoryTask, "deterministic"))

    # pass a pointer of the model to the problem
    # Most problem classes have their own method for setting the model, the trajectory task
    # seems to be the exception.
    # I guess it is the complex tasks that have the method reimplemented because they also need
    # to set the model on the subtask
    
    # get the problem for the task to set some parameters
    problem <- CCopasiTask_getProblem(trajectoryTask)
    invisible(CCopasiProblem_setModel(problem,CCopasiDataModel_getModel(dataModel)))

    # actiavate the task so that it will be run when the model is saved
    # and passed to CopasiSE
    invisible(CCopasiTask_setScheduled(trajectoryTask,TRUE))

    # set the report for the task
    invisible(CReport_setReportTemplate(CCopasiTask_getReport(trajectoryTask),report))
    # set the output filename
    invisible(CReport_setTarget(CCopasiTask_getReport(trajectoryTask),"example3.txt"))
    # don't append output if the file exists, but overwrite the file
    invisible(CReport_setAppend(CCopasiTask_getReport(trajectoryTask),FALSE))

    # simulate 100 steps
    invisible(CTrajectoryProblem_setStepNumber(problem,100))
    # start at time 0
    invisible(CModel_setInitialTime(CCopasiDataModel_getModel(dataModel),0.0))
    # simulate a duration of 10 time units
    invisible(CTrajectoryProblem_setDuration(problem, 10))
    # tell the problem to actually generate time series data
    invisible(CTrajectoryProblem_setTimeSeriesRequested(problem, TRUE))

    # set some parameters for the LSODA method through the method
    method <- CCopasiTask_getMethod(trajectoryTask)

    parameter <- CCopasiParameterGroup_getParameter(method,"Absolute Tolerance")
    stopifnot(!is.null(parameter))
    stopifnot(CCopasiParameter_getType(parameter) == "UDOUBLE")
    invisible(CCopasiParameter_setDblValue(parameter, 1.0e-12))

    result <- TRUE
    invisible(CCopasiMessage_clearDeque())
    # now we run the actual trajectory
    tryCatch(result <- CCopasiTask_process(trajectoryTask,TRUE), error = function(e) {
      write("Error. Running the time course simulation failed.", stderr())
      # check if there are additional error messages
      if (CCopasiMessage_size() > 0) {
          # print the messages in chronological order
          write(CCopasiMessage_getAllMessageText(TRUE), stderr())
      }
      quit(save = "default", status = 1, runLast = TRUE)
    } )

    if (result == FALSE) {
        write("Error. Running the time course simulation failed.", stderr())
        # check if there are additional error messages
        if (CCopasiMessage_size() > 0) {
            # print(the messages in chronological order)
            write(CCopasiMessage_getAllMessageText(TRUE), stderr())
        }
        quit(save = "default", status = 1, runLast = TRUE)
    }

    # look at the timeseries
    timeSeries <- CTrajectoryTask_getTimeSeries(trajectoryTask)
    # we simulated 100 steps, including the initial state, this should be
    # 101 step in the timeseries
    numSteps <- CTimeSeries_getRecordedSteps(timeSeries)
    stopifnot(numSteps == 101)
    cat("The time series consists of " , numSteps , ".\n", sep = "")
    cat("Each step contains " , CTimeSeries_getNumVariables(timeSeries) , " variables.\n", sep = "")
    cat("The final state is: \n")
    iMax <- CTimeSeries_getNumVariables(timeSeries)
    lastIndex <- numSteps - 1
    i <- 0
    while ( i < iMax) {
        # here we get the particle number (at least for the species)
        # the unit of the other variables may not be particle numbers
        # the concentration data can be acquired with getConcentrationData
        cat(CTimeSeries_getTitle(timeSeries,i) , ": " , CTimeSeries_getData(timeSeries, lastIndex, i),"\n", sep = "")
        i <- i + 1
    }
} else{
    write("Usage: example3 SBMLFILE", stderr())
    quit(save = "default", status = 1, runLast = TRUE)
}

