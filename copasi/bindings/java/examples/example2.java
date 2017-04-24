// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
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
        assert CRootContainer.getRoot() != null;
        // create a new datamodel
        CDataModel dataModel = CRootContainer.addDatamodel();
        assert CRootContainer.getDatamodelList().size() == 1;
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
                CCompartment compartment = model.getCompartment(i);
                assert compartment != null;
                System.out.println("\t" + compartment.getObjectName());
            }

            // output number and names of all metabolites
            iMax = (int)model.getMetabolites().size();
            System.out.println("Number of Metabolites: " + (new Integer(iMax)).toString());
            System.out.println("Metabolites: ");
            for (i = 0;i < iMax;++i)
            {
                CMetab metab = model.getMetabolite(i);
                assert metab != null;
                System.out.println("\t" + metab.getObjectName());
            }

            // output number and names of all reactions
            iMax = (int)model.getReactions().size();
            System.out.println("Number of Reactions: " + (new Integer(iMax)).toString());
            System.out.println("Reactions: ");
            for (i = 0;i < iMax;++i)
            {
                CReaction reaction = model.getReaction(i);
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
