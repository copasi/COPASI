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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CSBMLExporter_H__
#define CSBMLExporter_H__

#include <vector>
#include <string>
#include <set>
#include <map>

#include "copasi/copasi.h"

#include "copasi/function/CEvaluationNodeFunction.h"
#include <sbml/FunctionDefinition.h>
#include "copasi/sbml/SBMLIncompatibility.h"
#include "copasi/utilities/CProcessReport.h"

class CAnnotation;
class CChemEqElement;
class CCompartment;
class CDataModel;
class CCopasiParameter;
class CEvaluationNode;
class CEvent;
class CExpression;
class CFunction;
class CFunctionDB;
class CMetab;
class CModelValue;
class CReaction;
class CModelEntity;
class SBMLIncompatibility;
class CProcessReport;

LIBSBML_CPP_NAMESPACE_BEGIN
class Event;
class KineticLaw;
class Model;
class Parameter;
class Rule;
class SBase;
class SBMLDocument;
class UnitDefinition;
class XMLNode;
LIBSBML_CPP_NAMESPACE_END

class CSBMLExporter
{
protected:
  SBMLDocument* mpSBMLDocument;
  unsigned int mSBMLLevel;
  unsigned int mSBMLVersion;
  std::vector<const CModelEntity*> mAssignmentVector;
  std::vector<const CModelEntity*> mODEVector;
  std::vector<const CModelEntity*> mInitialAssignmentVector;
  std::map<const CDataObject*, SBase*> mCOPASI2SBMLMap;
  std::set<SBase*> mHandledSBMLObjects;
  std::set<CFunction*> mUsedFunctions;
  std::map<std::string, const SBase*> mIdMap;
  std::vector<SBMLIncompatibility> mIncompatibilities;
  bool mIncompleteExport;
  bool mVariableVolumes;
  const CModelValue* mpAvogadro;
  std::string mAvogadroId;
  bool mAvogadroCreated;
  std::map<std::string, const SBase*> mMetaIdMap;
  bool mMIRIAMWarning;
  std::map<std::string, const CEvaluationTree*> mFunctionIdMap;
  bool mDocumentDisowned;
  bool mExportCOPASIMIRIAM;
  std::map<std::string, Parameter*> mParameterReplacementMap;
  std::set<std::string> mSpatialSizeUnitsSpecies;
  ListOfFunctionDefinitions mExportedFunctions;
  std::map<const FunctionDefinition*, const CDataObject*> mFunctionMap;
  std::map<const std::string, Parameter*> mInitialValueMap;
  /**
   * the progress handler for the export
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

public:

  /**
   * Sets the progress handler to be used while exporting
   * set to NULL, to stop reporting
   *
   * @param pHandler the progress handler to be used, or NULL
   */
  void setHandler(CProcessReport * pProcessReport);

  /**
   * @return the currently set callback handler
   */
  const CProcessReport * getCallBack() const;

  /**
   * resets the currently set callback by calling setHandler(NULL)
   */
  virtual void clearCallBack();

  /**
   * This utility functions adds a new step to the progress dialog (if present)
   * @param globalStep the global steps that have been completed
   * @param currentTotal the total for current task
   * @param title the title of the current task
   * @return a boolean indicating whether processing should be stopped
   */
  bool createProgressStepOrStop(unsigned C_INT32 globalStep,
                                unsigned C_INT32 currentTotal,
                                const std::string& title);

  /**
   * Notifies the progress dialog of local progress
   *
   * @return a boolean indicating whether processing should be stopped
   */
  bool reportCurrentProgressOrStop();

  /**
   * Notifies the progress dialog that a step finished
   */
  void finishCurrentStep();

  /**
   * Notifies the progress dialog that the overall exporting is complete
   */
  void finishExport();

  /**
   * Default constructor
   */
  CSBMLExporter();

  /**
   * Destructor
   */
  ~CSBMLExporter();

  SBMLDocument* getSBMLDocument();

