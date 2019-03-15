/**
 * This is an example on how to build models with the COPASI backend API.
 */
using org.COPASI;
using System.Diagnostics;

class example1
{

 static void Main()
 {
     Debug.Assert(CRootContainer.getRoot() != null);
     // create a new datamodel
     CDataModel dataModel = CRootContainer.addDatamodel();
     Debug.Assert(CRootContainer.getDatamodelList().size() == 1);
     // get the model from the datamodel
     CModel model = dataModel.getModel();
     Debug.Assert(model != null);
     // set the units for the model
     // we want seconds as the time unit
     // microliter as the volume units
     // and nanomole as the substance units
     model.setTimeUnit(CUnit.s);
     model.setVolumeUnit(CUnit.microl);
     model.setQuantityUnit(CUnit.nMol);

     // we have to keep a set of all the initial values that are changed during
     // the model building process
     // They are needed after the model has been built to make sure all initial
     // values are set to the correct initial value
     ObjectStdVector changedObjects=new ObjectStdVector();

     // create a compartment with the name cell and an initial volume of 5.0
     // microliter
     CCompartment compartment = model.createCompartment("cell", 5.0);
     CDataObject obj= compartment.getInitialValueReference();
     Debug.Assert(obj!= null);
     changedObjects.Add(obj);
     Debug.Assert(compartment != null);
     Debug.Assert(model.getCompartments().size() == 1);
     // create a new metabolite with the name glucose and an inital
     // concentration of 10 nanomol
     // the metabolite belongs to the compartment we created and is is to be
     // fixed
     CMetab glucose = model.createMetabolite("glucose", compartment.getObjectName(), 10.0, CModelEntity.Status_FIXED);
     obj = glucose.getInitialValueReference();
     Debug.Assert(obj != null);
     changedObjects.Add(obj);
     Debug.Assert(glucose != null);
     Debug.Assert(model.getMetabolites().size() == 1);
     // create a second metabolite called glucose-6-phosphate with an initial
     // concentration of 0. This metabolite is to be changed by reactions
     CMetab g6p = model.createMetabolite("glucose-6-phosphate", compartment.getObjectName(), 0.0, CModelEntity.Status_REACTIONS);
     Debug.Assert(g6p != null);
     obj = g6p.getInitialValueReference();
     Debug.Assert(obj != null);
     changedObjects.Add(obj);
     Debug.Assert(model.getMetabolites().size() == 2);
     // another metabolite for ATP, also fixed
     CMetab atp = model.createMetabolite("ATP", compartment.getObjectName(), 10.0, CModelEntity.Status_FIXED);
     Debug.Assert(atp != null);
     obj = atp.getInitialValueReference();
     Debug.Assert(obj != null);
     changedObjects.Add(obj);
     Debug.Assert(model.getMetabolites().size() == 3);
     // and one for ADP
     CMetab adp = model.createMetabolite("ADP", compartment.getObjectName(), 0.0, CModelEntity.Status_REACTIONS);
     Debug.Assert(adp != null);
     obj = adp.getInitialValueReference();
     Debug.Assert(obj != null);
     changedObjects.Add(obj);
     Debug.Assert(model.getMetabolites().size() == 4);
     // now we create a reaction
     CReaction reaction = model.createReaction("hexokinase");
     Debug.Assert(reaction != null);
     Debug.Assert(model.getReactions().size() == 1);
     // hexokinase converts glucose and ATP to glucose-6-phosphate and ADP
     // we can set these on the chemical equation of the reaction
     CChemEq chemEq = reaction.getChemEq();
     // glucose is a substrate with stoichiometry 1
     chemEq.addMetabolite(glucose.getKey(), 1.0, CChemEq.SUBSTRATE);
     // ATP is a substrate with stoichiometry 1
     chemEq.addMetabolite(atp.getKey(), 1.0, CChemEq.SUBSTRATE);
     // glucose-6-phosphate is a product with stoichiometry 1
     chemEq.addMetabolite(g6p.getKey(), 1.0, CChemEq.PRODUCT);
     // ADP is a product with stoichiometry 1
     chemEq.addMetabolite(adp.getKey(), 1.0, CChemEq.PRODUCT);
     Debug.Assert(chemEq.getSubstrates().size() == 2);
     Debug.Assert(chemEq.getProducts().size() == 2);
     // this reaction is to be irreversible
     reaction.setReversible(false);
     Debug.Assert(reaction.isReversible() == false);
     // now we ned to set a kinetic law on the reaction
     // maybe constant flux would be OK
     // we need to get the function from the function database
     CFunctionDB funDB = CRootContainer.getFunctionList();
     Debug.Assert(funDB != null);
     // it should be in the list of suitable functions
     // lets get all suitable functions for an irreversible reaction with  2 substrates
     // and 2 products
     CFunctionStdVector suitableFunctions = funDB.suitableFunctions(2, 2, COPASI.TriFalse);
     Debug.Assert((suitableFunctions.Count > 0));
     int i,iMax=(int)suitableFunctions.Count;
     for (i=0;i<iMax;++i)
     {
         // we just assume that the only suitable function with Constant in
         // it's name is the one we want
         if (suitableFunctions[i].getObjectName().IndexOf("Constant") != -1)
         {
             break;
         }
     }
     if (i != iMax)
     {
         // we set the function
         // the method should be smart enough to associate the reaction entities
         // with the correct function parameters
         reaction.setFunction(suitableFunctions[i]);
         Debug.Assert(reaction.getFunction() != null);
         // constant flux has only one function parameter
         Debug.Assert(reaction.getFunctionParameters().size() == 1);
         // so there should be only one entry in the parameter mapping as well
         Debug.Assert(reaction.getParameterCNs().Count == 1);
         CCopasiParameterGroup parameterGroup = reaction.getParameters();
         Debug.Assert(parameterGroup.size() == 1);
         CCopasiParameter parameter = parameterGroup.getParameter(0);
         // make sure the parameter is a local parameter
         Debug.Assert(reaction.isLocalParameter(parameter.getObjectName()));
         // now we set the value of the parameter to 0.5
         Debug.Assert(parameter.getType() == CCopasiParameter.Type_DOUBLE);
         parameter.setDblValue(0.5);
         obj = parameter.getValueReference();
         Debug.Assert(obj != null);
         changedObjects.Add(obj);
     }
     else
     {
         System.Console.Error.WriteLine("Error. Could not find a kinetic law that conatins the term \"Constant\".");
         System.Environment.Exit(1);
     }
     // now we also create a separate reaction for the backwards reaction and
     // set the kinetic law to irreversible mass action
     // now we create a reaction
     reaction = model.createReaction("hexokinase-backwards");
     Debug.Assert(reaction != null);
     Debug.Assert(model.getReactions().size() == 2);
     chemEq = reaction.getChemEq();
     // glucose is a product with stoichiometry 1
     chemEq.addMetabolite(glucose.getKey(), 1.0, CChemEq.PRODUCT);
     // ATP is a product with stoichiometry 1
     chemEq.addMetabolite(atp.getKey(), 1.0, CChemEq.PRODUCT);
     // glucose-6-phosphate is a substrate with stoichiometry 1
     chemEq.addMetabolite(g6p.getKey(), 1.0, CChemEq.SUBSTRATE);
     // ADP is a substrate with stoichiometry 1
     chemEq.addMetabolite(adp.getKey(), 1.0, CChemEq.SUBSTRATE);
     Debug.Assert(chemEq.getSubstrates().size() == 2);
     Debug.Assert(chemEq.getProducts().size() == 2);
     // this reaction is to be irreversible
     reaction.setReversible(false);
     Debug.Assert(reaction.isReversible() == false);
     // now we ned to set a kinetic law on the reaction
     CFunction massAction = (CFunction)funDB.findFunction("Mass action (irreversible)");
     Debug.Assert(massAction != null);
     // we set the function
     // the method should be smart enough to associate the reaction entities
     // with the correct function parameters
     reaction.setFunction(massAction);
     Debug.Assert(reaction.getFunction() != null);

     Debug.Assert(reaction.getFunctionParameters().size() == 2);
     // so there should be two entries in the parameter mapping as well
     Debug.Assert(reaction.getParameterCNs().Count == 2);
     // mass action is a special case since the parameter mappings for the
     // substrates (and products) are in a vector

     // Let us create a global parameter that is determined by an assignment
     // and that is used as the rate constant of the mass action kinetics
     // it gets the name rateConstant and an initial value of 1.56
     CModelValue modelValue = model.createModelValue("rateConstant", 1.56);
     Debug.Assert(modelValue != null);
     obj = modelValue.getInitialValueReference();
     Debug.Assert(obj != null);
     changedObjects.Add(obj);
     Debug.Assert(model.getModelValues().size() == 1);
     // set the status to assignment
     modelValue.setStatus(CModelEntity.Status_ASSIGNMENT);
     // the assignment does not have to make sense
     modelValue.setExpression("1.0 / 4.0 + 2.0");

     // now we have to adjust the parameter mapping in the reaction so
     // that the kinetic law uses the global parameter we just created instead
     // of the local one that is created by default
     // The first parameter is the one for the rate constant, so we point it to
     // the key of out model value
     reaction.setParameterObject(0, modelValue);
     // now we have to set the parameter mapping for the substrates
     reaction.addParameterObject("substrate", g6p);
     reaction.addParameterObject("substrate", adp);

     // finally compile the model
     // compile needs to be done before updating all initial values for
     // the model with the refresh sequence
     model.compileIfNecessary();

     // now that we are done building the model, we have to make sure all
     // initial values are updated according to their dependencies
     model.updateInitialValues(changedObjects);

     // save the model to a COPASI file
     // we save to a file named example1.cps 
     // and we want to overwrite any existing file with the same name
     // Default tasks are automatically generated and will always appear in cps
     // file unless they are explicitley deleted before saving.
     dataModel.saveModel("example1.cps", true);

     // export the model to an SBML file
     // we save to a file named example1.xml, we want to overwrite any
     // existing file with the same name and we want SBML L2V3
     try
     {
       dataModel.exportSBML("example1.xml", true, 2, 3);
     }
     catch
     {
        System.Console.Error.WriteLine("Error. Exporting the model to SBML failed.");
     }
 }
}
