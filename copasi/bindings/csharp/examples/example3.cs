/**
 * This is an example on how to import an sbml file
 * create a report for a time course simulation 
 * and run a time course simulation
 */

using org.COPASI;
using System.Diagnostics;

class example3
{
  static void Main(string[] args)
  {
      Debug.Assert(CCopasiRootContainer.getRoot() != null);
      // create a new datamodel
      CCopasiDataModel dataModel = CCopasiRootContainer.addDatamodel();
      Debug.Assert(CCopasiRootContainer.getDatamodelList().size() == 1);
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
          CReportTemplateVector reports = dataModel.getReportTemplateList();
          // create a new report template object
          CReportTemplate report = reports.createReportTemplate("Report", "Output for timecourse");
          // set the task type for the report template to timecourse
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
          
          body.Add(new CRegisteredObjectName(model.getObject(new CCopasiObjectName("Reference=Time")).getCN().getString()));
          body.Add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));
          header.Add(new CRegisteredObjectName(new CCopasiStaticString("time").getCN().getString()));
          header.Add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));

          uint i, iMax =(uint) model.getMetabolites().size();
          for (i = 0;i < iMax;++i)
          {
              CMetab metab = model.getMetabolite(i);
              Debug.Assert(metab != null);
              // we don't want output for FIXED metabolites right now
              if (metab.getStatus() != CModelEntity.FIXED)
              {
                  // we want the concentration oin the output
                  // alternatively, we could use "Reference=Amount" to get the
                  // particle number
                  body.Add(new CRegisteredObjectName(metab.getObject(new CCopasiObjectName("Reference=Concentration")).getCN().getString()));
                  // add the corresponding id to the header
                  header.Add(new CRegisteredObjectName(new CCopasiStaticString(metab.getSBMLId()).getCN().getString()));
                  // after each entry, we need a seperator
                  if(i!=iMax-1)
                  {
                    body.Add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));
                    header.Add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));
                  }

              }
          }


          // get the trajectory task object
          CTrajectoryTask trajectoryTask = (CTrajectoryTask)dataModel.getTask("Time-Course");
          Debug.Assert(trajectoryTask != null);
          // if there isn't one
          if (trajectoryTask == null)
          {
              // create a new one
              trajectoryTask = new CTrajectoryTask();

              // add the new time course task to the task list
              // this method makes sure that the object is now owned 
              // by the list and that it does not get deleted by SWIG
              dataModel.getTaskList().addAndOwn(trajectoryTask);
          }

          // run a deterministic time course
          trajectoryTask.setMethodType(CCopasiMethod.deterministic);

          // pass a pointer of the model to the problem
          trajectoryTask.getProblem().setModel(dataModel.getModel());

          // actiavate the task so that it will be run when the model is saved
          // and passed to CopasiSE
          trajectoryTask.setScheduled(true);

          // set the report for the task
          trajectoryTask.getReport().setReportTemplate(report);
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
          Debug.Assert(parameter.getType() == CCopasiParameter.DOUBLE);
          parameter.setDblValue(1.0e-12);

          bool result=true;
          try
          {
              // now we run the actual trajectory
              result=trajectoryTask.process(true);
          }
          catch
          {
              System.Console.Error.WriteLine( "Error. Running the time course simulation failed." );
              // check if there are additional error messages
              if (CCopasiMessage.size() > 0)
              {
                  // print the messages in chronological order
                  System.Console.Error.WriteLine(CCopasiMessage.getAllMessageText(true));
              }
              System.Environment.Exit(1);
          }
          if(result==false)
          {
              System.Console.Error.WriteLine( "An error occured while running the time course simulation." );
              // check if there are additional error messages
              if (CCopasiMessage.size() > 0)
              {
                  // print the messages in chronological order
                  System.Console.Error.WriteLine(CCopasiMessage.getAllMessageText(true));
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
