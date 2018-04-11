# This is an example on how to build models with the COPASI backend API.
use strict;
use warnings;

use COPASI;

unless(defined(&COPASI::CRootContainer::getRoot())){warn "Assertion failed";die;}
# create a new datamodel
my $dataModel = &COPASI::CRootContainer::addDatamodel();
unless(COPASI::DataModelVector::size(COPASI::CRootContainer::getDatamodelList()) == 1){warn "Assertion failed";die;}
# get the model from the datamodel
my $model = $dataModel->getModel();
unless(defined($model)){warn "Assertion failed";die;}
# set the units for the model
# we want seconds as the time unit
# microliter as the volume units
# and nanomole as the substance units
$model->setTimeUnit($COPASI::CUnit::s);
$model->setVolumeUnit($COPASI::CUnit::microl);
$model->setQuantityUnit($COPASI::CUnit::nMol);

# we have to keep a set of all the initial values that are changed during
# the model building process
# They are needed after the model has been built to make sure all initial
# values are set to the correct initial value
my $changedObjects = new COPASI::ObjectStdVector();

# create a compartment with the name cell and an initial volume of 5.0
# microliter
my $compartment = $model->createCompartment("cell", 5.0);
my $object = $compartment->getObject(new COPASI::CCommonName("Reference=InitialVolume"));
unless(defined($object)){warn "Assertion failed";die;}
$changedObjects->push($object);
unless(defined($compartment)){warn "Assertion failed";die;}
unless($model->getCompartments()->size() == 1){warn "Assertion failed";die;}
# create a new metabolite with the name glucose and an inital
# concentration of 10 nanomol
# the metabolite belongs to the compartment we created and is is to be
# fixed
my $glucose = $model->createMetabolite("glucose", $compartment->getObjectName(), 10.0, $COPASI::CModelEntity::FIXED);
unless(defined($glucose)){warn "Assertion failed";die;}
$object = $glucose->getObject(new COPASI::CCommonName("Reference=InitialConcentration"));
unless(defined($object)){warn "Assertion failed";die;}
$changedObjects->push($object);
unless($model->getMetabolites()->size() == 1){warn "Assertion failed";die;}
# create a second metabolite called glucose-6-phosphate with an initial
# concentration of 0. This metabolite is to be changed by reactions
my $g6p = $model->createMetabolite("glucose-6-phosphate", $compartment->getObjectName(), 0.0, $COPASI::CModelEntity::REACTIONS);
unless(defined($g6p)){warn "Assertion failed";die;}
$object = $g6p->getObject(new COPASI::CCommonName("Reference=InitialConcentration"));
unless(defined($object)){warn "Assertion failed";die;}
$changedObjects->push($object);
unless($model->getMetabolites()->size() == 2){warn "Assertion failed";die;}
# another metabolite for ATP, also fixed
my $atp = $model->createMetabolite("ATP", $compartment->getObjectName(), 10.0, $COPASI::CModelEntity::FIXED);
unless(defined($atp)){warn "Assertion failed";die;};
$object = $atp->getObject(new COPASI::CCommonName("Reference=InitialConcentration"));
unless(defined($object)){warn "Assertion failed";die;}
$changedObjects->push($object);
unless($model->getMetabolites()->size() == 3){warn "Assertion failed";die;}
# and one for ADP
my $adp = $model->createMetabolite("ADP", $compartment->getObjectName(), 0.0, $COPASI::CModelEntity::REACTIONS);
unless(defined($adp)){warn "Assertion failed";die;}
$object = $adp->getObject(new COPASI::CCommonName("Reference=InitialConcentration"));
unless(defined($object)){warn "Assertion failed";die;}
$changedObjects->push($object);
unless($model->getMetabolites()->size() == 4){warn "Assertion failed";die;}
# now we create a reaction
my $reaction = $model->createReaction("hexokinase");
unless(defined($reaction)){warn "Assertion failed";die;}
unless($model->getReactions()->size() == 1){warn "Assertion failed";die;}
# hexokinase converts glucose and ATP to glucose-6-phosphate and ADP
# we can set these on the chemical equation of the reaction
my $chemEq = $reaction->getChemEq();
# glucose is a substrate with stoichiometry 1
$chemEq->addMetabolite($glucose->getKey(), 1.0, $COPASI::CChemEq::SUBSTRATE);
# ATP is a substrate with stoichiometry 1
$chemEq->addMetabolite($atp->getKey(), 1.0, $COPASI::CChemEq::SUBSTRATE);
# glucose-6-phosphate is a product with stoichiometry 1
$chemEq->addMetabolite($g6p->getKey(), 1.0, $COPASI::CChemEq::PRODUCT);
# ADP is a product with stoichiometry 1
$chemEq->addMetabolite($adp->getKey(), 1.0, $COPASI::CChemEq::PRODUCT);
unless($chemEq->getSubstrates()->size() == 2){warn "Assertion failed";die;}
unless($chemEq->getProducts()->size() == 2){warn "Assertion failed";die;}
# this reaction is to be irreversible
$reaction->setReversible("");
unless($reaction->isReversible() eq ""){warn "Assertion failed";die;}
# now we ned to set a kinetic law on the reaction
# maybe constant flux would be OK
# we need to get the function from the function database
my $funDB = COPASI::CRootContainer::getFunctionList();
unless(defined($funDB)){warn "Assertion failed";die;}
# it should be in the list of suitable functions
# lets get all suitable functions for an irreversible reaction with  2 substrates
# and 2 products
# It seems that swig wraps the vector to a real perl array
# Heureka, finally found out that this is not an array, but a reference and that
# this handles differently.
my $suitableFunctions = $funDB->suitableFunctions(2, 2, $COPASI::TriFalse);
unless(@{$suitableFunctions} > 0){warn "Assertion failed";die;}
my $function = '';


