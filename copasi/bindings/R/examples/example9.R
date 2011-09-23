#options(echo = FALSE) # disable echoing of input

#  
#  This example is similar to example 8. We also calculate the jacobian,
#  but this time we want the jacobian at the steady state.
#  This is somewhat easier than calculating it manually in the model
#  because the steady state calculates it and we can get an annotated matrix which
#  tells us which coumn and which row represent what.
#  
#  So in this example, we learn how to work with annotated matrices.
#  


# First we load the COPASI package
dyn.load(paste("COPASI", .Platform$dynlib.ext, sep=""))
source("COPASI.R")
# I Don't know exactly what the next line does, but this is what the SWIG
# documentation has to say about it:
# The cacheMetaData(1) will cause R to refresh its object tables. Without it, inheritance of wrapped objects may fail.
cacheMetaData(1)


MODEL_STRING <- '<?xml version="1.0" encoding="UTF-8"?>\n <!-- Created by COPASI version 4.5.31 (Debug) on 2010-05-11 13:40 with libSBML version 4.1.0-b3. -->\n <sbml xmlns="http://www.sbml.org/sbml/level2/version4" level="2" version="4">\n <model metaid="COPASI1" id="Model_1" name="New Model">\n <listOfUnitDefinitions>\n <unitDefinition id="volume" name="volume">\n <listOfUnits>\n <unit kind="litre" scale="-3"/>\n </listOfUnits>\n </unitDefinition>\n <unitDefinition id="substance" name="substance">\n <listOfUnits>\n <unit kind="mole" scale="-3"/>\n </listOfUnits>\n </unitDefinition>\n <unitDefinition id="unit_0">\n <listOfUnits>\n <unit kind="second" exponent="-1"/>\n </listOfUnits>\n </unitDefinition>\n </listOfUnitDefinitions>\n <listOfCompartments>\n <compartment id="compartment_1" name="compartment" size="1"/>\n </listOfCompartments>\n <listOfSpecies>\n <species metaid="COPASI2" id="species_1" name="A" compartment="compartment_1" initialConcentration="1"/>\n <species metaid="COPASI3" id="species_2" name="B" compartment="compartment_1" initialConcentration="0"/>\n <species metaid="COPASI4" id="species_3" name="C" compartment="compartment_1" initialConcentration="0"/>\n </listOfSpecies>\n <listOfReactions>\n <reaction metaid="COPASI5" id="reaction_1" name="reaction_1" reversible="false">\n <listOfReactants>\n <speciesReference species="species_1"/>\n </listOfReactants>\n <listOfProducts>\n <speciesReference species="species_2"/>\n </listOfProducts>\n <kineticLaw>\n <math xmlns="http://www.w3.org/1998/Math/MathML">\n <apply>\n <times/>\n <ci> compartment_1 </ci>\n <ci> k1 </ci>\n <ci> species_1 </ci>\n </apply>\n </math>\n <listOfParameters>\n <parameter id="k1" name="k1" value="0.2" units="unit_0"/>\n </listOfParameters>\n </kineticLaw>\n </reaction>\n <reaction metaid="COPASI6" id="reaction_2" name="reaction_2" reversible="false">\n <listOfReactants>\n <speciesReference species="species_2"/>\n </listOfReactants>\n <listOfProducts>\n <speciesReference species="species_3"/>\n </listOfProducts>\n <kineticLaw>\n <math xmlns="http://www.w3.org/1998/Math/MathML">\n <apply>\n <times/>\n <ci> compartment_1 </ci>\n <ci> k1 </ci>\n <ci> species_2 </ci>\n </apply>\n </math>\n <listOfParameters>\n <parameter id="k1" name="k1" value="0.1" units="unit_0"/>\n </listOfParameters>\n </kineticLaw>\n </reaction>\n </listOfReactions>\n </model>\n </sbml>\n' 

