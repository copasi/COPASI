/**
 * This is an example on how to export the math model from a copasi file.
 */
import org.COPASI.*;

public class exampleMathExport
{

	public static void main(String[] args)
	{
		System.loadLibrary("CopasiJava");
		assert CCopasiRootContainer.getRoot() != null;
		// create a new datamodel
		CCopasiDataModel dataModel = CCopasiRootContainer.addDatamodel();
		assert CCopasiRootContainer.getDatamodelList().size() == 1;
		
		if (args.length != 2)
		{
			System.err.println("Need to arguments, filename and filter.");
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
			System.out.println(dataModel.exportMathModelToString(args[1]));
		}
		catch(java.lang.Exception ex)
		{
			System.err.println("Error. Exporting the model to math failed.");
		}
	}
}
