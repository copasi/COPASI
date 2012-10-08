// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

/**
 * This is an example on how to access an unsupported annotation on a model element.
 */
import org.COPASI.*;

public class printUnsupportedAnnotation
{
	public static void main(String[] args)
	{
		System.loadLibrary("CopasiJava");
		assert CCopasiRootContainer.getRoot() != null;
		// create a new datamodel
		CCopasiDataModel dataModel = CCopasiRootContainer.addDatamodel();
		assert CCopasiRootContainer.getDatamodelList().size() == 1;
		
		if (args.length != 1)
		{
			System.err.println("Need one argument: SBML | CPS filename.");
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
			CModel model = dataModel.getModel();
			int numAnnotations = model.getNumUnsupportedAnnotations();
			System.out.println("The model has: " + numAnnotations + " unsupported annotations.");
			
			if (numAnnotations ==  0)
			{
				// we don't have an annotation, so lets add one
				model.addUnsupportedAnnotation("http://myannotation.org", "<test xmlns='http://myannotation.org' value='blaaaahaaa'/>");
				
			}
			System.out.println("The name of the first is: " + model.getUnsupportedAnnotationName(0));
			System.out.println("The raw xml of the first is: " + model.getUnsupportedAnnotation(0));
		}
		catch(java.lang.Exception ex)
		{
			System.err.println("Error: " + ex.getMessage());
		}
	}
}