# initialize the backend library
# since we are not interested in the arguments
# that are passed to main, we pass 0 and None to
# init
stopifnot(!is.null(CCopasiRootContainer_getRoot()))
# create a new datamodel
dataModel <- CCopasiRootContainer_addDatamodel()
stopifnot(!is.null(dataModel))
stopifnot(DataModelVector_size(CCopasiRootContainer_getDatamodelList()) == 1)
# next we import a simple SBML model from a string

# clear the message queue so that we only have error messages from the import in the queue
invisible(CCopasiMessage_clearDeque())
result <- TRUE
tryCatch(result <- CCopasiDataModel_importSBMLFromString(dataModel,MODEL_STRING), error = function(e) {
  write("An exception has occured during the import of the SBML model", stderr())
  quit(save = "default", status = 1, runLast = TRUE)
} )

# check if the import was successful
mostSevere <- CCopasiMessage_getHighestSeverity()
# if it was a filtered error, we convert it to an unfiltered type
# the filtered error messages have the same value as the unfiltered, but they
# have the 7th bit set which basically adds 128 to the value
mostSevere <- mostSevere & 127

# we assume that the import succeeded if the return value is TRUE and
# the most severe error message is not an error or an exception
if (result != TRUE &&  mostSevere < CCopasiMessage.ERROR) {
    write("Sorry. Model could not be imported.", stderr())
    quit(save = "default", status = 1, runLast = TRUE)
}

# get the trajectory task object
task <- CCopasiDataModel_getTask(dataModel,"Steady-State")

# if there isn't one
if (is.null(task)) {
    # create a new one
    task <- CSteadyStateTask()
    # add the new task to the task list
    invisible(CCopasiTaskList_addAndOwn(CCopasiDataModel_getTaskList(dataModel),task))
}

invisible(CCopasiMessage_clearDeque())

tryCatch(CSteadyStateTask_process(task,TRUE), error = function(e) {
  write("Error. Running the scan failed.", stderr())
  # check if there are additional error messages
  if (CCopasiMessage_size() > 0) {
      # print the messages in chronological order
      write(CCopasiMessage_getAllMessageText(TRUE), stderr())
  }
  quit(save = "default", status = 1, runLast = TRUE)
} )


# now we can get the result of the steady state calculation, e.g. the jacobian
# matrix of the model at the steady state
# here we can either get the jacobian as we did in example 8 as a matrix with
# getJacobian, or we can use getJacobianAnnotated to get an annotated matrix
# Corresponding methods for the reduced jacobian are getJacobianX and getJacobianXAnnotated
aj <- CSteadyStsteTask_getJacobianAnnotated(task)
stopifnot(!is.null(aj))

if (!is.null(aj)) {
    # we do the output, but as in contrast to the jacobian in example 8,
    # we now have all the information for the output in one place

    # first the array annotation can tell us how many dimensions it has.
    # Since the matrix is a 2D array, it should have 2 dimensions
    stopifnot(CArrayAnnotation_dimensionality(aj) == 2)
    # since the matrix has a dimensionality of 2, the inde for the underlaying abstract array
    # object is a vector with two unsigned int elements
    # First element is the index for the outer dimension and the second element is the index
    # for the inner dimension
    index <- SizeTStdVector(2)
    # since the rows and columns have the same annotation for the jacobian, it doesn't matter
    # for which dimension we get the annotations
    annotations <- CArrayAnnotation_getAnnotationsString(aj,1)
    cat("Jacobian Matrix:\n")
    cat("\n")
    format(" ", width = 7)

    i <- 0
    while (i < StringStdVector_size(annotations)) {
        format(annotations[i], width = 7)
        i <- i + 1
    }
    cat("\n")
    
    i <- 0
    while (i < StringStdVector_size(annotations)) {
        format(annotations[i], width = 7)
        index[0] <- i

        j <- 0
        while (j < StringStdVector_size(annotations)) {
            index[1] <- j
            arr <- CArrayAnnotation_array(aj);
            format(CCopasiAbtractArray_get(arr,index), width = 7, digits = 3)
            j <- j + 1
        }
        cat("\n")
        i <- i + 1
    }
}


