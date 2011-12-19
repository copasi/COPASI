#options(echo = FALSE) # disable echoing of input

# This is an example on how to build models with the COPASI backend API.

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
datamodel_list <- CCopasiRootContainer_getDatamodelList()
stopifnot(DataModelVector_size(datamodel_list) == 1)
# get the model from the datamodel
model <- CCopasiDataModel_getModel(dataModel)
stopifnot(!is.null(model))
# set the units for the model
# we want seconds as the time unit
# microliter as the volume units
# and nanomole as the substance units
invisible(CModel_setTimeUnit(model,'s'))
invisible(CModel_setVolumeUnit(model,'microl'))
invisible(CModel_setQuantityUnit(model,'nMol'))

# we have to keep a set of all the initial values that are changed during
# the model building process
# They are needed after the model has been built to make sure all initial
# values are set to the correct initial value
changedObjects <- ObjectStdVector()

# create a compartment with the name cell and an initial volume of 5.0
# microliter
compartment <- CModel_createCompartment(model,"cell", 5.0)
object <- CCopasiObject_getObject(compartment,CCopasiObjectName("Reference=InitialVolume"))
stopifnot(!is.null(object))
invisible(ObjectStdVector_push_back(changedObjects,object))
stopifnot(!is.null(compartment))
stopifnot(CompartmentVector_size(CModel_getCompartments(model)) == 1)
# create a new metabolite with the name glucose and an inital
# concentration of 10 nanomol
# the metabolite belongs to the compartment we created and is is to be
# fixed
glucose <- CModel_createMetabolite(model,"glucose", CCopasiObject_getObjectName(compartment), 10.0, "FIXED")
stopifnot(!is.null(glucose))
object <- CCopasiObject_getObject(glucose,CCopasiObjectName("Reference=InitialConcentration"))
stopifnot(!is.null(object))
invisible(ObjectStdVector_push_back(changedObjects,object))
stopifnot(MetabVector_size(CModel_getMetabolites(model)) == 1)
# create a second metabolite called glucose-6-phosphate with an initial
# concentration of 0. This metabolite is to be changed by reactions
g6p <- CModel_createMetabolite(model,"glucose-6-phosphate", CCopasiObject_getObjectName(compartment), 0.0, "REACTIONS")
stopifnot(!is.null(g6p))
object <- CCopasiObject_getObject(g6p,CCopasiObjectName("Reference=InitialConcentration"))
stopifnot(!is.null(object))
invisible(ObjectStdVector_push_back(changedObjects,object))
stopifnot(MetabVector_size(CModel_getMetabolites(model)) == 2)
# another metabolite for ATP, also fixed
atp <- CModel_createMetabolite(model,"ATP", CCopasiObject_getObjectName(compartment), 10.0, "FIXED")
stopifnot(!is.null(atp))
object <- CCopasiObject_getObject(atp,CCopasiObjectName("Reference=InitialConcentration"))
stopifnot(!is.null(object))
invisible(ObjectStdVector_push_back(changedObjects,object))
stopifnot(MetabVector_size(CModel_getMetabolites(model)) == 3)
# and one for ADP
adp <- CModel_createMetabolite(model,"ADP", CCopasiObject_getObjectName(compartment), 0.0, "REACTIONS")
stopifnot(!is.null(adp))
object <- CCopasiObject_getObject(adp,CCopasiObjectName("Reference=InitialConcentration"))
stopifnot(!is.null(object))
invisible(ObjectStdVector_push_back(changedObjects,object))
stopifnot(MetabVector_size(CModel_getMetabolites(model)) == 4)
# now we create a reaction
reaction <- CModel_createReaction(model,"hexokinase")
stopifnot(!is.null(reaction))
stopifnot(ReactionVector_size(CModel_getReactions(model)) == 1)
# hexokinase converts glucose and ATP to glucose-6-phosphate and ADP
# we can set these on the chemical equation of the reaction
chemEq <- CReaction_getChemEq(reaction)
# glucose is a substrate with stoichiometry 1
invisible(CChemEq_addMetabolite(chemEq,CCopasiObject_getKey(glucose), 1.0, "SUBSTRATE"))
# ATP is a substrate with stoichiometry 1
invisible(CChemEq_addMetabolite(chemEq,CCopasiObject_getKey(atp), 1.0, "SUBSTRATE"))
# glucose-6-phosphate is a product with stoichiometry 1
invisible(CChemEq_addMetabolite(chemEq,CCopasiObject_getKey(g6p), 1.0, "PRODUCT"))
# ADP is a product with stoichiometry 1
invisible(CChemEq_addMetabolite(chemEq,CCopasiObject_getKey(adp), 1.0, "PRODUCT"))
stopifnot(CChemEqElementVector_size(CChemEq_getSubstrates(chemEq)) == 2)
stopifnot(CChemEqElementVector_size(CChemEq_getProducts(chemEq)) == 2)
# this reaction is to be irreversible
invisible(CReaction_setReversible(reaction,FALSE))
stopifnot(CReaction_isReversible(reaction) == FALSE)
# now we ned to set a kinetic law on the reaction
# maybe constant flux would be OK
# we need to get the function from the function database
funDB <- CCopasiRootContainer_getFunctionList()
stopifnot(!is.null(funDB))
# it should be in the list of suitable functions
# lets get all suitable functions for an irreversible reaction with  2 substrates
# and 2 products
suitableFunctions <- CFunctionDB_suitableFunctions(funDB,2, 2, "TriFalse")
stopifnot(length(suitableFunctions) > 0)
fun <- NULL