  /**
   * Export the model to SBML.
   * The SBML model is returned as a string. In case of an error, an
   * empty string is returned.
   */
  const std::string exportModelToString(CDataModel& dataModel,
                                        unsigned int sbmlLevel,
                                        unsigned int sbmlVersion);

  /**
   * Export the model to SBML.
   * The model is written to the file given by filename.
   * If the export fails, false is returned.
   */
  bool exportModel(CDataModel& dataModel,
                   const std::string& filename,
                   unsigned int sbmlLevel = 2,
                   unsigned int sbmlVersion = 1,
                   bool overwrite = false);

  /**
   * Checks wether the given data model can be exported to a certain version of SBML.
   * If it can be exported, the result vector will be empty, otherwise it will
   * contain a number of messages that specify why it can't be exported.
   */
  static const std::vector<SBMLIncompatibility> isModelSBMLCompatible(
    const CDataModel& pDataModel,
    int sbmlLevel,
    int sbmlVersion,
    std::map<std::string, const SBase*>& idMap);

  /**
   * This method assures that the SBMLDocument is not deleted by the destructor of the exporter.
   * This allows us to get the SBMLDocument from the exporter and store it in the data model without having to copy it.
   */
  void disownSBMLDocument();

  /**
   * Returns a const pointer to the COPASI2SBMLMap.
   */
  const std::map<const CDataObject*, SBase*>& getCOPASI2SBMLMap() const;

  /**
   * Returns whether the exporter is supposed to export COPASIs MIRIAM
   * annotation in addition to SBML MIRIAM.
   */
  bool isSetExportCOPASIMIRIAM() const;

  /**
   * Sets whether the exporter is supposed to export COPASIs MIRIAM
   * annotation in addition to SBML MIRIAM.
   */
  void setExportCOPASIMIRIAM(bool exportMIRIAM);

  /**
   * Create a unique id for an SBML object.
   * I can't just take the Copasi key of the object since this might conflict
   * with an already existing sbml id which came from the sbmlid attribute in a
   * copasi file or directly by importing an SBML file.
   */
  static const std::string createUniqueId(const std::map<std::string, const SBase*>& idMap,
                                          const std::string& prefix,
                                          bool addIndexForFirst,
                                          const std::string & separator = "_");

  /**
   * Method to create a valid XHTML node from a CModels comments string.
   * This method is declared public so that I can call it from the unit tests.
   */
  static XMLNode* createSBMLNotes(const std::string& notes_string);

  bool exportLayout(unsigned int sbmlLevel, CDataModel& dataModel);
protected:

  /**
   * Creates the units for the SBML model.
   */
  void createUnits(const CDataModel& dataModel);

  /**
   * Creates the time unit for the SBML model.
   */
  void createTimeUnit(const CDataModel& dataModel);

  /**
   * Creates the volume unit for the SBML model.
   */
  void createLengthUnit(const CDataModel& dataModel);

  /**
   * Creates the volume unit for the SBML model.
   */
  void createAreaUnit(const CDataModel& dataModel);

  /**
   * Creates the volume unit for the SBML model.
   */
  void createVolumeUnit(const CDataModel& dataModel);

  /**
   * Creates the substance unit for the SBML model.
   */
  void createSubstanceUnit(const CDataModel& dataModel);

  /**
   * Creates the compartments for the model.
   */
  bool createCompartments(CDataModel& dataModel);

  /**
   * Creates the compartment for the given COPASI compartment.
   */
  void createCompartment(const CCompartment& compartment);

  /**
   * Creates the compartments for the model.
   */
  bool createMetabolites(CDataModel& dataModel);

  /**
   * Creates the species for the given COPASI metabolite.
   */
  void createMetabolite(const CMetab& metab);

  /**
   * Creates the parameters for the model.
   */
  bool createParameters(CDataModel& dataModel);

  /**
   * Creates the parameter for the given COPASI parameter.
   */
  void createParameter(const CModelValue& parameter);

  /**
   * Creates the reactions for the model.
   */
  bool createReactions(CDataModel& dataModel);

  /**
   * Creates the reaction for the given COPASI reaction.
   */
  void createReaction(const CReaction& reaction, CDataModel& dataModel);

