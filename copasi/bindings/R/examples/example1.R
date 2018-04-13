#options(echo = FALSE) # disable echoing of input

# This is an example on how to build models with the COPASI backend API.

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
datamodel_list <- CRootContainer_getDatamodelList()
stopifnot(datamodel_list$size() == 1)
# get the model from the datamodel
model <- dataModel$getModel()
stopifnot(!is.null(model))
# set the units for the model
# we want seconds as the time unit
# microliter as the volume units
# and nanomole as the substance units
invisible(model$setTimeUnit('s'))
invisible(model$setVolumeUnit('microl'))
invisible(model$setQuantityUnit('nMol'))

# we have to keep a set of all the initial values that are changed during
# the model building process
# They are needed after the model has been built to make sure all initial
# values are set to the correct initial value
changedObjects <- ObjectStdVector()

# create a compartment with the name cell and an initial volume of 5.0
# microliter
compartment <- model$createCompartment("cell", 5.0)
object <- compartment$getObject(CCommonName("Reference=InitialVolume"))
stopifnot(!is.null(object))
invisible(changedObjects$push_back(object))
stopifnot(!is.null(compartment))
stopifnot(model$getCompartments()$size() == 1)
# create a new metabolite with the name glucose and an inital
# concentration of 10 nanomol
# the metabolite belongs to the compartment we created and is is to be
# fixed
glucose <- model$createMetabolite("glucose", compartment$getObjectName(), 10.0, "FIXED")
stopifnot(!is.null(glucose))
object <- glucose$getObject(CCommonName("Reference=InitialConcentration"))
stopifnot(!is.null(object))
invisible(changedObjects$push_back(object))
stopifnot(model$getMetabolites()$size() == 1)
# create a second metabolite called glucose-6-phosphate with an initial
# concentration of 0. This metabolite is to be changed by reactions
g6p <- model$createMetabolite("glucose-6-phosphate", compartment$getObjectName(), 0.0, "REACTIONS")
stopifnot(!is.null(g6p))
object <- g6p$getObject(CCommonName("Reference=InitialConcentration"))
stopifnot(!is.null(object))
invisible(changedObjects$push_back(object))
stopifnot(model$getMetabolites()$size() == 2)
# another metabolite for ATP, also fixed
atp <- model$createMetabolite("ATP", compartment$getObjectName(), 10.0, "FIXED")
stopifnot(!is.null(atp))
object <- atp$getObject(CCommonName("Reference=InitialConcentration"))
stopifnot(!is.null(object))
invisible(changedObjects$push_back(object))
stopifnot(model$getMetabolites()$size() == 3)
# and one for ADP
adp <- model$createMetabolite("ADP", compartment$getObjectName(), 0.0, "REACTIONS")
stopifnot(!is.null(adp))
object <- adp$getObject(CCommonName("Reference=InitialConcentration"))
stopifnot(!is.null(object))
invisible(changedObjects$push_back(object))
stopifnot(model$getMetabolites()$size() == 4)
# now we create a reaction
reaction <- model$createReaction("hexokinase")
stopifnot(!is.null(reaction))
stopifnot(model$getReactions()$size() == 1)
# hexokinase converts glucose and ATP to glucose-6-phosphate and ADP
# we can set these on the chemical equation of the reaction
chemEq <- reaction$getChemEq()
# glucose is a substrate with stoichiometry 1
invisible(chemEq$addMetabolite(glucose$getKey(), 1.0, "SUBSTRATE"))
# ATP is a substrate with stoichiometry 1
invisible(chemEq$addMetabolite(atp$getKey(), 1.0, "SUBSTRATE"))
# glucose-6-phosphate is a product with stoichiometry 1
invisible(chemEq$addMetabolite(g6p$getKey(), 1.0, "PRODUCT"))
# ADP is a product with stoichiometry 1
invisible(chemEq$addMetabolite(adp$getKey(), 1.0, "PRODUCT"))
stopifnot(chemEq$getSubstrates()$size() == 2)
stopifnot(chemEq$getProducts()$size() == 2)
# this reaction is to be irreversible
invisible(reaction$setReversible(FALSE))
stopifnot(reaction$isReversible() == FALSE)
# now we ned to set a kinetic law on the reaction
# maybe constant flux would be OK
# we need to get the function from the function database
funDB <- CRootContainer_getFunctionList()
stopifnot(!is.null(funDB))
# it should be in the list of suitable functions
# lets get all suitable functions for an irreversible reaction with  2 substrates
# and 2 products
suitableFunctions <- funDB$suitableFunctions(2, 2, "TriFalse")
stopifnot(length(suitableFunctions) > 0)
fun <- NULL

