#
# This is an example on how to create user defined kinetic functions with the COPASI API
#
use strict;
use warnings;

use COPASI;


unless(defined(COPASI::CRootContainer::getRoot())){warn "Assertion failed.\n";die;}
# create a new datamodel
my $dataModel = COPASI::CRootContainer::addDatamodel();
unless(COPASI::CRootContainer::getDatamodelList()->size() == 1){warn "Assertion failed.\n";die;}
# get the model from the datamodel
my $model = $dataModel->getModel();
unless(defined($model)){warn "Assertion failed.\n";die;}
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
unless(defined($object)){warn "Assertion failed.\n";die;}
$changedObjects->push($object);
unless(defined($compartment)){warn "Assertion failed.\n";die;}
unless($model->getCompartments()->size() == 1){warn "Assertion failed.\n";die;}
# create a new metabolite with the name S and an inital
# concentration of 10 nanomol
# the metabolite belongs to the compartment we created and is is to be
# fixed
my $S = $model->createMetabolite("S", $compartment->getObjectName(), 10.0, $COPASI::CModelEntity::FIXED);
$object = $S->getObject(new COPASI::CCommonName("Reference=InitialConcentration"));
unless(defined($object)){warn "Assertion failed.\n";die;}
$changedObjects->push($object);
unless(defined($compartment)){warn "Assertion failed.\n";die;}
unless(defined($S)){warn "Assertion failed.\n";die;}
unless($model->getMetabolites()->size() == 1){warn "Assertion failed.\n";die;}
# create a second metabolite called P with an initial
# concentration of 0. This metabolite is to be changed by reactions
my $P = $model->createMetabolite("P", $compartment->getObjectName(), 0.0, $COPASI::CModelEntity::REACTIONS);
unless(defined($P)){warn "Assertion failed.\n";die;}
$object = $P->getObject(new COPASI::CCommonName("Reference=InitialConcentration"));
unless(defined($object)){warn "Assertion failed.\n";die;}
$changedObjects->push($object);
unless($model->getMetabolites()->size() == 2){warn "Assertion failed.\n";die;}

# now we create a reaction
my $reaction = $model->createReaction("reaction");
unless(defined($reaction)){warn "Assertion failed.\n";die;}
unless($model->getReactions()->size() == 1){warn "Assertion failed.\n";die;}
# reaction converts S to P
# we can set these on the chemical equation of the reaction
my $chemEq = $reaction->getChemEq();
# S is a substrate with stoichiometry 1
$chemEq->addMetabolite($S->getKey(), 1.0, $COPASI::CChemEq::SUBSTRATE);
# P is a product with stoichiometry 1
$chemEq->addMetabolite($P->getKey(), 1.0, $COPASI::CChemEq::PRODUCT);
unless($chemEq->getSubstrates()->size() == 1){warn "Assertion failed.\n";die;}
unless($chemEq->getProducts()->size() == 1){warn "Assertion failed.\n";die;}
# this reaction is to be irreversible
$reaction->setReversible("");
unless(!$reaction->isReversible()){warn "Assertion failed.\n";die;}

my $MV = $model->createModelValue("K", 42.0);
# set the status to FIXED
$MV->setStatus($COPASI::CModelEntity::FIXED);
unless(defined($MV)){warn "Assertion failed.\n";die;}
$object = $MV->getObject(new COPASI::CCommonName("Reference=InitialValue"));
unless(defined($object)){warn "Assertion failed.\n";die;}
$changedObjects->push($object);
unless($model->getModelValues()->size() == 1){warn "Assertion failed.\n";die;}

# now we ned to set a kinetic law on the reaction
# for this we create a user defined function
my $funDB = COPASI::CRootContainer::getFunctionList();
unless(defined($funDB)){warn "Assertion failed.\n";die;}

my $function = $funDB->createFunction("My Rate Law",$COPASI::CEvaluationTree::UserDefined);

my $rateLaw = $funDB->findFunction("My Rate Law");

unless(defined($rateLaw)){warn "Assertion failed.\n";die;}

# now we create the formula for the function and set it on the function
my $formula = "(1-0.4/(EXPONENTIALE^(temp-37)))*0.00001448471257*1.4^(temp-37)*substrate";

my $result = $function->setInfix($formula);

# make the function irreversible
$function->setReversible($COPASI::TriFalse);
# the formula string should have been parsed now
# and COPASI should have determined that the formula string contained 2 parameters (temp and substrate)
my $variables = $function->getVariables();
# per default the usage of those parameters will be set to VARIABLE
my $ind = $function->getVariableIndex("temp");
my $param = $variables->getParameter($ind);
unless($param->getUsage() == $COPASI::CFunctionParameter::VARIABLE){warn "Assertion failed.\n";die;}
# This is correct for temp, but substrate should get the usage SUBSTRATE in order
# for us to use the function with the reaction created above
# So we need to set the usage for "substrate" manually
$ind = $function->getVariableIndex("substrate");
$param = $variables->getParameter($ind);
$param->setUsage($COPASI::CFunctionParameter::SUBSTRATE);

# set the rate law for the reaction
$reaction->setFunction($function);
unless(defined($reaction->getFunction())){warn "Assertion failed.\n";die;}

# COPASI also needs to know what object it has to assocuiate with the individual function parameters
# In our case we need to tell COPASI that substrate is to be replaced by the substrate of the reaction
# and temp is to be replaced by the global parameter K
$reaction->setParameterMapping("substrate", $S->getKey());
$reaction->setParameterMapping("temp", $MV->getKey());

# finally compile the model
# compile needs to be done before updating all initial values for
# the model with the refresh sequence
$model->compileIfNecessary();

# now that we are done building the model, we have to make sure all
# initial values are updated according to their dependencies
$model->updateInitialValues($changedObjects);

# save the model to a COPASI file
# we save to a file named example1.cps 
# and we want to overwrite any existing file with the same name
# Default tasks are automatically generated and will always appear in cps
# file unless they are explicitley deleted before saving.
$dataModel->saveModel("example7.cps", 1);

# export the model to an SBML file
# we save to a file named example1.xml, we want to overwrite any
# existing file with the same name and we want SBML L2V3
eval {
  $dataModel->exportSBML("example7.xml", 1, 2, 3);
} or do {
   warn "Error. Exporting the model to SBML failed.\n";
   die;
};