  /**
   * Creates the initial assignments for the model.
   */
  bool createInitialAssignments(CDataModel& dataModel);

  /**
   * Creates the initial assignment for the given COPASI model entity.
   */
  void createInitialAssignment(const CModelEntity& modelEntity, CDataModel& dataModel);

  /**
   * Creates the rules for the model.
   */
  bool createRules(CDataModel& dataModel);

  /**
   * Creates the rule for the given COPASI model entity.
   */
  void createRule(const CModelEntity& modelEntity, CDataModel& dataModel, Rule* pOldRule);

  /**
   * Create all function definitions.
   */
  bool createFunctionDefinitions(CDataModel& dataModel);

  /**
   * Create the SBML function definition from the given COPASI function.
   */
  void createFunctionDefinition(CFunction& function, CDataModel& dataModel);

  /**
   * @brief creates and SBML UnitDefinition for the given unit
   * @param unit the COPASI unit element
   * @return the SBML UnitDefinition
   */
  UnitDefinition* createUnitDefinitionFor(const CUnit& unit);

  /**
   * @brief exports the given unit to the sbmlElement
   * @param unit the unit to export
   * @param sbmlElement the sbml element that the unit should be assigned to
   */
  void exportAndAssignUnit(const CUnit& unit, SBase* sbmlElement);

  /**
   * Checks all assignments (initial and transient) for references to objects
   * that can not be exported to SBML.
   */
  void checkForUnsupportedObjectReferences(const CDataModel& dataModel,
      unsigned int sbmlLevel,
      unsigned int sbmlVersion,
      std::vector<SBMLIncompatibility>& result);
  /**
   * Checks the given expression for references to objects
   * that can not be exported to SBML.
   */
  static void checkForUnsupportedObjectReferences(const CEvaluationTree& expression,
      const CDataModel& dataModel,
      unsigned int sbmlLevel,
      unsigned int sbmlVersion,
      std::vector<SBMLIncompatibility>& result,
      std::map<std::string, const SBase*>& idMap,
      bool initialExpression = false,
      std::map<const std::string, Parameter*>* initialMap = NULL);

  /**
   * Checks all expressions in the given datamodel for piecewise defined
   * functions.
   */
  static void checkForPiecewiseFunctions(const CDataModel& dataModel,
                                         std::vector<SBMLIncompatibility>& result);

  /**
   * Checks the given node and all it's children for the occurrence of
   * piecewise functions.
   */
  static void checkForPiecewiseFunctions(const CEvaluationNode& node,
                                         std::vector<SBMLIncompatibility>& result,
                                         const std::string& objectName,
                                         const std::string& objectType);

  /**
   * Checks whether the given data model can be exported to SBML Level1
   * If it can be exported, the result vector will be empty, otherwise it will
   * contain a number of messages that specify why it can't be exported.
   */
  static void isModelSBMLL1Compatible(const CDataModel& dataModel,
                                      std::vector<SBMLIncompatibility>& result);

  /**
   * Checks whether the given data model can be exported to SBML Level2 Version1.
   * If it can be exported, the result vector will be empty, otherwise it will
   * contain a number of messages that specify why it can't be exported.
   */
  static void isModelSBMLL2V1Compatible(const CDataModel& dataModel,
                                        std::vector<SBMLIncompatibility>& result);

  /**
   * Checks whether the given data model can be exported to SBML Level2 Version3.
   * If it can be exported, the result vector will be empty, otherwise it will
   * contain a number of messages that specify why it can't be exported.
   */
  static void isModelSBMLL2V3Compatible(const CDataModel& dataModel,
                                        std::vector<SBMLIncompatibility>& result);

  /**
   * Checks whether the model contains a metabolite that is defined by an ODE
   * expression and that is located in a variable volume. Since COPASI
   * interprets the expression differently from SBML, we can not correctly
   * export this yet. See Bug 903.
   */
  static void checkForODESpeciesInNonfixedCompartment(const CDataModel& dataModel,
      std::vector<SBMLIncompatibility> result);

