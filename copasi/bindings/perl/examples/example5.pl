# 
# This is an example on how to run an optimization task.
# And how to access the result of an optimization.
# 
use strict;
use warnings;

use COPASI;

unless(defined(COPASI::CRootContainer::getRoot())){warn "Assertion failed";die;}
# create a new datamodel
my $dataModel = COPASI::CRootContainer::addDatamodel();
unless(COPASI::CRootContainer::getDatamodelList()->size() == 1){warn "Assertion failed";die;}
# get the model from the datamodel
my $model = $dataModel->getModel();
unless(defined($model )){warn "Assertion failed";die;}
$model->setVolumeUnit($COPASI::CUnit::fl);
$model->setTimeUnit($COPASI::CUnit::s);
$model->setQuantityUnit($COPASI::CUnit::fMol);
my $fixedModelValue = $model->createModelValue("F");
unless(defined($fixedModelValue )){warn "Assertion failed";die;}
$fixedModelValue->setStatus($COPASI::CModelEntity::FIXED);
$fixedModelValue->setInitialValue(3.0);   ;
my $variableModelValue = $model->createModelValue("V");
unless(defined($variableModelValue )){warn "Assertion failed";die;}
$variableModelValue->setStatus($COPASI::CModelEntity::ASSIGNMENT);
# we create a very simple assignment that is easy on the optimization
# a parabole with the minimum at x=6 should do just fine
my $s="(<" . $fixedModelValue->getObject(new COPASI::CCommonName("Reference=Value"))->getCN()->getString() . "> - 6.0)^2";
$variableModelValue->setExpression($s);
# now we compile the model and tell COPASI which values have changed so
# that COPASI can update the values that depend on those
$model->compileIfNecessary();
my $changedObjects = new COPASI::ObjectStdVector();
$changedObjects->push($fixedModelValue->getObject(new COPASI::CCommonName("Reference=InitialValue")));
$changedObjects->push($variableModelValue->getObject(new COPASI::CCommonName("Reference=InitialValue")));
$model->updateInitialValues($changedObjects);

# now we set up the optimization

# we want to do an optimization for the time course
# so we have to set up the time course task first
my $timeCourseTask = $dataModel->getTask("Time-Course");
unless(defined($timeCourseTask )){warn "Assertion failed";die;}
# since for this example it really doesn't matter how long we run the time course 
# we run for 1 second and calculate 10 steps
# run a deterministic time course
$timeCourseTask->setMethodType($COPASI::CCopasiMethod::deterministic);

# pass a pointer of the model to the problem
$timeCourseTask->getProblem()->setModel($dataModel->getModel());

# get the problem for the task to set some parameters
my $problem = $timeCourseTask->getProblem();
unless(defined($problem )){warn "Assertion failed";die;}

# simulate 10 steps
$problem->setStepNumber(10);
# start at time 0
$dataModel->getModel()->setInitialTime(0.0);
# simulate a duration of 1 time units
$problem->setDuration(1);
# tell the problem to actually generate time series data
$problem->setTimeSeriesRequested(1);

# get the optimization task
my $optTask = $dataModel->getTask("Optimization");
unless(defined($optTask )){warn "Assertion failed";die;}
# we want to use Levenberg-Marquardt as the optimization method
$optTask->setMethodType($COPASI::CCopasiMethod::LevenbergMarquardt);

# next we need to set subtask type on the problem
my $optProblem = $optTask->getProblem();
unless(defined($optProblem )){warn "Assertion failed";die;}
$optProblem->setSubtaskType($COPASI::CCopasiTask::timeCourse);

# we create the objective function
# we want to minimize the value of the variable model value at the end of
# the simulation
# the objective function is normally minimized

# we need to put the angled brackets around the common name of the object
my $objectiveFunction = "<" . $variableModelValue->getObject(new COPASI::CCommonName("Reference=Value"))->getCN()->getString() . ">";
# now we set the objective function in the problem
$optProblem->setObjectiveFunction($objectiveFunction);

# now we create the optimization items
# i.e. the model elements that have to be changed during the optimization
# in order to get to the optimal solution
my $optItem = $optProblem->addOptItem(new COPASI::CCommonName($fixedModelValue->getObject(new COPASI::CCommonName("Reference=InitialValue"))->getCN()));
# we want to change the fixed model value from -100 to +100 with a start
# value of 50
$optItem->setStartValue(50.0);
$optItem->setLowerBound(new COPASI::CCommonName("-100"));
$optItem->setUpperBound(new COPASI::CCommonName("100"));

# now we set some parameters on the method
# these parameters are specific to the method type we set above
# (in this case Levenberg-Marquardt)
my $optMethod = $optTask->getMethod();
unless(defined($optMethod )){warn "Assertion failed";die;}

# now we set some method parameters for the optimization method
# iteration limit
my $parameter = $optMethod->getParameter("Iteration Limit");
unless(defined($parameter )){warn "Assertion failed";die;}
$parameter->setIntValue(2000);
# tolerance
$parameter = $optMethod->getParameter("Tolerance");
unless(defined($parameter )){warn "Assertion failed";die;}
$parameter->setDblValue(1.0e-5);

# create a report with the correct filename and all the species against
# time.
my $reports = $dataModel->getReportDefinitionList();
# create a report definition object
my $report = $reports->createReportDefinition("Report", "Output for optimization");
# set the task type for the report definition to timecourse
$report->setTaskType($COPASI::CCopasiTask::optimization);
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

# in the report header we write two strings and a separator
$header->push(new COPASI::CRegisteredCommonName(new COPASI::CDataString("best value of objective function")->getCN()->getString()));
$header->push(new COPASI::CRegisteredCommonName($report->getSeparator()->getCN()->getString()));
$header->push(new COPASI::CRegisteredCommonName(new COPASI::CDataString("initial value of F")->getCN()->getString()));
# in the report body we write the best value of the objective function and
# the initial value of the fixed parameter separated by a komma
$body->push(new COPASI::CRegisteredCommonName($optProblem->getObject(new COPASI::CCommonName("Reference=Best Value"))->getCN()->getString()));
$body->push(new COPASI::CRegisteredCommonName($report->getSeparator()->getCN()->getString()));
$body->push(new COPASI::CRegisteredCommonName($fixedModelValue->getObject(new COPASI::CCommonName("Reference=InitialValue"))->getCN()->getString()));


# set the report for the task
$optTask->getReport()->setReportDefinition($report);
# set the output filename
$optTask->getReport()->setTarget("example5.txt");
# don't append output if the file exists, but overwrite the file
$optTask->getReport()->setAppend("");

my $result="";
eval {
  $result = $optTask->process(1);
}
or do {
    warn "Running the optimization failed.\n";
    die;
};

if(!$result) {
    warn "Running the optimization failed.\n";
    die;
}
# now we check if the optimization actually got the correct result
# the best value it should have is 0 and the best parameter value for
# that result should be 6 for the initial value of the fixed parameter
my $bestValue = $optProblem->getSolutionValue();
unless(abs($bestValue) < 1e-3){warn "Assertion failed";die;}
# we should only have one solution variable since we only have one
# optimization item
unless($optProblem->getSolutionVariables()->size() == 1){warn "Assertion failed";die;}
my $solution = $optProblem->getSolutionVariables()->get(0);
unless(abs(($solution - 6.0) / 6.0) < 1e-3){warn "Assertion failed";die;}


