// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/examples/example2.java,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2009/03/04 20:01:07 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

/**
 * This is an example on how to load a cps file
 * and output some information on the model
 */

import org.COPASI.*;

public class example2
{
    public static void main(String[] args)
    {
        assert CCopasiRootContainer.getRoot() != null;
        // create a new datamodel
        CCopasiDataModel dataModel = CCopasiRootContainer.addDatamodel();
        assert CCopasiRootContainer.getDatamodelList().size() == 1;
        // the only argument to the main routine should be the name of a CPS file
        if (args.length == 1)
        {
            String filename = args[0];
            try
            {
                // load the model without progress report
                dataModel.loadModel(filename);
            }
            catch (java.lang.Exception ex)
            {
                System.err.println("Error while loading the model from file named \"" + filename + "\".");
                System.exit(1);
            }
            CModel model = dataModel.getModel();
            assert model != null;
            System.out.println("Model statistics for model \"" + model.getObjectName() + "\".");

            // output number and names of all compartments
            int i, iMax = (int)model.getCompartments().size();
            System.out.println("Number of Compartments: " + (new Integer(iMax)).toString());
            System.out.println("Compartments: ");
            for (i = 0;i < iMax;++i)
            {
                CCompartment compartment = model.getCompartments().get(i);
                assert compartment != null;
                System.out.println("\t" + compartment.getObjectName());
            }

            // output number and names of all metabolites
            iMax = (int)model.getMetabolites().size();
            System.out.println("Number of Metabolites: " + (new Integer(iMax)).toString());
            System.out.println("Metabolites: ");
            for (i = 0;i < iMax;++i)
            {
                CMetab metab = model.getMetabolites().get(i);
                assert metab != null;
                System.out.println("\t" + metab.getObjectName());
            }

            // output number and names of all reactions
            iMax = (int)model.getReactions().size();
            System.out.println("Number of Reactions: " + (new Integer(iMax)).toString());
            System.out.println("Reactions: ");
            for (i = 0;i < iMax;++i)
            {
                CReaction reaction = model.getReactions().get(i);
                assert reaction != null;
                System.out.println("\t" + reaction.getObjectName());
            }
        }
        else
        {
            System.err.println("Usage: example2 CPSFILE");
            System.exit(1);
        }

    }
}
