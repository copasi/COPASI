// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

import org.COPASI.*;

/**
 * This example sets up the scan task from the command line.
 * 
 * It will take:
 * 
 * * an input copasi file: specifying the file to read * an output copasi file:
 * specifying where to save to * a task name: specifying the subtask to run in
 * the scan * then an arbitray number of scan items of the form:
 * "|scan,displayName,numSteps,min,max|"
 * 
 * 
 * So an example call would be:
 * 
 * SetupScan CardioGlyco-v1.cps out.cps "Steady-State"  "|scan,(Phosphofructosekinase).Vmax_4,10,40,160|"
 * 
 * this would read the CardioGlyco-v1.cps file, clear all scan items from it,
 * set the subtask to the steady state task, then add a scan item for the Vmax_4
 * value with 10 steps going from 40 to 160. Finally the result is written to
 * out.cps.
 *
 */
public class SetupScan {

	private static boolean addScanItem(CScanProblem problem, SetupScan.ScanItem item) {

		if (!item.valid)
			return false;

		if (item.type != CScanProblem.SCAN_LINEAR) {
			// need do add a bit of things to the scan item parsing, before they
			// are supported
			return false;
		}

		CCopasiParameterGroup cItem = problem.addScanItem(item.type, item.numSteps);

		// the parameters below already exist for SCAN_LINEAR, so we can just
		// set the values
		cItem.getParameter("Maximum").setDblValue(item.maxValue);
		cItem.getParameter("Minimum").setDblValue(item.minValue);
		cItem.getParameter("Object").setCNValue(item.cn);

		return true;
	}

	public static void main(String[] args) {

		if (args.length < 4) {
			System.out.println("usage: SetupScan inputFile outputFile subTask scanItem1...");
			return;
		}

		ScanDescription arg = new ScanDescription(args);
		if (!arg.valid) {
			System.err.println("The input arguments are not valid.");
			System.exit(1);
		}

		CDataModel dm = CRootContainer.addDatamodel();

		if (!dm.loadModel(arg.inputFile)) {
			System.err.println("Couldn't read COPASI file");
			System.err.println(CCopasiMessage.getAllMessageText());
			System.exit(1);
		}

		// resolve all the scan items from names to cn:
		if (!arg.resolveNames(dm)) {
			System.err.println("Couldn't resolve scan item name");
			System.exit(2);
		}

		CScanTask task = (CScanTask) dm.getTask("Scan");
		CScanProblem problem = (CScanProblem) task.getProblem();

		// set subtask
		problem.setSubtask(arg.subTask);

		// remove all existing scan items
		problem.clearScanItems();

		// then add the items
		for (ScanItem item : arg.scanItems) {
			if (!addScanItem(problem, item)) {
				System.err.println("Couldn't add Scan item");
				System.exit(2);
			}
		}

		// now save the file
		if (!dm.saveModel(arg.outputFile, true)) {
			System.err.println("Couldn't save COPASI file");
			System.err.println(CCopasiMessage.getAllMessageText());
			System.exit(1);
		}

	}

	/**
	 * Utility class parsing the command line argument into something that is easier
	 * to handle.
	 */
	static class ScanItem {

		ScanItem(String arg) {
			valid = false;

			if (!(arg.startsWith("|") && arg.endsWith("|"))) {
				System.err.println(
						"Invalid scan item, it should be of the form: |scan,(Phosphofructosekinase).Vmax_4,10,40,160|");
				return;
			}

			String[] parts = arg.substring(1, arg.length() - 1).split(",");

			if (parts.length != 5) {
				System.err.println(
						"Invalid scan item, it should be of the form: |scan,(Phosphofructosekinase).Vmax_4,10,40,160|");
				return;
			}

			typeName = parts[0].trim();

			if (typeName.equals("scan"))
				type = CScanProblem.SCAN_LINEAR;

			displayName = parts[1].trim();
			numSteps = Integer.valueOf(parts[2].trim());
			minValue = Double.valueOf(parts[3].trim());
			maxValue = Double.valueOf(parts[4].trim());

			valid = true;

		}

		boolean resolveDisplayName(CDataModel dm) {
			CDataObject obj = dm.findObjectByDisplayName(displayName);
			if (obj == null) {
				valid = false;
				System.err.println("couldn't resolve displayName: " + displayName);
				return false;
			}

			if (obj instanceof CModelEntity) {
				// resolve model elements to their initial value reference
				obj = ((CModelEntity) obj).getInitialValueReference();
			} else if (obj instanceof CCopasiParameter) {
				// resolve local parameters to its value reference
				obj = ((CCopasiParameter) obj).getValueReference();
			}

			cn = obj.getCN().getString();
			return true;
		}

		public boolean valid;
		public String typeName;
		public int type;
		public String displayName;
		public Integer numSteps;
		public Double minValue;
		public Double maxValue;
		public String cn;
	}

	/**
	 * Utility class parsing the command line arguments
	 */
	static class ScanDescription {

		ScanDescription(String[] args) {
			valid = false;
			inputFile = args[0];
			outputFile = args[1];
			subTaskName = args[2];

			switch (subTaskName) {
			case "Steady-State":
				subTask = CTaskEnum.Task_steadyState;
				break;
			case "Time-Course":
				subTask = CTaskEnum.Task_timeCourse;
				break;
			case "Optimization":
				subTask = CTaskEnum.Task_optimization;
				break;
			case "Parameter Estimation":
				subTask = CTaskEnum.Task_parameterFitting;
				break;
			case "Metabolic Control Analysis":
				subTask = CTaskEnum.Task_mca;
				break;
			case "Lyapunov Exponents":
				subTask = CTaskEnum.Task_lyap;
				break;
			case "Sensitivities":
				subTask = CTaskEnum.Task_sens;
				break;

			default:
				System.err.println("Unsupported subTask.");
				return;
			}

			scanItems = new ScanItem[args.length - 3];

			for (int i = 3; i < args.length; i++) {
				scanItems[i - 3] = new ScanItem(args[i]);
				if (!scanItems[i - 3].valid)
					return;
			}

			valid = true;

		}

		boolean resolveNames(CDataModel dm) {
			boolean result = true;

			for (int i = 0; i < scanItems.length; i++)
				result |= scanItems[i].resolveDisplayName(dm);

			return result;
		}

		public boolean valid;
		public String inputFile;
		public String outputFile;
		public String subTaskName;
		public int subTask;
		public ScanItem[] scanItems;

	}

}
