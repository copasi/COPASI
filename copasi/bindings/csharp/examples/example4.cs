/**
 * This is an example on how to import an sbml file
 * create a report for a time course simulation 
 * and run a scan for a stochastic time course simulation
 */
using System;
using org.COPASI;
using System.Diagnostics;

class example4
{
    static void Main()
    {
        Debug.Assert(CRootContainer.getRoot() != null);
        // create a new datamodel
        CDataModel dataModel = CRootContainer.addDatamodel();
        Debug.Assert(CRootContainer.getDatamodelList().size() == 1);
        // the only argument to the main routine should be the name of an SBML file
        try
        {
            // load the model
            dataModel.importSBMLFromString(MODEL_STRING);
        }
        catch
        {
            System.Console.Error.WriteLine( "Error while importing the model from the given String.");
            System.Environment.Exit(1);
        }
        CModel model = dataModel.getModel();
        Debug.Assert(model != null);
        // create a report with the correct filename and all the species against
        // time.
        CReportDefinitionVector reports = dataModel.getReportDefinitionList();
        // create a new report definition object
        CReportDefinition report = reports.createReportDefinition("Report", "Output for timecourse");
        // set the task type for the report definition to timecourse
        report.setTaskType(CTaskEnum.Task_timeCourse);
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
        body.Add(new CRegisteredCommonName(new CCommonName(dataModel.getModel().getCN().getString() + ",Reference=Time").getString()));
        body.Add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));
        header.Add(new CRegisteredCommonName(new CDataString("time").getCN().getString()));
        header.Add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));

        uint i, iMax = (uint)model.getMetabolites().size();
        for (i = 0;i < iMax;++i)
        {
            CMetab metab = model.getMetabolite(i);
            Debug.Assert(metab != null);
            // we don't want output for FIXED metabolites right now
            if (metab.getStatus() != CModelEntity.Status_FIXED)
            {
                // we want the concentration oin the output
                // alternatively, we could use "Reference=Amount" to get the
                // particle number
                body.Add(new CRegisteredCommonName(metab.getObject(new CCommonName("Reference=Concentration")).getCN().getString()));
                // add the corresponding id to the header
                header.Add(new CRegisteredCommonName(new CDataString(metab.getSBMLId()).getCN().getString()));
                
                if(i!=iMax-1)
                {
                  // after each entry, we need a seperator
                  body.Add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));

                  // and a seperator
                  header.Add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));
                }
            }
        }

        // get the trajectory task object
        CTrajectoryTask trajectoryTask = (CTrajectoryTask)dataModel.getTask("Time-Course");
        
        // run a stochastic time course
        trajectoryTask.setMethodType(CTaskEnum.Method_stochastic);

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
        CScanTask scanTask = (CScanTask)dataModel.getTask("Scan");

        // get the problem
        CScanProblem scanProblem = (CScanProblem)scanTask.getProblem();
        Debug.Assert(scanProblem != null);

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
        scanProblem.setSubtask(CTaskEnum.Task_timeCourse);

        // we just want to run the timecourse task a number of times, so we
        // create a repeat item with 100 repeats
        scanProblem.addScanItem(CScanProblem.SCAN_REPEAT, 100);

        // we want the output from the trajectory task
        scanProblem.setOutputInSubtask(true);

        // we don't want to set the initial conditions of the model to the end
        // state of the last run
        scanProblem.setContinueFromCurrentState(false);

        try
        {
            // now we run the actual trajectory
            scanTask.processWithOutputFlags(true, (int)CCopasiTask.ONLY_TIME_SERIES);
        }
        catch 
        {
            System.Console.Error.WriteLine( "Error. Running the scan failed.");
                      String lastErrors =  scanTask.getProcessError();
          // check if there are additional error messages
          if (!string.IsNullOrEmpty(lastErrors))
          {
              // print the messages in chronological order
              System.Console.Error.WriteLine(lastErrors);
          }

            System.Environment.Exit(1);
        }
    }

    static string MODEL_STRING=
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
