// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SBMLIMPORTER_H__
#define SBMLIMPORTER_H__

#include <string>
#include <map>
#include <set>
#include <utility>
#include "sbml/math/ASTNode.h"

#include "copasi/function/CFunctionDB.h"
#include "copasi/sbml/StdException.h"
#include "copasi/sbml/SBMLUnitSupport.h"
#include "copasi/model/CModel.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class SBMLDocument;
class Reaction;
class Species;
class Model;
class Compartment;
class Parameter;
class FunctionDefinition;
class SBase;
class Rule;
LIBSBML_CPP_NAMESPACE_END

class CCompartment;
class CMetab;
class CReaction;
class ConverterASTNode;
class CProcessReport;
class CListOfLayouts;
class SbmlProgressCallback;

class SBMLImporter : public SBMLUnitSupport
{
public:
  static bool areApproximatelyEqual(const double & x, const double & y, const double & t = 1e-9);

protected:
  static C_FLOAT64 round(const C_FLOAT64 & x);

  std::set<unsigned int> mIgnoredSBMLMessages;
  std::map<std::string, CMetab*> speciesMap;
  bool mIncompleteModel;
  bool mUnsupportedRuleFound;
  bool mUnsupportedRateRuleFound;
  bool mUnsupportedAssignmentRuleFound;
  bool mUnitOnNumberFound;
  bool mAssignmentToSpeciesReferenceFound;
  unsigned int mOriginalLevel;
  std::map<CFunction*, std::string> sbmlIdMap;
  std::set<std::string> mCreatedFunctions;
  CDataModel * mpDataModel;
  CModel* mpCopasiModel;
  std::map<std::string, std::string> mFunctionNameMapping;
  std::set<std::string> mDivisionByCompartmentReactions;

  /**
   * the import handler
   */
  CProcessReport * mpProcessReport;

  /**
   * the global import step handle
   */
  size_t mGlobalStepHandle;

  /**
   * global step counter
   */
  unsigned C_INT32 mGlobalStepCounter;

  /**
   * total step counter for global import
   */
  unsigned C_INT32 mGlobalStepTotal;

  /**
   * the current import step handle
   */
  size_t mCurrentStepHandle;

  /**
   * current step counter for current import
   */
  unsigned C_INT32 mCurrentStepCounter;
  /**
   * total steps of current import task
   */
  unsigned C_INT32 mCurrentStepTotal;

  std::map<Species*, Compartment*> mSubstanceOnlySpecies;
  std::set<std::string> mFastReactions;
  std::set<std::string> mReactions;
  std::set<std::string> mReactionsWithReplacedLocalParameters;
  std::set<std::string> mExplicitelyTimeDependentFunctionDefinitions;
  std::vector<std::string> mIgnoredParameterUnits;
  std::map<const ASTNode*, const CChemEqElement* > mStoichiometricExpressionMap;
  bool mDelayFound;
  std::set<const Parameter*> mPotentialAvogadroNumbers;
  bool mAvogadroCreated;
  bool mImportCOPASIMIRIAM;
  // this map maps a delay expression to the global parameter id it has been
  // replaced with
  std::map<std::string, std::string> mDelayNodeMap;
  std::set<std::string> mUsedSBMLIds;
  bool mUsedSBMLIdsPopulated;
  std::map<std::string, std::string> mKnownCustomUserDefinedFunctions;
  std::map<std::string, std::string> mKnownInitalValues;

  // this map is used for storing the parameters that are used as factors that have to be applied to the multiplicities
  // of the chemical equation elements
  const CModelValue* mpModelConversionFactor;
  // we only store the id of the species as the value and use this value as the key into the mSpeciesConversionParameterMap below
  std::map<const CChemEqElement*, std::pair<std::string, CChemEq::MetaboliteRole> > mChemEqElementSpeciesIdMap;
  // yet another map that stores conversion parameters per species id
  // This will speed up the assignment of
  std::map<std::string, const CModelValue*> mSpeciesConversionParameterMap;
  // and yet another map that maps SBML parameter keys to COPASI model values
  std::map<std::string, const CModelValue*> mSBMLIdModelValueMap;

