#
# This is an example on how to load a cps file
# and output some information on the model
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
# the only argument to the main routine should be the name of a CPS file
args <- commandArgs(trailingOnly = TRUE)
if (length(args) == 1) {
    filename <- args
    # load the model without progress report
   
    # I have no clue how exception handling in R works
    tryCatch(CCopasiDataModel_loadModel(dataModel,filename), error = function(e) {
      write(paste("Error while loading the model from file named \"" , filename , "\"."), stderr())
      quit(save = "default", status = 1, runLast = TRUE)
    } )

    model <- CCopasiDataModel_getModel(dataModel)
    stopifnot(!is.null(model))
    print(paste('Model statistics for model "' , CCopasiObject_getObjectName(model) , '".'))

    # output number and names of all compartments
    iMax <- CompartmentVector_size(CModel_getCompartments(model))
    print(paste("Number of Compartments: " , iMax))
    print("Compartments: ")
    i <- 0
    while ( i < iMax) {
        compartment <- CModel_getCompartment(model,i)
        stopifnot(!is.null(compartment))
        print(paste("    " , CCopasiObject_getObjectName(compartment)))
        i <- i + 1
    }
    # output number and names of all metabolites
    iMax <- MetabVector_size(CModel_getMetabolites(model))
    print(paste("Number of Metabolites: " , iMax))
    print("Metabolites: ")
    i <- 0
    while (i < iMax) {
        metab <- CModel_getMetabolite(model,i)
        stopifnot(!is.null(metab))
        print(paste("    " , CCopasiObject_getObjectName(metab)))
        i <- i + 1
    }
    # output number and names of all reactions
    iMax <- ReactionVector_size(CModel_getReactions(model))
    print("Number of Reactions: " , iMax)
    print("Reactions: ")
    i <- 0
    while ( i < iMax) {
        reaction <- CModel_getReaction(model,i)
        stopifnot(!is.null(reaction))
        print(paste("    " , CCopasiObject_getObjectName(reaction)))
        i <- i + 1
    }
} else {
    write( "Usage: example2 CPSFILE", stderr())
    quit(save = "default", status = 1, runLast = TRUE)
}