index <- 0
maxIndex <- CFunctionStdVector_size(suitableFunctions)
while (index < maxIndex){
    # we just assume that the only suitable function with Constant in
    # it's name is the one we want

    # using the ___getitem__ function looks awkward, but I have not found out how else
    # I can get to the elements of wrapped std::vector instances
    temp_fun <- CFunctionStdVector___getitem__(suitableFunctions,index)
    name=CCopasiObject_getObjectName(temp_fun)
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
    invisible(CReaction_setFunction(reaction,fun))
    stopifnot(!is.null(CReaction_getFunction(reaction)))
    # constant flux has only one function parameter
    invisible(CReaction_getFunctionParameters(reaction))
    stopifnot(CFunctionParameters_size(CReaction_getFunctionParameters(reaction)) == 1)
    # so there should be only one entry in the parameter mapping as well
    stopifnot(length(CReaction_getParameterMappings(reaction)) == 1)
    parameterGroup <- CReaction_getParameters(reaction)
    stopifnot(CCopasiParameterGroup_size(parameterGroup) == 1)
    parameter <- CCopasiParameterGroup_getParameter(parameterGroup, 0)
    # make sure the parameter is a local parameter
    stopifnot(CReaction_isLocalParameter(reaction,CCopasiObject_getObjectName(parameter)))
    stopifnot(CCopasiParameter_getType(parameter) == "DOUBLE")
    # now we set the value of the parameter to 0.5
    invisible(CCopasiParameter_setDblValue(parameter,0.5))
    object <- CCopasiObject_getObject(parameter,CCopasiObjectName("Reference=Value"))
    stopifnot(!is.null(object))
    invisible(ObjectStdVector_push_back(changedObjects,object))
} else{
    write("Error. Could not find a kientic law that contains the term \"Constant\"." , stderr())
    quit(save = "default", status = 1, runLast = TRUE)
}
# now we also create a separate reaction for the backwards reaction and
# set the kinetic law to irreversible mass action
# now we create a reaction
reaction <- CModel_createReaction(model,"hexokinase-backwards")
stopifnot(!is.null(reaction))
stopifnot(ReactionVector_size(CModel_getReactions(model)) == 2)
chemEq <- CReaction_getChemEq(reaction)
# glucose is a product with stoichiometry 1
invisible(CChemEq_addMetabolite(chemEq,CCopasiObject_getKey(glucose), 1.0, "PRODUCT"))
# ATP is a product with stoichiometry 1
invisible(CChemEq_addMetabolite(chemEq,CCopasiObject_getKey(atp), 1.0, "PRODUCT"))
# glucose-6-phosphate is a substrate with stoichiometry 1
invisible(CChemEq_addMetabolite(chemEq,CCopasiObject_getKey(g6p), 1.0, "SUBSTRATE"))
# ADP is a substrate with stoichiometry 1
invisible(CChemEq_addMetabolite(chemEq,CCopasiObject_getKey(adp), 1.0, "SUBSTRATE"))
stopifnot(CChemEqElementVector_size(CChemEq_getSubstrates(chemEq)) == 2)
stopifnot(CChemEqElementVector_size(CChemEq_getProducts(chemEq)) == 2)
# this reaction is to be irreversible
invisible(CReaction_setReversible(reaction,FALSE))
stopifnot(CReaction_isReversible(reaction) == FALSE)
# now we ned to set a kinetic law on the reaction
massAction <- CFunctionDB_findFunction(funDB,"Mass action (irreversible)")
stopifnot(!is.null(massAction))
# we set the function
# the method should be smart enough to associate the reaction entities
# with the correct function parameters

