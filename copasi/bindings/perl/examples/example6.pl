# 
# This is an example on how to run an parameter fitting task.
# The example creates a simple model and runs a time course simulation on it.
# The timecourse data is written to file with some noise added to it.
# This data is used to fit the original parameters.
# 
use strict;
use warnings;

use COPASI;

my $MODEL_STRING = <<END;
<?xml version="1.0" encoding="UTF-8"?>
<!-- Created by COPASI version 4.5.30 (Debug) on 2009-03-30 08:01 with libSBML version 3.3.2. -->
<sbml xmlns="http:#www.sbml.org/sbml/level2" level="2" version="1">
  <model metaid="COPASI1" id="Model_1" name="Model">
    <listOfUnitDefinitions>
      <unitDefinition id="volume">
        <listOfUnits>
          <unit kind="litre" scale="-3"/>
        </listOfUnits>
      </unitDefinition>
      <unitDefinition id="substance">
        <listOfUnits>
          <unit kind="mole" scale="-3"/>
        </listOfUnits>
      </unitDefinition>
    </listOfUnitDefinitions>
    <listOfCompartments>
      <compartment id="compartment_1" name="compartment" size="1"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="species_1" name="A" compartment="compartment_1" initialConcentration="5"/>
      <species id="species_2" name="B" compartment="compartment_1" initialConcentration="0"/>
      <species id="species_3" name="C" compartment="compartment_1" initialConcentration="0"/>
    </listOfSpecies>
    <listOfReactions>
      <reaction id="reaction_1" name="reaction" reversible="">
        <listOfReactants>
          <speciesReference species="species_1"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="species_2"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http:#www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> compartment_1 </ci>
              <ci> k1 </ci>
              <ci> species_1 </ci>
            </apply>
          </math>
          <listOfParameters>
            <parameter id="k1" name="k1" value="0.03"/>
          </listOfParameters>
        </kineticLaw>
      </reaction>
      <reaction id="reaction_2" name="reaction_1" reversible="">
        <listOfReactants>
          <speciesReference species="species_2"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="species_3"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http:#www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> compartment_1 </ci>
              <ci> k1 </ci>
              <ci> species_2 </ci>
            </apply>
          </math>
          <listOfParameters>
            <parameter id="k1" name="k1" value="0.004"/>
          </listOfParameters>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>
END

unless(defined(COPASI::CRootContainer::getRoot())){warn "Assertion failed";die;}
# create a datamodel
my $dataModel = COPASI::CRootContainer::addDatamodel();
unless(COPASI::CRootContainer::getDatamodelList()->size() == 1){warn "Assertion failed";die;}
# first we load a simple model
eval {
  # load the model 
  $dataModel->importSBMLFromString($MODEL_STRING);
} or do {
  warn "Error while importing the model.\n";
  die;
};

# now we need to run some time course simulation to get data to fit
# against

# get the trajectory task object
my $trajectoryTask = $dataModel->getTask("Time-Course");
unless(defined($trajectoryTask)){warn "Assertion failed";die;}
# if there isn't one
if (!defined($trajectoryTask)) {
    # create a one
    $trajectoryTask = new COPASI::CTrajectoryTask();

    # add the time course task to the task list
    # this method makes sure that the object is now owned 
    # by the list and that it does not get deleted by SWIG
    $dataModel->getTaskList()->addAndOwn($trajectoryTask);
}

# run a deterministic time course
$trajectoryTask->setMethodType($COPASI::CCopasiMethod::deterministic);

# pass a pointer of the model to the problem
$trajectoryTask->getProblem()->setModel($dataModel->getModel());

# activate the task so that it will be run when the model is saved
# and passed to CopasiSE
$trajectoryTask->setScheduled(1);

# get the problem for the task to set some parameters
my $problem = $trajectoryTask->getProblem();

# simulate 4000 steps
$problem->setStepNumber(4000);
# start at time 0
$dataModel->getModel()->setInitialTime(0.0);
# simulate a duration of 400 time units
$problem->setDuration(400);
# tell the problem to actually generate time series data
$problem->setTimeSeriesRequested(1);

