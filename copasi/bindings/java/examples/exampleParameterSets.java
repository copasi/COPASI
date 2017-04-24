// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

import org.COPASI.CDataModel;
import org.COPASI.CCopasiMessage;
import org.COPASI.CRootContainer;
import org.COPASI.CModel;
import org.COPASI.CModelParameterSet;
import org.COPASI.CModelParameter;
import org.COPASI.ModelParameterSetVectorN;

public class exampleParameterSets
{

    public static void main(String[] args)
    {
        CRootContainer.init();

        if (args.length == 0)
        {
            System.err.println("Need one argument, copasi file");
            System.exit(1);
        }

        CDataModel dataModel = CRootContainer.addDatamodel();
        if (!dataModel.loadModel(args[0]))
        {
            System.err.println("Could not open file");
            System.err.println(CCopasiMessage.getAllMessageText());
            System.exit(1);
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
        
        int count = (int) parameterSets.size();
        System.out.println(String.format("There are: %d parametersets", count));
        
        for (int i = 0; i < count; i++)
        {
            CModelParameterSet current = (CModelParameterSet) parameterSets.get(i);
            printParameterSet(current);
        }

    }


    private static void printParameterSet(CModelParameterSet set)
    {
        System.out.println(String.format("  key           : %s", set.getKey()));
        System.out.println(String.format("  name          : %s", set.getName()));
        System.out.println(String.format("  isActive      : %b", set.isActive()));
       
        int numGroups = set.size();
        System.out.println(String.format("  num groups    : %s", numGroups));
        
        for (int i = 0; i < numGroups; i++)
        {
            CModelParameter current = set.getModelParameter(i);
            printModelParameter(current, i);            
        }
        
    }
    
    private static void printModelParameter(CModelParameter param, int count)
    {                
        System.out.print(String.format("  % d = %s (%s)", count, param.getName(), param.getCN().getString()));
        
        if (param.hasValue())
            System.out.print(String.format(" --> %f", param.getValue()));
        else if (param.isInitialExpressionValid() && param.getInitialExpression().length() > 0 )
            System.out.print(String.format(" --> %s", param.getInitialExpression()));
        System.out.println();
        int numChildren = (int)param.getNumChildren();
        for (int i = 0; i < numChildren; i++)
        {
            CModelParameter current = param.getChild(i);
            printModelParameter(current, i);
        }        
    }
}
