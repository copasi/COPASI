/**
 * This is an example on how to create user defined kinetic functions with the COPASI API
 */
using org.COPASI;
using System.Diagnostics;

class example7
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
     CDataObject obj = compartment.getValueReference();
     Debug.Assert(obj != null);
     changedObjects.Add(obj);
     Debug.Assert(compartment != null);
     Debug.Assert(model.getCompartments().size() == 1);
     // create a new metabolite with the name S and an inital
     // concentration of 10 nanomol
     // the metabolite belongs to the compartment we created and is is to be
     // fixed
     CMetab S = model.createMetabolite("S", compartment.getObjectName(), 10.0, CModelEntity.Status_FIXED);
     obj = S.getInitialConcentrationReference();
     Debug.Assert((obj != null));
     changedObjects.Add(obj);
     Debug.Assert((compartment != null));
     Debug.Assert(S != null);
     Debug.Assert(model.getMetabolites().size() == 1);
     // create a second metabolite called P with an initial
     // concentration of 0. This metabolite is to be changed by reactions
     CMetab P = model.createMetabolite("P", compartment.getObjectName(), 0.0, CModelEntity.Status_REACTIONS);
     Debug.Assert(P != null);
     obj = P.getInitialConcentrationReference();
     Debug.Assert(obj != null);
     changedObjects.Add(obj);
     Debug.Assert(model.getMetabolites().size() == 2);

     // now we create a reaction
     CReaction reaction = model.createReaction("reaction");
     Debug.Assert(reaction != null);
     Debug.Assert(model.getReactions().size() == 1);
     // reaction converts S to P
     // we can set these on the chemical equation of the reaction
     CChemEq chemEq = reaction.getChemEq();
     // S is a substrate with stoichiometry 1
     chemEq.addMetabolite(S.getKey(), 1.0, CChemEq.SUBSTRATE);
     // P is a product with stoichiometry 1
     chemEq.addMetabolite(P.getKey(), 1.0, CChemEq.PRODUCT);
     Debug.Assert(chemEq.getSubstrates().size() == 1);
     Debug.Assert(chemEq.getProducts().size() == 1);
     // this reaction is to be irreversible
     reaction.setReversible(false);
     Debug.Assert(reaction.isReversible() == false);

     CModelValue MV = model.createModelValue("K", 42.0);
     // set the status to FIXED
     MV.setStatus(CModelEntity.Status_FIXED);
     Debug.Assert(MV != null);
     obj = MV.getInitialValueReference();
     Debug.Assert(obj != null);
     changedObjects.Add(obj);
     Debug.Assert(model.getModelValues().size() == 1);

     // now we ned to set a kinetic law on the reaction
     // for this we create a user defined function
     CFunctionDB funDB = CRootContainer.getFunctionList();
     Debug.Assert(funDB != null);

     CFunction function = (CFunction)funDB.createFunction("My Rate Law",CEvaluationTree.UserDefined);

     CFunction rateLaw = (CFunction)funDB.findFunction("My Rate Law");

     Debug.Assert(rateLaw != null);

     // now we create the formula for the function and set it on the function
     string formula = "(1-0.4/(EXPONENTIALE^(temp-37)))*0.00001448471257*1.4^(temp-37)*substrate";

     var result = function.setInfix(formula);
     Debug.Assert(result.isSuccess());
     // make the function irreversible
     function.setReversible(COPASI.TriFalse);
     // the formula string should have been parsed now
     // and COPASI should have determined that the formula string contained 2 parameters (temp and substrate)
     CFunctionParameters variables = function.getVariables();
     // per default the usage of those parameters will be set to VARIABLE
     uint index = function.getVariableIndex("temp");
     CFunctionParameter param = variables.getParameter(index);
     Debug.Assert(param.getUsage() == CFunctionParameter.Role_VARIABLE);
     // This is correct for temp, but substrate should get the usage SUBSTRATE in order
     // for us to use the function with the reaction created above
     // So we need to set the usage for "substrate" manually
     index = function.getVariableIndex("substrate");
     param = variables.getParameter(index);
     param.setUsage(CFunctionParameter.Role_SUBSTRATE);

     // set the rate law for the reaction
     reaction.setFunction(function);
     Debug.Assert(reaction.getFunction() != null);

     // COPASI also needs to know what object it has to assocuiate with the individual function parameters
     // In our case we need to tell COPASI that substrate is to be replaced by the substrate of the reaction
     // and temp is to be replaced by the global parameter K
     reaction.setParameterObject("substrate", S);
     reaction.setParameterObject("temp", MV);
     
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
     dataModel.saveModel("example7.cps", true);

     // export the model to an SBML file
     // we save to a file named example1.xml, we want to overwrite any
     // existing file with the same name and we want SBML L2V3
     try
     {
       dataModel.exportSBML("example7.xml", true, 2, 3);
     }
     catch
     {
        System.Console.Error.WriteLine("Error. Exporting the model to SBML failed.");
     }
 }
}