  /**
   * Checks whether the rule in the given model entity can be exported to
   * the specified version of SBML.
   * If it can be exported, the result vector will be empty, otherwise it will
   * contain a number of messages that specify why it can't be exported.
   */
  static void isExpressionSBMLCompatible(const CEvaluationTree& expr,
                                         const CDataModel& dataModel,
                                         int sbmlLevel,
                                         int sbmlVersion,
                                         std::vector<SBMLIncompatibility>& result,
                                         std::map<std::string, const SBase*>& idMap,
                                         const std::string& objectDescription,
                                         bool initialExression = false,
                                         std::map<const std::string, Parameter*>* initialMap = NULL);

  /**
   * Checks whether the rule in the given model entity can be exported to SBML Level2 Version1.
   * If it can be exported, the result vector will be empty, otherwise it will
   * contain a number of messages that specify why it can't be exported.
   */
  static void isExpressionSBMLL1Compatible(const CEvaluationTree& expr,
      const CDataModel& dataModel,
      std::vector<SBMLIncompatibility>& result);

  /**
   * Checks whether the rule in the given model entity can be exported to SBML Level2 Version1.
   * If it can be exported, the result vector will be empty, otherwise it will
   * contain a number of messages that specify why it can't be exported.
   */
  static void isExpressionSBMLL2V1Compatible(const CEvaluationTree& expr,
      const CDataModel& dataModel,
      std::vector<SBMLIncompatibility>& result);

  /**
   * Checks whether the rule in the given model entity can be exported to SBML Level2 Version3.
   * If it can be exported, the result vector will be empty, otherwise it will
   * contain a number of messages that specify why it can't be exported.
   */
  static void isExpressionSBMLL2V3Compatible(const CEvaluationTree& expression,
      const CDataModel& pDataModel,
      std::vector<SBMLIncompatibility>& result);

  /**
   * This methods checks, whether the model uses any function calls
   * that can not be expressed in SBML like the random distribution
   * functions.
   */
  void checkForUnsupportedFunctionCalls(const CDataModel& dataModel,
                                        unsigned int sbmlLEvel,
                                        unsigned int sbmlVersion,
                                        std::vector<SBMLIncompatibility>& result);

  /**
   * This static methods checks recursively, whether the given CEvaluationNode
   * contains any function calls that can not be expressed in SBML like the
   * random distribution functions.
   */
  static void checkForUnsupportedFunctionCalls(const CEvaluationNode& node,
      const std::set<CEvaluationNode::SubType>& unsupportedFunctions,
      std::vector<SBMLIncompatibility>& result,
      const std::string& objectDescription);

  /**
   * This method checks whether the given model contains any initial assignments.
   */
  static void checkForInitialAssignments(const CDataModel& dataModel,
                                         std::vector<SBMLIncompatibility>& result);

  /**
   * Goes through the given SBML model and puts all ids with the
   * corresponding object into a map.
   */
  const std::map<std::string, const SBase*> createIdMap(const Model& sbmlModel);

  /**
   * Create the kinetic law for the given reaction.
   * On failure NULL is returned.
   */
  KineticLaw* createKineticLaw(const CReaction& reaction, CDataModel& dataModel,
                               unsigned int level, unsigned int version);