invisible(CReaction_setFunction(reaction,massAction))
stopifnot(!is.null(CReaction_getFunction(reaction)))
stopifnot(CFunctionParameters_size(CReaction_getFunctionParameters(reaction)) == 2)
# so there should be two entries in the parameter mapping as well
###### Somehow this test fails miserably
###### The length function returns 1 as the result and if I use StringStdVector_size
###### instead of length I get 6 as the result.
###### stopifnot(length(CReaction_getParameterMappings(reaction)) == 2)
# mass action is a special case since the parameter mappings for the
# substrates (and products) are in a vector

# Let us create a global parameter that is determined by an assignment
# and that is used as the rate constant of the mass action kinetics
# it gets the name rateConstant and an initial value of 1.56
modelValue <- CModel_createModelValue(model,"rateConstant", 1.56)
stopifnot(!is.null(modelValue))
object <- CCopasiObject_getObject(modelValue,CCopasiObjectName("Reference=InitialValue"))
stopifnot(!is.null(object))
invisible(ObjectStdVector_push_back(changedObjects,object))
stopifnot(ModelValueVector_size(CModel_getModelValues(model)) == 1)
# set the status to assignment
invisible(CModelEntity_setStatus(modelValue,"ASSIGNMENT"))
# the assignment does not have to make sense
invisible(CModelEntity_setExpression(modelValue,"1.0 / 4.0 + 2.0"))

# now we have to adjust the parameter mapping in the reaction so
# that the kinetic law uses the global parameter we just created instead
# of the local one that is created by default
# The first parameter is the one for the rate constant, so we point it to
# the key of out model value
invisible(CReaction_setParameterMapping(reaction,0, CCopasiObject_getKey(modelValue)))
# now we have to set the parameter mapping for the substrates
invisible(CReaction_addParameterMapping(reaction,"substrate", CCopasiObject_getKey(g6p)))
invisible(CReaction_addParameterMapping(reaction,"substrate", CCopasiObject_getKey(adp)))

# finally compile the model
# compile needs to be done before updating all initial values for
# the model with the refresh sequence
invisible(CModel_compileIfNecessary(model))

# now that we are done building the model, we have to make sure all
# initial values are updated according to their dependencies
invisible(CModel_updateInitialValues(model,changedObjects))

# save the model to a COPASI file
# we save to a file named example1.cps, we don't want a progress report
# and we want to overwrite any existing file with the same name
# Default tasks are automatically generated and will always appear in cps
# file unless they are explicitley deleted before saving.
invisible(CCopasiDataModel_saveModel(dataModel,"example1.cps", TRUE))

# export the model to an SBML file
# we save to a file named example1.xml, we want to overwrite any
# existing file with the same name and we want SBML L2V3
invisible(CCopasiDataModel_exportSBML(dataModel,"example1.xml", TRUE, 2, 3))



