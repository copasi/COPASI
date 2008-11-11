// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/ParameterEstimationServiceSkeleton.java,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: jdada $ 
//   $Date: 2008/11/11 12:19:57 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

/**
 * ParameterEstimationServiceSkeleton.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis2 version: 1.3  Built on : Aug 10, 2007 (04:45:47 LKT)
 */
package org.copasi.copasiws.services.parameterestimationws;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Properties;
import java.util.Random;

import org.apache.axiom.om.util.UUIDGenerator; 
//import org.apache.catalina.tribes.util.UUIDGenerator;

import org.apache.xmlbeans.XmlOptions;
import org.copasi.condorClient.CondorScheddStub;
import org.copasi.copasiws.services.parameterestimationws.types.AffectedExperiment;
import org.copasi.copasiws.services.parameterestimationws.types.ArbitraryVariable;
import org.copasi.copasiws.services.parameterestimationws.types.ExperimentalData;
import org.copasi.copasiws.services.parameterestimationws.types.GeneticAlgorithm;
import org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument;
import org.copasi.copasiws.services.parameterestimationws.types.ItemToFit;
import org.copasi.copasiws.services.parameterestimationws.types.LevenbergMarquardt;
import org.copasi.copasiws.services.parameterestimationws.types.Method;
import org.copasi.copasiws.services.parameterestimationws.types.ModelObject;
import org.copasi.copasiws.services.parameterestimationws.types.ModelToExperimentMap;
import org.copasi.copasiws.services.parameterestimationws.types.OutputResult;
import org.copasi.copasiws.services.parameterestimationws.types.ParticleSwarm;
import org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument;
import org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument;
import org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument;
import org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument;
import org.copasi.copasiws.services.parameterestimationws.types.SimulatedAnnealing;
import org.copasi.copasiws.services.parameterestimationws.types.Species;
import org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument;
import org.copasi.copasiws.services.parameterestimationws.types.Status;
import org.copasi.copasiws.services.parameterestimationws.types.StatusCode;
import org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument;
import org.copasi.copasiws.services.parameterestimationws.types.User;
import org.copasi.copasiws.services.parameterestimationws.types.WeightMethod;
import org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument;
import org.copasi.jobmanager.CondorJobManager;
import org.copasi.jobmanager.CopasiExecutor;
import org.copasi.schema.COPASIDocument;
import org.copasi.schema.CPARAMETER;
import org.copasi.schema.CPARAMETERLIST;
import org.copasi.schema.CREPORTSECTION;
import org.copasi.schema.CTASKTYPE;
import org.copasi.utils.FileProcessor;
import org.copasi.utils.SimpleUserChecker;
import org.sbrml.www.sbrml.level1.version1.Operation;
import org.sbrml.www.sbrml.level1.version1.ResultComponent;
import org.sbrml.www.sbrml.level1.version1.SbrmlDocument;

import condor.ClassAdStruct;


/**
 *  ParameterEstimationServiceSkeleton java skeleton for the axisService
 */
public class ParameterEstimationServiceSkeleton {

    // the directory for all user jobs, will the set through configuration file in the future.
    String copasiWSJobDirectory = "/usr/local/CopasiWSJobs";
    /**

    /**
     * Auto generated method signature
     * @param createSimulationResource
     */
    public org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceResponseDocument createSimulationResource(
        org.copasi.copasiws.services.parameterestimationws.types.CreateSimulationResourceDocument createSimulationResource)
        throws ServiceFaultMessage {
    	CreateSimulationResourceResponseDocument respDoc = CreateSimulationResourceResponseDocument.Factory
		.newInstance();
		CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse createSimulationResponse = CreateSimulationResourceResponseDocument.CreateSimulationResourceResponse.Factory
				.newInstance();
		
		
		Random rand = new Random();	
		// the resource Id
		int n = 100000;
		int resourceId = rand.nextInt(n+1) + 1;
		// get the user
		User user = createSimulationResource.getCreateSimulationResource().getUser();
		
		//check user name		
		SimpleUserChecker userChecker = new SimpleUserChecker();
		if(!userChecker.checkUser(user.getUserId())){
			throw new ServiceFaultMessage("You are not allowed to use COPASI simulation resource");
		}

		// check if user is allowed to run job on server or if the user has
		// exceeded the allocated no of transaction
		// ...TODO -- this need database query

		// setting the status of simulator resource created by the user
		Status status = Status.Factory.newInstance();
		status.setCode(StatusCode.Enum.forString("SUCCESS"));

		status.setMessage("A new simulator resource has been created for you");			

		// create the directory and file resources for this transaction
		try {
			String userJobDirectory = copasiWSJobDirectory + "/userJobs/"
					+ user.getUserId() + "/" + resourceId;
			boolean success = new File(userJobDirectory).mkdirs();

			// set up the response to the use simulator resource request initiated by the user
			if (success) {				
				createSimulationResponse.setResourceId(resourceId);
			} else {
				System.out.println("There problem creating user's directory resources");
			}

			createSimulationResponse.setStatus(status);
			respDoc.setCreateSimulationResourceResponse(createSimulationResponse);

			// return the response to the user
			return respDoc;
		} catch (Exception e) {
			throw new ServiceFaultMessage("", e);
		}
	}

