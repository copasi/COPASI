// Begin git Header 
//   Commit: cf72a6e3a7662b8b743413467970ba5ea2719ba0 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-10-08 09:13:54 +0200 
// End git Header 

// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

/**
 * This is an example on how to export the math model from a copasi file.
 */
using org.COPASI;
using System;
using System.Diagnostics;

public class exampleMathExport
{
	public static void Main(String[] args)
	{
		// create a new datamodel
		CDataModel dataModel = CRootContainer.addDatamodel();
		
		if (args.Length != 2)
		{
			Console.WriteLine("Need two arguments: filename and filter.");
			Environment.Exit(1);
		}
		
		String filename = args[0];
		try
		{
			String ext =  System.IO.Path.GetExtension(filename);
			if (ext.Trim().ToLowerInvariant() == "xml")
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
		catch 
		{
			Console.WriteLine("Error while loading the model from file named \"" + filename + "\".");
			Environment.Exit(1);
		}
		try
		{
			// clear warnings / error messages
			CCopasiMessage.clearDeque();
			
			// convert
			String translation = dataModel.exportMathModelToString(args[1]);
			
			// if conversion failed print message
			if (string.IsNullOrEmpty(translation))
			{
				Console.WriteLine("Translation failed: ");
				Console.WriteLine(CCopasiMessage.getAllMessageText());
			}
			
			// print translation 
			Console.WriteLine(translation);
		}
		catch
		{
			Console.WriteLine("Error. Exporting the model to math failed.");
		}
	}
}
