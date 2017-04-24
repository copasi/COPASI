// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Inteectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

using org.COPASI;
using System;
using System.Diagnostics;

public class exampleParameterSets
{

  public static void Main(String[] args)
  {
    if (args.Length == 0)
    {
      Console.WriteLine("Need one argument, copasi file");
      Environment.Exit(1);
    }

    CDataModel dataModel = CRootContainer.addDatamodel();
    if (!dataModel.loadModel(args[0]))
    {
      Console.WriteLine("Could not open file");
      Console.WriteLine(CCopasiMessage.getAllMessageText());
      Environment.Exit(1);
    }

    CModel model = dataModel.getModel();
    ModelParameterSetVectorN sets = model.getModelParameterSets();

    // if we don't have one, create one
    if (sets.size() == 0)
    {
      CModelParameterSet newSet = new CModelParameterSet("Current State", model);
      newSet.createFromModel();
      printParameterSet(newSet);
      sets.add(newSet);
    }

    // interrogate the exiting parameter sets
    printExistingParametersets(model.getModelParameterSets());

  }


  private static void
          printExistingParametersets(ModelParameterSetVectorN parameterSets)
  {

    int count = (int)parameterSets.size();
    Console.WriteLine(String.Format("There are: %d parametersets", count));

    for (uint i = 0; i < count; i++)
    {
      CModelParameterSet current = (CModelParameterSet)parameterSets.get(i);
      printParameterSet(current);
    }

  }


  private static void printParameterSet(CModelParameterSet set)
  {
    Console.WriteLine(String.Format("  key           : {0}", set.getKey()));
    Console.WriteLine(String.Format("  name          : {0}", set.getName()));
    Console.WriteLine(String.Format("  isActive      : {0}", set.isActive()));

    int numGroups = (int)set.size();
    Console.WriteLine(String.Format("  num groups    : {0}", numGroups));

    for (int i = 0; i < numGroups; i++)
    {
      CModelParameter current = set.getModelParameter(i);
      printModelParameter(current, i);
    }

  }

  private static void printModelParameter(CModelParameter param, int count)
  {
    Console.Write(String.Format("  {0} = {1} ({2})", count, param.getName(), param.getCN().getString()));

    if (param.hasValue())
      Console.Write(String.Format(" --> {0}", param.getValue()));
    else if (param.isInitialExpressionValid() && !string.IsNullOrEmpty(param.getInitialExpression()))
      Console.Write(String.Format(" --> {0}", param.getInitialExpression()));
    Console.WriteLine();
    int numChildren = (int)param.getNumChildren();
    for (uint i = 0; i < numChildren; i++)
    {
      CModelParameter current = param.getChild(i);
      printModelParameter(current, (int)i);
    }
  }
}
