// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

import org.COPASI.*;

/**
 * This example, loads the given COPASI file, creates an output handler
 * that collects all additionally entered display names during the execution
 * of the scan task.
 *
 * Example:
 *
 *   java CustomOutput CardioGlyco-v1.cps "[ATP]" "[ADP]"
 *
 * would load the cps file, run the scan defined therein, while collecting ATP
 * and ADP concentrations
 *
 */
public class CustomOutput {

  public static void main(String[] args) {

    if (args.length == 0)
       {
         System.out.println("usage: CustomOutput <cps file> displayName1 ...");
         return;
       }

       CDataModel dataModel = CRootContainer.addDatamodel();

       if (!dataModel.loadModel(args[0]))
       {
         System.out.println("Couldn't open the model: ");
         System.out.println(CCopasiMessage.getAllMessageText());
         return;
       }

       // create data handler that collects all named elements
       CDataHandler dh = new CDataHandler();
       for (int i = 1; i < args.length; i++)
       {
         CDataObject obj = dataModel.findObjectByDisplayName(args[i]);

         // if we got null returned, the element wasn't found
         if (obj == null)
         {
           System.err.println("the display name: " + args[i] + " could not be resolved in the model, skipping.");
           continue;
         }

         // if it is a model entity, we want to narrow it to its value
         // reference
         if (obj instanceof CModelEntity)
           obj = ((CModelEntity) obj).getValueReference();

         // add as during handler to collect during the execution of the task
         dh.addDuringName(new CRegisteredCommonName( obj.getCN().getString()));

         // also collect the same data after the task is run
         dh.addAfterName(new CRegisteredCommonName( obj.getCN().getString()));
       }

       
       // now get the scan task and run it.
       CCopasiTask task = dataModel.getTask("Scan");

       // initialize passing along the output handler
       if (!task.initializeRawWithOutputHandler((int)CCopasiTask.OUTPUT_UI, dh))
       {
         System.err.println("Couldn't initialize the steady state task");
         System.err.println(CCopasiMessage.getAllMessageText());
         System.exit(1);
       }

       //run
       if (!task.processRaw(true))
       {
         System.err.println("Couldn't run the steady state task");
         System.err.println(CCopasiMessage.getAllMessageText());
         System.exit(1);
       }

       task.restore();

       // at this point we have the output we collected, lets just print it

       // print header
       for (int i = 1; i < args.length; i++)
       {
         System.out.print(args[1]);

         if (i + 1 < args.length)
           System.out.print("\t");
       }
       System.out.println();

       // get number of rows recorded
       int numRows = dh.getNumRowsDuring();

       // print each row collected during the run
       for (int i = 0; i < numRows; i++)
       {
         FloatStdVector data = dh.getNthRow(i);
         for (int j = 0; j < data.size(); j++)
         {
           System.out.print(data.get(j));
           if (j + 1 < data.size())
             System.out.print("\t");
         }
         System.out.println();
       }
       System.out.println();

       // print final row collected after the run
       FloatStdVector data = dh.getAfterData();
       for (int j = 0; j < data.size(); j++)
       {
         System.out.print(data.get(j));
         if (j + 1 < data.size())
           System.out.print("\t");
       }


  }

}
