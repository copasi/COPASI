using org.COPASI;
using System;
using System.Diagnostics;

public class Run_MCA
{

  static CCopasiDataModel dataModel = null;

  /// <summary>
  /// Utility function printing an annotated matrix
  /// </summary>
  /// <param name="title"></param>
  /// <param name="annotated_matrix"></param>
  public static void print_annotated_matrix(string title, CArrayAnnotation annotated_matrix)
  {

    Console.WriteLine(title);
    Console.WriteLine("==========");

    var size = annotated_matrix.size();
    if (size.Count != 2)
    {
      Console.WriteLine("  This simple function only deals with two dimensional matrices");
      return;
    }

    var rows = size[0];
    var columns = size[1];

    Console.WriteLine(string.Format("Size of the matrix is: {0} rows x {1} columns", rows, columns));

    var row_headers = annotated_matrix.getAnnotationsString(0);
    var col_headers = annotated_matrix.getAnnotationsString(1);

    // print column headers
    Console.Write("\t\t");
    for (int i = 0; i < columns; ++i)
      Console.Write(string.Format("{0}\t", col_headers[i]));
    Console.WriteLine();

    for (int j = 0; j < rows; ++j)
    {


      for (int i = 0; i < columns; ++i)
      {
        if (i == 0)
          Console.Write(string.Format("{0}\t", row_headers[j]));

        var current_object = annotated_matrix.getObject(new CCopasiObjectName(string.Format("[{0}][{1}]", j, i)));
        var current = current_object.printToString();
        Console.Write(string.Format("{0}\t", current));
      }
      Console.WriteLine();
    }
    Console.WriteLine();
  }

  /// <summary>
  /// This function runs the MCA task on the given SBML file
  /// </summary>
  /// <param name="file_name"></param>
  public static void run_mca(string file_name)
  {
    if (dataModel == null)
      dataModel = CCopasiRootContainer.addDatamodel();

    // load COPASI file
    if (file_name.EndsWith(".cps"))
    {
      if (!dataModel.loadModel(file_name))
      {
        Console.WriteLine("Could not load COPASI file due to:");
        Console.WriteLine(CCopasiMessage.getAllMessageText());
        Environment.Exit(1);
      }
    }
    // load sbml file
    else if (!dataModel.importSBML(file_name))
    {
      Console.WriteLine("Could not load SBML file due to:");
      Console.WriteLine(CCopasiMessage.getAllMessageText());
      Environment.Exit(1);
    }

    // setup mca task
    var task = dataModel.getTask("Metabolic Control Analysis") as CMCATask;
    //# mark task as executable
    task.setScheduled(true);
    var problem = task.getProblem() as CMCAProblem;
    // specify that we want to perform steady state analysis
    problem.setSteadyStateRequested(true);

    // run mca task
    if (!task.initialize((int)CCopasiTask.OUTPUT_UI))
    {
      Console.WriteLine("could not initialize mca task");
      Console.WriteLine(CCopasiMessage.getAllMessageText());
      Environment.Exit(2);
    }
    if (!task.processWithOutputFlags(true, (int)CCopasiTask.OUTPUT_UI))
    {
      Console.WriteLine("could not run mca task");
      Console.WriteLine(task.getProcessError());
      Environment.Exit(3);
    }
    // messages
    Console.WriteLine(CCopasiMessage.getAllMessageText());
    Console.WriteLine(task.getProcessError());

    // print results
    var method = task.getMethod() as CMCAMethod;
    print_annotated_matrix("Scaled Concentration Control Coefficients", method.getScaledConcentrationCCAnn());
    print_annotated_matrix("Scaled Flux Control Coefficients", method.getScaledFluxCCAnn());
    print_annotated_matrix("Scaled Elasticities", method.getScaledElasticitiesAnn());

  }

  public static int Main(String[] args)
  {
    if (args.Length != 1)
    {
      Console.WriteLine("usage: run_mca <sbml file | copasi file>");
      return 1;
    }
    run_mca(args[0]);
    return 0;
  }
}