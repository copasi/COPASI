/**
 * This is an example on how to calculate and output the Jacobian matrix
 * in COPASI
 */
using org.COPASI;
using System.Diagnostics;

class example8
{

  protected static string MODEL_STRING = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n <!-- Created by COPASI version 4.5.31 (Debug) on 2010-05-11 13:40 with libSBML version 4.1.0-b3. -->\n <sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">\n <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n <listOfUnitDefinitions>\n <unitDefinition id=\"volume\" name=\"volume\">\n <listOfUnits>\n <unit kind=\"litre\" scale=\"-3\"/>\n </listOfUnits>\n </unitDefinition>\n <unitDefinition id=\"substance\" name=\"substance\">\n <listOfUnits>\n <unit kind=\"mole\" scale=\"-3\"/>\n </listOfUnits>\n </unitDefinition>\n <unitDefinition id=\"unit_0\">\n <listOfUnits>\n <unit kind=\"second\" exponent=\"-1\"/>\n </listOfUnits>\n </unitDefinition>\n </listOfUnitDefinitions>\n <listOfCompartments>\n <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n </listOfCompartments>\n <listOfSpecies>\n <species metaid=\"COPASI2\" id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n <species metaid=\"COPASI3\" id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n <species metaid=\"COPASI4\" id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n </listOfSpecies>\n <listOfReactions>\n <reaction metaid=\"COPASI5\" id=\"reaction_1\" name=\"reaction_1\" reversible=\"false\">\n <listOfReactants>\n <speciesReference species=\"species_1\"/>\n </listOfReactants>\n <listOfProducts>\n <speciesReference species=\"species_2\"/>\n </listOfProducts>\n <kineticLaw>\n <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n <apply>\n <times/>\n <ci> compartment_1 </ci>\n <ci> k1 </ci>\n <ci> species_1 </ci>\n </apply>\n </math>\n <listOfParameters>\n <parameter id=\"k1\" name=\"k1\" value=\"0.2\" units=\"unit_0\"/>\n </listOfParameters>\n </kineticLaw>\n </reaction>\n <reaction metaid=\"COPASI6\" id=\"reaction_2\" name=\"reaction_2\" reversible=\"false\">\n <listOfReactants>\n <speciesReference species=\"species_2\"/>\n </listOfReactants>\n <listOfProducts>\n <speciesReference species=\"species_3\"/>\n </listOfProducts>\n <kineticLaw>\n <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n <apply>\n <times/>\n <ci> compartment_1 </ci>\n <ci> k1 </ci>\n <ci> species_2 </ci>\n </apply>\n </math>\n <listOfParameters>\n <parameter id=\"k1\" name=\"k1\" value=\"0.1\" units=\"unit_0\"/>\n </listOfParameters>\n </kineticLaw>\n </reaction>\n </listOfReactions>\n </model>\n </sbml>\n";