    /**
     * Auto generated method signature
     * @param sendModel
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SendModelResponseDocument sendModel(
			org.copasi.copasiws.services.parameterestimationws.types.SendModelDocument sendModel)
			throws ServiceFaultMessage {
		SendModelResponseDocument respDoc = SendModelResponseDocument.Factory
				.newInstance();
		SendModelResponseDocument.SendModelResponse sendModelResponse = SendModelResponseDocument.SendModelResponse.Factory
				.newInstance();

		// get the model format
		String inputFormat = sendModel.getSendModel().getInputFormat().toString();

		String copasiml = null;
		String sbml = null;

		// get the resource and the user IDs
		int resourceId = sendModel.getSendModel().getResourceId();
		String userId = sendModel.getSendModel().getUserId();
		
		//check user name
		SimpleUserChecker userChecker = new SimpleUserChecker();
		if(!userChecker.checkUser(userId)){
			throw new ServiceFaultMessage("You are not allowed to use COPASI simulation resource");
		}

		CopasiExecutor executor = new CopasiExecutor();

		String userJobDirectory = copasiWSJobDirectory + "/userJobs/" + userId
				+ "/" + resourceId;

		String sbmlFile = userJobDirectory + "/" + "sbml.xml";
		String copasimlFile = userJobDirectory + "/" + "copasi.cps";

		try {
			// check to know the input format of the model from user.
			if (inputFormat.equalsIgnoreCase("sbml")) {

				// get the sbml model
				sbml = sendModel.getSendModel().getSbml();

				// write the sbml to file in user's job directory
				FileWriter writer = new FileWriter(new File(sbmlFile));
				BufferedWriter buffWriter = new BufferedWriter(writer);
				buffWriter.write(sbml);
				buffWriter.close();
				writer.close();

				// convert the sbml model to copasiml using the command line
				// arguments for copasi
				// create copasi file for the output of conversion process
				File copasiFile = new File(copasimlFile);

				// set up the command line arguments for copasi
				String commandLineArgument = copasiWSJobDirectory
						+ "/copasi-condor/CopasiSE -i " + sbmlFile
						+ " --verbose -s " + copasiFile.toString();

				// execute CopasiSE to convert sbml to copasiml
				executor.executeCopasi(commandLineArgument);

			} else {
				// get the copasiml model
				copasiml = sendModel.getSendModel().getCopasiml();

				// write the copasiml to file in user's job directory
				FileWriter writer = new FileWriter(new File(copasimlFile));
				BufferedWriter buffWriter = new BufferedWriter(writer);
				buffWriter.write(copasiml);
				buffWriter.close();
				writer.close();
			}

			// setting the status of transaction initiated by the user
			Status status = Status.Factory.newInstance();
			status.setCode(StatusCode.Enum.forString("SUCCESS"));
			status.setMessage("Your model file has been saved");
			sendModelResponse.setStatus(status);
			respDoc.setSendModelResponse(sendModelResponse);			

			return respDoc;
		} catch (Exception e) {
			throw new ServiceFaultMessage("", e);
		}
	}

    /**
     * Auto generated method signature
     * @param sendExperimentalData
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataResponseDocument sendExperimentalData(
			org.copasi.copasiws.services.parameterestimationws.types.SendExperimentalDataDocument sendExperimentalData)
			throws ServiceFaultMessage {
		SendExperimentalDataResponseDocument respDoc = SendExperimentalDataResponseDocument.Factory
				.newInstance();
		SendExperimentalDataResponseDocument.SendExperimentalDataResponse sendExpDataResponse = SendExperimentalDataResponseDocument.SendExperimentalDataResponse.Factory
				.newInstance();

		// get the experimental data and the model object map
		ExperimentalData[] userExperiment = sendExperimentalData
				.getSendExperimentalData().getExperimentalDataArray();

		// get the resource and user IDs
		int resourceId = sendExperimentalData.getSendExperimentalData().getResourceId();
		String userId = sendExperimentalData.getSendExperimentalData().getUserId();
		
		//check user name
		SimpleUserChecker userChecker = new SimpleUserChecker();
		if(!userChecker.checkUser(userId)){
			throw new ServiceFaultMessage("You are not allowed to use COPASI simulation resource");
		}

		String userJobDirectory = copasiWSJobDirectory + "/userJobs/" + userId
				+ "/" + resourceId;
		try {
			//save the experimental data from the user
			saveExperimentalData(userExperiment, userJobDirectory);

			// setting the status of transaction initiated by the user
			Status status = Status.Factory.newInstance();
			status.setCode(StatusCode.Enum.forString("SUCCESS"));
			status.setMessage("Your experimental data has been saved to file");

			sendExpDataResponse.setStatus(status);
			respDoc.setSendExperimentalDataResponse(sendExpDataResponse);

			return respDoc;
		} catch (Exception e) {
			System.out.println(e.toString());
			throw new ServiceFaultMessage("", e);
		}

	}

    /**
     * Auto generated method signature
     * @param setModelToExperimentMap
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapResponseDocument setModelToExperimentMap(
			org.copasi.copasiws.services.parameterestimationws.types.SetModelToExperimentMapDocument setModelToExperimentMap)
			throws ServiceFaultMessage {
		SetModelToExperimentMapResponseDocument respDoc = SetModelToExperimentMapResponseDocument.Factory
				.newInstance();
		SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse setModelToExperimentMapResponse = SetModelToExperimentMapResponseDocument.SetModelToExperimentMapResponse.Factory
				.newInstance();

		// get the experiemtal data and the model object map
		ModelToExperimentMap[] userModelToExperimentMap = setModelToExperimentMap
				.getSetModelToExperimentMap().getModelToExperimentMapArray();

		String copasiml = null;

		// get the transaction and the user ID
		int resourceId = setModelToExperimentMap.getSetModelToExperimentMap().getResourceId();
		String userId = setModelToExperimentMap.getSetModelToExperimentMap().getUserId();
		
		//check user name
		SimpleUserChecker userChecker = new SimpleUserChecker();
		if(!userChecker.checkUser(userId)){
			throw new ServiceFaultMessage("You are not allowed to use COPASI simulation resource");
		}

		FileProcessor fileProcessor = new FileProcessor();
		String userJobDirectory = copasiWSJobDirectory + "/userJobs/" + userId
				+ "/" + resourceId;

		String copasimlFile = userJobDirectory + "/" + "copasi.cps";
		COPASIDocument copasiDoc;

		try {
			XmlOptions options = new XmlOptions();
			Map<String, String> substitutes = new HashMap<String, String>();
			substitutes.put("", "http://copasi.org/schema");
			options.setLoadSubstituteNamespaces(substitutes);
			copasiDoc = COPASIDocument.Factory.parse(new File(copasimlFile),
					options);

			// add the model to experiment map to the copasiml model
			copasiDoc = addModelToExperimentMap(copasiDoc,
					userModelToExperimentMap, userJobDirectory);

			String copasiString = copasiDoc.toString();
			//	copasiString = copasiString.replaceAll("&amp;#x09;", "&#x09;");
			
			//copasiString = copasiString.replaceAll("&quot;", "\"");
			

			// save the new copasiml to file
			fileProcessor.saveModelInSpecifiedDirectory(copasiString, userJobDirectory, "copasi.cps");

			// setting the status of transaction initiated by the user
			Status status = Status.Factory.newInstance();
			status.setCode(StatusCode.Enum.forString("SUCCESS"));
			status
					.setMessage("Your model has been updated with the experimental data");

			setModelToExperimentMapResponse.setStatus(status);
			respDoc
					.setSetModelToExperimentMapResponse(setModelToExperimentMapResponse);

			return respDoc;
		} catch (Exception e) {
			System.out.println(e.toString());
			throw new ServiceFaultMessage("", e);
		}
	}

    /**
     * Auto generated method signature
     * @param setFitItemsAndMethod
     */
    public org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodResponseDocument setFitItemsAndMethod(
			org.copasi.copasiws.services.parameterestimationws.types.SetFitItemsAndMethodDocument setFitItemsAndMethod)
			throws ServiceFaultMessage {
		SetFitItemsAndMethodResponseDocument respDoc = SetFitItemsAndMethodResponseDocument.Factory
				.newInstance();
		SetFitItemsAndMethodResponseDocument.SetFitItemsAndMethodResponse setFitItemsAndMethodResponse = SetFitItemsAndMethodResponseDocument.SetFitItemsAndMethodResponse.Factory
				.newInstance();

		// get the item to fit information
		ItemToFit[] itemToFitArray = setFitItemsAndMethod
				.getSetFitItemsAndMethod().getItemToFitArray();
		Method method = setFitItemsAndMethod.getSetFitItemsAndMethod().getMethod();

		String copasiml = null;

		// get the transaction and the user ID
		int resourceId = setFitItemsAndMethod.getSetFitItemsAndMethod().getResourceId();
		String userId = setFitItemsAndMethod.getSetFitItemsAndMethod().getUserId();
		
		//check user name
		SimpleUserChecker userChecker = new SimpleUserChecker();
		if(!userChecker.checkUser(userId)){
			throw new ServiceFaultMessage("You are not allowed to use COPASI simulation resource");
		}

		FileProcessor fileProcessor = new FileProcessor();
		String userJobDirectory = copasiWSJobDirectory + "/userJobs/" + userId
				+ "/" + resourceId;

		String copasimlFile = userJobDirectory + "/" + "copasi.cps";
		String outputTarget = "copasiOutput.txt";
		
		COPASIDocument copasiDoc;

		try {
			XmlOptions options = new XmlOptions();
			Map<String, String> substitutes = new HashMap<String, String>();
			substitutes.put("", "http://copasi.org/schema");
			options.setLoadSubstituteNamespaces(substitutes);
			copasiDoc = COPASIDocument.Factory.parse(new File(copasimlFile), options);

			// add the model to experiment map to the copasiml model
			if (itemToFitArray == null || method == null)
				throw new ServiceFaultMessage(
						"Fit item or method can not be null");

			copasiDoc = addFitItemAndMethod(copasiDoc, itemToFitArray, method,
					outputTarget);

			String copasiString = copasiDoc.toString().replaceAll("&amp;#x09;",
					"&#x09;");
			// String copasiString = copasiDoc.toString().replaceAll("&quot;",
			// "\"");
			copasiString = copasiString.replaceAll("&quot;", "\"");
			
			// save the new copasiml to file
			fileProcessor.saveModelInSpecifiedDirectory(copasiString,
					userJobDirectory, "copasi.cps");			

			// setting the status of the fit item request from the user user
			Status status = Status.Factory.newInstance();
			status.setCode(StatusCode.Enum.forString("SUCCESS"));
			status.setMessage("Your model has been updated with the fit items");

			setFitItemsAndMethodResponse.setStatus(status);
			respDoc.setSetFitItemsAndMethodResponse(setFitItemsAndMethodResponse);

			return respDoc;
		} catch (Exception e) {
			System.out.println(e.toString());
			throw new ServiceFaultMessage("", e);
		}
	}
    