  // in this set we store the ids of all SBML species references
  // so that we can later check if a reference to a species reference is used
  // in a mathematical expression
  std::map<std::string, double> mSBMLSpeciesReferenceIds;

  bool mRateRuleForSpeciesReferenceIgnored;
  bool mEventAssignmentForSpeciesReferenceIgnored;
  bool mConversionFactorFound;

  std::map<std::string, CCompartment*> mCompartmentMap;
  std::map<std::string, CModelValue*> mParameterFluxMap;
  std::set<const CDataObject*> mChangedObjects;

  SbmlProgressCallback *mpSbmlCallback;

  /**
   * This utility functions adds a new step to the progress dialog (if present)
   * @param globalStep the global steps that have been completed
   * @param currentTotal the total for current task
   * @param title the title of the current task
   * @return a boolean indicating whether processing should be stopped
   */
  bool createProgressStepOrStop(unsigned C_INT32 globalStep, unsigned C_INT32 currentTotal, const std::string& title);

  /**
   * Notifies the progress dialog of local progress
   * @return a boolean indicating whether processing should be stopped
   */
  bool reportCurrentProgressOrStop();

  /**
   * Notifies the progress dialog that a step finished
   */
  void finishCurrentStep();

  /**
   * Notifies the progress dialog that all importing is complete
   */
  void finishImport();

  /**
   * checks the given document, and if not valid stops
   * @param sbmlDoc the document to be checked
   * @return true if serious errors were encountered and importing stopped
   */
  bool checkValidityOfSourceDocument(SBMLDocument* sbmlDoc);