foreach my $fun (@{$suitableFunctions}){
    # we just assume that the only suitable function with Constant in
    # it's name is the one we want
    my $name = $fun->getObjectName();
    if((index $name,"Constant") != -1){
        $function=$fun;
        last;
    }
}

if(defined($function)){
    # we set the function
    # the method should be smart enough to associate the reaction entities
    # with the correct function parameters
    $reaction->setFunction($function);
    unless(defined($reaction->getFunction())){warn "Assertion failed";die;}
    # constant flux has only one function parameter
    unless($reaction->getFunctionParameters()->size() == 1){warn "Assertion failed";die;}
    # so there should be only one entry in the parameter mapping as well
    unless($reaction->getParameterMappings()->size() == 1){warn "Assertion failed";die;}
    my $parameterGroup = $reaction->getParameters();
    unless($parameterGroup->size() == 1){warn "Assertion failed";die;}
    my $parameter = $parameterGroup->getParameter(0);
    # make sure the parameter is a local parameter
    unless($reaction->isLocalParameter($parameter->getObjectName())){warn "Assertion failed";die;}
    unless($parameter->getType() == $COPASI::CCopasiParameter::DOUBLE){warn "Assertion failed";die;}
    # now we set the value of the parameter to 0.5
    $parameter->setDblValue(0.5);
    $object = $parameter->getObject(new COPASI::CCommonName("Reference=Value"));
    unless(defined($object)){warn "Assertion failed";die;}
    $changedObjects->push($object);
}
else
{
    warn "Error. Could not find kinetic law that contains the term \"Constant\".";
    die;
}

# now we also create a separate reaction for the backwards reaction and
# set the kinetic law to irreversible mass action
# now we create a reaction
$reaction = $model->createReaction("hexokinase-backwards");
unless(defined($reaction)){warn "Assertion failed";die;}
unless($model->getReactions()->size() == 2){warn "Assertion failed";die;}
$chemEq = $reaction->getChemEq();
# glucose is a product with stoichiometry 1
$chemEq->addMetabolite($glucose->getKey(), 1.0, $COPASI::CChemEq::PRODUCT);
# ATP is a product with stoichiometry 1
$chemEq->addMetabolite($atp->getKey(), 1.0, $COPASI::CChemEq::PRODUCT);
# glucose-6-phosphate is a substrate with stoichiometry 1
$chemEq->addMetabolite($g6p->getKey(), 1.0, $COPASI::CChemEq::SUBSTRATE);
# ADP is a substrate with stoichiometry 1
$chemEq->addMetabolite($adp->getKey(), 1.0, $COPASI::CChemEq::SUBSTRATE);
unless($chemEq->getSubstrates()->size() == 2){warn "Assertion failed";die;}
unless($chemEq->getProducts()->size() == 2){warn "Assertion failed";die;}
# this reaction is to be irreversible
$reaction->setReversible("");
unless($reaction->isReversible() eq ""){warn "Assertion failed";die;}
# now we ned to set a kinetic law on the reaction
my $massAction = $funDB->findFunction("Mass action (irreversible)");
unless(defined($massAction)){warn "Assertion failed";die;}
# we set the function
# the method should be smart enough to associate the reaction entities
# with the correct function parameters
$reaction->setFunction($massAction);
unless(defined($reaction->getFunction())){warn "Assertion failed";die;}

unless($reaction->getFunctionParameters()->size() == 2){warn "Assertion failed";die;}
# so there should be two entries in the parameter mapping as well
unless($reaction->getParameterMappings()->size() == 2){warn "Assertion failed";die;}
# mass action is a special case since the parameter mappings for the
# substrates (and products) are in a vector

# Let us create a global parameter that is determined by an assignment
# and that is used as the rate constant of the mass action kinetics
# it gets the name rateConstant and an initial value of 1.56
my $modelValue = $model->createModelValue("rateConstant", 1.56);
unless(defined($modelValue)){warn "Assertion failed";die;}
$object = $modelValue->getObject(new COPASI::CCommonName("Reference=InitialValue"));
unless(defined($object)){warn "Assertion failed";die;}
$changedObjects->push($object);
unless($model->getModelValues()->size() == 1){warn "Assertion failed";die;}
# set the status to assignment
$modelValue->setStatus($COPASI::CModelEntity::ASSIGNMENT);
# the assignment does not have to make sense
$modelValue->setExpression("1.0 / 4.0 + 2.0");

# now we have to adjust the parameter mapping in the reaction so
# that the kinetic law uses the global parameter we just created instead
# of the local one that is created by default
# The first parameter is the one for the rate constant, so we point it to
# the key of out model value
$reaction->setParameterObject(0, $modelValue);
# now we have to set the parameter mapping for the substrates
$reaction->addParameterObject("substrate", $g6p);
$reaction->addParameterObject("substrate", $adp);

# finally compile the model
# compile needs to be done before updating all initial values for
# the model with the refresh sequence
$model->compileIfNecessary();

# now that we are done building the model, we have to make sure all
# initial values are updated according to their dependencies
$model->updateInitialValues($changedObjects);

# save the model to a COPASI file
# we save to a file named example1.cps, we don't want a progress report
# and we want to overwrite any existing file with the same name
# Default tasks are automatically generated and will always appear in cps
# file unless they are explicitley deleted before saving.
$dataModel->saveModel("example1.cps", 1);

# export the model to an SBML file
# we save to a file named example1.xml, we want to overwrite any
# existing file with the same name and we want SBML L2V3
$dataModel->exportSBML("example1.xml", 1, 2, 3);