    /**
     * Auto generated method signature
     * @param startSimulator
     */
    public org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorResponseDocument startSimulator(
			org.copasi.copasiws.services.parameterestimationws.types.StartSimulatorDocument startSimulator)
			throws ServiceFaultMessage {
    	StartSimulatorResponseDocument respDoc = StartSimulatorResponseDocument.Factory
				.newInstance();
    	StartSimulatorResponseDocument.StartSimulatorResponse startSimulatorResponse = StartSimulatorResponseDocument.StartSimulatorResponse.Factory
				.newInstance();

		// get the transaction and the user ID
		int resourceId = startSimulator.getStartSimulator().getResourceId();
		String userId = startSimulator.getStartSimulator().getUserId();
		
		//check user name
		SimpleUserChecker userChecker = new SimpleUserChecker();
		if(!userChecker.checkUser(userId)){
			throw new ServiceFaultMessage("You are not allowed to use COPASI simulation resource");
		}

	//	FileProcessor fileProcessor = new FileProcessor();
		String userJobDirectory = copasiWSJobDirectory + "/userJobs/" + userId
				+ "/" + resourceId;
		// testing the condor web services
		CondorJobManager jobManager = new CondorJobManager();

		try {
			String condorService = "http://garfinkel.mib.man.ac.uk:8081";
			CondorScheddStub schedd = new CondorScheddStub(condorService);

			// prepare the files to send to condor
			File file = new File(userJobDirectory);
			File[] myFiles = file.listFiles();
			
			List<String> list = new ArrayList<String>();
			for (int fi = 0; fi < myFiles.length; fi++) {
				list.add(myFiles[fi].getAbsolutePath());
			}
			String[] files = (String[]) list.toArray((new String[0]));

			// System.out.println("After object conversion:" + files);
			ClassAdStruct jobAd = ClassAdStruct.Factory.newInstance();
			Integer []jobInfo = null;
			
			String requirements ="(OpSys == \"LINUX\" && Arch == \"X86_64\") || (OpSys == \"LINUX\" && Arch == \"x86_64\")";
			String arguments = "-s copasi.E.cps --home " + userJobDirectory +" copasi.cps" ;

			if (files.length == 0) throw new Exception("No file input");
			try {
				jobInfo = jobManager.submitJob(schedd,jobAd, files,	userJobDirectory, requirements, arguments);
			} catch (Exception e) {
				throw new ServiceFaultMessage("Problem:" + e.toString());
			}
			if(jobInfo!=null)
			{
				//create job properties file
				Properties jobProps = new Properties();
				jobProps.setProperty("clusterId", String.valueOf(jobInfo[1]));
				jobProps.setProperty("jobId", String.valueOf(jobInfo[2]));				
				FileOutputStream out = new FileOutputStream(userJobDirectory +"/jobProps");
				jobProps.store(out, "---No Comment---");
				out.close();				
				
				// setting the status of the fit item request from the user user
				Status status = Status.Factory.newInstance();
				status.setCode(StatusCode.Enum.forString("SUCCESS"));
				status.setMessage("Parameter estimation simulator has been started");				
				startSimulatorResponse.setStatus(status);
				respDoc.setStartSimulatorResponse(startSimulatorResponse);
				System.out.println("Succesfull job submission to condor ========:"+ jobInfo[1]);
			}else throw new ServiceFaultMessage("Simulator fails to start, job can not be submitted to condor. try again");
			
			return respDoc;
		} catch (Exception e) {
			System.out.println(e.toString());
			throw new ServiceFaultMessage("", e);
		}
	}

