// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/examples/example3.java,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2009/03/04 20:01:07 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

/**
 * This is an example on how to import an sbml file
 * create a report for a time course simulation 
 * and run a time course simulation
 */

import org.COPASI.*;

public class example3
{
  public static void main(String[] args)
  {
      assert CCopasiRootContainer.getRoot() != null;
      // create a new datamodel
      CCopasiDataModel dataModel = CCopasiRootContainer.addDatamodel();
      assert CCopasiRootContainer.getDatamodelList().size() == 1;
      // the only argument to the main routine should be the name of an SBML file
      if (args.length == 1)
      {
          String filename = args[0];
          try
          {
              // load the model 
              dataModel.importSBML(filename);
          }
          catch (java.lang.Exception ex)
          {
              System.err.println( "Error while importing the model from file named \"" + filename + "\"." );
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
          
          body.add(new CRegisteredObjectName(new CCopasiObjectName(dataModel.getModel().getCN() + ",Reference=Time").toString()));
          body.add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));
          header.add(new CRegisteredObjectName(new CCopasiStaticString("time").getCN().getString()));
          header.add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));

          int i, iMax =(int) model.getMetabolites().size();
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
                  // after each entry, we need a seperator
                  if(i!=iMax-1)
                  {
                    body.add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));
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
              CCopasiObject object=taskList.getObject(new CCopasiObjectName("Time-Course"));
              assert object != null;
              long index=taskList.getIndex(object);

              taskList.remove(index);

              // add the new time course task to the task list
              taskList.add(trajectoryTask, true);
          }

          // run a deterministic time course
          trajectoryTask.setMethodType(CCopasiMethod.deterministic);

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
          assert parameter != null;
          assert parameter.getType() == CCopasiParameter.DOUBLE;
          parameter.setDblValue(1.0e-12);


          try
          {
              // now we run the actual trajectory
              trajectoryTask.process(true);
          }
          catch (java.lang.Exception ex)
          {
              System.err.println( "Error. Running the time course simulation failed." );
              // check if there are additional error messages
              if (CCopasiMessage.size() > 0)
              {
                  // print the messages in chronological order
                  System.err.println(CCopasiMessage.getAllMessageText(true));
              }
              System.exit(1);
          }

          // look at the timeseries
          CTimeSeries timeSeries = trajectoryTask.getTimeSeries();
          // we simulated 100 steps, including the initial state, this should be
          // 101 step in the timeseries
          assert timeSeries.getRecordedSteps() == 101;
          System.out.println( "The time series consists of " + (new Long(timeSeries.getRecordedSteps())).toString() + "." );
          System.out.println( "Each step contains " + (new Long(timeSeries.getNumVariables())).toString() + " variables." );
          System.out.println( "The final state is: " );
          iMax = (int)timeSeries.getNumVariables();
          int lastIndex = (int)timeSeries.getRecordedSteps() - 1;
          for (i = 0;i < iMax;++i)
          {
              // here we get the particle number (at least for the species)
              // the unit of the other variables may not be particle numbers
              // the concentration data can be acquired with getConcentrationData
              System.out.println(timeSeries.getTitle(i) + ": " + (new Double(timeSeries.getData(lastIndex, i))).toString() );
          }

      }
      else
      {
          System.err.println("Usage: example3 SBMLFILE" );
          System.exit(1);
      }

  }
}
