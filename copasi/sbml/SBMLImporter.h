// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLImporter.h,v $
//   $Revision: 1.63.4.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/02/25 10:43:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SBMLIMPORTER_H__
#define SBMLIMPORTER_H__

#include <string>
#include <map>
#include <utility>
#include "sbml/math/ASTNode.h"

#include "copasi/function/CFunctionDB.h"
#include "copasi/sbml/StdException.h"
#include "copasi/model/CModel.h"

#include "sbml/UnitDefinition.h"

class SBMLDocument;
class CCompartment;
class CMetab;
class CReaction;
class Reaction;
class Species;
class Model;
class Compartment;
class SBMLDocument;
class ConverterASTNode;
class Parameter;
class FunctionDefinition;
class SBase;
class CProcessReport;
class Rule;
#ifdef WITH_LAYOUT
class CListOfLayouts;
#endif // WITH_LAYOUT

class SBMLImporter
  {
  protected:
    static const double UNIT_MULTIPLIER_TOLERANCE;

  protected:
    std::set<unsigned int> mIgnoredSBMLMessages;
    std::map<std::string, CMetab*> speciesMap;
    CFunctionDB* functionDB;
    bool mIncompleteModel;
    bool mUnsupportedRuleFound;
    bool mUnsupportedRateRuleFound;
    bool mUnsupportedAssignmentRuleFound;
    unsigned int mLevel;
    unsigned int mVersion;
    std::map<CEvaluationTree*, std::string> sbmlIdMap;
    std::set<std::string> mUsedFunctions;
    CModel* mpCopasiModel;
    std::map<std::string, std::string> mFunctionNameMapping;
    std::set<std::string> mDivisionByCompartmentReactions;
    CProcessReport* mpImportHandler;
    unsigned C_INT32 mImportStep;
    unsigned C_INT32 mhImportStep;
    unsigned C_INT32 mTotalSteps;
    std::map<Species*, Compartment*> mSubstanceOnlySpecies;
    bool mFastReactionsEncountered;
    std::set<std::string> mExplicitelyTimeDependentFunctionDefinitions;
    std::vector<std::string> mIgnoredParameterUnits;
    std::map<const ASTNode*, std::pair<CCopasiObjectName, CChemEq::MetaboliteRole> > mStoichiometricExpressionMap;
    bool mDelayFound;
    std::set<const Parameter*> mPotentialAvogadroNumbers;
    bool mAvogadroCreated;

    /**
     * Creates and returns a Copasi CModel from the SBMLDocument given as argument.
     */
    CModel* createCModelFromSBMLDocument(SBMLDocument* doc, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    /**
     * Creates and returns a Copasi CFunction from the SBML FunctionDefinition
     * given as argument.
     */
    CFunction* createCFunctionFromFunctionDefinition(const FunctionDefinition* sbmlFunction, CFunctionDB* pTmpFunctionDB, Model* pSBMLModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    CFunction* createCFunctionFromFunctionTree(const FunctionDefinition* pSBMLFunction, Model* pSBMLModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    /**
     * Creates and returns a Copasi CCompartment from the SBML Compartment
     * given as argument.
     */
    CCompartment* createCCompartmentFromCompartment(const Compartment* sbmlComp, CModel* copasiModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, const Model* pSBMLModel);

    /**
     * Creates and returns a Copasi CMetab from the given SBML Species object.
     */
    CMetab* createCMetabFromSpecies(const Species* sbmlSpecies, CModel* copasiModel, CCompartment* copasiCompartment, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, const Model* pSBMLModel);

    /**
     * Checks if no id is used in more than one Assignment and RateRule.
     */
    void areRulesUnique(const Model* copasiMode);

    /**
     * Imports the given Rule if Copasi supports this kind of Rule, otherwise a warning is created.
     */
    void importSBMLRule(const Rule* sbmlRule, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, Model* pSBMLModel);

    /**
     * Imports the given AssignmentRule which is for a global parameter.
     */
    void importRuleForModelEntity(const Rule* rule, CModelEntity* pMV, CModelEntity::Status ruleType, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, Model* pSBMLModel);

    /**
     * Imports the given RateRule if Copasi supports this kind of RateRule, otherwise a warning is created.
     */
    void importRule(const Rule* rule, CModelEntity::Status ruleType, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, Model* pSBMLModel);

    /**
     * Recurses an ASTNode tree and gets all SBML Ids in the tree.
     * The ids are stored in the given set.
     */
    void getIdsFromNode(const ASTNode* pNode, std::set<std::string>& idSet);

    /**
     * Checks the expression for a give rate or assignment rule for
     * consistency. This basically means it checks that no id present in the
     * expression is the target for one of the following rate or assignment
     * rules.
     */
    void checkRuleMathConsistency(const Rule* pRule, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    /**
     * Creates and returns a Copasi CModelValue from the given SBML Parameter object.
     */
    CModelValue* createCModelValueFromParameter(const Parameter* sbmlParameter, CModel* copasiModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    /**
     * Creates and returns a Copasi CReaction object from the given SBML
     * Reaction object.
     */
    CReaction* createCReactionFromReaction(const Reaction* sbmlReaction, Model* sbmlModel, CModel* cmodel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, CFunctionDB* pTmpFunctionDB);

    /**
     * Creates a map of each parameter of the function definition and its
     * corresponding parameter in the function call.
     */
    std::map<std::string , ASTNode*> createBVarMap(const ASTNode* uDefFunction, const ASTNode* function);

    /**
     * Returns the user defined SBML function definition that belongs to the given
     * name, or NULL if none can be found.
     */
    const FunctionDefinition* getFunctionDefinitionForName(const std::string name, const Model* model);

    /**
     * Replaces the variables in a function definition with the actual function
     * parameters that were used when the function was called. The function returns
     * a pointer to the ConverterAST node with the replaced variables.
     */
    ConverterASTNode* replaceBvars(const ASTNode* node, std::map<std::string, ASTNode*> bvarMap);

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
     * Returns the copasi VolumeUnit corresponding to the given SBML Volume
     *  UnitDefinition.
     */
    std::pair<CModel::VolumeUnit, bool> handleVolumeUnit(const UnitDefinition* uDef);

    /**
     * Returns the copasi QuantityUnit corresponding to the given SBML
     *  Substance UnitDefinition.
     */
    std::pair<CModel::QuantityUnit, bool> handleSubstanceUnit(const UnitDefinition* uDef);

    /**
     * Returns the copasi TimeUnit corresponding to the given SBML Time
     *  UnitDefinition.
     */
    std::pair<CModel::TimeUnit, bool> handleTimeUnit(const UnitDefinition* uDef);

    /**
     * Replaces all occurences of the log function with two arguments by
     * a division of two separate calls to log.
     */
    void replaceLog(ConverterASTNode* sourceNode);

    /**
     * Replaces all occurences of the root function with two arguments by
     * a call to the power function with the inverse of the first argument.
     */
    void replaceRoot(ConverterASTNode* sourceNode);

    /**
     * Replaces the ids of named nodes in an ASTNode tree with
     * the correspondingCopasi Common Names.
     */
    bool sbmlId2CopasiCN(ASTNode* pNode, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, CCopasiParameterGroup& pParamGroup);

    /**
     * Upon import a function object might change its name due to naming conflicts in the function
     * database. So each ASTNode tree has its call node names replaced
     * before it will be processed further.
     */
    void replaceCallNodeNames(ConverterASTNode* pNode);

    /**
     * The data for a CEvaluationNodeObject needs to have the common
     * name of the model it refers to as its data. Since this model is
     * only known via a pointer in the SBMLImporter at the time of
     * import, all AST_NAME_TIME nodes that are imported need to have
     * their name replaced by the common name of this model.
     */
    void replaceTimeNodeNames(ConverterASTNode* pNode);

    /**
     * COPASI can not handle the delay function yet, so if it is used in some expression, we
     * have to abort reading the file.
     */
    void isDelayFunctionUsed(ConverterASTNode* pNode);

    /**
     * In a proeprocessing step each expression tree that is imported,
     * e.g. for function definitions, rules, event or kinetic laws
     * is preprocessed to replace some of the nodes data.
     * See also replaceCallNodeNames and replaceTimeNodeNames.
     */
    void preprocessNode(ConverterASTNode* pNode, Model* pSBMLModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    CFunction* findCorrespondingFunction(const CFunction* tree, const CReaction* reaction);

    bool areEqualFunctions(const CFunction* pFun, const CFunction* pFun2);

    /**
     * Compares to CEvaluationNode based subtrees recursively.
     */
    bool areEqualSubtrees(const CEvaluationNode* pNode1, const CEvaluationNode* pNode2);

    std::vector<CEvaluationNodeObject*>* isMassAction(const CEvaluationTree* pTree, const CChemEq& chemicalEquation, const CEvaluationNodeCall* pCallNode = NULL);

    std::vector<CEvaluationNodeObject*>* isMassActionExpression(const CEvaluationNode* pRootNode, const CChemEq& chemicalEquation);

    std::vector<CEvaluationNodeObject*>* isMassActionFunction(const CFunction* pFun, const CChemEq& chemicalEquation, const std::vector<std::vector< std::string > >& functionArgumentCNs);

    /**
     * This function takes a node and tries to find out wether the tree under this node consists
     * only of multiply operators and object nodes.
     * The arguments to the multiply operators are returned.
     */
    void separateProductArguments(const CEvaluationNode* pRootNode, std::vector<const CEvaluationNode*>& arguments);

    void doMapping(CReaction* pCopasiReaction, const CEvaluationNodeCall* pCallNode);

    bool isSimpleFunctionCall(const CEvaluationNode* pRootNode);

    void setCorrectUsage(CReaction* pCopasiReaction, const CEvaluationNodeCall* pCallNode);

    /**
     * Checks if a given tree is multiplied by a compartment identifier.
     * If so, a copy of the tree is returned in which the multiplication has been removed.
     */
    ConverterASTNode* isMultipliedByVolume(const ASTNode* node, const std::string& compartmentSBMLId);

    CEvaluationNode* variables2objects(const CEvaluationNode* pOrigNode, const std::map<std::string, std::string>& replacementMap);

    CEvaluationTree* createExpressionFromFunction(const CFunction* pFun, const std::vector<std::vector<std::string > >& functionArgumentCNs);

    void renameMassActionParameters(CEvaluationNodeCall* pCallNode);

    /**
     * Checks if the volume with the given CN is one of the parameters to the given call node.
     */
    bool containsVolume(const ASTNode* pNode, const std::string& compartmentCN);

    /**
     * Finds all functions that are used and removes those that are not.
     */
    bool removeUnusedFunctions(CFunctionDB* pTmpFunctionDB, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    /**
     * Finds all functions calls directly or indirectly used in a function
     * tree.
     */
    void findFunctionCalls(const CEvaluationNode* pNode, std::set<std::string>& functionNameSet);

    /**
     * Heuristically checks wether a model was meant to be simulated stochastically.
     * If the substance units are set to items and all reaction are irreversible this function
     * will return true;
     */
    bool isStochasticModel(const Model* pSBMLModel);

    void replaceObjectNames(ASTNode* pNode, const std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, bool initialExpression = false);

    /**
     * For function definitions that use the time symbol we have to make this a
     * variable that is passed to the function instead.
     * The function recursively goes through the AST tree rooted in root and
     * changs all time nodes to varaible nodes with name newNodeName.
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
     * those initial values have been set in the sbml model.
     * Otherwise the routine checks if a rule or an initial assignment has been set for the entity.
     * If the entity has not been set in any way, an error message is created.
     */
    bool setInitialValues(CModel* pModel, const std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    void checkElementUnits(const Model* pSBMLModel, CModel* pCopasiModel, int level, int version);

    /**
     * If the given UnitDefinition can be converted to a form of litres, the
     * funktion return the UnitDefinition in litres, otherwise NULL is returned.
     */
    static Unit* convertSBMLCubicmetresToLitres(const Unit* pU);

    /**
     * This funktion normalizes the multiplier to be within the range 1.0 <=
     * multiplier < 10.0.
     */
    static void normalizeSBMLUnit(Unit* pU);

    /**
     * This method takes the id of a unit as it can appear in an SBML file, and
     * returns a new UnitDefinition object for that id.
     */
    static UnitDefinition* getSBMLUnitDefinitionForId(const std::string& unitId, const Model* pSBMLModel);

    /**
     * Imports all initial assignments if there are any.
     */
    void importInitialAssignments(Model* pSBMLModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlMap);

    /**
     * This method evaluates all stoichiometric expressions and sets them as
     * constants on the CChemEqElement.
     */
    void applyStoichiometricExpressions(std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, Model* pSBMLModel);

    /**
     * Creates a function definition for the delay function.
     */
    void createDelayFunctionDefinition();

    /**
     * This method goes through the list of global parameters and tries to find
     * a parameter that could correspond to avogadros number.
     */
    void findAvogadroConstant(Model* pSBMLModel, double factor);

    /**
     * This method replaces references to the id of species which have the
     * hasOnlySubstanceUnits flag set with the reference divided by avogadros
     * number.
     * The method tries to determine if there already is a multiplication with
     * avogadros number and removes this multiplication rather than adding a new division.
     */
    void replaceAmountReferences(ConverterASTNode* pNode, Model* pSBMLModel, double factor, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    /**
     * This method creates a global parameter the represents the factor that is
     * used to convert a particle number into the amount units set on the
     * model.
     * The parameter is only created if it is needed and after exporting the
     * model, the parameter is deleted from the COPASI model again.
     */
    void createHasOnlySubstanceUnitFactor(Model* pSBMLModel, double factor, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

  public:
    SBMLImporter();
    ~SBMLImporter();

    CModel* readSBML(std::string filename,
                     CFunctionDB* funDB,
                     SBMLDocument*& pSBMLDocument,
                     std::map<CCopasiObject*, SBase*>& copasi2sbmlmap
#ifdef WITH_LAYOUT
                     , CListOfLayouts *& prLol
#endif
);

    //CModel* readSBML(std::string filename, CFunctionDB* funDB, SBMLDocument *& pSBMLDocument, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    CModel* parseSBML(const std::string& sbmlDocumentText,
                      CFunctionDB* funDB,
                      SBMLDocument *& pSBMLDocument,
                      std::map<CCopasiObject*, SBase*>& copasi2sbmlmap
#ifdef WITH_LAYOUT
                      , CListOfLayouts *& prLol
#endif
);

    //CModel* parseSBML(const std::string& sbmlDocumentText, CFunctionDB* funDB, SBMLDocument*& pSBMLDocument, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    static void printMap(const std::map<CCopasiObject*, SBase*>& map);

    void restoreFunctionDB();

    void setImportHandler(CProcessReport* pHandler);

    /**
     * Enhanced method to identify identical sbml unit definitions.
     * This method uses the areIdentical method from libSBML, but if the method
     * return false, it does some extra checks.
     * Right now it check for example if two volumes, one given in litre and one
     * given in cubic meters are identical.
     */
    static bool areSBMLUnitDefinitionsIdentical(const UnitDefinition* pUdef1, const UnitDefinition* pUdef2);

    CProcessReport* getImportHandlerAddr();
  };

#endif