    /**
     * Auto generated method signature
     * @param getSimulatorStatus
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusResponseDocument getSimulatorStatus(
			org.copasi.copasiws.services.parameterestimationws.types.GetSimulatorStatusDocument getSimulatorStatus)
			throws ServiceFaultMessage {
		GetSimulatorStatusResponseDocument respDoc = GetSimulatorStatusResponseDocument.Factory.newInstance();
		GetSimulatorStatusResponseDocument.GetSimulatorStatusResponse getSimulatorStatusResponse = GetSimulatorStatusResponseDocument.GetSimulatorStatusResponse.Factory.newInstance();
		
		// get the user and resource IDs
		int resourceId = getSimulatorStatus.getGetSimulatorStatus().getResourceId();
		String userId = getSimulatorStatus.getGetSimulatorStatus().getUserId();

		//check user name
		SimpleUserChecker userChecker = new SimpleUserChecker();
		if(!userChecker.checkUser(userId)){
			throw new ServiceFaultMessage("You are not allowed to use COPASI simulation resource");
		}
		
		String userJobDirectory = copasiWSJobDirectory + "/userJobs/" + userId 	+ "/" + resourceId;
		
		// testing the condor web services
		CondorJobManager jobManager = new CondorJobManager();
				
		int clusterId = 0;
		int jobId = 0;	

		try {
			String condorService = "http://garfinkel.mib.man.ac.uk:8081";
			CondorScheddStub schedd = new CondorScheddStub(condorService);

			int jobStatus; 		
			try {
				// load job job properties
				Properties jobProps = new Properties();
				FileInputStream in = new FileInputStream(userJobDirectory + "/jobProps");
				jobProps.load(in);
				in.close();
				clusterId = Integer.parseInt(jobProps.getProperty("clusterId"));
				jobId = Integer.parseInt(jobProps.getProperty("jobId"));
				jobStatus = jobManager.getJobAd(schedd, clusterId, jobId);
			} catch (Exception e) {
				throw new ServiceFaultMessage("Problem:" + e.toString());
			}
			// setting the status of the get simulator status request from the user user
			Status status = Status.Factory.newInstance();
			switch (jobStatus) {
				case 0:
					status.setCode(StatusCode.Enum.forString("CANNOT_BE_STARTED"));
					status.setMessage("Try again later");
				case 1:
					status.setCode(StatusCode.Enum.forString("SCHEDULE_TO_START"));
					status.setMessage("Simulation about to start");
					break;
				case 2:
					status.setCode(StatusCode.Enum.forString("RUNNING"));
					status.setMessage("Simulation is running, check for results later");	
					break;
				case 3:
					status.setCode(StatusCode.Enum.forString("STARTING_PROBLEM"));
					status.setMessage("Problem is start the simulation engine, please recreate another resource");	
					break;	
				case 4:
					status.setCode(StatusCode.Enum.forString("COMPLETED"));
					status.setMessage("Simulation is completed, you can now request for your simulation results");	
					break;
				case 5:
					status.setCode(StatusCode.Enum.forString("SUSPENDED"));
					status.setMessage("Simulation has been suspended, check later for status later");	
					break;					
				default:
					throw new ServiceFaultMessage("Sorry, no response from the simulator, try again later");				
			}				
			getSimulatorStatusResponse.setStatus(status);
			respDoc.setGetSimulatorStatusResponse(getSimulatorStatusResponse);				
			return respDoc;
		} catch (Exception e) {
			System.out.println(e.toString());
			throw new ServiceFaultMessage("", e);
		}
	}

    /**
     * Auto generated method signature
     * @param getResult
     */
    public org.copasi.copasiws.services.parameterestimationws.types.GetResultResponseDocument getResult(
        org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument getResult)
        throws ServiceFaultMessage {
    	GetResultResponseDocument respDoc = GetResultResponseDocument.Factory.newInstance();
    	GetResultResponseDocument.GetResultResponse getResultResponse = GetResultResponseDocument.GetResultResponse.Factory.newInstance();
		
		// get the user and resource IDs
		int resourceId = getResult.getGetResult().getResourceId();
		String userId = getResult.getGetResult().getUserId();
		String outputFormat = getResult.getGetResult().getOutputFormat().toString();
		
		//check user name
		SimpleUserChecker userChecker = new SimpleUserChecker();
		if(!userChecker.checkUser(userId)){
			throw new ServiceFaultMessage("You are not allowed to use COPASI simulation resource");
		}
		
		String userJobDirectory = copasiWSJobDirectory + "/userJobs/" + userId 	+ "/" + resourceId;
		
		//initiate the result element document
		OutputResult outputResult = OutputResult.Factory.newInstance();       
		try {
			FileProcessor fileProcessor = new FileProcessor();		
	        String resultText = fileProcessor.readFileAsString(userJobDirectory+"/copasiOutput.txt"); 
	        if(resultText==null){
	        	throw new ServiceFaultMessage("Problem in getting your result, please try again later");
	        }
	        outputResult.setTextResult(resultText);
	        getResultResponse.setOutputResult(outputResult);	        
	        respDoc.setGetResultResponse(getResultResponse);				
			return respDoc;
		} catch (Exception e) {
			System.out.println(e.toString());
			throw new ServiceFaultMessage("", e);
		}
	}
     
    public void saveExperimentalData(ExperimentalData[] userExperiment,
			String userJobDirectory) throws ServiceFaultMessage {
		FileProcessor fileProcessor;

		try {
			for (int k = 0; k < userExperiment.length; k++) {
				fileProcessor = new FileProcessor();
				String experimentalDataId = userExperiment[k].getExperimentDataId();

				// add all experimental data file to job inputFile buffer

				String fileAsString = userExperiment[k].getDataFileInStringFormat();
				experimentalDataId = experimentalDataId.replaceAll(" ", "");

				fileProcessor.writeToFile(fileAsString, userJobDirectory + "/"
						+ experimentalDataId + ".txt");
			}

		} catch (Exception e) {
			e.printStackTrace();
			throw new ServiceFaultMessage(
					"Problem with modification of CopasiML, please try again:",
					e);

		}

	}
    
