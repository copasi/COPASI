// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/CSBMLExporter.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/11/29 21:04:13 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CSBMLExporter_H__
#define CSBMLExporter_H__

#include <vector>
#include <string>
#include <set>
#include <map>

#include "function/CEvaluationNodeFunction.h";

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

class CSBMLExporter
  {
  protected:
    SBMLDocument* mpSBMLDocument;
    unsigned int mSBMLLevel;
    unsigned int mSBMLVersion;
    std::vector<CModelEntity*> mAssignmentVector;
    std::vector<CModelEntity*> mInitialAssignmentVector;
    std::map<const CCopasiObject*, SBase*> mCOPASI2SBMLMap;
    std::set<SBase*> mHandledSBMLObjects;
    std::set<CFunction*> mUsedFunctions;
    std::map<std::string, const SBase*> mIdMap;
    std::vector<SBMLIncompatibility> mIncompatibilities;
    bool mIncompleteExport;

  public:
    /**
     * Default Konstruktor
     */
    CSBMLExporter();

    /**
     * Destruktor
     */
    ~CSBMLExporter();

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
    void createInitialAssignments(const CCopasiDataModel& dataModel);

    /**
     * Creates the initial assignment for the given COPASI model entity.
     */
    void createInitialAssignment(const CModelEntity& modelEntity);

    /**
     * Creates the rules for the model.
     */
    void createRules(const CCopasiDataModel& dataModel);

    /**
     * Creates the rule for the given COPASI model entity.
     */
    void createRule(const CModelEntity& modelEntity);

    /**
     * Create all function definitions.
     */
    void createFunctionDefinitions(CCopasiDataModel& dataModel);

    /**
     * Create the SBML function definition from the given COPASI function.
     */
    void createFunctionDefinition(CFunction& function);

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
    static void checkForUnsupportedObjectReferences(const CExpression& expression, const CCopasiDataModel& dataModel, unsigned int sbmlLevel, unsigned int sbmlVersion, std::vector<SBMLIncompatibility>& result);

    /**
     * Checks all expressions in the given datamodel for piecewise defined
     *functions.
     */
    static void checkForPiecewiseFunctions(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result);
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
    static void isExpressionSBMLCompatible(const CExpression& expr, const CCopasiDataModel& dataModel, int sbmlLevel, int sbmlVersion, std::vector<SBMLIncompatibility>& result);

    /**
     * Checks wether the rule in the given model entity can be exported to SBML Level2 Version1.
     * If it can be exported, the result vector will be empty, otherwise it will
     * contain a number of messages that specify why it can't be exported.
     */
    static void isExpressionSBMLL1Compatible(const CExpression& expr, const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * Checks wether the rule in the given model entity can be exported to SBML Level2 Version1.
     * If it can be exported, the result vector will be empty, otherwise it will
     * contain a number of messages that specify why it can't be exported.
     */
    static void isExpressionSBMLL2V1Compatible(const CExpression& expr, const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * Checks wether the rule in the given model entity can be exported to SBML Level2 Version3.
     * If it can be exported, the result vector will be empty, otherwise it will
     * contain a number of messages that specify why it can't be exported.
     */
    static void isExpressionSBMLL2V3Compatible(const CExpression& expression, const CCopasiDataModel& pDataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * This static methods checks, wether the model uses any function calls
     * that can not be expressed in SBML like the random distribution
     * functions.
     */
    void checkForUnsupportedFunctionCalls(const CCopasiDataModel& dataModel,
                                          unsigned int sbmlLEvel, unsigned int sbmlVersion,
                                          std::vector<SBMLIncompatibility>& result);

    /**
     * This static methods checks, wether the given CEvaluationTree uses any function calls
     * that can not be expressed in SBML like the random distribution
     * functions.
     */
    static void checkForUnsupportedFunctionCalls(const CEvaluationTree& tree,
        const std::set<CEvaluationNodeFunction::SubType>& unsupportedFunctions,
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
    static void checkForInitialAssignments(const CCopasiDataModel& pDataModel, std::vector<SBMLIncompatibility>& result);

    /**
     * Goes through the given SBML model and puts all ids with the
     * corresponding object into a map.
     */
    const std::map<std::string, const SBase*> createIdMap(const Model& sbmlModel);

    /**
     * Create the kinetic law for the given reaction.
     * On failure NULL is returned.
     */
    KineticLaw* createKineticLaw(const CReaction& reaction, CCopasiDataModel& dataModel);

    /**
     * Go through a CEvaluationNode base tree and return a list of
     * functions directly called in this tree.
     */
    const std::set<CFunction*> findDirectlyUsedFunctions(const CEvaluationNode* pRootNode, CCopasiDataModel& dataModel);

    /**
     * checks if the given ASTNode based tree is divided by the
     * volume of the compartment identified by the given id string.
     */
    static ASTNode* isDividedByVolume(const ASTNode* pRootNode, const std::string& compartmentId);

    /**
     * Creates an expression from a given node and a set of parameter
     * mappings by
     * replacing the function arguments with the parameters.
     */
    static CEvaluationNode* createExpressionTree(const CEvaluationNode* const pNode,
        const std::map<std::string, std::string>& parameterMap,
        const CCopasiDataModel& dataModel);

    /**
     * Creates an expression from a given function and a set of parameters by
     * replacing the function arguments with the parameters.
     */
    static CEvaluationNode* createExpressionTree(const CFunction* const pFun,
        const std::vector<std::vector<std::string> >& arguments,
        const CCopasiDataModel& dataModel);

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
     * Sorts the initial assignments.
     */
    void orderInitialAssignments(const CCopasiDataModel& dataModel);

    /**
     * Sorts the rules.
     */
    void orderRules(const CCopasiDataModel& dataModel);

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
     * Additionally remove all function definitions and all unit
     * definitions that have not been used in the file.
     */
    void removeUnusedObjects(const CCopasiDataModel& pDataModel);
  };

#endif // CSBLExporter_H__
