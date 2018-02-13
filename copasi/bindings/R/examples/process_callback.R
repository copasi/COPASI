#
# This example registers a callback handler, 
# so that when an R interrupt is registered
# the running COPASI task will react immediately 
# to interrupts.
#
# Usage: R --slave -f process_callback.R --args <input-filename>
#


# First we load the COPASI package
dyn.load(paste("COPASI", .Platform$dynlib.ext, sep=""))
source("COPASI.R")
cacheMetaData(1)

dataModel <- CRootContainer_addDatamodel()
args <- commandArgs(trailingOnly = TRUE)
# stop if we don't have any arguments
if (length(args) != 1) {
  stop("Need one argument, the COPASI filename to run.")
}

# load teh model
filename <- args[1]
tryCatch(invisible(dataModel$loadModel(filename)), error = function(e) {
  write(paste("Error while loading the model from file named \"" , filename , "\"."), stderr())
  quit(save = "default", status = 1, runLast = TRUE)
} )

# setup callback with a timeout of 1000
# change this value as needed to setup the maximum
# time allotted before the operation will be stopped (0 to disable)
cb <- RProcessCallback(1000)
    
# get tasks 
taskList <- (dataModel$getTaskList())
i <- 0
# iterate through tasks
while ( i < taskList$size())
{
  task <- dataModel$getTask(i)

  if (is.null(task))
  {
    # skip invalid tasks
    i <- i + 1
    next
  }

  if (!task$isScheduled())
  {
    # skip tasks that are not scheduled
    i <- i + 1
    next
  }

  print(paste("Running Scheduled Task: ",task$getObjectName()," stop anytime using CTRL+C | R interrupt"))
  # set callback 
  task$setCallBack(cb)
  # run task
  task$process(TRUE)
  # reset callback 
  task$clearCallBack()
  i <- i + 1
  
}

print("done...")