    public COPASIDocument addModelToExperimentMap(COPASIDocument copasiDoc,
			ModelToExperimentMap[] userModelToExperimentMap,
			String userJobDirectory) throws ServiceFaultMessage {

		try {
			COPASIDocument.COPASI copasi = copasiDoc.getCOPASI();
			COPASIDocument.COPASI.ListOfTasks listOfTasks = copasi
					.getListOfTasks();
			COPASIDocument.COPASI.ListOfTasks.Task[] task = listOfTasks
					.getTaskArray();

			CPARAMETERLIST.ParameterGroup experimentSetGroup = CPARAMETERLIST.ParameterGroup.Factory
					.newInstance();
			experimentSetGroup.setName("Experiment Set");

			for (int i = 0; i < task.length; i++) {
				System.out.println(task[i].getName());
				if (task[i].getName().equalsIgnoreCase("Parameter Estimation")) {
					COPASIDocument.COPASI.ListOfTasks.Task.Problem problem = task[i]
							.getProblem();

					CPARAMETERLIST.ParameterGroup[] paramGroup = problem
							.getParameterGroupArray();

					for (int j = 0; j < paramGroup.length; j++) {
						if (paramGroup[j].getName().equalsIgnoreCase(
								"Experiment Set")) {

							CPARAMETERLIST.ParameterGroup paramSubGroup;

							for (int k = 0; k < userModelToExperimentMap.length; k++) {

								String experimentDataId = userModelToExperimentMap[k]
										.getExperimentDataId();
								if (experimentDataId == null)
									throw new ServiceFaultMessage(
											"You must supply experimenta Data Id");
								// debug, must be removed
								System.out.println(experimentDataId);

								// replace empty space in data id string
								experimentDataId = experimentDataId.replaceAll(" ", "");

								// test to make sure that the experimental data
								// id sent
								// earlier is the same the one use for object
								// map
								File file = new File(userJobDirectory + "/"
										+ experimentDataId + ".txt");
								if (!file.exists()) {
									throw new ServiceFaultMessage(
											"Experimental data Id is not correct");
								}

								paramSubGroup = paramGroup[j]
										.addNewParameterGroup();

								paramSubGroup.setName("Experiment_"
										+ userModelToExperimentMap[k]
												.getExperimentSerialNumber());

								CPARAMETER cParam = paramSubGroup
										.addNewParameter();
								cParam.setName("Key");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("key"));
								cParam.setValue("Experiment_"
										+ userModelToExperimentMap[k]
												.getExperimentSerialNumber());

								cParam = paramSubGroup.addNewParameter();
								cParam.setName("File Name");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("file"));
								cParam.setValue(file.getName());

								cParam = paramSubGroup.addNewParameter();
								cParam.setName("First Row");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("unsignedInteger"));
								cParam.setValue(userModelToExperimentMap[k]
										.getDataFirstRow().toString());

								cParam = paramSubGroup.addNewParameter();
								cParam.setName("Last Row");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("unsignedInteger"));
								cParam.setValue(userModelToExperimentMap[k]
										.getDataLastRow().toString());

								cParam = paramSubGroup.addNewParameter();
								cParam.setName("Experiment Type");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("unsignedInteger"));
								cParam.setValue("1");

								cParam = paramSubGroup.addNewParameter();
								cParam.setName("Separator");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("string"));
								cParam.setValue("&#x09;");

								cParam = paramSubGroup.addNewParameter();
								cParam.setName("Row containing Names");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("unsignedInteger"));
								cParam.setValue("2147483647");

