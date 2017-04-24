# 
# This is an example on how to import an sbml file
# create a report for a time course simulation 
# and run a scan for a stochastic time course simulation
# 

use COPASI;

my $MODEL_STRING = <<END;
<?xml version="1.0" encoding="UTF-8"?>
<!-- Created by COPASI version 4.4.29 (Debug) on 2009-03-05 14:41 with libSBML version 3.3.0. -->
<sbml xmlns="http://www.sbml.org/sbml/level2/version3" level="2" version="3">
  <model metaid="COPASI1" id="Model_1" name="New Model">
    <listOfUnitDefinitions>
      <unitDefinition id="volume">
        <listOfUnits>
          <unit kind="litre" scale="-6"/>
        </listOfUnits>
      </unitDefinition>
      <unitDefinition id="substance">
        <listOfUnits>
          <unit kind="mole" scale="-9"/>
        </listOfUnits>
      </unitDefinition>
    </listOfUnitDefinitions>
    <listOfCompartments>
      <compartment id="compartment_1" name="compartment" size="1"/>
    </listOfCompartments>
    <listOfSpecies>
      <species metaid="COPASI2" id="species_1" name="A" compartment="compartment_1" initialConcentration="1e-10">
      </species>
      <species metaid="COPASI3" id="species_2" name="B" compartment="compartment_1" initialConcentration="0">
      </species>
      <species metaid="COPASI4" id="species_3" name="C" compartment="compartment_1" initialConcentration="0">
      </species>
    </listOfSpecies>
    <listOfReactions>
      <reaction id="reaction_1" name="reaction" reversible="false">
        <listOfReactants>
          <speciesReference species="species_1"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="species_2"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> compartment_1 </ci>
              <ci> k1 </ci>
              <ci> species_1 </ci>
            </apply>
          </math>
          <listOfParameters>
            <parameter id="k1" value="0.1"/>
          </listOfParameters>
        </kineticLaw>
      </reaction>
      <reaction id="reaction_2" name="reaction_1" reversible="false">
        <listOfReactants>
          <speciesReference species="species_2"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="species_3"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> compartment_1 </ci>
              <ci> k1 </ci>
              <ci> species_2 </ci>
            </apply>
          </math>
          <listOfParameters>
            <parameter id="k1" value="0.1"/>
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
# the only argument to the main routine should be the name of an SBML file
eval {
    # load the model
    $dataModel->importSBMLFromString($MODEL_STRING);
}
or do {
    warn  "Error while importing the model from given string.\n";
    die;
};

my $model = $dataModel->getModel();
unless(defined($model)){warn "Assertion failed";die;}
# create a report with the correct filename and all the species against
# time.
my $reports = $dataModel->getReportDefinitionList();
# create a report definition object
my $report = $reports->createReportDefinition("Report", "Output for timecourse");
# set the task type for the report definition to timecourse
$report->setTaskType($COPASI::CCopasiTask::timeCourse);
# we don't want a table
$report->setIsTable("");
# the entries in the output should be seperated by a ", "
$report->setSeparator(new COPASI::CCopasiReportSeparator(", "));

# we need a handle to the header and the body
# the header will display the ids of the metabolites and "time" for
# the first column
# the body will contain the actual timecourse data
my $header = $report->getHeaderAddr();
my $body = $report->getBodyAddr();
$body->push(new COPASI::CRegisteredCommonName(new COPASI::CCommonName($dataModel->getModel()->getCN()->getString() . ",Reference=Time")->getString()));
$body->push(new COPASI::CRegisteredCommonName($report->getSeparator()->getCN()->getString()));
$header->push(new COPASI::CRegisteredCommonName(new COPASI::CDataString("time")->getCN()->getString()));
$header->push(new COPASI::CRegisteredCommonName($report->getSeparator()->getCN()->getString()));