# set some parameters for the LSODA method through the method
my $method = $trajectoryTask->getMethod();

my $result=1;
eval {
    # now we run the actual trajectory
    $result=$trajectoryTask->process(1);
} or do {
    warn "Error. Running the time course simulation failed.\n";
    # check if there are additional error messages
    if (COPASI::CCopasiMessage::size() > 0) {
        # print the messages in chronological order
        warn COPASI::CCopasiMessage::getAllMessageText(1) , "\n";
    }
    die;
};

if (! $result) {
    warn "An error occured while running the time course simulation.\n";
    # check if there are additional error messages
    if (COPASI::CCopasiMessage::size() > 0) {
        # print the messages in chronological order
        warn COPASI::CCopasiMessage::getAllMessageText(1), "\n";
    }
    die;
}

# we write the data to a file and add some noise to it
# This is necessary since COPASI can only read experimental data from
# file.
my $timeSeries = $trajectoryTask->getTimeSeries();
# we simulated 100 steps, including the initial state, this should be
# 101 step in the timeseries
unless($timeSeries->getRecordedSteps() == 4001){warn "Assertion failed";die;}
my $iMax = $timeSeries->getNumVariables();
# there should be four variables, the three metabolites and time
unless($iMax == 5){warn "Assertion failed";die;}
my $lastIndex = $timeSeries->getRecordedSteps() - 1;
# open the file
# we need to remember in which order the variables are written to file
# since we need to specify this later in the parameter fitting task
my @indexSet=();
my @metabVector=();

# write the header
# the first variable in a time series is a always time, for the rest
# of the variables, we use the SBML id in the header
my $random=0.0;
open(OS,">fakedata_example6.txt");
print OS "# time ";
my $keyFactory=COPASI::CRootContainer::getKeyFactory();
unless(defined($keyFactory)){warn "Assertion failed";die;}
for (my $i=0;$i < $iMax;$i++) {
  my $key=$timeSeries->getKey($i);
  my $object=$keyFactory->get($key);
  unless(defined($object)){warn "Assertion failed";die;}
  # only write header data or metabolites
  if ($object->isa('COPASI::CMetab')) {
    print OS ", ";
    print OS $timeSeries->getSBMLId($i,$dataModel);
    push(@indexSet,$i);
    push(@metabVector,$object);
  }
};
print OS "\n";
my $data=0.0;
for (my $i=0;$i < $lastIndex;$i++) {
  my $s = "";
  for (my $j=0; $j < $iMax; $j++) {
    # we only want to  write the data for metabolites
    # the compartment does not interest us here
    # This is probably not perlish, but I am going to manually search
    # whether j is present in @indexSet
    my $found = "";
    foreach my $element (@indexSet) {
        if($element == $j) {
            $found=1;
        }
    };
    if (($j == 0) || $found) {
      #  # write the data with some noise (+-5% max)
      $random=rand();
      $data = $timeSeries->getConcentrationData($i, $j);
      # don't add noise to the time
      if ($j != 0) {
        $data += $data * ($random * 0.1 - 0.05);
      }
      $s = $s . "$data" . ", ";
    }
  }
  # remove the last two characters again
  print OS substr($s,0,length($s) - 2);
  print OS "\n";
};
close(OS);

# now we change the parameter values to see if the parameter fitting
# can really find the original values
$random=rand()*10;
my $reaction=$dataModel->getModel()->getReaction(0);
# we know that it is an irreversible mass action, so there is one
# parameter
unless($reaction->getParameters()->size() == 1){warn "Assertion failed";die;}
unless($reaction->isLocalParameter(0)){warn "Assertion failed";die;}
# the parameter of a irreversible mass action is called k1
$reaction->setParameterValue("k1",$random);

$reaction=$dataModel->getModel()->getReaction(1);
# we know that it is an irreversible mass action, so there is one
# parameter
unless($reaction->getParameters()->size() == 1){warn "Assertion failed";die;}
unless($reaction->isLocalParameter(0)){warn "Assertion failed";die;}
$reaction->setParameterValue("k1",$random);

