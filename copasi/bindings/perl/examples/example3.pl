# 
# This is an example on how to import an sbml file
# create a report for a time course simulation 
# and run a time course simulation
# 
use strict;
use warnings;

use COPASI;

unless(defined(COPASI::CRootContainer::getRoot())){warn "Assertion failed";die;}
# create a datamodel
my $dataModel = COPASI::CRootContainer::addDatamodel();
unless(COPASI::DataModelVector::size(COPASI::CRootContainer::getDatamodelList()) == 1){warn "Assertion failed";die;}
# the only argument to the main routine should be the name of an SBML file
if ($#ARGV + 1 == 1) {
    my $filename = $ARGV[0];
    eval {
        # load the model 
        $dataModel->importSBML($filename);
    }
    or do {
        warn  "Error while importing the model from file named \"" , $filename , "\".\n"; 
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
   
    my $str = new COPASI::CCommonName($dataModel->getModel()->getCN()->getString() . ",Reference=Time")->getString();
    $body->push(new COPASI::CRegisteredCommonName($str));
    $body->push(new COPASI::CRegisteredCommonName($report->getSeparator()->getCN()->getString()));
    $header->push(new COPASI::CRegisteredCommonName(new COPASI::CDataString("time")->getCN()->getString()));
    $header->push(new COPASI::CRegisteredCommonName($report->getSeparator()->getCN()->getString()));

    my $iMax = $model->getMetabolites()->size();
    for (my $i=0; $i < $iMax; $i++) {
        my $metab = $model->getMetabolite($i);
        unless(defined($metab)){warn "Assertion failed";die;}
        # we don't want output for FIXED metabolites right now
        if ($metab->getStatus() != $COPASI::CModelEntity::FIXED) {
            # we want the concentration oin the output
            # alternatively, we could use "Reference=Amount" to get the
            # particle number
            $body->push(new COPASI::CRegisteredCommonName($metab->getObject(new COPASI::CCommonName("Reference=Concentration"))->getCN()->getString()));
            # add the corresponding id to the header
            $header->push(new COPASI::CRegisteredCommonName(new COPASI::CDataString($metab->getSBMLId())->getCN()->getString()));
            # after each entry, we need a seperator
            if($i != ($iMax - 1)) {
              $body->push(new COPASI::CRegisteredCommonName($report->getSeparator()->getCN()->getString()));
              $header->push(new COPASI::CRegisteredCommonName($report->getSeparator()->getCN()->getString()));
            }
        }

    }
    # get the trajectory task object
    my $trajectoryTask = $dataModel->getTask("Time-Course");
    # if there isn't one
    if (!defined($trajectoryTask)) {
        # create a one
        $trajectoryTask = new COPASI::CTrajectoryTask();
        # add the time course task to the task list
        # this method makes sure the object is now owned by the list
        # and that SWIG does not delete it
        $dataModel->getTaskList()->addAndOwn($trajectoryTask);
    }

    # run a deterministic time course
    $trajectoryTask->setMethodType($COPASI::CCopasiMethod::deterministic);

    # pass a pointer of the model to the problem
    $trajectoryTask->getProblem()->setModel($dataModel->getModel());

    # activate the task so that it will be run when the model is saved
    # and passed to CopasiSE
    $trajectoryTask->setScheduled(1);

    # set the report for the task
    $trajectoryTask->getReport()->setReportDefinition($report);
    # set the output filename
    $trajectoryTask->getReport()->setTarget("example3.txt");
    # don't append output if the file exists, but overwrite the file
    $trajectoryTask->getReport()->setAppend("");

    # get the problem for the task to set some parameters
    my $problem = $trajectoryTask->getProblem();

    # simulate 100 steps
    $problem->setStepNumber(100);
    # start at time 0
    $dataModel->getModel()->setInitialTime(0.0);
    # simulate a duration of 10 time units
    $problem->setDuration(10);
    # tell the problem to actually generate time series data
    $problem->setTimeSeriesRequested(1);

    # set some parameters for the LSODA method through the method
    my $method = $trajectoryTask->getMethod();

    my $parameter = $method->getParameter("Absolute Tolerance");
    unless(defined($parameter)){warn "Assertion failed";die;}
    unless($parameter->getType() == $COPASI::CCopasiParameter::UDOUBLE){warn "Assertion failed";die;}
    $parameter->setDblValue(1.0e-12);

    my $result=1;
    eval {
        # now we run the actual trajectory
        $result = $trajectoryTask->process(1);
    }
    or do {
        warn  "Error. Running the time course simulation failed.\n";
        # check if there are additional error messages
        if (COPASI::CCopasiMessage::size() > 0) {
            # print the messages in chronological order
            warn COPASI::CCopasiMessage::getAllMessageText(1) , "\n";
        }
        die;
    };
    if (!$result) {
        warn "Error. Running the time course simulation failed.\n";
        # check if there are additional error messages
        if ( COPASI::CCopasiMessage::size() > 0 ) {
            # print the messages in chronological order
            warn COPASI::CCopasiMessage::getAllMessageText(1), "\n";
        }
        die;
    }

    # look at the timeseries
    my $timeSeries = $trajectoryTask->getTimeSeries();
    # we simulated 100 steps, including the initial state, this should be
    # 101 step in the timeseries
    unless($timeSeries->getRecordedSteps() == 101){warn "Assertion failed";die;}
    print  "The time series consists of " , $timeSeries->getRecordedSteps() , ".\n" ;
    print  "Each step contains " , $timeSeries->getNumVariables() , " variables.\n" ;
    print  "The final state is: \n" ;
    $iMax = $timeSeries->getNumVariables();
    my $lastIndex = $timeSeries->getRecordedSteps() - 1;
    for ( my $i = 0; $i < $iMax; $i++) {
        # here we get the particle number (at least for the species)
        # the unit of the other variables may not be particle numbers
        # the concentration data can be acquired with getConcentrationData
        print $timeSeries->getTitle($i) . ": " . $timeSeries->getData($lastIndex, $i) . "\n"  ;
    }
}
else {
    warn "Usage: example3 SBMLFILE\n";
    die;
}


