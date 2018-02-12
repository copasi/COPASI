#options(echo = FALSE) # disable echoing of input

#  
#  This is an example on how to calculate and output the Jacobian matrix
#  in COPASI
#  


# First we load the COPASI package
dyn.load(paste("COPASI", .Platform$dynlib.ext, sep=""))
source("COPASI.R")
# I Don't know exactly what the next line does, but this is what the SWIG
# documentation has to say about it:
# The cacheMetaData(1) will cause R to refresh its object tables. Without it, inheritance of wrapped objects may fail.
cacheMetaData(1)

MODEL_STRING <- '<?xml version="1.0" encoding="UTF-8"?><!-- Created by COPASI version4.5.31 (Debug) on 2010-05-11 13:40 with libSBML version 4.1.0-b3. --><sbml xmlns="http://www.sbml.org/sbml/level2/version4" level="2" version="4"><model metaid="COPASI1" id="Model_1" name="New Model"><listOfUnitDefinitions><unitDefinition id="volume" name="volume"><listOfUnits><unit kind="litre" scale="-3"/></listOfUnits></unitDefinition><unitDefinition id="substance" name="substance"><listOfUnits><unit kind="mole" scale="-3"/></listOfUnits></unitDefinition><unitDefinition id="unit_0"><listOfUnits><unit kind="second" exponent="-1"/></listOfUnits></unitDefinition></listOfUnitDefinitions><listOfCompartments><compartment id="compartment_1" name="compartment" size="1"/></listOfCompartments><listOfSpecies><species metaid="COPASI2" id="species_1" name="A" compartment="compartment_1" initialConcentration="1"/><species metaid="COPASI3" id="species_2" name="B" compartment="compartment_1" initialConcentration="0"/><species metaid="COPASI4" id="species_3" name="C" compartment="compartment_1" initialConcentration="0"/></listOfSpecies><listOfReactions><reaction metaid="COPASI5" id="reaction_1" name="reaction_1" reversible="false"><listOfReactants><speciesReference species="species_1"/></listOfReactants><listOfProducts><speciesReference species="species_2"/></listOfProducts><kineticLaw><math xmlns="http://www.w3.org/1998/Math/MathML"><apply><times/><ci> compartment_1 </ci><ci> k1 </ci><ci> species_1 </ci></apply></math><listOfParameters><parameter id="k1" name="k1" value="0.2" units="unit_0"/></listOfParameters></kineticLaw></reaction><reaction metaid="COPASI6" id="reaction_2" name="reaction_2" reversible="false"><listOfReactants><speciesReference species="species_2"/></listOfReactants><listOfProducts><speciesReference species="species_3"/></listOfProducts><kineticLaw><math xmlns="http://www.w3.org/1998/Math/MathML"><apply><times/><ci> compartment_1 </ci><ci> k1 </ci><ci> species_2 </ci></apply></math><listOfParameters><parameter id="k1" name="k1" value="0.1" units="unit_0"/></listOfParameters></kineticLaw></reaction></listOfReactions></model></sbml>'


stopifnot(!is.null(CRootContainer_getRoot()))
# create a new datamodel
dataModel <- CRootContainer_addDatamodel()
stopifnot(!is.null(dataModel))
stopifnot(CRootContainer_getDatamodelList()$size() == 1)
# next we import a simple SBML model from a string

# clear the message queue so that we only have error messages from the import in the queue
invisible(CCopasiMessage_clearDeque())
result <- TRUE
tryCatch(result <- dataModel$importSBMLFromString(MODEL_STRING), error = function(e) {
  write("Import of model failed miserably.", stderr())
  if(CCopasiMessage_size() > 0) {
    write(CCopasiMessage_getAllMessageText(TRUE), stderr())
  }
  quit(save = "default", status = 1, runLast = TRUE)
} )

# check if the import was successful
mostSevere <- CCopasiMessage_getHighestSeverity()
# if it was a filtered error, we convert it to an unfiltered type
# the filtered error messages have the same value as the unfiltered, but they
# have the 7th bit set which basically adds 128 to the value
# Since R maps enums to string, we can't handle it the same way as in the other
# languages
#mostSevere <- mostSevere & 127