my $fitTask=$dataModel->addTask($COPASI::CCopasiTask::parameterFitting);
unless(defined($fitTask)){warn "Assertion failed";die;}
# the method in a fit task is an instance of COptMethod or a subclass of
# it.
my $fitMethod=$fitTask->getMethod();
unless(defined($fitMethod)){warn "Assertion failed";die;}
# the object must be an instance of COptMethod or a subclass thereof
# (CFitMethod)
my $fitProblem=$fitTask->getProblem();
unless(defined($fitProblem)){warn "Assertion failed";die;}

my $experimentSet=$fitProblem->getParameter("Experiment Set");
unless(defined($experimentSet)){warn "Assertion failed";die;}

# first experiment (we only have one here)
my $experiment=new COPASI::CExperiment($dataModel);
unless(defined($experiment)){warn "Assertion failed";die;}
# tell COPASI where to find the data
# reading data from string is not possible with the current C++ API
$experiment->setFileName("fakedata_example6.txt");
# we have to tell COPASI that the data for the experiment is a komma
# separated list (the default is TAB separated)
$experiment->setSeparator(",");
# the data start in row 1 and goes to row 4001
$experiment->setFirstRow(1);
unless($experiment->getFirstRow()==1){warn "Assertion failed";die;}
$experiment->setLastRow(4001);
unless($experiment->getLastRow()==4001){warn "Assertion failed";die;}
$experiment->setHeaderRow(1);
unless($experiment->getHeaderRow()==1){warn "Assertion failed";die;}
$experiment->setExperimentType($COPASI::CCopasiTask::timeCourse);
unless($experiment->getExperimentType() == $COPASI::CCopasiTask::timeCourse){warn "Assertion failed";die;}
$experiment->setNumColumns(4);
unless($experiment->getNumColumns()==4){warn "Assertion failed";die;}
my $objectMap=$experiment->getObjectMap();
unless(defined($objectMap)){warn "Assertion failed";die;}
$result=$objectMap->setNumCols(4);
unless($result == 1){warn "Assertion failed";die;}
$result=$objectMap->setRole(0,$COPASI::CExperiment::time);
unless($result == 1){warn "Assertion failed";die;}
unless($objectMap->getRole(0) == $COPASI::CExperiment::time){warn "Assertion failed";die;}

my $model=$dataModel->getModel();
unless(defined($model)){warn "Assertion failed";die;}
my $timeReference=$model->getObject(new COPASI::CCommonName("Reference=Time"));
unless(defined($timeReference)){warn "Assertion failed";die;}
$objectMap->setObjectCN(0,$timeReference->getCN()->getString());

# now we tell COPASI which column contain the concentrations of
# metabolites and belong to dependent variables
$objectMap->setRole(1,$COPASI::CExperiment::dependent);
my $metab=$metabVector[0];
unless(defined($metab)){warn "Assertion failed";die;}
my $particleReference=$metab->getObject(new COPASI::CCommonName("Reference=Concentration"));
unless(defined($particleReference)){warn "Assertion failed";die;}
$objectMap->setObjectCN(1,$particleReference->getCN()->getString());

$objectMap->setRole(2,$COPASI::CExperiment::dependent);
$metab=$metabVector[1];
unless(defined($metab)){warn "Assertion failed";die;}
$particleReference=$metab->getObject(new COPASI::CCommonName("Reference=Concentration"));
unless(defined($particleReference)){warn "Assertion failed";die;}
$objectMap->setObjectCN(2,$particleReference->getCN()->getString());

$objectMap->setRole(3,$COPASI::CExperiment::dependent);
$metab=$metabVector[2];
unless(defined($metab)){warn "Assertion failed";die;}
$particleReference=$metab->getObject(new COPASI::CCommonName("Reference=Concentration"));
unless(defined($particleReference)){warn "Assertion failed";die;}
$objectMap->setObjectCN(3,$particleReference->getCN()->getString());

