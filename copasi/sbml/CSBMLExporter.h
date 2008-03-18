// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/CSBMLExporter.h,v $
//   $Revision: 1.17 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/03/18 16:56:59 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CSBMLExporter_H__
#define CSBMLExporter_H__

#include <vector>
#include <string>
#include <set>
#include <map>

#include "copasi.h"

#include "copasi/function/CEvaluationNodeFunction.h"

class SBase;
class SBMLDocument;
class CCopasiDataModel;
class SBMLIncompatibility;
class CCompartment;
class CMetab;
class CExpression;
class CEvaluationNode;
class CReaction;
class CCopasiParameter;
class CModelEntity;
class CFunction;
class KineticLaw;
class Model;
class CModelValue;
class CEvent;
class CChemEqElement;
class CFunctionDB;
class Rule;
class XMLNode;

class CSBMLExporter
  {
  protected:
    SBMLDocument* mpSBMLDocument;
    unsigned int mSBMLLevel;
    unsigned int mSBMLVersion;
    std::vector<CModelEntity*> mAssignmentVector;
    std::vector<CModelEntity*> mODEVector;
    std::vector<CModelEntity*> mInitialAssignmentVector;
    std::map<const CCopasiObject*, SBase*> mCOPASI2SBMLMap;
    std::set<SBase*> mHandledSBMLObjects;
    std::set<CFunction*> mUsedFunctions;
    std::map<std::string, const SBase*> mIdMap;
    std::vector<SBMLIncompatibility> mIncompatibilities;
    bool mIncompleteExport;
    bool mVariableVolumes;
    const CModelValue* mpAvogadro;
    bool mAvogadroCreated;
    std::map<std::string, const SBase*> mMetaIdMap;

  public:
    /**
     * Default Konstruktor
     */
    CSBMLExporter();

    /**
     * Destruktor
     */
    ~CSBMLExporter();

    SBMLDocument* getSBMLDocument(){return this->mpSBMLDocument;};

    /**
     * Export the model to SBML.
     * The SBML model is returned as a string. In case of an error, an
     * empty string is returned.
     */
    const std::string exportModelToString(CCopasiDataModel& dataModel, unsigned int sbmlLevel, unsigned int sbmlVersion);

    /**
     * Export the model to SBML.
     * The model is written to the file given by filename.
     * If the export fails, false is returned.
     */
    bool exportModel(CCopasiDataModel& dataModel, const std::string& filename, unsigned int sbmlLevel = 2, unsigned int sbmlVersion = 1, bool overwrite = false);

    /**
     * Checks wether the given data model can be exported to a certain version of SBML.
     * If it can be exported, the result vector will be empty, otherwise it will
     * contain a number of messages that specify why it can't be exported.
     */
    static const std::vector<SBMLIncompatibility> isModelSBMLCompatible(const CCopasiDataModel& pDataModel, int sbmlLevel, int sbmlVersion);
  protected:
    /**
     * Creates the units for the SBML model.
     */
    void createUnits(const CCopasiDataModel& dataModel);

    /**
     * Creates the time unit for the SBML model.
     */
    void createTimeUnit(const CCopasiDataModel& dataModel);

    /**
     * Creates the volume unit for the SBML model.
     */
    void createVolumeUnit(const CCopasiDataModel& dataModel);

    /**
     * Creates the substance unit for the SBML model.
     */
    void createSubstanceUnit(const CCopasiDataModel& dataModel);

    /**
     * Creates the compartments for the model.
     */
    void createCompartments(CCopasiDataModel& dataModel);

    /**
     * Creates the compartment for the given COPASI compartment.
     */
    void createCompartment(CCompartment& compartment);

    /**
     * Creates the compartments for the model.
     */
    void createMetabolites(CCopasiDataModel& dataModel);

    /**
     * Creates the species for the given COPASI metabolite.
     */
    void createMetabolite(CMetab& metab);

    /**
     * Creates the parameters for the model.
     */
    void createParameters(CCopasiDataModel& dataModel);

    /**
     * Creates the parameter for the given COPASI parameter.
     */
    void createParameter(CModelValue& parameter);

    /**
     * Creates the reactions for the model.
     */
    void createReactions(CCopasiDataModel& dataModel);

    /**
     * Creates the reaction for the given COPASI reaction.
     */
    void createReaction(CReaction& reaction, CCopasiDataModel& dataModel);

    /**
     * Creates the initial assignments for the model.
     */
    void createInitialAssignments(CCopasiDataModel& dataModel);

    /**
     * Creates the initial assignment for the given COPASI model entity.
     */
    void createInitialAssignment(const CModelEntity& modelEntity, CCopasiDataModel& dataModel);

    /**
     * Creates the rules for the model.
     */
    void createRules(CCopasiDataModel& dataModel);

    /**
     * Creates the rule for the given COPASI model entity.
     */
    void createRule(const CModelEntity& modelEntity, CCopasiDataModel& dataModel, Rule* pOldRule);

    /**
     * Create all function definitions.
     */
    void createFunctionDefinitions(CCopasiDataModel& dataModel);

    /**
     * Create the SBML function definition from the given COPASI function.
     */
    void createFunctionDefinition(CFunction& function, const CCopasiDataModel& dataModel);

    /**
     * Create a unique id for an SBML object.
     * I can't just take the Copasi key of the object since this might conflict
     * with an already existing sbml id which came from the sbmlid attribute in a
     * copasi file or directly by importing an SBML file.
     */
    static const std::string createUniqueId(const std::map<std::string, const SBase*>& idMap, const std::string& prefix);

    /**
     * Checks all assignments (initial and transient) for references to objects
     * that can not be exported to SBML.
     */
    void checkForUnsupportedObjectReferences(const CCopasiDataModel& dataModel, unsigned int sbmlLevel, unsigned int sbmlVersion, std::vector<SBMLIncompatibility>& result);
    /**
     * Checks the given expression for references to objects
     * that can not be exported to SBML.
     */
    static void checkForUnsupportedObjectReferences(const CEvaluationTree& expression, const CCopasiDataModel& dataModel, unsigned int sbmlLevel, unsigned int sbmlVersion, std::vector<SBMLIncompatibility>& result, bool initialExpression = false);

    /**
     * Checks all expressions in the given datamodel for piecewise defined
     * functions.
     */
    static void checkForPiecewiseFunctions(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * Checks the given node and all it's children for the occurence of
     * piecewise functions.
     */
    static void checkForPiecewiseFunctions(const CEvaluationNode& node, std::vector<SBMLIncompatibility>& result, const std::string& objectName, const std::string& objectType);

    /**
     * Checks wether the given data model can be exported to SBML Level1
     * If it can be exported, the result vector will be empty, otherwise it will
     * contain a number of messages that specify why it can't be exported.
     */
    static void isModelSBMLL1Compatible(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * Checks wether the given data model can be exported to SBML Level2 Version1.
     * If it can be exported, the result vector will be empty, otherwise it will
     * contain a number of messages that specify why it can't be exported.
     */
    static void isModelSBMLL2V1Compatible(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * Checks wether the given data model can be exported to SBML Level2 Version3.
     * If it can be exported, the result vector will be empty, otherwise it will
     * contain a number of messages that specify why it can't be exported.
     */
    static void isModelSBMLL2V3Compatible(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * Checks wether the model contains a metabolite that is defined by an ODE
     * expression and that is located in a variable volume. Since COPASI
     * interprets the expression differntly from SBML, we can not correctly
     * export this yet. See Bug 903.
     */
    static void checkForODESpeciesInNonfixedCompartment(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility> result);

    /**
     * Checks wether the rule in the given model entity can be exported to
     * the specified version of SBML.
     * If it can be exported, the result vector will be empty, otherwise it will
     * contain a number of messages that specify why it can't be exported.
     */
    static void isExpressionSBMLCompatible(const CEvaluationTree& expr, const CCopasiDataModel& dataModel, int sbmlLevel, int sbmlVersion, std::vector<SBMLIncompatibility>& result,
                                           const std::string& objectName, const std::string& objectType, bool initialExression = false);

    /**
     * Checks wether the rule in the given model entity can be exported to SBML Level2 Version1.
     * If it can be exported, the result vector will be empty, otherwise it will
     * contain a number of messages that specify why it can't be exported.
     */
    static void isExpressionSBMLL1Compatible(const CEvaluationTree& expr, const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * Checks wether the rule in the given model entity can be exported to SBML Level2 Version1.
     * If it can be exported, the result vector will be empty, otherwise it will
     * contain a number of messages that specify why it can't be exported.
     */
    static void isExpressionSBMLL2V1Compatible(const CEvaluationTree& expr, const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * Checks wether the rule in the given model entity can be exported to SBML Level2 Version3.
     * If it can be exported, the result vector will be empty, otherwise it will
     * contain a number of messages that specify why it can't be exported.
     */
    static void isExpressionSBMLL2V3Compatible(const CEvaluationTree& expression, const CCopasiDataModel& pDataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * This static methods checks, wether the model uses any function calls
     * that can not be expressed in SBML like the random distribution
     * functions.
     */
    void checkForUnsupportedFunctionCalls(const CCopasiDataModel& dataModel,
                                          unsigned int sbmlLEvel, unsigned int sbmlVersion,
                                          std::vector<SBMLIncompatibility>& result);

    /**
     * This static methods checks recursively, whether the given CEvaluationNode constains any function calls
     * that can not be expressed in SBML like the random distribution
     * functions.
     */
    static void checkForUnsupportedFunctionCalls(const CEvaluationNode& node,
        const std::set<CEvaluationNodeFunction::SubType>& unsupportedFunctions,
        std::vector<SBMLIncompatibility>& result,
        const std::string& objectName, const std::string& objectType);

    /**
     * This method checks wether the given model contains any initial assignments.
     */
    static void checkForInitialAssignments(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * Goes through the given SBML model and puts all ids with the
     * corresponding object into a map.
     */
    const std::map<std::string, const SBase*> createIdMap(const Model& sbmlModel);

    /**
     * Create the kinetic law for the given reaction.
     * On failure NULL is returned.
     */
    KineticLaw* createKineticLaw(CReaction& reaction, CCopasiDataModel& dataModel);

    /**
     * Go through a CEvaluationNode base tree and add the names
     * of all functions directly called in this tree to the set.
     */
    static void findDirectlyUsedFunctions(const CEvaluationNode* pRootNode, std::set<std::string>& result);

    /**
     * checks if the given ASTNode based tree is divided by the
     * volume of the compartment identified by the given id string.
     */
    static ASTNode* isDividedByVolume(const ASTNode* pRootNode, const std::string& compartmentId);

    /**
     * Creates an expression from a given node and a set of parameter
     * mappings by
     * replacing the function arguments with the parameters.
    static CEvaluationNode* createExpressionTree(const CEvaluationNode* const pNode,
        const std::map<std::string, std::string>& parameterMap,
        const CCopasiDataModel& dataModel);
     */

    /**
     * Creates an expression from a given function and a set of parameters by
     * replacing the function arguments with the parameters.
    static CEvaluationNode* createExpressionTree(const CFunction* const pFun,
        const std::vector<std::vector<std::string> >& arguments,
        const CCopasiDataModel& dataModel);
     */

    /**
     * Create an expression that corresponds to a kinetic law.
     * If the kinetic law was mass action, the expression is a mass action term
     * , otherwise it is a function call.
     */
    CEvaluationNode* createKineticExpression(CFunction* pFun, const std::vector<std::vector<std::string> >& arguments);

    /**
     * Checks if the given datamodel contains events.
     * This is called if SBML Level 1 is to be exported.
     */
    static void checkForEvents(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * Creates an SBMLDocument from the given CCopasiDataModelObject.
     * It checks if an SBMLDocument already exists from an import and if
     * this is the case, the old document is copied.
     * If none exists a new one is created.
     * Copying the old one makes sure that if something goes wrong during
     * export, the original model is still consistent.
     */
    void createSBMLDocument(CCopasiDataModel& dataModel);

    /**
     * Sorts the rules.
     */
    std::vector<CModelEntity*> orderRules(const CCopasiDataModel& dataModel);

    /**
     * Creates a new COPASI2SBMLMap baed on the old map and the copied
     * SBMLDocument.
     */
    void updateCOPASI2SBMLMap(const CCopasiDataModel& dataModel);

    /**
     * Creates the events for the given data model.
     */
    void createEvents(CCopasiDataModel& dataModel);

    /**
     * Creates an SBML Event for the given COPASI event.
     */
    void createEvent(CEvent& event);

    /**
     * This method creates an ASTNode tree where all the species specified in
     * the given vector are multiplied. This is used to create the mass action
     * kinetic law.
     */
    static ASTNode* createTimesTree(const CCopasiVector<CChemEqElement >& vect, unsigned int pos = 0);

    /**
     * Remove all compartments, species, parameters and reactions
     * that did not end up in mHandledSBMLObjects during an export.
     */
    void removeUnusedObjects();

    /**
     * Takes a set of functions and recursively finds functions used by those
     * functions
     */
    static const std::vector<CFunction*> findUsedFunctions(std::set<CFunction*>& functions, CFunctionDB* pFunctionDB);

    static const std::set<CFunction*> createFunctionSetFromFunctionNames(const std::set<std::string>& names, CFunctionDB* pFunDB);

    /**
     * This method takes care of expanding all function calls in all
     * expressions and converting functions that are not supported in Level 1
     * as well as constants that were not supported in Level 1
     */
    void convertToLevel1();

    /**
     * Creates a set of all function subtypes that can not be exported for a
     * certain SBML level.
     */
    static const std::set<CEvaluationNodeFunction::SubType> createUnsupportedFunctionTypeSet(unsigned int sbmlLevel);

    /**
     * Find all ModelEntities for which the given node and its children contains
     * references.
     */
    static void findModelEntityDependencies(const CEvaluationNode* pNode, const CCopasiDataModel& dataModel, std::set<const CModelEntity*>& dependencies);

    /**
     * Creates an ASTNode based tree where all occurences of nodes that are not
     * supported in SBML Level 1 are replaced by supported constructs.
     * On error an exception is created.
     * The caller is responsible for freeing the memory of the returned object.
     */
    static ASTNode* convertASTTreeToLevel1(const ASTNode* pNode, const Model* pModel, std::string& message);

    /**
     * This method goes through the ASTNode based tree rooted at pNode and
     * replaces all unsupported nodes with constructs supported by SBML Level 1
     * The caller is responsible for freeing the memory of the returned object.
     */
    static ASTNode* replaceL1IncompatibleNodes(const ASTNode* pNode);

    /**
     * This method creates the CEvaluationNode based tree for a reversible or
     * irreversible Mass Action call.
     * The first parameter contains the arguments from the COPASI reaction.
     * The second argument determines whether it is reversible or irreversible
     * mass action.
     */
    static CEvaluationNode* createMassActionExpression(const std::vector<std::vector<std::string> >& arguments, bool isReversible);

    /**
     * Checks if the given string is a valid SId
     */
    static bool isValidSId(const std::string& id);

    /**
     * Remove the initial assignment for the entity with the given id
     * if there is any.
     */
    void removeInitialAssignment(const std::string& sbmlId);

    /**
     * Remove the rule for the entity with the given id
     * if there is any.
     */
    void removeRule(const std::string& sbmlId);

    /**
     * Replaces references to species with reference to species divided by
     * volume if it is a reference to a concentration or by a reference to the
     * species times avogadros number if it is a reference to the amount.
     * The method also takes into consideration the substance units of the
     * model.
     */
    CEvaluationNode* replaceSpeciesReferences(const CEvaluationNode* pOrigNode, const CCopasiDataModel& dataModel);

    /**
     * Try to find a global parameter that represents avogadros number.
     */
    void findAvogadro(const CCopasiDataModel& dataModel);

    /**
     * This method gets the MIRIAM annotation from the given COPASI object and
     * sets it on the given SBML object.
     */
    bool updateMIRIAMAnnotation(const CCopasiObject* pCOPASIObject, SBase* pSBMLObject, std::map<std::string, const SBase*>& metaIds);

    /**
     * This method creates a copy of parent where the child with the given index is
     * replaced by the new child given as the second argument.
     * If index is greater than the number of children - 1, NULL is returned.
     */
    XMLNode* replaceChild(const XMLNode* pParent, const XMLNode* pNewChild, unsigned int index);

    /**
     * This method goes through the given SBML model and collects all ids and
     * meta ids used in the model.
     */
    void collectIds(Model* pModel, std::map<std::string, const SBase*>& ids, std::map<std::string, const SBase*>& metaIds);
  };

#endif // CSBLExporter_H__
