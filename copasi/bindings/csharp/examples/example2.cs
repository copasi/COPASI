/**
 * This is an example on how to load a cps file
 * and output some information on the model
 */

using org.COPASI;
using System.Diagnostics;

class example2
{
    static void Main(string[] args)
    {
        Debug.Assert(CRootContainer.getRoot() != null);
        // create a new datamodel
        CDataModel dataModel = CRootContainer.addDatamodel();
        Debug.Assert(CRootContainer.getDatamodelList().size() == 1);
        // the only argument to the main routine should be the name of a CPS file
        if (args.Length == 1)
        {
            string filename = args[0];
            try
            {
                // load the model without progress report
                dataModel.loadModel(filename);
            }
            catch
            {
                System.Console.Error.WriteLine("Error while loading the model from file named \"" + filename + "\".");
                System.Environment.Exit(1);
            }
            CModel model = dataModel.getModel();
            Debug.Assert(model != null);
            System.Console.WriteLine("Model statistics for model \"" + model.getObjectName() + "\".");

            // output number and names of all compartments
            uint i, iMax = (uint)model.getCompartments().size();
            System.Console.WriteLine("Number of Compartments: " + System.Convert.ToString(iMax));
            System.Console.WriteLine("Compartments: ");
            for (i = 0;i < iMax;++i)
            {
                CCompartment compartment = model.getCompartment(i);
                Debug.Assert(compartment != null);
                System.Console.WriteLine("\t" + compartment.getObjectName());
            }

            // output number and names of all metabolites
            iMax = (uint)model.getMetabolites().size();
            System.Console.WriteLine("Number of Metabolites: " + System.Convert.ToString(iMax));
            System.Console.WriteLine("Metabolites: ");
            for (i = 0;i < iMax;++i)
            {
                CMetab metab = model.getMetabolite(i);
                Debug.Assert(metab != null);
                System.Console.WriteLine("\t" + metab.getObjectName());
            }

            // output number and names of all reactions
            iMax = (uint)model.getReactions().size();
            System.Console.WriteLine("Number of Reactions: " + System.Convert.ToString(iMax));
            System.Console.WriteLine("Reactions: ");
            for (i = 0;i < iMax;++i)
            {
                CReaction reaction = model.getReaction(i);
                Debug.Assert(reaction != null);
                System.Console.WriteLine("\t" + reaction.getObjectName());
            }
        }
        else
        {
            System.Console.Error.WriteLine("Usage: example2 CPSFILE");
            System.Environment.Exit(1);
        }

    }
}
