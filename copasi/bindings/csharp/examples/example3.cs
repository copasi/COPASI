/**
 * This is an example on how to import an sbml file
 * create a report for a time course simulation 
 * and run a time course simulation
 */
using System;
using org.COPASI;
using System.Diagnostics;

class example3
{
  static void Main(string[] args)
  {
      Debug.Assert(CRootContainer.getRoot() != null);
      // create a new datamodel
      CDataModel dataModel = CRootContainer.addDatamodel();
      Debug.Assert(CRootContainer.getDatamodelList().size() == 1);
      // the only argument to the main routine should be the name of an SBML file
      if (args.Length == 1)
      {
          string filename = args[0];
          try
          {
              // load the model 
              dataModel.importSBML(filename);
          }
          catch 
          {
              System.Console.Error.WriteLine( "Error while importing the model from file named \"" + filename + "\"." );
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
          
          body.Add(new CRegisteredCommonName(model.getObject(new CCommonName("Reference=Time")).getCN().getString()));
          body.Add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));
          header.Add(new CRegisteredCommonName(new CDataString("time").getCN().getString()));
          header.Add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));

          uint i, iMax =(uint) model.getMetabolites().size();
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
                  // after each entry, we need a seperator
                  if(i!=iMax-1)
                  {
                    body.Add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));
                    header.Add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));
                  }

              }
          }


          // get the trajectory task object
          CTrajectoryTask trajectoryTask = (CTrajectoryTask)dataModel.getTask("Time-Course");

          // run a deterministic time course
          trajectoryTask.setMethodType(CTaskEnum.Method_deterministic);

          // pass a pointer of the model to the problem
          trajectoryTask.getProblem().setModel(dataModel.getModel());

          // actiavate the task so that it will be run when the model is saved
          // and passed to CopasiSE
          trajectoryTask.setScheduled(true);

          // set the report for the task
          trajectoryTask.getReport().setReportDefinition(report);
          // set the output filename
          trajectoryTask.getReport().setTarget("example3.txt");
          // don't append output if the file exists, but overwrite the file
          trajectoryTask.getReport().setAppend(false);

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

          // set some parameters for the LSODA method through the method
          CTrajectoryMethod method = (CTrajectoryMethod)trajectoryTask.getMethod();

          CCopasiParameter parameter = method.getParameter("Absolute Tolerance");
          Debug.Assert(parameter != null);
          Debug.Assert(parameter.getType() == CCopasiParameter.Type_DOUBLE);
          parameter.setDblValue(1.0e-12);

          bool result=true;
          try
          {
              // now we run the actual trajectory
              result=trajectoryTask.processWithOutputFlags(true, (int)CCopasiTask.ONLY_TIME_SERIES);
          }
          catch
          {
              System.Console.Error.WriteLine( "Error. Running the time course simulation failed." );
                        String lastErrors =  trajectoryTask.getProcessError();
          // check if there are additional error messages
          if (!string.IsNullOrEmpty(lastErrors))
          {
              // print the messages in chronological order
              System.Console.Error.WriteLine(lastErrors);
          }

              System.Environment.Exit(1);
          }
          if(result==false)
          {
              System.Console.Error.WriteLine( "An error occured while running the time course simulation." );
                        String lastErrors =  trajectoryTask.getProcessError();
          // check if there are additional error messages
          if (!string.IsNullOrEmpty(lastErrors))
          {
              // print the messages in chronological order
              System.Console.Error.WriteLine(lastErrors);
          }

              System.Environment.Exit(1);
          }

          // look at the timeseries
          CTimeSeries timeSeries = trajectoryTask.getTimeSeries();
          // we simulated 100 steps, including the initial state, this should be
          // 101 step in the timeseries
          Debug.Assert(timeSeries.getRecordedSteps() == 101);
          System.Console.WriteLine( "The time series consists of " + System.Convert.ToString(timeSeries.getRecordedSteps()) + "." );
          System.Console.WriteLine( "Each step contains " + System.Convert.ToString(timeSeries.getNumVariables()) + " variables." );
          System.Console.WriteLine( "The final state is: " );
          iMax = (uint)timeSeries.getNumVariables();
          uint lastIndex = (uint)timeSeries.getRecordedSteps() - 1;
          for (i = 0;i < iMax;++i)
          {
              // here we get the particle number (at least for the species)
              // the unit of the other variables may not be particle numbers
              // the concentration data can be acquired with getConcentrationData
              System.Console.WriteLine(timeSeries.getTitle(i) + ": " + System.Convert.ToString(timeSeries.getData(lastIndex, i)) );
          }

      }
      else
      {
          System.Console.Error.WriteLine("Usage: example3 SBMLFILE" );
          System.Environment.Exit(1);
      }

  }
}