my $iMax = $model->getMetabolites()->size();
for (my $i=0; $i < $iMax; $i++) {
    $metab = $model->getMetabolite($i);
    unless(defined($metab)){warn "Assertion failed";die;}
    # we don't want output for FIXED metabolites right now
    if ($metab->getStatus() != $COPASI::CModelEntity::FIXED) {
        # we want the concentration in the output
        # alternatively, we could use "Reference=Amount" to get the
        # particle number
        $body->push(new COPASI::CRegisteredCommonName($metab->getObject(new COPASI::CCommonName("Reference=Concentration"))->getCN()->getString()));
        # add the corresponding id to the header
        $header->push(new COPASI::CRegisteredCommonName(new COPASI::CDataString($metab->getSBMLId())->getCN()->getString()));
        
        if ($i != ($iMax-1)) {
          # after each entry, we need a seperator
          $body->push(new COPASI::CRegisteredCommonName($report->getSeparator()->getCN()->getString()));

          # and a seperator
          $header->push(new COPASI::CRegisteredCommonName($report->getSeparator()->getCN()->getString()));
        }
    }
}
# get the trajectory task object
$trajectoryTask = $dataModel->getTask("Time-Course");
unless(defined($trajectoryTask)){warn "Assertion failed";die;}
# if there isn't one
if (!defined($trajectoryTask)) {
    # create a one
    $trajectoryTask = new COPASI::CTrajectoryTask();
    # add the time course task to the task list
    # this method makes sure the object is now owned by the list
    # and that SWIG does not delete it
    $dataModel->getTaskList()->addAndOwn($trajectoryTask);
}


# run a stochastic time course
$trajectoryTask->setMethodType($COPASI::CCopasiMethod::stochastic);

# pass a pointer of the model to the problem
$trajectoryTask->getProblem()->setModel($dataModel->getModel());

# we don't want the trajectory task to run by itself, but we want to
# run it from a scan, so we deactivate the standalone trajectory task
$trajectoryTask->setScheduled("");

# get the problem for the task to set some parameters
$problem = $trajectoryTask->getProblem();

# simulate 100 steps
$problem->setStepNumber(100);
# start at time 0
$dataModel->getModel()->setInitialTime(0.0);
# simulate a duration of 10 time units
$problem->setDuration(10);
# tell the problem to actually generate time series data
$problem->setTimeSeriesRequested(1);

# now we set up the scan
$scanTask = $dataModel->getTask("Scan");
unless(defined($scanTask)){warn "Assertion failed";die;}
if (!defined(scanTask)) {
    # create a scan task
    $scanTask = new COPASI::CScanTask();
    # add the scan task
    # this method makes sure the object is now owned by the list
    # and that SWIG does not delete it
    $dataModel->getTaskList()->addAndOwn($scanTask);
}

# get the problem
$scanProblem = $scanTask->getProblem();
unless(defined($scanProblem)){warn "Assertion failed";die;}

# set the model for the problem
$scanProblem->setModel($dataModel->getModel());

# activate the task so that is is run
# if the model is saved and passed to CopasiSE
$scanTask->setScheduled(1);

# set the report for the task
$scanTask->getReport()->setReportDefinition($report);

# set the output file for the report
$scanTask->getReport()->setTarget("example4.txt");
# don't append to an existing file, but overwrite
$scanTask->getReport()->setAppend("");

# tell the scan that we want to make a scan over a trajectory task
$scanProblem->setSubtask($COPASI::CCopasiTask::timeCourse);

# we just want to run the timecourse task a number of times, so we
# create a repeat item with 100 repeats
$scanProblem->addScanItem($COPASI::CScanProblem::SCAN_REPEAT, 100);

# we want the output from the trajectory task
$scanProblem->setOutputInSubtask(1);

# we don't want to set the initial conditions of the model to the end
# state of the last run
$scanProblem->setAdjustInitialConditions("");

eval {
    # now we run the actual trajectory
    $scanTask->process(1);
}
or do {
    warn  "Error. Running the scan failed.\n";
    # check if there are additional error messages
    if (COPASI::CCopasiMessage::size() > 0) {
        # print the messages in chronological order
        warn  COPASI::CCopasiMessage::getAllMessageText(1);
    }
    die;
}


