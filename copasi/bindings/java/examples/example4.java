// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/examples/example4.java,v $ 
//   $Revision: 1.3 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2009/03/05 14:33:26 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

/**
 * This is an example on how to import an sbml file
 * create a report for a time course simulation 
 * and run a scan for a stochastic time course simulation
 */

import org.COPASI.*;

class example4
{
    public static void main(String[] args)
    {
        assert CCopasiRootContainer.getRoot() != null;
        // create a new datamodel
        CCopasiDataModel dataModel = CCopasiRootContainer.addDatamodel();
        assert CCopasiRootContainer.getDatamodelList().size() == 1;
        // the only argument to the main routine should be the name of an SBML file
        try
        {
            // load the model
            dataModel.importSBMLFromString(MODEL_STRING);
        }
        catch (java.lang.Exception ex)
        {
            System.err.println( "Error while importing the model from the given String.");
            System.exit(1);
        }
        CModel model = dataModel.getModel();
        assert model != null;
        // create a report with the correct filename and all the species against
        // time.
        CReportDefinitionVector reports = dataModel.getReportDefinitionList();
        // create a new report definition object
        CReportDefinition report = reports.createReportDefinition("Report", "Output for timecourse");
        // set the task type for the report definition to timecourse
        report.setTaskType(CCopasiTask.timeCourse);
        // we don't want a table
        report.setIsTable(false);
        // the entries in the output should be seperated by a ", "
        report.setSeparator(new CCopasiReportSeparator(", "));

        // we need a handle to the header and the body
        // the header will display the ids of the metabolites and "time" for
        // the first column
        // the body will contain the actual timecourse data
        ReportItemVector header = report.getHeaderAddr();
        ReportItemVector body = report.getBodyAddr();
        body.add(new CRegisteredObjectName(new CCopasiObjectName(dataModel.getModel().getCN().getString() + ",Reference=Time").getString()));
        body.add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));
        header.add(new CRegisteredObjectName(new CCopasiStaticString("time").getCN().getString()));
        header.add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));

        int i, iMax = (int)model.getMetabolites().size();
        for (i = 0;i < iMax;++i)
        {
            CMetab metab = model.getMetabolites().get(i);
            assert metab != null;
            // we don't want output for FIXED metabolites right now
            if (metab.getStatus() != CModelEntity.FIXED)
            {
                // we want the concentration oin the output
                // alternatively, we could use "Reference=Amount" to get the
                // particle number
                body.add(new CRegisteredObjectName(metab.getObject(new CCopasiObjectName("Reference=Concentration")).getCN().getString()));
                // add the corresponding id to the header
                header.add(new CRegisteredObjectName(new CCopasiStaticString(metab.getSBMLId()).getCN().getString()));
                
                if(i!=iMax-1)
                {
                  // after each entry, we need a seperator
                  body.add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));

                  // and a seperator
                  header.add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));
                }
            }
        }
        // get the task list
        TaskVectorN taskList = dataModel.getTaskList();

        // get the trajectory task object
        CTrajectoryTask trajectoryTask = (CTrajectoryTask)taskList.getObject(new CCopasiObjectName("Time-Course"));
        // if there isn't one
        if (trajectoryTask == null)
        {
            // create a new one
            trajectoryTask = new CTrajectoryTask();
            // remove any existing trajectory task just to be sure since in
            // theory only the cast might have failed above
            taskList.removeByName("Time-Course");

            // add the new time course task to the task list
            taskList.add(trajectoryTask, true);
        }

        // run a stochastic time course
        trajectoryTask.setMethodType(CCopasiMethod.stochastic);

        // pass a pointer of the model to the problem
        trajectoryTask.getProblem().setModel(dataModel.getModel());

        // we don't want the trajectory task to run by itself, but we want to
        // run it from a scan, so we deactivate the standalone trajectory task
        trajectoryTask.setScheduled(false);

        // get the problem for the task to set some parameters
        CTrajectoryProblem problem = (CTrajectoryProblem)trajectoryTask.getProblem();

        // simulate 100 steps
        problem.setStepNumber(100);
        // start at time 0
        dataModel.getModel().setInitialTime(0.0);
        // simulate a duration of 10 time units
        problem.setDuration(10);
        // tell the problem to actually generate time series data
        problem.setTimeSeriesRequested(true);

        // now we set up the scan
        CScanTask scanTask = (CScanTask)taskList.getObject(new CCopasiObjectName("Scan"));
        if (scanTask == null)
        {
            // create a new scan task
            scanTask = new CScanTask();
            // just to be on the save side, delete any existing scan task
            taskList.removeByName("Scan");
            // add the new scan task
            taskList.add(scanTask, true);
        }

        // get the problem
        CScanProblem scanProblem = (CScanProblem)scanTask.getProblem();
        assert scanProblem != null;

        // set the model for the problem
        scanProblem.setModel(dataModel.getModel());

        // activate the task so that is is run
        // if the model is saved and passed to CopasiSE
        scanTask.setScheduled(true);

        // set the report for the task
        scanTask.getReport().setReportDefinition(report);

        // set the output file for the report
        scanTask.getReport().setTarget("example4.txt");
        // don't append to an existing file, but overwrite
        scanTask.getReport().setAppend(false);

        // tell the scan that we want to make a scan over a trajectory task
        scanProblem.setSubtask(CCopasiTask.timeCourse);

        // we just want to run the timecourse task a number of times, so we
        // create a repeat item with 100 repeats
        scanProblem.createScanItem(CScanProblem.SCAN_REPEAT, 100);

        // we want the output from the trajectory task
        scanProblem.setOutputInSubtask(true);

        // we don't want to set the initial conditions of the model to the end
        // state of the last run
        scanProblem.setAdjustInitialConditions(false);

        try
        {
            // now we run the actual trajectory
            scanTask.process(true);
        }
        catch (java.lang.Exception ex)
        {
            System.err.println( "Error. Running the scan failed.");
            // check if there are additional error messages
            if (CCopasiMessage.size() > 0)
            {
                // print the messages in chronological order
                System.err.println( CCopasiMessage.getAllMessageText(true));
            }
            System.exit(1);
        }
    }

    static String MODEL_STRING=
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
  "<!-- Created by COPASI version 4.4.29 (Debug) on 2009-03-05 14:41 with libSBML version 3.3.0. -->\n" +
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n" +
  "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n" +
  "    <listOfUnitDefinitions>\n" +
  "      <unitDefinition id=\"volume\">\n" +
  "        <listOfUnits>\n" +
  "          <unit kind=\"litre\" scale=\"-6\"/>\n" +
  "        </listOfUnits>\n" +
  "      </unitDefinition>\n" +
  "      <unitDefinition id=\"substance\">\n" +
  "        <listOfUnits>\n" +
  "          <unit kind=\"mole\" scale=\"-9\"/>\n" +
  "        </listOfUnits>\n" +
  "      </unitDefinition>\n" +
  "    </listOfUnitDefinitions>\n" +
  "    <listOfCompartments>\n" +
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n" +
  "    </listOfCompartments>\n" +
  "    <listOfSpecies>\n" +
  "      <species metaid=\"COPASI2\" id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1e-10\">\n" +
  "      </species>\n" +
  "      <species metaid=\"COPASI3\" id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"0\">\n" +
  "      </species>\n" +
  "      <species metaid=\"COPASI4\" id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"0\">\n" +
  "      </species>\n" +
  "    </listOfSpecies>\n" +
  "    <listOfReactions>\n" +
  "      <reaction id=\"reaction_1\" name=\"reaction\" reversible=\"false\">\n" +
  "        <listOfReactants>\n" +
  "          <speciesReference species=\"species_1\"/>\n" +
  "        </listOfReactants>\n" +
  "        <listOfProducts>\n" +
  "          <speciesReference species=\"species_2\"/>\n" +
  "        </listOfProducts>\n" +
  "        <kineticLaw>\n" +
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n" +
  "            <apply>\n" +
  "              <times/>\n" +
  "              <ci> compartment_1 </ci>\n" +
  "              <ci> k1 </ci>\n" +
  "              <ci> species_1 </ci>\n" +
  "            </apply>\n" +
  "          </math>\n" +
  "          <listOfParameters>\n" +
  "            <parameter id=\"k1\" value=\"0.1\"/>\n" +
  "          </listOfParameters>\n" +
  "        </kineticLaw>\n" +
  "      </reaction>\n" +
  "      <reaction id=\"reaction_2\" name=\"reaction_1\" reversible=\"false\">\n" +
  "        <listOfReactants>\n" +
  "          <speciesReference species=\"species_2\"/>\n" +
  "        </listOfReactants>\n" +
  "        <listOfProducts>\n" +
  "          <speciesReference species=\"species_3\"/>\n" +
  "        </listOfProducts>\n" +
  "        <kineticLaw>\n" +
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n" +
  "            <apply>\n" +
  "              <times/>\n" +
  "              <ci> compartment_1 </ci>\n" +
  "              <ci> k1 </ci>\n" +
  "              <ci> species_2 </ci>\n" +
  "            </apply>\n" +
  "          </math>\n" +
  "          <listOfParameters>\n" +
  "            <parameter id=\"k1\" value=\"0.1\"/>\n" +
  "          </listOfParameters>\n" +
  "        </kineticLaw>\n" +
  "      </reaction>\n" +
  "    </listOfReactions>\n" +
  "  </model>\n" +
  "</sbml>\n";
}
