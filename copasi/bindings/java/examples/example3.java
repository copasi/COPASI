// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
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
		assert CRootContainer.getRoot() != null;
		// create a new datamodel
		CDataModel dataModel = CRootContainer.addDatamodel();
		assert CRootContainer.getDatamodelList().size() == 1;

		// the only argument to the main routine should be the name of an SBML file
		if (args.length != 1) {
			System.err.println("Usage: example3 SBMLFILE" );
			System.exit(1);
		}

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
		CReportDefinition report = createReportDefinition(model, reports);


		// get the trajectory task object
		CTrajectoryTask trajectoryTask = 
				(CTrajectoryTask)dataModel.getTask("Time-Course");
		assert trajectoryTask != null;

		// run a deterministic time course
		trajectoryTask.setMethodType(CTaskEnum.Method_deterministic);

		// pass a pointer of the model to the problem
		trajectoryTask.getProblem().setModel(dataModel.getModel());

		// activate the task so that it will be run when the model is saved
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
		assert parameter.getType() == CCopasiParameter.Type_DOUBLE;
		parameter.setDblValue(1.0e-12);

		boolean result=true;
		try
		{
			// now we run the actual trajectory , the output flag identifies, what 
			// sort of output is collected when running the task, important options
			// are: 
			//
			//	CCopasiTask.OUTPUT_UI: collect the same output, as the UI 
			//	CCopasiTask.OUTPUT_UI
			//
			result=trajectoryTask.processWithOutputFlags(true, (int)CCopasiTask.OUTPUT_UI);
		}
		catch (java.lang.Exception ex)
		{
			System.err.println( "Error. Running the time course simulation failed." );
			String lastError = trajectoryTask.getProcessError();
			// check if there are additional error messages
			if (lastError.length() > 0)
			{
				// print the messages in chronological order
				System.err.println(lastError);
			}
			System.exit(1);
		}
		
		if(result==false)
		{
			System.err.println( "An error occured while running the time course simulation." );
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
		int iMax = (int)timeSeries.getNumVariables();
		int lastIndex = (int)timeSeries.getRecordedSteps() - 1;
		for (int i = 0;i < iMax;++i)
		{
			// here we get the particle number (at least for the species)
			// the unit of the other variables may not be particle numbers
			// the concentration data can be acquired with getConcentrationData
			System.out.println(timeSeries.getTitle(i) + ": " + (new Double(timeSeries.getData(lastIndex, i))).toString() );
		}

	}

	private static CReportDefinition createReportDefinition(CModel model, CReportDefinitionVector reports) 
	{
		CReportDefinition report = reports.createReportDefinition("Report", "Output for timecourse");
		// set the task type for the report definition to timecourse
		report.setTaskType(CTaskEnum.Task_timeCourse);
		// we don't want a table
		report.setIsTable(false);
		// the entries in the output should be separated by a ", "
		report.setSeparator(new CCopasiReportSeparator(", "));

		// we need a handle to the header and the body
		// the header will display the ids of the metabolites and "time" for
		// the first column
		// the body will contain the actual timecourse data
		ReportItemVector header = report.getHeaderAddr();
		ReportItemVector body = report.getBodyAddr();

		body.add(new CRegisteredCommonName(model.getObject(new CCommonName("Reference=Time")).getCN().getString()));
		body.add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));
		header.add(new CRegisteredCommonName(new CDataString("time").getCN().getString()));
		header.add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));

		int i, iMax =(int) model.getMetabolites().size();
		for (i = 0;i < iMax;++i)
		{
			CMetab metab = model.getMetabolite(i);
			assert metab != null;
			// we don't want output for FIXED metabolites right now
			if (metab.getStatus() != CModelEntity.Status_FIXED)
			{
				// we want the concentration oin the output
				// alternatively, we could use "Reference=Amount" to get the
				// particle number
				body.add(new CRegisteredCommonName(metab.getObject(new CCommonName("Reference=Concentration")).getCN().getString()));
				// add the corresponding id to the header
				header.add(new CRegisteredCommonName(new CDataString(metab.getSBMLId()).getCN().getString()));
				// after each entry, we need a separator
				if(i!=iMax-1)
				{
					body.add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));
					header.add(new CRegisteredCommonName(report.getSeparator().getCN().getString()));
				}

			}
		}
		return report;
	}
}