  static void Main()
  {
    Debug.Assert((CRootContainer.getRoot() != null));
    // create a new datamodel
    CDataModel dataModel = CRootContainer.addDatamodel();
    Debug.Assert((dataModel != null));
    Debug.Assert((CRootContainer.getDatamodelList().size() == 1));
    // next we import a simple SBML model from a string

    // clear the message queue so that we only have error messages from the import in the queue
    CCopasiMessage.clearDeque();
    bool result=true;
    try
    {
      result = dataModel.importSBMLFromString(MODEL_STRING);
    }
    catch
    {
        System.Console.Error.WriteLine("Import of model failed miserably.");
        System.Environment.Exit(1);
    }
    // check if the import was successful
    int mostSevere = CCopasiMessage.getHighestSeverity();
    // if it was a filtered error, we convert it to an unfiltered type
    // the filtered error messages have the same value as the unfiltered, but they
    // have the 7th bit set which basically adds 128 to the value
    mostSevere = mostSevere & 127;

    // we assume that the import succeeded if the return value is true and
    // the most severe error message is not an error or an exception
    if (result != true &&  mostSevere < CCopasiMessage.ERROR)
    {
        System.Console.Error.WriteLine("Sorry. Model could not be imported.");
        System.Environment.Exit(1);
    }

    //
    // now we tell the model object to calculate the jacobian
    //
    CModel model = dataModel.getModel();
    Debug.Assert((model != null));

    if (model != null)
    {
        // running a task, e.g. a trajectory will automatically make sure that
        // the initial values are transferred to the current state before the calculation begins.
        // If we use low level calculation methods like the one to calculate the jacobian, we
        // have to make sure the the initial values are applied to the state
        model.applyInitialValues();
        // we need an array that stores the result
        // the size of the matrix does not really matter because
        // the calculateJacobian autoamtically resizes it to the correct
        // size
        FloatMatrix jacobian=new FloatMatrix();
        // the first parameter to the calculation function is a reference to
        // the matrix where the result is to be stored
        // the second parameter is the derivationFactor for the calculation
        // it basically represents a relative delta value for the calculation of the derivatives
        // the third parameter is a boolean indicating whether the jacobian should
        // be calculated from the reduced (true) or full (false) system
        model.getMathContainer().calculateJacobian(jacobian, 1e-12, false);
        // now we print the result
        // the jacobian stores the values in the order they are
        // given in the user order in the state template so it is not really straight
        // forward to find out which column/row corresponds to which species
        CStateTemplate stateTemplate = model.getStateTemplate();
        // and we need the user order
        SizeTVector userOrder = stateTemplate.getUserOrder();
        // from those two, we can construct an new vector that contains
        // the names of the entities in the jacobian in the order in which they appear in
        // the jacobian
        System.Collections.Generic.List<string> nameVector=new System.Collections.Generic.List<string>();
        CModelEntity entity = null;
        int status;

        for (uint i = 0; i < userOrder.size(); ++i)
        {
            entity = stateTemplate.getEntity(userOrder.get(i));
            Debug.Assert((entity != null));
            // now we need to check if the entity is actually
            // determined by an ODE or a reaction
            status = entity.getStatus();

            if (status == CModelEntity.Status_ODE ||
                    (status == CModelEntity.Status_REACTIONS && entity.isUsed()))
            {
                nameVector.Add(entity.getObjectName());
            }
        }

        Debug.Assert((nameVector.Count == jacobian.numRows()));
        // now we print the matrix, for this we assume that no
        // entity name is longer then 5 character which is a save bet since
        // we know the model
        System.Console.Out.NewLine = "";
        System.Console.WriteLine(System.String.Format("Jacobian Matrix:{0}",System.Environment.NewLine));
        System.Console.WriteLine(System.String.Format("size:{0}x{1}{2}", jacobian.numRows(), jacobian.numCols(), System.Environment.NewLine));
        System.Console.WriteLine(System.String.Format("{0}", System.Environment.NewLine));
        System.Console.Out.WriteLine(System.String.Format("{0,7}"," "));

        for (int i = 0; i < nameVector.Count; ++i)
        {
            System.Console.Out.WriteLine(System.String.Format("{0,7}",nameVector[i]));
        }

        System.Console.WriteLine(System.String.Format("{0}", System.Environment.NewLine));

        for (uint i = 0; i < nameVector.Count; ++i)
        {
            System.Console.Out.WriteLine(System.String.Format("{0,7}",nameVector[(int)i]));

            for (uint j = 0; j < nameVector.Count; ++j)
            {
                System.Console.Out.WriteLine(System.String.Format("{0,7:0.###}",jacobian.get(i,j)));
            }

            System.Console.WriteLine(System.String.Format("{0}", System.Environment.NewLine));
        }

        // we can also calculate the jacobian of the reduced system
        // in a similar way
        model.getMathContainer().calculateJacobian(jacobian, 1e-12, true);
        // this time generating the output is actually simpler because the rows
        // and columns are ordered in the same way as the independent variables of the state temple
        System.Console.WriteLine(System.String.Format("{0}{0}",System.Environment.NewLine));
        System.Console.WriteLine(System.String.Format("Reduced Jacobian Matrix:{0}{0}", System.Environment.NewLine));
        System.Console.Out.WriteLine(System.String.Format("{0:6}"," "));
        
        uint iMax = stateTemplate.getNumIndependent();
        
        for (uint i=0;i<iMax;++i)
        {
          System.Console.Out.WriteLine(System.String.Format("\t{0:7}",stateTemplate.getIndependent(i).getObjectName()));
        }

        System.Console.WriteLine(System.String.Format("{0}",System.Environment.NewLine));

        for (uint i = 0; i < iMax; ++i)
        {
            System.Console.Out.WriteLine(System.String.Format("{0:7}",stateTemplate.getIndependent(i).getObjectName()));

            for (uint j = 0; j < iMax; ++j)
            {
                System.Console.Out.WriteLine(System.String.Format("{0,7:0.###}",jacobian.get(i,j)));
            }

            System.Console.WriteLine(System.String.Format("{0}", System.Environment.NewLine));
        }

    }

  }

}