index <- 0
maxIndex <- suitableFunctions$size()
while (index < maxIndex){
    # we just assume that the only suitable function with Constant in
    # it's name is the one we want

    # using the ___getitem__ function looks awkward, but I have not found out how else
    # I can get to the elements of wrapped std::vector instances
    temp_fun <- suitableFunctions[index][[1]]
    name=temp_fun$getObjectName()
    if (length(grep("Constant",name)) != 0) {
        fun <- temp_fun
        break
    }
    index <- index + 1    
}        
if (!is.null(fun)){
    # we set the function
    # the method should be smart enough to associate the reaction entities
    # with the correct function parameters
    invisible(reaction$setFunction(fun))
    stopifnot(!is.null(reaction$getFunction()))
    # constant flux has only one function parameter
    invisible(reaction$getFunctionParameters())
    stopifnot(reaction$getFunctionParameters()$size() == 1)
    # so there should be only one entry in the parameter mapping as well
    stopifnot(length(reaction$getParameterCNs()) == 1)
    parameterGroup <- reaction$getParameters()
    stopifnot(parameterGroup$size() == 1)
    parameter <- parameterGroup$getParameter(0)
    # make sure the parameter is a local parameter
    stopifnot(reaction$isLocalParameter(parameter$getObjectName()))
    stopifnot(parameter$getType() == "DOUBLE")
    # now we set the value of the parameter to 0.5
    invisible(parameter$setDblValue(0.5))
    object <- parameter$getObject(CCommonName("Reference=Value"))
    stopifnot(!is.null(object))
    invisible(changedObjects$push_back(object))
} else{
    write("Error. Could not find a kientic law that contains the term \"Constant\"." , stderr())
    quit(save = "default", status = 1, runLast = TRUE)
}
# now we also create a separate reaction for the backwards reaction and
# set the kinetic law to irreversible mass action
# now we create a reaction
reaction <- model$createReaction("hexokinase-backwards")
stopifnot(!is.null(reaction))
stopifnot(model$getReactions()$size() == 2)
chemEq <- reaction$getChemEq()
# glucose is a product with stoichiometry 1
invisible(chemEq$addMetabolite(glucose$getKey(), 1.0, "PRODUCT"))
# ATP is a product with stoichiometry 1
invisible(chemEq$addMetabolite(atp$getKey(), 1.0, "PRODUCT"))
# glucose-6-phosphate is a substrate with stoichiometry 1
invisible(chemEq$addMetabolite(g6p$getKey(), 1.0, "SUBSTRATE"))
# ADP is a substrate with stoichiometry 1
invisible(chemEq$addMetabolite(adp$getKey(), 1.0, "SUBSTRATE"))
stopifnot(chemEq$getSubstrates()$size() == 2)
stopifnot(chemEq$getProducts()$size() == 2)
# this reaction is to be irreversible
invisible(reaction$setReversible(FALSE))
stopifnot(reaction$isReversible() == FALSE)
# now we ned to set a kinetic law on the reaction
massAction <- funDB$findFunction("Mass action (irreversible)")
stopifnot(!is.null(massAction))
# we set the function
# the method should be smart enough to associate the reaction entities
# with the correct function parameters

invisible(reaction$setFunction(massAction))
stopifnot(!is.null(reaction$getFunction()))
stopifnot(reaction$getFunctionParameters()$size() == 2)
# so there should be two entries in the parameter mapping as well
###### Somehow this test fails miserably
###### The length function returns 1 as the result and if I use StringStdVector_size
###### instead of length I get 6 as the result.
###### stopifnot(length(reaction$getParameterMappings()) == 2)
# mass action is a special case since the parameter mappings for the
# substrates (and products) are in a vector

# Let us create a global parameter that is determined by an assignment
# and that is used as the rate constant of the mass action kinetics
# it gets the name rateConstant and an initial value of 1.56
modelValue <- model$createModelValue("rateConstant", 1.56)
stopifnot(!is.null(modelValue))
object <- modelValue$getObject(CCommonName("Reference=InitialValue"))
stopifnot(!is.null(object))
invisible(changedObjects$push_back(object))
stopifnot(model$getModelValues()$size() == 1)
# set the status to assignment
invisible(modelValue$setStatus("ASSIGNMENT"))
# the assignment does not have to make sense
invisible(modelValue$setExpression("1.0 / 4.0 + 2.0"))

# now we have to adjust the parameter mapping in the reaction so
# that the kinetic law uses the global parameter we just created instead
# of the local one that is created by default
# The first parameter is the one for the rate constant, so we point it to
# the key of out model value
invisible(reaction$setParameterObject(0, modelValue))
# now we have to set the parameter mapping for the substrates
invisible(reaction$addParameterObject("substrate", g6p))
invisible(reaction$addParameterObject("substrate", adp))

# finally compile the model
# compile needs to be done before updating all initial values for
# the model with the refresh sequence
invisible(model$compileIfNecessary())

# now that we are done building the model, we have to make sure all
# initial values are updated according to their dependencies
invisible(model$updateInitialValues(changedObjects))

# save the model to a COPASI file
# we save to a file named example1.cps, we don't want a progress report
# and we want to overwrite any existing file with the same name
# Default tasks are automatically generated and will always appear in cps
# file unless they are explicitley deleted before saving.
invisible(dataModel$saveModel("example1.cps", TRUE))

# export the model to an SBML file
# we save to a file named example1.xml, we want to overwrite any
# existing file with the same name and we want SBML L2V3
invisible(dataModel$exportSBML("example1.xml", TRUE, 2, 3))