  /**
   * Go through a CEvaluationNode base tree and add the names
   * of all functions directly called in this tree to the set.
   */
  static void findDirectlyUsedFunctions(const CEvaluationNode* pRootNode,
                                        std::set<std::string>& result);

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
      const CDataModel& dataModel);
   */

  /**
   * Creates an expression from a given function and a set of parameters by
   * replacing the function arguments with the parameters.
  static CEvaluationNode* createExpressionTree(const CFunction* const pFun,
      const std::vector<std::vector<std::string> >& arguments,
      const CDataModel& dataModel);
   */

  /**
   * Create an expression that corresponds to a kinetic law.
   * If the kinetic law was mass action, the expression is a mass action term
   * , otherwise it is a function call.
   */
  CEvaluationNode* createKineticExpression(CFunction* pFun,
      const std::vector<std::vector<const CDataObject *> >& arguments);

  /**
   * Checks if the given datamodel contains events.
   * This is called if SBML Level 1 is to be exported.
   * @return false if an event was used in the model, true otherwise
   */
  static bool checkForEvents(const CDataModel & dataModel,
                             std::vector< SBMLIncompatibility > & result);

  /**
   * Creates an SBMLDocument from the given CDataModelObject.
   * It checks if an SBMLDocument already exists from an import and if
   * this is the case, the old document is copied.
   * If none exists a new one is created.
   * Copying the old one makes sure that if something goes wrong during
   * export, the original model is still consistent.
   *
   * @return true, if exporting should continue, false otherwise
   */
  bool createSBMLDocument(CDataModel& dataModel);

  /**
   * Sorts the rules.
   */
  std::vector<const CModelEntity*> orderRules(const CDataModel& dataModel);

  /**
   * Creates a new COPASI2SBMLMap based on the old map and the copied
   * SBMLDocument.
   */
  void updateCOPASI2SBMLMap(const CDataModel& dataModel);

  /**
   * Creates the events for the given data model.
   */
  bool createEvents(CDataModel& dataModel);

  /**
   * Creates an SBML Event for the given COPASI event.
   */
  void createEvent(const CEvent& event, Event* pSBMLEvent, CDataModel& dataModel);

  /**
   * This method creates the individual event assignments for the given
   * event.
   */
  void exportEventAssignments(const CEvent& event, Event* pSBMLEvent, CDataModel& dataModel);

  /**
   * This method checks if the given event assignment object is SBML
   * compatible.
   */
  static void isEventAssignmentSBMLCompatible(const CDataObject * pTarget,
      const CExpression* pExpression,
      const CDataModel& dataModel,
      unsigned int sbmlLevel,
      unsigned int sbmlVersion,
      const std::string& eventName,
      std::vector<SBMLIncompatibility>& result,
      std::map<std::string, const SBase*>& idMap);

  /**
   * This method checks if the given event object is SBML
   * compatible.
   */
  static void isEventSBMLCompatible(const CEvent* pEvent,
                                    const CDataModel& dataModel,
                                    unsigned int sbmlLevel,
                                    unsigned int sbmlVersion,
                                    std::vector<SBMLIncompatibility>& result,
                                    std::map<std::string, const SBase*>& idMap
                                   );

  /**
   * This method creates an ASTNode tree where all the species specified in
   * the given vector are multiplied. This is used to create the mass action
   * kinetic law.
   */
  static ASTNode* createTimesTree(const CDataVector<CChemEqElement >& vect,
                                  unsigned int pos = 0);

  /**
   * Remove all compartments, species, parameters and reactions
   * that did not end up in mHandledSBMLObjects during an export.
   */
  void removeUnusedObjects();

  /**
   * Takes a set of functions and recursively finds functions used by those
   * functions
   */
  static const std::vector<CFunction*> findUsedFunctions(std::set<CFunction*>& functions,
      CFunctionDB* pFunctionDB);

  static const std::set<CFunction*> createFunctionSetFromFunctionNames(
    const std::set<std::string>& names, CFunctionDB* pFunDB);

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
  static const std::set<CEvaluationNode::SubType> createUnsupportedFunctionTypeSet(
    unsigned int sbmlLevel);

  /**
   * Find all ModelEntities for which the given node and its children contains
   * references.
   */
  static void findModelEntityDependencies(const CEvaluationNode* pNode,
                                          const CDataModel& dataModel,
                                          std::set<const CModelEntity*>& dependencies);

  /**
   * Creates an ASTNode based tree where all occurrences of nodes that are not
   * supported in SBML Level 1 are replaced by supported constructs.
   * On error an exception is created.
   * The caller is responsible for freeing the memory of the returned object.
   */
  static ASTNode* convertASTTreeToLevel1(const ASTNode* pNode,
                                         const ListOfFunctionDefinitions& functions,
                                         std::string& message);

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
  static CEvaluationNode* createMassActionExpression(
    const std::vector<std::vector<const CDataObject *> >& arguments,
    bool isReversible);

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
  CEvaluationNode* replaceSpeciesReferences(const CEvaluationNode* pOrigNode,
      const CDataModel& dataModel);

  void createAvogadroIfNeeded(const CDataModel & dataModel);

  /**
   * Try to find a global parameter that represents avogadros number.
   */
  void findAvogadro(const CDataModel& dataModel);

  /**
   * This method gets the MIRIAM annotation from the given COPASI object and
   * sets it on the given SBML object.
   */
  bool updateMIRIAMAnnotation(const CDataObject* pCOPASIObject,
                              SBase* pSBMLObject,
                              std::map<std::string, const SBase*>& metaIds);

  /**
   * This is a general method to set the notes of an SBase object based on a COPASI
   * Annotation.
   * This will allow us to export notes on objects other than just the model.
   */
  static bool setSBMLNotes(SBase* pSBase, const CAnnotation* pAnno);

  /**
   * This method creates a copy of parent where the child with the given index is
   * replaced by the new child given as the second argument.
   * If index is greater than the number of children - 1, NULL is returned.
   */
  XMLNode* replaceChild(const XMLNode* pParent, const XMLNode* pNewChild, unsigned int index);

  /**
   * This method goes through the given datamodel and collects all SBML ids.
   */
  void collectIds(const CDataModel& dataModel, std::map<std::string, const SBase*>& idMap);

  /**
    * This converts an CEvaluationNode based tree to an ASTNode tree.
    * It makes sure that all functions used in function calls already have a
    * unique SBML id.
    */
  ASTNode* convertToASTNode(const CEvaluationNode* pOrig, CDataModel& dataModel);

  /**
   * This method traverse a CEvaluationTree and set the SBML id on all
   * functions that are used in function calls in the tree.
   */
  void setFunctionSBMLIds(const CEvaluationNode* pNode, CDataModel& dataModel);

  /**
   * Creates error messages from the list of incompatibilities and thows an
   * exception.
   */
  void outputIncompatibilities() const;

  /**
   * Goes through the expression tree and tries to find occurences of local
   * parameters. If one is found, a global parameter is created and all
   * references to the local parameters are substituted.
   */
  void replace_local_parameters(ASTNode* pOrigNode, const CDataModel& dataModel);

  /**
   * This method goes through the expression tree and tries to find node
   * names that correspond to common names of local parameters.
   * If the common name also occurs in the replacement map, the node name has
   * to be set to the id of the corresponding global parameter, otherwise the name
   * has to be set to the object name of the parameter.
   */
  void restore_local_parameters(ASTNode* pOrigNode, const CDataModel& dataModel);

  /**
   * Since we want to replace local reaction parameters by global parameters if they
   * are used in an assignment, we have to create the reactions after creating the
   * rules and events. On the other hand, a reaction flux might also be referenced in
   * an assignment or an event and the creation of this rule or event only works
   * if the reactions already have SBML ids.
   * To solve this problem, the reactions have to be assigned SBML ids prior to
   * creating rules and events.
   */
  void assignSBMLIdsToReactions(CModel* pModel);

  /**
   * This method goes through all compartments and events and checks if
   * there is an assignment to a volume.
   */
  bool hasVolumeAssignment(const CDataModel& dataModel);

  /**
   * This method multiplies a given expression by the given object.
   * The caller is responsible for freeing the memory for the new expression.
   */
  static CEvaluationNode* multiplyByObject(const CEvaluationNode* pOrigNode,
      const CDataObject* pObject);

  /**
   * Converts the SBML model given in SBML Level 1 Version 2 format to SBML Level 1 Version 1.
   * The method basically removes the namespace attribute on the sbml element
   * and changes the version from 2 to 1.
   * It also renames all "species" elements to "specie".
   * All other changes between SBML Level 1 Version 2 and Level 1 Version 1 should not be relevant here.
   */
  static void convert_to_l1v1(std::string& l1v2_string);

  void addInitialAssignmentsToModel(const CDataModel & dataModel);
};

#endif // CSBLExporter_H__
