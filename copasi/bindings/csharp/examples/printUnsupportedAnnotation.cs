// Begin git Header 
//   Commit: b65477b5186fddedce2954f221e2baf96295c096 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-10-08 10:26:47 +0200 
// End git Header 

// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

/**
 * This is an example on how to access an unsupported annotation on a model element.
 */
using org.COPASI;
using System;
using System.Diagnostics;


public class printUnsupportedAnnotation
{
	public static void Main(String[] args)
	{
		// create a new datamodel
		CDataModel dataModel = CRootContainer.addDatamodel();
		
		if (args.Length != 1)
		{
			Console.WriteLine("Need one argument: SBML | CPS filename.");
			Environment.Exit(1);
		}
		
		String filename = args[0];
		try
		{
			String ext = System.IO.Path.GetExtension(filename);
			if (ext.Trim().ToLowerInvariant().EndsWith("xml"))
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
			CModel model = dataModel.getModel();
			int numAnnotations = model.getNumUnsupportedAnnotations();
			Console.WriteLine("The model has: " + numAnnotations + " unsupported annotations.");
			
			if (numAnnotations ==  0)
			{
				Console.WriteLine("adding custom annotation");
				// we don't have an annotation, so lets add one
				if (!model.addUnsupportedAnnotation("http://myannotation.org", "<test xmlns='http://myannotation.org' value='blaaaahaaa'/>"))
				{
					Console.WriteLine("couldn't set annotation: ");
					Console.WriteLine(CCopasiMessage.getAllMessageText());
				}
				
			}
			Console.WriteLine("The name of the first is: " + model.getUnsupportedAnnotationName(0));
			Console.WriteLine("The raw xml of the first is: " + model.getUnsupportedAnnotation(0));
		}
		catch (Exception ex)
		{
			Console.WriteLine("Error: " + ex.Message);
		}
	}
}