								cParam = paramSubGroup.addNewParameter();
								cParam.setName("Weight Method");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("unsignedInteger"));
								if (userModelToExperimentMap[k]
										.getWeightMethod().equals(
												WeightMethod.MEAN))
									cParam.setValue("0");
								else if (userModelToExperimentMap[k]
										.getWeightMethod().equals(
												WeightMethod.MEAN_SQUARE))
									cParam.setValue("1");
								else if (userModelToExperimentMap[k]
										.getWeightMethod()
										.equals(WeightMethod.STANDARD_DEVIATION))
									cParam.setValue("2");
								else
									throw new ServiceFaultMessage(
											"No such weight method fault");

								cParam = paramSubGroup.addNewParameter();
								cParam.setName("Data is Row Oriented");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("bool"));
								cParam.setValue(String
										.valueOf(userModelToExperimentMap[k]
												.getDataIsRowOriented()));

								cParam = paramSubGroup.addNewParameter();
								cParam.setName("Number of Columns");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("unsignedInteger"));
								cParam.setValue(userModelToExperimentMap[k]
										.getNumberOfColumn().toString());

								// set the object map group
								CPARAMETERLIST.ParameterGroup paramObjectMapGroup;
								paramObjectMapGroup = paramSubGroup
										.addNewParameterGroup();

								paramObjectMapGroup.setName("Object Map");
								ModelObject[] modelObject = userModelToExperimentMap[k]
										.getModelObjectArray();
								for (int mk = 0; mk < modelObject.length; mk++) {

									// String modelObjectType =
									// modelObject[mk].getModelObjectType().toString();

									CPARAMETERLIST.ParameterGroup paramObjectMapSubGroup;

									// model object time

									if (modelObject[mk]
											.getVariableType()
											.equals(
													ModelObject.VariableType.TIME)) {
										paramObjectMapSubGroup = paramObjectMapGroup
												.addNewParameterGroup();
										switch (modelObject[mk]
												.getColumnInExperimentalData()
												.intValue()) {
										case 1:
											paramObjectMapSubGroup.setName("0");
											break;
										case 2:
											paramObjectMapSubGroup.setName("1");
											break;
										case 3:
											paramObjectMapSubGroup.setName("2");
											break;
										default:
											throw new Exception(
													"Invalid column number");
										}
										cParam = paramObjectMapSubGroup
												.addNewParameter();
										cParam.setName("Role");
										cParam.setType(CPARAMETER.Type.Enum
												.forString("unsignedInteger"));
										cParam.setValue("3");
									}

									// model object species

									if (modelObject[mk]
											.getModelObjectType()
											.equals(
													ModelObject.ModelObjectType.SPECIES)) {

										COPASIDocument.COPASI.Model.ListOfMetabolites.Metabolite[] metabolitesArray = copasi
												.getModel()
												.getListOfMetabolites()
												.getMetaboliteArray();
										COPASIDocument.COPASI.Model.ListOfCompartments.Compartment[] compartmentArray = copasi
												.getModel()
												.getListOfCompartments()
												.getCompartmentArray();

										String COPASIKey = getCOPASIKey(copasi,
												modelObject[mk].getSpecies()
														.getModelId());

										if (COPASIKey == null) {
											throw new ServiceFaultMessage(
													"No such modelId in model");
										}
										for (int mi = 0; mi < metabolitesArray.length; mi++) {
											if (metabolitesArray[mi].getKey()
													.equals(COPASIKey)) {
												paramObjectMapSubGroup = paramObjectMapGroup
														.addNewParameterGroup();
												switch (modelObject[mk]
														.getColumnInExperimentalData()
														.intValue()) {
												case 1:
													paramObjectMapSubGroup
															.setName("0");
													break;
												case 2:
													paramObjectMapSubGroup
															.setName("1");
													break;
												case 3:
													paramObjectMapSubGroup
															.setName("2");
													break;
												default:
													throw new Exception(
															"Invalid column number");
												}

												if (modelObject[mk]
														.getVariableType()
														.equals(
																ModelObject.VariableType.INDEPENDENT)) {
													cParam = paramObjectMapSubGroup
															.addNewParameter();
													cParam.setName("Role");
													cParam
															.setType(CPARAMETER.Type.Enum
																	.forString("unsignedInteger"));
													cParam.setValue("1");
												}

												for (int ci = 0; ci < compartmentArray.length; ci++) {
													if (compartmentArray[ci]
															.getKey()
															.equals(
																	metabolitesArray[mi]
																			.getCompartment())) {

														if (modelObject[mk]
																.getSpecies()
																.getQuantityType()
																.equals(
																		Species.QuantityType.INITIAL_CONCENTRATION)) {
															if (metabolitesArray[mi]
																	.getKey()
																	.equals(
																			COPASIKey)) {
																cParam = paramObjectMapSubGroup
																		.addNewParameter();
																cParam
																		.setName("Object CN\" type=\"cn\" value="
																				+ "\"CN=Root,Model="
																				+ copasi
																						.getModel()
																						.getName()
																				+ ",Vector=Compartments["
																				+ compartmentArray[ci]
																						.getName()
																				+ "],"
																				+ "Vector=Metabolites["
																				+ metabolitesArray[mi]
																						.getName()
																				+ "],Reference=InitialConcentration");
															} else if (modelObject[mk]
																	.getSpecies()
																	.getQuantityType()
																	.equals(
																			Species.QuantityType.INITIAL_PARTICLE_NUMBER)) {
																cParam = paramObjectMapSubGroup
																		.addNewParameter();
																cParam
																		.setName("Object CN\" type=\"cn\" value="
																				+ "\"CN=Root,Model="
																				+ copasi
																						.getModel()
																						.getName()
																				+ ",Vector=Compartments["
																				+ compartmentArray[ci]
																						.getName()
																				+ "],"
																				+ "Vector=Metabolites["
																				+ metabolitesArray[mi]
																						.getName()
																				+ "], Reference=InitialParticleNumber");
															}
														}
													}
												}

											}
										}
									}

									// model object arbitrary variable
									if (modelObject[mk]
											.getModelObjectType()
											.equals(
													ModelObject.ModelObjectType.ARBITRARY_VARIABLE)) {
										COPASIDocument.COPASI.Model.ListOfModelValues.ModelValue[] modelValuesArray = copasi
												.getModel()
												.getListOfModelValues()
												.getModelValueArray();

										String COPASIKey = getCOPASIKey(copasi,
												modelObject[mk]
														.getArbitraryVariable()
														.getModelId());
										if (COPASIKey == null) {
											throw new ServiceFaultMessage(
													"No such modelId in model");
										}

										for (int mvi = 0; mvi < modelValuesArray.length; mvi++) {
											if (modelValuesArray[mvi].getKey()
													.equals(COPASIKey)) {

												paramObjectMapSubGroup = paramObjectMapGroup
														.addNewParameterGroup();
												switch (modelObject[mk]
														.getColumnInExperimentalData()
														.intValue()) {
												case 1:
													paramObjectMapSubGroup
															.setName("0");
													break;
												case 2:
													paramObjectMapSubGroup
															.setName("1");
													break;
												case 3:
													paramObjectMapSubGroup
															.setName("2");
													break;
												default:
													throw new Exception(
															"Invalid column number");
												}

												if (modelObject[mk]
														.getVariableType()
														.equals(
																ModelObject.VariableType.DEPENDENT)) {
													cParam = paramObjectMapSubGroup
															.addNewParameter();
													cParam.setName("Role");
													cParam
															.setType(CPARAMETER.Type.Enum
																	.forString("unsignedInteger"));
													cParam.setValue("2");
												}
												if (modelObject[mk]
														.getArbitraryVariable()
														.getQuantityType()
														.equals(
																ArbitraryVariable.QuantityType.VALUE)) {
													cParam = paramObjectMapSubGroup
															.addNewParameter();
													cParam
															.setName("Object CN\" type=\"cn\" value="
																	+ "\"CN=Root,Model="
																	+ copasi
																			.getModel()
																			.getName()
																	+ ",Vector=Values["
																	+ modelValuesArray[mvi]
																			.getName()
																	+ "],Reference=Value");
												} else if (modelObject[mk]
														.getArbitraryVariable()
														.getQuantityType()
														.equals(
																ArbitraryVariable.QuantityType.INITIAL_VALUE)) {
													cParam = paramObjectMapSubGroup
															.addNewParameter();
													cParam
															.setName("Object CN\" type=\"cn\" value="
																	+ "\"CN=Root,Model="
																	+ copasi
																			.getModel()
																			.getName()
																	+ ",Vector=Values["
																	+ modelValuesArray[mvi]
																			.getName()
																	+ "],Reference=InitialValue");
												}
											}
										}
									}

								}

							}
						}
					}

					problem.setParameterGroupArray(paramGroup);
					task[i].setProblem(problem);
					System.out.println("I can't get here please");
					task[i].setScheduled(true);

					// we don't want to repeat the loop if the parameter estimation task
					// has been found
					i = i + 99999;
				}
			}
			listOfTasks.setTaskArray(task);
			copasi.setListOfTasks(listOfTasks);
			copasiDoc.setCOPASI(copasi);

			return copasiDoc;
		} catch (Exception e) {
			e.printStackTrace();
			throw new ServiceFaultMessage(
					"Problem with modification of CopasiML, please try again:",
					e);

		}

	}
    
    public COPASIDocument addFitItemAndMethod(COPASIDocument copasiDoc,
			ItemToFit[] itemToFit, Method userMethod, String outputTarget)
			throws ServiceFaultMessage {

		try {
			COPASIDocument.COPASI copasi = copasiDoc.getCOPASI();
			COPASIDocument.COPASI.ListOfTasks listOfTasks = copasi
					.getListOfTasks();
			COPASIDocument.COPASI.ListOfTasks.Task[] task = listOfTasks
					.getTaskArray();

			// CPARAMETERLIST.ParameterGroup experimentSetGroup =
			// CPARAMETERLIST.ParameterGroup.Factory.newInstance();
			// experimentSetGroup.setName("OptimizationItemList");

			for (int i = 0; i < task.length; i++) {
				System.out.println(task[i].getName());
				if (task[i].getName().equalsIgnoreCase("Parameter Estimation")) {
					COPASIDocument.COPASI.ListOfTasks.Task.Problem problem = task[i]
							.getProblem();

					CPARAMETERLIST.ParameterGroup[] paramGroup = problem
							.getParameterGroupArray();

					for (int j = 0; j < paramGroup.length; j++) {
						if (paramGroup[j].getName().equalsIgnoreCase(
								"OptimizationItemList")) {

							CPARAMETERLIST.ParameterGroup paramSubGroup;

							for (int k = 0; k < itemToFit.length; k++) {

								AffectedExperiment[] affectedExpArray = itemToFit[k]
										.getAffectedExperimentArray();
								// String experimentDataId =
								// itemToFit[k].getExperimentDataId();
								if (affectedExpArray == null)
									throw new ServiceFaultMessage(
											"You must supply the affected experiment");

								// debug, must be removed
								// System.out.println(experimentDataId);

								// replace empty space in data id string
								// experimentDataId =
								// experimentDataId.replaceAll(" ", "");

								// test to make sure that the experimental data
								// id sent
								// earlier is the same the one use for object
								// map
								/*
								 * File file = new File(userJobDirectory +"/" +
								 * experimentDataId + ".txt");
								 * if(!file.exists()){ throw new
								 * ServiceFaultMessage("Experimental data Id is
								 * not correct"); }
								 */

								paramSubGroup = paramGroup[j]
										.addNewParameterGroup();
								paramSubGroup.setName("FitItem");

								if (itemToFit[k].getModelObjectType().equals(
										ItemToFit.ModelObjectType.SPECIES)) {
									CPARAMETER cParam = paramSubGroup
											.addNewParameter();

									COPASIDocument.COPASI.Model.ListOfMetabolites.Metabolite[] metabolitesArray = copasi
											.getModel().getListOfMetabolites()
											.getMetaboliteArray();
									String COPASIKey = getCOPASIKey(copasi,
											itemToFit[k].getSpecies()
													.getModelId());

									// cParam = paramSubGroup.addNewParameter();
									cParam
											.setName("ObjectCN\" type=\"cn\" value="
													+ "\"CN=Root,Model="
													+ copasi.getModel()
															.getName()
													+ ",Vector=Values["
													+ COPASIKey
													+ "],Reference=Value");

								} else if (itemToFit[k]
										.getModelObjectType()
										.equals(
												ItemToFit.ModelObjectType.REACTION)) {
									COPASIDocument.COPASI.Model.ListOfReactions.Reaction[] reactionArray = copasi
											.getModel().getListOfReactions()
											.getReactionArray();

									String rCOPASIKey = getCOPASIKey(copasi,
											itemToFit[k].getReaction()
													.getModelId());
									String paramId = itemToFit[k].getReaction()
											.getParameterID();

									if (rCOPASIKey == null) {
										throw new ServiceFaultMessage(
												"No such reaction with that id in model");
									}

									for (int ri = 0; ri < reactionArray.length; ri++) {
										// if(!reactionArray[ri].getKey().equals(rCOPASIKey)){
										// throw new ServiceFaultMessage("No
										// such reaction with
										// that id in model");
										// }

										for (int pi = 0; pi < reactionArray[ri]
												.getListOfConstants()
												.getConstantArray().length; pi++) {
											// CPARAMETER cParam =
											// paramSubGroup.addNewParameter();
											// for(int cpi=0;
											// cpi<reactionArray[ri].getListOfConstants()onstantArray().getKineticLaw().getListOfCallParameters().getCallParameterArray()[pi].getSourceParameterArray().length;cpi++){
											if (reactionArray[ri].getKey()
													.equals(rCOPASIKey)
													&& reactionArray[ri]
															.getListOfConstants()
															.getConstantArray()[pi]
															.getName().equals(
																	paramId)) {
												CPARAMETER cParam = paramSubGroup
														.addNewParameter();
												// cParam =
												// paramSubGroup.addNewParameter();
												cParam
														.setName("ObjectCN\" type=\"cn\" value="
																+ "\"CN=Root,Model="
																+ copasi
																		.getModel()
																		.getName()
																+ ",Vector=Reactions["
																+ reactionArray[ri]
																		.getName()
																+ "],ParameterGroup=Parameters,Parameter="
																+ paramId
																+ ",Reference=Value");
											}
										}
										// if(reactionArray[i].getListOfConstants().getConstantArray();

										// for(int cpi=0;
										// cpi<reactionArray[ri].getKineticLaw().getListOfCallParameters().getCallParameterArray().length;
										// cpi++){
										/*
										 * for(int cpi=0; cpi<reactionArray[ri].getKineticLaw().getListOfCallParameters().getCallParameterArray()[pi].getSourceParameterArray().length;cpi++){
										 * if(reactionArray[ri].getKineticLaw().getListOfCallParameters().getCallParameterArray()[pi].getSourceParameterArray()[cpi].getReference().equals(pCOPASIKey)){
										 * cParam =
										 * paramSubGroup.addNewParameter();
										 * cParam.setName("Object CN\"
										 * type=\"cn\" value=" +
										 * "\"CN=Root,Model="+
										 * copasi.getModel().getName() +
										 * ",Vector=Reactions[" + rCOPASIKey +"]
										 * ,ParameterGroup=Parameters,Parameter=" +
										 * pCOPASIKey +"Reference=Value"); } }
										 */
										// }
									}
								} else if (itemToFit[k]
										.getModelObjectType()
										.equals(
												ItemToFit.ModelObjectType.ARBITRARY_VARIABLE)) { // model
									// object
									// arbitrary
									// variable
									COPASIDocument.COPASI.Model.ListOfModelValues.ModelValue[] modelValuesArray = copasi
											.getModel().getListOfModelValues()
											.getModelValueArray();

									String COPASIKey = getCOPASIKey(copasi,
											itemToFit[k].getArbitraryVariable()
													.getModelId());
									if (COPASIKey == null) {
										throw new ServiceFaultMessage(
												"No such modelId in model");
									}

									for (int mvi = 0; mvi < modelValuesArray.length; mvi++) {
										if (modelValuesArray[mvi].getKey()
												.equals(COPASIKey)) {
											if (itemToFit[k]
													.getArbitraryVariable()
													.getQuantityType()
													.equals(
															ArbitraryVariable.QuantityType.VALUE)) {
												CPARAMETER cParam = paramSubGroup
														.addNewParameter();
												cParam
														.setName("ObjectCN\" type=\"cn\" value="
																+ "\"CN=Root,Model="
																+ copasi
																		.getModel()
																		.getName()
																+ ",Vector=Values["
																+ modelValuesArray[mvi]
																		.getName()
																+ "],Reference=Value");
											} else if (itemToFit[k]
													.getArbitraryVariable()
													.getQuantityType()
													.equals(
															ArbitraryVariable.QuantityType.INITIAL_VALUE)) {
												CPARAMETER cParam = paramSubGroup
														.addNewParameter();
												cParam
														.setName("ObjectCN\" type=\"cn\" value="
																+ "\"CN=Root,Model="
																+ copasi
																		.getModel()
																		.getName()
																+ ",Vector=Values["
																+ modelValuesArray[mvi]
																		.getName()
																+ "],Reference=InitialValue");
											}
										}
									}
								}
								// COPASIDocument.COPASI.Model.ListOfModelValues.ModelValue
								// [] modelValue =
								// copasi.getModel().getListOfModelValues().getModelValueArray();
								CPARAMETER cParam = paramSubGroup
										.addNewParameter();
								cParam.setName("LowerBound");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("cn"));
								cParam.setValue(Double.toString(itemToFit[k]
										.getLowerBound()));

								cParam = paramSubGroup.addNewParameter();
								cParam.setName("UpperBound");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("cn"));
								cParam.setValue(Double.toString(itemToFit[k]
										.getUpperBound()));

								cParam = paramSubGroup.addNewParameter();
								cParam.setName("StartValue");
								cParam.setType(CPARAMETER.Type.Enum
										.forString("float"));
								cParam.setValue(Float.toString(itemToFit[k]
										.getStartValue()));

								CPARAMETERLIST.ParameterGroup paramAffSubGroup;
								paramAffSubGroup = paramSubGroup
										.addNewParameterGroup();
								paramAffSubGroup
										.setName("Affected Experiments");
								for (int ai = 0; ai < affectedExpArray.length; ai++) {
									if (!affectedExpArray[ai]
											.getExperiment()
											.equals(
													AffectedExperiment.Experiment.ALL)) {
										CPARAMETER cAffParam = paramAffSubGroup
												.addNewParameter();
										cAffParam.setName("Experiment Key");
										cAffParam.setType(CPARAMETER.Type.Enum
												.forString("key"));
										cAffParam.setValue("Experiment_"
												+ affectedExpArray[ai]
														.getExperiment()
														.toString());
									}

								}

							}

						}

					}

					COPASIDocument.COPASI.ListOfTasks.Task.Method method = COPASIDocument.COPASI.ListOfTasks.Task.Method.Factory
							.newInstance();

					System.out.println(userMethod);
					if (userMethod.getMethodName().equals(
							Method.MethodName.LEVENBERG_MARQUARDT)) {
						method.setName(userMethod.getMethodName().toString());
						method.setType("LevenbergMarquardt");
						LevenbergMarquardt lvMarquardt = userMethod
								.getLevenbergMarquardt();

						CPARAMETER cParam = method.addNewParameter();
						cParam.setName("Iteration Limit");
						cParam.setType(CPARAMETER.Type.Enum
								.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(lvMarquardt
								.getIterationLimit()));

						cParam = method.addNewParameter();
						cParam.setName("Tolerance");
						cParam.setType(CPARAMETER.Type.Enum.forString("float"));
						cParam.setValue(String.valueOf(lvMarquardt
								.getTolerance()));
					}else if (userMethod.getMethodName().equals(Method.MethodName.GENETIC_ALGORITHM)) {
						method.setName(userMethod.getMethodName().toString());
						method.setType("GeneticAlgorithm");
						GeneticAlgorithm gAlgorithm = userMethod.getGeneticAlgorithm();

						CPARAMETER cParam = method.addNewParameter();
						cParam.setName("Number of Generations");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(gAlgorithm.getNumberOfGenerations()));

						cParam = method.addNewParameter();
						cParam.setName("Population Size");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(gAlgorithm.getPopulationSize()));
						
						cParam = method.addNewParameter();
						cParam.setName("Random Number Generator");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(gAlgorithm.getRandomNumberGenerator()));
						
						cParam = method.addNewParameter();
						cParam.setName("Seed");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(gAlgorithm.getSeed()));
					}else if (userMethod.getMethodName().equals(Method.MethodName.PARTICLE_SWARM)) {
						method.setName(userMethod.getMethodName().toString());
						method.setType("ParticleSwarm");
						ParticleSwarm pSwarm = userMethod.getParticleSwarm();

						CPARAMETER cParam = method.addNewParameter();
						cParam.setName("Iteration Limit");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(pSwarm.getIterationLimit()));

						cParam = method.addNewParameter();
						cParam.setName("Swarm Size");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(pSwarm.getSwarmSize()));
						
						cParam = method.addNewParameter();
						cParam.setName("Std. Deviation");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(pSwarm.getStandardDeviation()));						
						
						cParam = method.addNewParameter();
						cParam.setName("Random Number Generator");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(pSwarm.getRandomNumberGenerator()));
						
						cParam = method.addNewParameter();
						cParam.setName("Seed");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(pSwarm.getSeed()));						
					}else if (userMethod.getMethodName().equals(Method.MethodName.SIMULATED_ANNEALING)) {
						method.setName(userMethod.getMethodName().toString());
						method.setType("SimulatedAnnealing");
						SimulatedAnnealing sAnnealing = userMethod.getSimulatedAnnealing();
						
						CPARAMETER cParam = method.addNewParameter();
						cParam.setName("Start Temperature");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedFloat"));
						cParam.setValue(String.valueOf(sAnnealing.getStartTemperature()));
						
						cParam = method.addNewParameter();
						cParam.setName("Cooling Factor");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedFloat"));
						cParam.setValue(String.valueOf(sAnnealing.getCoolingFactor()));	
						
						cParam = method.addNewParameter();
						cParam.setName("Tolerance");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedFloat"));
						cParam.setValue(String.valueOf(sAnnealing.getTolerance()));	
						
						cParam = method.addNewParameter();
						cParam.setName("Random Number Generator");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(sAnnealing.getRandomNumberGenerator()));
						
						cParam = method.addNewParameter();
						cParam.setName("Seed");
						cParam.setType(CPARAMETER.Type.Enum.forString("unsignedInteger"));
						cParam.setValue(String.valueOf(sAnnealing.getSeed()));
				        
					}else{throw new ServiceFaultMessage("The optimization method you entered is not yet supported");}
					 
					
					problem.setParameterGroupArray(paramGroup);
					task[i].setProblem(problem);
					System.out.println("I have set Fit items and Method");
					task[i].setScheduled(true);

					// set the file to save the results
					task[i].getReport().setTarget(outputTarget);
					task[i].setMethod(method);
					// we don't want to repeat the loop if the parameter
					// estimation task
					// has been found
					i = i + 99999;

				}
			}

			listOfTasks.setTaskArray(task);
			copasi.setListOfTasks(listOfTasks);
			copasiDoc.setCOPASI(copasi);

			return copasiDoc;
		} catch (Exception e) {
			e.printStackTrace();
			throw new ServiceFaultMessage(
					"Problem with modification of CopasiML, please try again:",
					e);
		}

	}
        
    // get the COPASI key from the SBML id
	public String getCOPASIKey(COPASIDocument.COPASI copasi, String SBMLId) {
		String COPASIKey = null;
		COPASIDocument.COPASI.SBMLReference.SBMLMap[] SBMLMap = copasi
				.getSBMLReference().getSBMLMapArray();
		for (int i = 0; i < SBMLMap.length; i++) {
			if (SBMLMap[i].getSBMLid().equals(SBMLId))
				COPASIKey = SBMLMap[i].getCOPASIkey();
		}
		return COPASIKey;
	}	
}