$experimentSet->addExperiment($experiment);
unless($experimentSet->getExperimentCount()==1){warn "Assertion failed";die;}
# addExperiment makes a copy, so we need to get the added experiment
# again
$experiment=$experimentSet->getExperiment(0);
unless(defined($experiment)){warn "Assertion failed";die;}

# now we have to define the two fit items for the two local parameters
# of the two reactions
$reaction=$model->getReaction(0);
unless(defined($reaction)){warn "Assertion failed";die;}
unless($reaction->isLocalParameter(0) == 1){warn "Assertion failed";die;}
my $parameter = $reaction->getParameters()->getParameter(0);
unless(defined($parameter)){warn "Assertion failed";die;}

# define a CFitItem
my $parameterReference=$parameter->getObject(new COPASI::CCommonName("Reference=Value"));
unless(defined($parameterReference)){warn "Assertion failed";die;}
my $fitItem1=new COPASI::CFitItem($dataModel);
unless(defined($fitItem1)){warn "Assertion failed";die;}
$fitItem1->setObjectCN($parameterReference->getCN());
$fitItem1->setStartValue(4.0);
$fitItem1->setLowerBound(new COPASI::CCommonName("0.00001"));
$fitItem1->setUpperBound(new COPASI::CCommonName("10"));
# add the fit item to the correct parameter group
my $optimizationItemGroup=$fitProblem->getParameter("OptimizationItemList");
unless(defined($optimizationItemGroup)){warn "Assertion failed";die;}
$optimizationItemGroup->addParameter($fitItem1);

$reaction=$model->getReaction(1);
unless(defined($reaction)){warn "Assertion failed";die;}
unless($reaction->isLocalParameter(0)==1){warn "Assertion failed";die;}
$parameter=$reaction->getParameters()->getParameter(0);
unless(defined($parameter)){warn "Assertion failed";die;}

# define a CFitItem
$parameterReference=$parameter->getObject(new COPASI::CCommonName("Reference=Value"));
unless(defined($parameterReference)){warn "Assertion failed";die;}
my $fitItem2=new COPASI::CFitItem($dataModel);
unless(defined($fitItem2)){warn "Assertion failed";die;}
$fitItem2->setObjectCN($parameterReference->getCN());
$fitItem2->setStartValue(4.0);
$fitItem2->setLowerBound(new COPASI::CCommonName("0.00001"));
$fitItem2->setUpperBound(new COPASI::CCommonName("10"));
# add the fit item to the correct parameter group
$optimizationItemGroup->addParameter($fitItem2);

$result=1;
eval {
  # running the task for this example will probably take some time
  print "This can take some time...\n";
  $result=$fitTask->process(1);
}
or do {
  warn "Error. Parameter fitting failed.\n";
  die;
};

unless($result == 1){warn "Assertion failed";die;}
# unless(that there are two optimization items){warn "Assertion failed";die;}
unless($fitProblem->getOptItemList()->size() == 2){warn "Assertion failed";die;}
# the order should be the order in which we added the items above
my $optItemList = $fitProblem->getOptItemList(); 
my $optItem1 = $optItemList->get(0);
my $optItem2 = $optItemList->get(1);
# the actual results are stored in the fit problem
unless($fitProblem->getSolutionVariables()->size() == 2){warn "Assertion failed";die;}
print "value for " , $optItem1->getObject()->getCN()->getString() , ": " , $fitProblem->getSolutionVariables()->get(0), "\n";
print "value for " , $optItem2->getObject()->getCN()->getString() , ": " , $fitProblem->getSolutionVariables()->get(1), "\n";
# depending on the noise, the fit can be quite bad, so we are a litle
# relaxed here (we should be within 3% of the original values)
unless((abs($fitProblem->getSolutionVariables()->get(0) - 0.03) / 0.03) < 3e-2){warn "Assertion failed";die;}
unless((abs($fitProblem->getSolutionVariables()->get(1) - 0.004) / 0.004) < 3e-2){warn "Assertion failed";die;}

