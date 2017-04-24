// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

/**
 * This is an example on how to export the math model from a copasi file.
 */
import org.COPASI.*;

public class exampleMathExport
{
	public static void main(String[] args)
	{
		System.loadLibrary("CopasiJava");
		assert CRootContainer.getRoot() != null;
		// create a new datamodel
		CDataModel dataModel = CRootContainer.addDatamodel();
		assert CRootContainer.getDatamodelList().size() == 1;
		
		if (args.length != 2)
		{
			System.err.println("Need two arguments: filename and filter.");
			System.exit(1);
		}
		
		String filename = args[0];
		try
		{
			String ext = filename.substring(filename.lastIndexOf('.') + 1);
			if (ext.trim().toLowerCase().equals("xml"))
			{
				// load the model without progress report
				dataModel.importSBML(filename);
			}         
			else
			{
				// load the model without progress report
				dataModel.loadModel(filename);
			}         
		}
		catch (java.lang.Exception ex)
		{
			System.err.println("Error while loading the model from file named \"" + filename + "\".");
			System.exit(1);
		}
		try
		{
			// clear warnings / error messages
			CCopasiMessage.clearDeque();
			
			// convert
			String translation = dataModel.exportMathModelToString(args[1]);
			
			// if conversion failed print message
			if (translation.length() == 0)
			{
				System.err.println("Translation failed: ");
				System.err.println(CCopasiMessage.getAllMessageText());
			}
			
			// print translation 
			System.out.println(translation);
		}
		catch(java.lang.Exception ex)
		{
			System.err.println("Error. Exporting the model to math failed.");
		}
	}
}