# we assume that the import succeeded if the return value is TRUE and
# the most severe error message is not an error or an exception
errorList <- list("RAW","TRACE","COMMANDLINE","WARNING","RAW_FILTERED","TRACE_FILTERED","COMMANDLINE_FILTERED", "WARNING_FILTERED")
if (result != TRUE && any(errorList,mostSevere)) {
    write("Sorry. Model could not be imported.", stderr())
    quit(save = "default", status = 1, runLast = TRUE)
}

#
# now we tell the model object to calculate the jacobian
#
model <- dataModel$getModel()
stopifnot(!is.null(model))

if (!is.null(model)) {
    # running a task, e.g. a trajectory will automatically make sure that
    # the initial values are transferred to the current state before the calculation begins.
    # If we use low level calculation methods like the one to calculate the jacobian, we
    # have to make sure the the initial values are applied to the state
    invisible(model$applyInitialValues())
    # we need an array that stores the result
    # the size of the matrix does not really matter because
    # the calculateJacobian automatically resizes it to the correct
    # size
    jacobian <- FloatMatrix()
    # the first parameter to the calculation function is a reference to
    # the matrix where the result is to be stored
    # the second parameter is the derivationFactor for the calculation
    # it basically represents a relative delta value for the calculation of the derivatives
    # the third parameter termed resolution in the C++ API is currently ignores
    # so it does not matter what value you give here.
    
    container <- model$getMathContainer()
    invisible(container$calculateJacobian(jacobian, 1e-12, FALSE))
   
    # now we print the result
    # the jacobian stores the values in the order they are
    # given in the user order in the state template so it is not really straight
    # forward to find out which column/row corresponds to which species
    stateTemplate <- model$getStateTemplate()
    # and we need the user order
    userOrder <- stateTemplate$getUserOrder()
    # from those two, we can construct an new vector that contains
    # the names of the entities in the jacobian in the order in which they appear in
    # the jacobian
    nameVector <- list()
    entity <- NULL
    status <- -1
    
    i <- 0
    while (i < userOrder$size()) {
        entity <- stateTemplate$getEntity(userOrder$get(i))
        stopifnot(!is.null(entity))
        # now we need to check if the entity is actually
        # determined by an ODE or a reaction
        status <- entity$getStatus()

        if (status == "ODE" || (status == "REACTIONS" && entity$isUsed())) {
            nameVector[[length(nameVector)+1]] <- entity$getObjectName()
        }
        i <- i + 1
    }


    stopifnot(length(nameVector) == jacobian$numRows())
    # now we print the matrix, for this we assume that no
    # entity name is longer then 5 character which is a save bet since
    # we know the model
    cat("Jacobian Matrix:\n")
    cat("\n")
    cat(format(" ", width = 7))

    i <- 1
    while(i <= length(nameVector)) {
        cat(format(nameVector[i], width = 7))
        i <- i + 1
    }

    cat("\n")

    i <- 0
    while( i < length(nameVector)) {
        cat(format(nameVector[i+1], width = 7))
        j <- 0
        while (j < length(nameVector)) {
            cat(format(jacobian$get(i,j), width = 7 , digits = 3))
            j <- j + 1
        }

        cat("\n")
        i <- i + 1
    }

    # we can also calculate the jacobian of the reduced system
    # in a similar way
    invisible(container$calculateJacobian(jacobian, 1e-12, TRUE))
    # this time generating the output is actually simpler because the rows
    # and columns are ordered in the same way as the independent variables of the state temple
    cat("\n")
    cat("\n")
    cat("Reduced Jacobian Matrix:\n")
    cat("\n")
    cat(format(" ", width = 7))
    
    iMax <- stateTemplate$getNumIndependent()
   
    i <- 0
    while (i < iMax) {
       cat(format(stateTemplate$getIndependent(i)$getObjectName(), width = 7))
       i <- i + 1
    }

    cat("\n")

    i <- 0
    while (i < iMax) {
        cat(format(stateTemplate$getIndependent(i)$getObjectName(), width = 7))

        j <- 0
        while (j < iMax) {
            cat(format(jacobian$get(i,j), width = 7 , digits = 3))
            j <- j + 1
        }

        cat("\n")
        i <- i + 1
    }
}