  /**
   * Creates and returns a COPASI CModel from the SBMLDocument given as argument.
   */
  CModel* createCModelFromSBMLDocument(SBMLDocument * doc,
                                       std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * Creates and returns a COPASI CFunction from the SBML FunctionDefinition
   * given as argument.
   */
  CFunction* createCFunctionFromFunctionDefinition(const FunctionDefinition* sbmlFunction,
      Model* pSBMLModel,
      std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  CFunction* createCFunctionFromFunctionTree(const FunctionDefinition* pSBMLFunction,
      Model* pSBMLModel,
      std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * Creates and returns a COPASI CCompartment from the SBML Compartment
   * given as argument.
   */
  CCompartment* createCCompartmentFromCompartment(const Compartment* sbmlComp,
      CModel* copasiModel,
      std::map<const CDataObject *, SBase*>& copasi2sbmlmap,
      const Model* pSBMLModel);

  /**
   * Creates and returns a COPASI CMetab from the given SBML Species object.
   */
  CMetab* createCMetabFromSpecies(const Species* sbmlSpecies,
                                  CModel* copasiModel,
                                  CCompartment* copasiCompartment,
                                  std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                                  const Model* pSBMLModel);

  /**
   * Checks if no id is used in more than one Assignment and RateRule.
   */
  void areRulesUnique(const Model* copasiMode);

  /**
   * Imports the given Rule if COPASI supports this kind of Rule, otherwise a warning is created.
   */
  void importSBMLRule(const Rule* sbmlRule,
                      std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                      Model* pSBMLModel);

  /**
   * Imports the given AssignmentRule which is for a global parameter.
   */
  void importRuleForModelEntity(const Rule* rule,
                                const CModelEntity* pMV,
                                CModelEntity::Status ruleType,
                                std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                                Model* pSBMLModel);

  /**
   * Imports all events
   */
  void importEvents(Model* pSBMLModel,
                    CModel* pCopasiModel,
                    std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * Imports the given event.
   */
  void importEvent(const Event* pEvent,
                   Model* pSBMLModel,
                   CModel* pCopasiModel,
                   std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * Imports the given RateRule if COPASI supports this kind of RateRule, otherwise a warning is created.
   */
  void importRule(const Rule* rule,
                  CModelEntity::Status ruleType,
                  std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                  Model* pSBMLModel);

  /**
   * Recurses an ASTNode tree and gets all SBML Ids in the tree.
   * The ids are stored in the given set.
   */
  void getIdsFromNode(const ASTNode* pNode,
                      std::set<std::string>& idSet);

  /**
   * Checks the expression for a give rate or assignment rule for
   * consistency. This basically means it checks that no id present in the
   * expression is the target for one of the following rate or assignment
   * rules.
   */
  void checkRuleMathConsistency(const Rule* pRule,
                                std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * Creates and returns a COPASI CModelValue from the given SBML Parameter object.
   */
  CModelValue* createCModelValueFromParameter(const Parameter* sbmlParameter,
      CModel* copasiModel,
      std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * Creates and returns a COPASI CReaction object from the given SBML
   * Reaction object.
   */
  CReaction* createCReactionFromReaction(Reaction* sbmlReaction,
                                         Model* sbmlModel,
                                         CModel* cmodel, std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * Creates a map of each parameter of the function definition and its
   * corresponding parameter in the function call.
   */
  std::map<std::string, ASTNode*> createBVarMap(const ASTNode* uDefFunction,
      const ASTNode* function);

  /**
   * Returns the user defined SBML function definition that belongs to the given
   * name, or NULL if none can be found.
   */
  const FunctionDefinition* getFunctionDefinitionForName(const std::string& name,
      const Model* model);

  /**
   * Replaces the variables in a function definition with the actual function
   * parameters that were used when the function was called. The function returns
   * a pointer to the ConverterAST node with the replaced variables.
   */
  // ConverterASTNode* replaceBvars(const ASTNode* node,
  //                                std::map<std::string, ASTNode*> bvarMap);

  /**
   * This function replaces the AST_FUNCTION_POWER ASTNodes in a ASTNode tree
   * with the AST_POWER node.
   */
  void replacePowerFunctionNodes(ASTNode* node);

  /**
   * This functions replaces all species nodes for species that are in the substanceOnlySpeciesVector.
   * With the node multiplied by the volume of the species compartment.
  void replaceSubstanceOnlySpeciesNodes(ConverterASTNode* node, const std::map<Species*, Compartment*>& substanceOnlySpecies);
   */

  /**
   * Replaces all occurrences of the log function with two arguments by
   * a division of two separate calls to log.
   */
  void replaceLog(ConverterASTNode* sourceNode);

  /**
   * Replaces all occurrences of the root function with two arguments by
   * a call to the power function with the inverse of the first argument.
   */
  void replaceRoot(ConverterASTNode* sourceNode);

  /**
   * Replaces the ids of named nodes in an ASTNode tree with
   * the correspondingCopasi Common Names.
   */
  bool sbmlId2CopasiCN(ASTNode* pNode,
                       std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                       CCopasiParameterGroup& pParamGroup,
                       SBase* pParentObject = NULL);

  /**
   * Upon import a function object might change its name due to naming conflicts in the function
   * database. So each ASTNode tree has its call node names replaced
   * before it will be processed further.
   */
  void replaceCallNodeNames(ASTNode* pNode);

  /**
   * This function replaces calls to the delay function in an ASTNode tree
   * by a node that references a new global parameter which the function
   * creates. The global parameter gets an expression which corresponds to the
   * delay call.
   * This is necessary because all knetic laws in COPASI are function calls and
   * function definitions should not contain a call to delay.
   */
  void replace_delay_nodes(ConverterASTNode* pNode,
                           Model* pModel,
                           std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                           Reaction* pSBMLReaction,
                           std::map<std::string, std::string>& localReplacementMap
                          );

  /**
   * If we replace delay nodes within kineitc laws, we have to make sure that
   * there is no reference to a local parameter within the replaced
   * delay node because that would mean that we end up with a reference to a
   * local parameter in the rule for the delay replacement which is not allowed
   * in SBML.
   * Therefore we have to convert all local parameters which occur within a
   * delay call into global parameters.
   * This method finds all local parameters that have to be converted to global
   * parameters and it already creates the necessary global parameters.
   * The localReplacementMap returns a mapping between the is of the original
   * parameter and the id of the new parameter it will be replaced with.
   * This map is used in a second step to actually replace the nodes in the
   * expression.
   */
  void find_local_parameters_in_delay(ASTNode* pNode,
                                      Reaction* pSBMLReaction,
                                      Model* pModel,
                                      std::map<std::string, std::string>& localReplacementMap,
                                      const std::set<std::string>& localIds,
                                      std::map<const CDataObject*, SBase*>& copasi2sbmlmap
                                     );

  /**
   * This method gets an ASTNode and a map between old node names and new node
   * names. All AST_NAME nodes with an "old" name are replaced by a node with
   * the "new" name.
   */
  void replace_name_nodes(ASTNode* pNode, const std::map<std::string, std::string>& replacementMap);

  /**
   * The data for a CEvaluationNodeObject needs to have the common
   * name of the model it refers to as its data. Since this model is
   * only known via a pointer in the SBMLImporter at the time of
   * import, all AST_NAME_TIME nodes that are imported need to have
   * their name replaced by the common name of this model.
   * Starting with SBML Level 3 this also applies to the avogadro number.
   */
  void replaceTimeAndAvogadroNodeNames(ASTNode* pNode);

  /**
   * COPASI can not handle the delay function yet, so if it is used in some expression, we
   * have to abort reading the file.
   */
  bool isDelayFunctionUsed(ConverterASTNode* pNode);

  /**
   * In a preprocessing step each expression tree that is imported,
   * e.g. for function definitions, rules, event or kinetic laws
   * is preprocessed to replace some of the nodes data.
   * See also replaceCallNodeNames and replaceTimeNodeNames.
   */
  void preprocessNode(ConverterASTNode* pNode,
                      Model* pSBMLModel,
                      std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                      Reaction* pSBMLReaction = NULL);

  CFunction* findCorrespondingFunction(const CExpression * pExpression, const CReaction* reaction);

public:
  static bool areEqualFunctions(const CFunction* pFun, const CFunction* pFun2);

  static bool isEmptyOrWhiteSpace(const std::string & name);

  /**
   * Compares to CEvaluationNode based subtrees recursively.
   */
  static bool areEqualSubtrees(const CEvaluationNode* pNode1, const CEvaluationNode* pNode2);

protected:
  std::vector<CEvaluationNodeObject*>* isMassAction(const CEvaluationTree* pTree,
      const CChemEq& chemicalEquation,
      const CEvaluationNodeCall* pCallNode = NULL);

  /**
   * Checks if the given node is an object node that represents a parameter
   * or a model value or a function which has a single parameter and a single node which also represents a parameter.
   */
  const CDataObject* isConstantFlux(const CEvaluationNode* pRoot,
                                    CModel* pModel);

  std::vector<CEvaluationNodeObject*>* isMassActionExpression(const CEvaluationNode* pRootNode,
      const CChemEq& chemicalEquation);

  std::vector<CEvaluationNodeObject*>* isMassActionFunction(const CFunction* pFun,
      const CChemEq& chemicalEquation,
      const std::vector<std::vector< std::string > >& functionArgumentCNs);

  /**
   * This function takes a node and tries to find out whether the tree under this node consists
   * only of multiply operators and object nodes.
   * The arguments to the multiply operators are returned.
   */
  void separateProductArguments(const CEvaluationNode* pRootNode,
                                std::vector<const CEvaluationNode*>& arguments);

  void doMapping(CReaction* pCopasiReaction, const CEvaluationNodeCall* pCallNode);

  bool isSimpleFunctionCall(const CEvaluationNode* pRootNode);

  void setCorrectUsage(CReaction* pCopasiReaction, const CEvaluationNodeCall* pCallNode);

  /**
   * Checks if a compartment size node occurs multiplicatively in the tree.
   * If so, it is removed from the tree.
   * If it returns false, the tree was not changed
   */
  bool divideByVolume(ASTNode* node, const std::string& compartmentSBMLId);

  CEvaluationNode* variables2objects(const CEvaluationNode* pOrigNode,
                                     const std::map<std::string, std::string>& replacementMap);

  CEvaluationTree* createExpressionFromFunction(const CFunction* pFun,
      const std::vector<std::vector<std::string > >& functionArgumentCNs);

  void renameMassActionParameters(CEvaluationNodeCall* pCallNode);

  /**
   * Checks if the volume with the given CN is one of the parameters to the given call node.
   */
  bool containsVolume(const ASTNode* pNode, const std::string& compartmentCN);

  /**
   * Finds all functions that are used and removes those that are not.
   */
  bool removeUnusedFunctions(std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * Finds all functions calls directly or indirectly used in a function
   * tree.
   */
  void findFunctionCalls(const CEvaluationNode* pNode, std::set<std::string>& functionNameSet);

  /**
   * Heuristically checks whether a model was meant to be simulated stochastically.
   * If the substance units are set to items and all reaction are irreversible this function
   * will return true;
   */
  bool isStochasticModel(const Model* pSBMLModel);

  /**
   * If an initial expression uses time, we have to import it as initial time
   * instead.
   * This method takes an AST node and converts all time nodes to object nodes
   * that have the common name of the time as the name.
   */
  void replace_time_with_initial_time(ASTNode* pNode, const CModel* pCOPASIModel);

  void replaceObjectNames(ASTNode* pNode,
                          const std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                          bool initialExpression = false);

  /**
   * For function definitions that use the time symbol we have to make this a
   * variable that is passed to the function instead.
   * The function recursively goes through the AST tree rooted in root and
   * changes all time nodes to variable nodes with name newNodeName.
   * If a time node has been found, the function return true, otherwise false
   * is returned.
   */
  bool replaceTimeNodesInFunctionDefinition(ASTNode* root, std::string newNodeName);

  /**
   * This function replaces function calls to all functions listed in mExplicitelyTimeDependentFunctionDefinitions
   * with the same call but an additional parameter which is the time.
   * This replacement includes all model entities that have a mathematical
   * expression, so depending on the version of SBML, this would include:
   * initial assignments, rules, constraints, kinetic laws and events.
   * The corresponding replacement for the function definitions is done in
   * replaceTimeNodesInFunctionDefinition.
   */
  void replaceTimeDependentFunctionCalls(ASTNode* root);

  /**
   * Sets the initial values on compartments, metabolites and model values if
   * those initial values have been set in the SBML model.
   * Otherwise the routine checks if a rule or an initial assignment has been set for the entity.
   * If the entity has not been set in any way, an error message is created.
   */
  bool setInitialValues(CModel* pModel,
                        const std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * Imports all initial assignments if there are any.
   */
  void importInitialAssignments(Model* pSBMLModel, std::map<const CDataObject*, SBase*>& copasi2sbmlMap, const CModel* pCOPASIModel);

  /**
   * This method evaluates all stoichiometric expressions and sets them as
   * constants on the CChemEqElement.
   */
  void applyStoichiometricExpressions(std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                                      Model* pSBMLModel);

  /**
   * Creates a function definition for the delay function.
   */
  void createDelayFunctionDefinition();

  /**
   * This method goes through the list of global parameters and tries to find
   * a parameter that could correspond to avogadros number.
   */
  void findAvogadroConstant(Model* pSBMLModel,
                            double factor);

  /**
   * This method replaces references to the id of species which have the
   * hasOnlySubstanceUnits flag set with the reference divided by avogadros
   * number.
   * The method tries to determine if there already is a multiplication with
   * avogadros number and removes this multiplication rather than adding a new division.
   */
  void replaceAmountReferences(ConverterASTNode* pNode,
                               Model* pSBMLModel,
                               double factor,
                               std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * This method creates a global parameter the represents the factor that is
   * used to convert a particle number into the amount units set on the
   * model.
   * The parameter is only created if it is needed and after exporting the
   * model, the parameter is deleted from the COPASI model again.
   */
  void createHasOnlySubstanceUnitFactor(Model* pSBMLModel,
                                        double factor,
                                        std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * Multiplies all species nodes that belong to species with the
   * hasSubstanceOnlyUnits flag set with the volume of the compartment that
   * the species belongs to.
   * This is only done for kineticLaw, all other mathematical expressions
   * import those references as particle number nodes divided by the
   * quantity2unit factor.
   */
  void multiplySubstanceOnlySpeciesByVolume(ConverterASTNode* pNode);

  /**
   * Imports the MIRIAM annotation from the given SBML object and sets it on
   * the given COPASI object.
   */
  bool importMIRIAM(const SBase* pSBMLObject, CDataObject* pCOPASIObject);

  /**
   * Starting with SBML Level 2 Version 4, function definitions no longer need to
   * be ordered, i.e. a function definition may refer to another function
   * definition that is defined somewhere further down in the file.
   * So we have to import the function definitions in the correct order.
   */
  void importFunctionDefinitions(Model * pSBMLModel,
                                 std::map< const CDataObject *, SBase * > & copasi2sbmlmap);

  /**
   * static method that finds all direct function dependencies of a given
   * function definition.
   */
  static void findDirectDependencies(const FunctionDefinition* pFunDef,
                                     std::map<const FunctionDefinition*, std::set<std::string> >& dependencies);

  /**
   * static method that recursively finds all direct function dependencies of the
   * expression rooted at the given node.
   */
  static void findDirectDependencies(const ASTNode* pNode,
                                     std::set<std::string>& dependencies);

public:
  SBMLImporter();
  ~SBMLImporter();

  CModel* readSBML(std::string filename,
                   SBMLDocument*& pSBMLDocument,
                   std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                   CListOfLayouts *& prLol,
                   CDataModel* pDataModel);

  //CModel* readSBML(std::string filename, CFunctionDB* funDB, SBMLDocument *& pSBMLDocument, std::map<CDataObject*, SBase*>& copasi2sbmlmap);

  CModel* parseSBML(const std::string& sbmlDocumentText,
                    SBMLDocument *& pSBMLDocument,
                    std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                    CListOfLayouts *& prLol,
                    CDataModel* pDataModel);

  //CModel* parseSBML(const std::string& sbmlDocumentText, CFunctionDB* funDB, SBMLDocument*& pSBMLDocument, std::map<CDataObject*, SBase*>& copasi2sbmlmap);
#ifdef COPASI_DEBUG
  static void printMap(const std::map<CDataObject*, SBase*>& map);
#endif // COPASI_DEBUG

  void restoreFunctionDB();

  /**
   * This call deletes an existing COPASI model.
   * The method can e.g. be called to clean up if an import fails.
   */
  void deleteCopasiModel();

  /**
   * sets a progress handler to inform about updates
   */
  void setImportHandler(CProcessReport * pProcessReport);

  /**
   * @return the progress handler set
   */
  const CProcessReport * getProcessReport() const;

  /**
   * clears the currently set progress handler
   */
  virtual void clearCallBack();

  /**
   * Returns the flag that determines whether COPASI MIRIAM annotation is
   * imported if it is present.
   */
  bool getImportCOPASIMIRIAM() const;

  /**
   * Sets the flag that determines whether COPASI MIRIAM annotation is
   * imported if it is present.
   */
  void setImportCOPASIMIRIAM(bool import);

  /**
   * This method takes an AST node and a set of ids and returns the first id
   * from the set it finds in the AST tree.
   * This is e.g. used to check if expression in L2V1 contain references to reaction ids.
   */
  std::string findIdInASTTree(const ASTNode* pMath, const std::set<std::string>& reactionIds);
  std::string findIdInASTTree(const ASTNode* pMath, const std::map<std::string, double>& reactionIds);

  /**
   * This method divides the given expression by the given object and returns a new expression.
   * The caller is responsible for freeing the memory for the new expression.
   */
  static CEvaluationNode* divideByObject(const CEvaluationNode* pOrigNode, const CDataObject* pObject);

  /**
   * This method reads the notes from an arbitrate SBase object
   * and set them on the given CAnnotation instance.
   */
  static bool importNotes(CAnnotation* pAnno, const SBase* pSBase);

  /**
   * This method check if a unit has been set on a number node.
   * If such a node is found in the tree, true is returned.
   */
  static bool checkForUnitsOnNumbers(const ASTNode* pNode);

  /**
   * This method checks if there are conversion factors that need to be applied to
   * ChemicalEquationElements and applies them.
   */
  void applyConversionFactors();

  /**
   * Goes through all SBML reactions and collects the ids of all species references.
   */
  static void updateSBMLSpeciesReferenceIds(Model* pModel, std::map<std::string, double>& ids);
};

#endif // SBMLIMPORTER_H__
