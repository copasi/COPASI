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

stopifnot(!is.null(CRootContainer_getRoot()))
# create a datamodel
dataModel <- CRootContainer_addDatamodel()
stopifnot(CRootContainer_getDatamodelList()$size() == 1)
# the only argument to the main routine should be the name of an SBML file
args <- commandArgs(trailingOnly = TRUE)
if (length(args) == 1) {
    filename <- args[1]
    tryCatch(dataModel$importSBML(filename), error = function(e) {
      write(paste("Error while importing the model from file named \"" , filename , "\"."), stderr())
      quit(save = "default", status = 1, runLast = TRUE)
    } )

    model <- dataModel$getModel()
    stopifnot(!is.null(model))
    # create a report with the correct filename and all the species against
    # time.
    reports <- dataModel$getReportDefinitionList()
    # create a report definition object
    report <- reports$createReportDefinition("Report", "Output for timecourse")
    # set the task type for the report definition to timecourse
    invisible(report$setTaskType("timeCourse"))
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

    cn <- model$getCN()
    stopifnot(!is.null(cn))
    cn_string <- cn$getString()
    stopifnot(!is.null(cn_string))
    
    cn_string <- paste(cn_string,",Reference=Time", sep = "")
    on <- CRegisteredCommonName(cn_string)
    stopifnot(!is.null(on))
    invisible(body$push_back(on))

    separator <- report$getSeparator()
    stopifnot(!is.null(separator))
    cn <- separator$getCN()
    stopifnot(!is.null(cn))
    cn_string <- cn$getString()
    sep_on <- CRegisteredCommonName(cn_string)
    stopifnot(!is.null(on))
    invisible(body$push_back(sep_on))

    s <- CDataString("time")
    stopifnot(!is.null(s))
    cn <- s$getCN()
    stopifnot(!is.null(cn))
    cn_string <- cn$getString()
    on <- CRegisteredCommonName(cn_string)
    stopifnot(!is.null(on))

    invisible(header$push_back(on))
    invisible(header$push_back(sep_on))
   
    iMax <- model$getMetabolites()$size()
    i <- 0
    while ( i < iMax ) {
        metab <- model$getMetabolite(i)
        stopifnot(!is.null(metab))
        # we don't want output for FIXED metabolites right now
        if (metab$getStatus() != "FIXED") {
            # we want the concentration in the output
            # alternatively, we could use "Reference=Amount" to get the
            # particle number
            # We could probably just concatenate the string to get the common name for
            # the particle number, but in this case, we get the object and get its common name
            obj <- CDataContainer_getObject(metab , CCommonName("Reference=Concentration"))
            cn <- obj$getCN()
            cn_string <- cn$getString()
            on <- CRegisteredCommonName(cn_string)
            invisible(body$push_back(on))
            # add the corresponding id to the header
            s <- CDataString(metab$getSBMLId())
            cn <- s$getCN()
            cn_string <- cn$getString()
            on <- CRegisteredCommonName(cn_string)
            invisible(header$push_back(on))
            # after each entry, we need a seperator
            if( i != (iMax-1) ) {
              invisible(body$push_back(sep_on))
              invisible(header$push_back(sep_on))
            }
        }
        i <- i + 1
    }
    # get the trajectory task object
    trajectoryTask <- as(dataModel$getTask("Time-Course"), "_p_CTrajectoryTask")
    # if there isn't one
    if (is.null(trajectoryTask)) {
        # create a one
        trajectoryTask <- CTrajectoryTask()
        # add the time course task to the task list
        # this method makes sure the object is now owned by the list
        # and that SWIG does not delete it
        invisible(dataModel$getTaskList()$addAndOwn(trajectoryTask))
    }

    # run a deterministic time course
    invisible(trajectoryTask$setMethodType("deterministic"))

    # pass a pointer of the model to the problem
    # Most problem classes have their own method for setting the model, the trajectory task
    # seems to be the exception.
    # I guess it is the complex tasks that have the method reimplemented because they also need
    # to set the model on the subtask
    
    # get the problem for the task to set some parameters
    problem <- as(trajectoryTask$getProblem(), "_p_CTrajectoryProblem")
    invisible(problem$setModel(dataModel$getModel()))

    # actiavate the task so that it will be run when the model is saved
    # and passed to CopasiSE
    invisible(trajectoryTask$setScheduled(TRUE))

    # set the report for the task
    invisible(trajectoryTask$getReport()$setReportDefinition(report))
    # set the output filename
    invisible(trajectoryTask$getReport()$setTarget("example3.txt"))
    # don't append output if the file exists, but overwrite the file
    invisible(trajectoryTask$getReport()$setAppend(FALSE))

    # simulate 100 steps
    invisible(problem$setStepNumber(100))
    # start at time 0
    invisible(dataModel$getModel()$setInitialTime(0.0))
    # simulate a duration of 10 time units
    invisible(problem$setDuration(10))
    # tell the problem to actually generate time series data
    invisible(problem$setTimeSeriesRequested(TRUE))

    # set some parameters for the LSODA method through the method
    method <- trajectoryTask$getMethod()

    parameter <- method$getParameter("Absolute Tolerance")
    stopifnot(!is.null(parameter))
    stopifnot(parameter$getType() == "UDOUBLE")
    invisible(parameter$setDblValue(1.0e-12))

    result <- TRUE
    invisible(CCopasiMessage_clearDeque())
    # now we run the actual trajectory
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
        write("Error. Running the time course simulation failed.", stderr())
        # check if there are additional error messages
        if (CCopasiMessage_size() > 0) {
            # print(the messages in chronological order)
            write(CCopasiMessage_getAllMessageText(TRUE), stderr())
        }
        quit(save = "default", status = 1, runLast = TRUE)
    }

    # look at the timeseries
    timeSeries <- trajectoryTask$getTimeSeries()
    # we simulated 100 steps, including the initial state, this should be
    # 101 step in the timeseries
    numSteps <- timeSeries$getRecordedSteps()
    stopifnot(numSteps == 101)
    cat("The time series consists of " , numSteps , ".\n", sep = "")
    cat("Each step contains " , timeSeries$getNumVariables() , " variables.\n", sep = "")
    cat("The final state is: \n")
    iMax <- timeSeries$getNumVariables()
    lastIndex <- numSteps - 1
    i <- 0
    while ( i < iMax) {
        # here we get the particle number (at least for the species)
        # the unit of the other variables may not be particle numbers
        # the concentration data can be acquired with getConcentrationData
        cat(timeSeries$getTitle(i) , ": " , timeSeries$getData(lastIndex, i),"\n", sep = "")
        i <- i + 1
    }
} else{
    write("Usage: example3 SBMLFILE", stderr())
    quit(save = "default", status = 1, runLast = TRUE)
}

