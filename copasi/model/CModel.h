// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CModel
#define COPASI_CModel

#include <map>
#include <vector>
#include <set>
#include <string>

#include "copasi/model/CModelValue.h"

#include "copasi/model/CState.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CEvent.h"
#include "copasi/model/CMoiety.h"
#include "copasi/model/CModelParameterSet.h"

#include "copasi/utilities/CVector.h"
#include "copasi/utilities/CMatrix.h"
#include "copasi/utilities/CLinkMatrix.h"
#include "copasi/report/CCopasiContainer.h"
#include "copasi/utilities/CUnit.h"

#include "copasi/math/CMathDependencyGraph.h"

class CMathContainer;
class CProcessReport;
class CArrayAnnotation;
class CMathModel;
class CExperiment;

class CModel : public CModelEntity
{
public:
  /**
   * Enum of valid model types.
   */
  enum ModelType {deterministic = 0, stochastic};

  /**
   * String representation of the valid model types.
   */
  static const char * ModelTypeNames[];

  enum DependencyType {initial = 0, transient, physical};

  enum UnitType {volume = 0,
                 area,
                 length,
                 time,
                 quantity
                };

private:
  /**
   *  Copy constructor
   *  @param "const CModel &" src
   */
  CModel(const CModel & src);

  CModel& operator=(const CModel& src);

public:
  // static CModel * fromData(const CData & data);
  // virtual CData toData() const;
  virtual bool applyData(const CData & data);

  /**
   *  constructor
   */
  CModel(CCopasiContainer* pParent);

  /**
   * Destructor
   */
  ~CModel();        // destructor (deallocation code here)

  /**
   * Set the object parent
   * @param const CCopasiContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CCopasiContainer * pParent);

  /**
   * Retrieve the units of the object.
   * @return std::string units
   */
  virtual const std::string getUnits() const;

  /**
   * Retrieve the units of the child object.
   * @return std::string units
   */
  virtual std::string getChildObjectUnits(const CCopasiObject * pObject) const;

  /**
   * Converts the set of reactions to a set of reactions where all reactions are irreversible.
  */
  bool convert2NonReversible();

#ifdef WITH_PE_EVENT_CREATION
  /**
   * Creates events for all elements of an parameter estimation  time course experiment
   */
  bool createEventsForTimeseries(CExperiment* experiment = NULL);
#endif

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @return Fail
   */
  C_INT32 load(CReadConfig &configBuffer);

  /**
   *  This function must be called to initialize the vector of Metabolites
   *  after finishing adding metabolites to compartments.
   */
  void initializeMetabolites();

  /**
   *  This must be called whenever something is changed in the model
   *  that would make it necessary to recalculate the matrix decomposition
   */
  void setCompileFlag(bool flag = true);

  /**
   * Check whether a model compile is necessary.
   * @return const bool & isCompileNecessary
   */
  const bool & isCompileNecessary() const;

  /**
   * Compile the model if necessary
   * @param CProcessReport* pProcessReport
   * @return bool success
   */
  bool compileIfNecessary(CProcessReport* pProcessReport);

  /**
   * Force a compile the model.
   * @param CProcessReport* pProcessReport
   * @return bool success
   */
  bool forceCompile(CProcessReport* pProcessReport);

  bool buildDependencyGraphs();

  /**
   *  Build the Stoichiometry Matrix from the chemical equations of the steps
   */
  void buildStoi();

  /**
   *  Build the core of the link matrix L
   *  @param const CMatrix< C_FLOAT64 > & LU
   */
  void buildLinkZero();

  /**
   *  Build the Reduced Stoichiometry Matrix from the LU decomposition
   */
  void buildRedStoi();

  /**
   *  Build the moieties based on the LU decomposition
   */
  void buildMoieties();

private:
  /**
   *  compute the actual initial value of all moieties
   *  (from the initial values of the metabolites).
   */
  void updateMoietyValues();

public:
  //********** Metabs *****************************

  /**
   * Return the metabolites of this model
   * @return CCopasiVectorN< CMetab > & metabolites
   */
  const CCopasiVector< CMetab > & getMetabolites() const;
  CCopasiVector< CMetab > & getMetabolites();

  /**
   * Retrieves the vector of metabolites at it is used in the reduced model.
   * @return const CCopasiVectorN< CMetab > &metabolites
   */
  const CCopasiVector< CMetab > & getMetabolitesX() const;
  CCopasiVector< CMetab > & getMetabolitesX();

  /**
   *  Get the number of total metabolites
   *  @return C_INT32 totMetab
   */
  size_t getNumMetabs() const;

  /**
   *  Get the number of variable metabolites
   *  @return size_t totMetab
   */
  size_t getNumVariableMetabs() const;

  /**
   *  Get the number of metabolites determined by ODEs
   *  @return size_t dimension
   */
  size_t getNumODEMetabs() const;

  /**
   *  Get the number of metabolites determined by assignments
   *  @return size_t dimension
   */
  size_t getNumAssignmentMetabs() const;

  /**
   *  Get the number of independent metabolites determined by reactions
   *  @return size_t dimension
   */
  size_t getNumIndependentReactionMetabs() const;

  /**
   *  Get the number of dependent metabolites determined by reactions
   *  @return size_t dimension
   */
  size_t getNumDependentReactionMetabs() const;

  //********** additional values *****************************

  /**
   * Return the non concentration values of this model
   * @return CCopasiVectorN< CModelValue > & values
   */
  const CCopasiVectorN< CModelValue > & getModelValues() const;
  CCopasiVectorN< CModelValue > & getModelValues();

  /**
   *  Get the number of non concentration values
   *  @return C_INT32
   */
  size_t getNumModelValues() const;

  /**
   * Return the non model parameter sets
   * @return CCopasiVectorN< CModelParameterSet > & modelParameterSets
   */
  const CCopasiVectorN< CModelParameterSet > & getModelParameterSets() const;
  CCopasiVectorN< CModelParameterSet > & getModelParameterSets();

  /**
   * Retrieve the parameter set
   * @return const CModelParameterSet & modelParameterSet
   */
  const CModelParameterSet & getActiveModelParameterSet() const;
  CModelParameterSet & getActiveModelParameterSet();

  /**
   * Update the model initial values from the active parameter set.
   */
  void applyActiveParameterSet();

  /**
   * refresh the active parameter set from the model initial values
   */
  void refreshActiveParameterSet();

  //********** TT *****************************

public:
  //********** Reactions *****************************

  /**
   * Return the vector of reactions
   * @return CCopasiVectorNS <CReaction> & reactions
   */
  CCopasiVectorNS < CReaction > & getReactions();

  /**
   * Return the vector of reactions
   * @return const CCopasiVectorS <CReaction> & reactions
   */
  const CCopasiVectorNS < CReaction > & getReactions() const;

  /**
   * Get the total steps
   * @return size_t total steps;
   */
  size_t getTotSteps() const;

  /**
   * Retrieve the vector of particle fluxes from the model
   * @return const CVector< C_FLOAT64 > & particleFlux
   */
  const CVector< C_FLOAT64 > & getParticleFlux() const;

  //********* Events **************************

  /**
   * Return the vector of events
   */
  CCopasiVectorN < CEvent > & getEvents();

  /**
   * Return the vector of events
   */
  const CCopasiVectorN < CEvent > & getEvents() const;

  //******************************************+

  /**
   * Return the key of this model
   * @return string key
   */
  const std::string & getKey() const;

  /**
   * Return a pointer to the current time
   */
  //virtual void * getValuePointer() const;

  //************** time *********************

  /**
   * Set the start time for modeling
   * @param const C_FLOAT64 & time
   */
  void setInitialTime(const C_FLOAT64 & time);

  /**
   * Retrieve the initial time
   * @return const C_FLOAT64 & time
   */
  const C_FLOAT64 & getInitialTime() const;

  /**
   * Set the actual model time
   * @param const C_FLOAT64 & time
   */
  void setTime(const C_FLOAT64 & time);

  /**
   * Retrieve the actual model time
   * @return const C_FLOAT64 & time
   */
  const C_FLOAT64 & getTime() const;

  //************** compartments *********************

  /**
   * Return the compartments of this model
   * @return CCopasiVectorNS < CCompartment > *
   */
  CCopasiVectorNS < CCompartment > & getCompartments();

  /**
   * Return the compartments of this model
   * @return const CCopasiVectorNS < CCompartment > *
   */
  const CCopasiVectorNS < CCompartment > & getCompartments() const;

  //***************************************************

  /**
   *  Get the Reduced Stoichiometry Matrix of this Model
   */
  const CMatrix < C_FLOAT64 > & getRedStoi() const;

  /**
   *  Get the stoichiometry matrix of this model
   */
  const CMatrix < C_FLOAT64 > & getStoi() const;

  /**
   * @return Get the matrix annotation to the stoichiometry matrix.
   */
  const CArrayAnnotation * getStoiAnnotation() const;

  /**
   * Return the mMoieties of this model
   * @return CCopasiVectorN < CMoiety > &
   */
  const CCopasiVector < CMoiety > & getMoieties() const;

  /**
   * Returns the pointer to the species with the given name
   * @param const std::string & name
   * @return CMetab * pSpecies
   */
  CMetab * findMetabByName(const std::string & name) const;

  /**
   * Returns the index of the moiety
   * @param const std::string & Target
   * @return index
   */
  size_t findMoiety(const std::string &Target) const;

  /**
   * Get the LU decomposition matrix of this model
   * @return const TNT::Matrix < C_FLOAT64 > & LU
   */
  //    const CMatrix < C_FLOAT64 > & getmLU() const;

  /**
   * Get the link matrix L of the relation: Stoi = L * RedStoi
   * @return const CLinkMatrixView L
   */
  const CLinkMatrixView & getL() const;

  /**
   * Get the relevant portion of the link matrix L.
   * @return const CLinkMatrix & L0
   */
  const CLinkMatrix & getL0() const;

  /**
   * initialize all values of the model with their initial values
   */
  void applyInitialValues();

  /**
   * Update all initial values.
   * @param const CModelParameter::Framework & framework
   * @return bool success
   */
  bool updateInitialValues(const CModelParameter::Framework & framework);

  /**
   * Copy the current state value to the initial state
   */
  void stateToIntialState();

  /**
   * Set the unit for volumes. If COPASI recognizes
   * the unit the conversion factors are set accordingly
   * and true is returned.
   * @param const std::string & name
   * @return bool success
   */
  bool setVolumeUnit(const std::string & name);

  /**
   * Set the unit for volumes. If COPASI recognizes
   * the unit the conversion factors are set accordingly
   * and true is returned.
   * @param const CModel::VolumeUnit & unit
   * @return bool success
   */
  bool setVolumeUnit(const CUnit::VolumeUnit & unitEnum);

  /**
   * Get the current volume unit of the model
   * @return const CUnit & volumeunit
   */
  const std::string & getVolumeUnit() const;

  /**
   * Get the unit for volumes
   * @return std::string volumeUnit
   */
  std::string getVolumeUnitName() const;

  /**
   * Get the unit for volumes
   * @return CModel::VolumeUnit volumeUnit
   */
  CUnit::VolumeUnit getVolumeUnitEnum() const;

  /**
   * Set the unit for areas.
   * @param const std::string & name
   * @return bool success
   */
  bool setAreaUnit(const std::string & name);

  /**
   * Set the unit for areas.
   * @param const CModel::AreaUnit & unit
   * @return bool success
   */
  bool setAreaUnit(const CUnit::AreaUnit & unitEnum);

  /**
   * Get the current area unit of the model
   * @return const CUnit & areaunit
   */
  const std::string & getAreaUnit() const;

  /**
   * Get the unit for areas
   * @return std::string areaUnit
   */
  std::string getAreaUnitName() const;

  /**
   * Get the unit for areas
   * @return CModel::AreaUnit areaUnit
   */
  CUnit::AreaUnit getAreaUnitEnum() const;

  /**
   * Set the unit for lengths.
   * @param const std::string & name
   * @return bool success
   */
  bool setLengthUnit(const std::string & name);

  /**
   * Set the unit for lengths.
   * @param const CModel::LengthUnit & unit
   * @return bool success
   */
  bool setLengthUnit(const CUnit::LengthUnit & unitEnum);

  /**
   * Get the current length unit of the model
   * @return const CUnit & lengthunit
   */
  const std::string & getLengthUnit() const;

  /**
   * Get the unit for lengths
   * @return std::string lengthUnit
   */
  std::string getLengthUnitName() const;

  /**
   * Get the unit for lengths
   * @return CModel::LengthUnit lengthUnit
   */
  CUnit::LengthUnit getLengthUnitEnum() const;

  /**
   * Set the unit for time. If COPASI recognizes
   * the unit the conversion factors are set accordingly
   * and true is returned.
   * @param const std::string & name
   * @return bool success
   */
  bool setTimeUnit(const std::string & name);

  /**
   * Set the unit for time. If COPASI recognizes
   * the unit the conversion factors are set accordingly
   * and true is returned.
   * @param const const CModel::TimeUnit & unit
   * @return bool success
   */
  bool setTimeUnit(const CUnit::TimeUnit & unitEnum);

  /**
   * Get the current time unit of the model
   * @return const CUnit & timeunit
   */
  const std::string & getTimeUnit() const;

  /**
   * Get the unit for time
   * @return std::string timeUnit
   */
  std::string getTimeUnitName() const;

  /**
   * Get the unit for time
   * @return CModel::TimeUnit timeUnit
   */
  CUnit::TimeUnit getTimeUnitEnum() const;

  /**
   * Set the unit for quantities. If COPASI recognizes
   * the unit the conversion factors are set accordingly
   * and true is returned.
   * @param const std::string & name
   * @return bool success
   */
  bool setQuantityUnit(const std::string & name,
                       const CModelParameter::Framework & frameWork);

  /**
   * Set the unit for quantities. If COPASI recognizes
   * the unit the conversion factors are set accordingly
   * and true is returned.
   * @param const CModel::QuantityUnit & unit
   * @return bool success
   */
  bool setQuantityUnit(const CUnit::QuantityUnit & unitEnum,
                       const CModelParameter::Framework & frameWork);

  /**
   * Get the current quantity unit of the model
   * @return const CUnit & quantityunit
   */
  const std::string getQuantityUnit() const;

  /**
   * Get the unit for quantities
   * @return std::string quantityUnit
   */
  std::string getQuantityUnitName() const;
  std::string getQuantityUnitOldXMLName() const;

  /**
   * Get the unit for quantities
   * @return CModel::QuantityUnit quantityUnit
   */
  CUnit::QuantityUnit getQuantityUnitEnum() const;

  /**
   * Set the type of the model
   * @param const ModelType & modelType
   */
  void setModelType(const ModelType & modelType);

  /**
   * Retrieve the type of the model.
   * @return const ModelType & modelType
   */
  const ModelType & getModelType() const;

  /**
   * Set the Avogadro number used for the model.
   * @param const C_FLOAT64 & avogadro
   */
  void setAvogadro(const C_FLOAT64 & avogadro,
                   const CModelParameter::Framework & frameWork);

  /**
   * Retrieve the Avogadro number.
   */
  const C_FLOAT64 & getAvogadro() const;

  /**
   *  Get the conversion factor quantity -> number
   */
  const C_FLOAT64 & getQuantity2NumberFactor() const;

  /**
   *  Get the conversion factor number -> quantity
   */
  const C_FLOAT64 & getNumber2QuantityFactor() const;

  //************  create/remove model entities *******************

  /**
   * Add a metabolite to the model
   * @param const std::string & name
   * @param const std::string & compartment
   * @param const C_FLOAT64 & iconc (default 1.0)
   * @param const CMetab::Status & status (default CMetab::METAB_VARIABL)
   * @return bool success (false if failed)
   * @see CMetab for more information
   */
  CMetab* createMetabolite(const std::string & name,
                           const std::string & compartment,
                           const C_FLOAT64 & iconc = 1.0,
                           const CModelEntity::Status & status = CModelEntity::REACTIONS);

  /* Remove a metabolite from the model */
  bool removeMetabolite(const std::string & key,
                        const bool & recursive = true);
  bool removeMetabolite(const size_t index,
                        const bool & recursive = true);
  bool removeMetabolite(const CMetab* pMetabolite,
                        const bool & recursive = true);

  /**
   * Appends pointers to all model objects, which are dependent on the candidates
   * to appropriate lists.
   * @param const std::set< const CCopasiObject * > & candidates
   * @param std::set< const CCopasiObject * > & dependentReactions
   * @param std::set< const CCopasiObject * > & dependentMetabolites
   * @param std::set< const CCopasiObject * > & dependentCompartments
   * @param std::set< const CCopasiObject * > & dependentModelValues
   * @param std::set< const CCopasiObject * > & dependentEvents
   * @param std::set< const CCopasiObject * > & dependentEventAssignments
   * @return bool objectsAppended
   */
  bool appendDependentModelObjects(const std::set< const CCopasiObject * > & candidates,
                                   std::set< const CCopasiObject * > & dependentReactions,
                                   std::set< const CCopasiObject * > & dependentMetabolites,
                                   std::set< const CCopasiObject * > & dependentCompartments,
                                   std::set< const CCopasiObject * > & dependentModelValues,
                                   std::set< const CCopasiObject * > & dependentEvents,
                                   std::set< const CCopasiObject * > & dependentEventAssignments) const;

  /**
   * Appends pointers to reactions which are dependent on the candidates to the
   * list.
   * @param std::set< const CCopasiObject * > candidates
   * @param std::set< const CCopasiObject * > & dependents
   * @return bool objectsAppended
   */
  bool appendDependentReactions(std::set< const CCopasiObject * > candidates,
                                std::set< const CCopasiObject * > & dependents) const;

  /**
  * Appends a pointers to events which are dependent on the candidates to the
  * list.
  * @param std::set< const CCopasiObject * > candidates
  * @param std::set< const CCopasiObject * > & dependents
  * @return bool objectsAppended
  */
  bool appendDependentEvents(std::set< const CCopasiObject * > candidates,
                             std::set< const CCopasiObject * > & dependents) const;

  /**
  * Appends a pointers to event assignments which are dependent on the candidates to the
  * list.
  * @param std::set< const CCopasiObject * > candidates
  * @param std::set< const CCopasiObject * > & dependents
  * @return bool objectsAppended
  */
  bool appendDependentEventAssignments(std::set< const CCopasiObject * > candidates,
                                       std::set< const CCopasiObject * > & dependents) const;

private:
  /**
   * Appends pointers to metabolites which are dependent on the candidates to the
   * list.
   * @param std::set< const CCopasiObject * > candidates
   * @param std::set< const CCopasiObject * > & dependents
   * @return bool objectsAppended
   */
  bool appendDependentMetabolites(std::set< const CCopasiObject * > candidates,
                                  std::set< const CCopasiObject * > & dependents) const;

  /**
   * Appends pointers to compartments which are dependent on the candidates to the
   * list.
   * @param std::set< const CCopasiObject * > candidates
   * @param std::set< const CCopasiObject * > & dependents
   * @return bool objectsAppended
   */
  bool appendDependentCompartments(std::set< const CCopasiObject * > candidates,
                                   std::set< const CCopasiObject * > & dependents) const;

  /**
   * Appends a pointers to model values which are dependent on the candidates to the
   * list.
   * @param std::set< const CCopasiObject * > candidates
   * @param std::set< const CCopasiObject * > & dependents
   * @return bool objectsAppended
   */
  bool appendDependentModelValues(std::set< const CCopasiObject * > candidates,
                                  std::set< const CCopasiObject * > & dependents) const;

public:
  /**
   * Remove all model objects which depend on the deleted objects
   * @param const std::set<const CCopasiObject*> & deletedObjects
   */
  void removeDependentModelObjects(const std::set<const CCopasiObject*> & deletedObjects);

  /**
   * Add a compartment to the model
   * @param const std::string &name
   * @param const C_FLOAT64 & volume (default 1.0)
   * @return bool success (false if failed)
   */
  CCompartment* createCompartment(const std::string & name,
                                  const C_FLOAT64 & volume = 1.0);

  /** Remove a Compartment from the model */
  bool removeCompartment(const size_t index,
                         const bool & recursive = true);

  /** Remove a Compartment from the model */
  bool removeCompartment(const std::string & key,
                         const bool & recursive = true);

  /** Remove a Compartment from the model */
  bool removeCompartment(const CCompartment * pCompartment,
                         const bool & recursive = true);

  /**
   * Add a new reaction to the model
   * @param const std::string &name
   * @return bool success (false if failed)
   */
  CReaction* createReaction(const std::string &name);

  /** Remove a reaction from the model using its pointer*/
  bool removeReaction(const CReaction * pReaction,
                      const bool & recursive = true);

  /** Remove a reaction from the model using its key*/
  bool removeReaction(const std::string & key,
                      const bool & recursive = true);

  /** Remove a reaction from the model using its index*/
  bool removeReaction(const size_t index,
                      const bool & recursive = true);

  /** Remove a local reaction parameter from the model */
  bool removeLocalReactionParameter(const std::string & key,
                                    const bool & recursive = true);

  /**
   * Add a new event to the model
   * @param const std::string &name
   * @return bool success (false if failed)
   */
  CEvent* createEvent(const std::string &name);

  /**
   * Remove an event from the model
   * @param const size_t index
   * @param const bool & recursive (default: true)
   * @return bool success
   */
  bool removeEvent(const size_t index,
                   const bool & recursive = true);

  /**
   * Remove an event from the model
   * @param const std::string & key
   * @param const bool & recursive (default: true)
   * @return bool success
   */
  bool removeEvent(const std::string & key,
                   const bool & recursive = true);

  /**
   * Remove an event from the model
   * @param const CEvent * pEvent
   * @param const bool & recursive (default: true)
   * @return bool success
   */
  bool removeEvent(const CEvent * pEvent,
                   const bool & recursive = true);

  /**
   * Add a non concentration value to the model
   * @param const std::string &name
   * @param const C_FLOAT64 & value (default 0.0)
   */
  CModelValue* createModelValue(const std::string & name,
                                const C_FLOAT64 & value = 0.0);

  bool removeModelValue(const CModelValue * pModelValue,
                        const bool & recursive = true);
  bool removeModelValue(const std::string & key,
                        const bool & recursive = true);
  bool removeModelValue(const size_t index,
                        const bool & recursive = true);

  //*************************

  /**
   * Retrieve the state template
   * @return const CModel::CStateTemplate & stateTemplate
   */
  const CStateTemplate & getStateTemplate() const;

  /**
   * Add a model entity to the model
   * @param const CModelEntity * pModelEntity
   */
  void addModelEntity(const CModelEntity * pModelEntity);

  /**
   * Remove a model entity to the model
   * @param const CModelEntity * pModelEntity
   */
  void removeModelEntity(const CModelEntity * pModelEntity);

  /**
   * Check whether the model contains reversible reactions
   * @return bool hasReversibleReaction
   */
  bool hasReversibleReaction() const;

  /**
   * check if the model is suitable for stochastic simulation
   **/
  std::string suitableForStochasticSimulation() const;

  /**
   * Check whether the model is autonomous
   * @return const bool &isAutonomous
   */
  const bool & isAutonomous() const;

  /**
   * Check whether the given object is a part of state variable
   * @param const CCopasiObject * pObject
   * @return bool isStateVariable
   */
  bool isStateVariable(const CCopasiObject * pObject) const;

  /**
   * Retrieve the corresponding transient state object of the given object
   * @param const CCopasiObject * pObject
   * @return CCopasiObject * correspondingTransientObject
   */
  CCopasiObject * getCorrespondingTransientObject(const CCopasiObject * pObject) const;

  /**
   * Build the update sequence used to calculate all initial values depending
   * on the changed objects. For metabolites the initial particle number is
   * updated by default unless itself is in the list of changed objects. In
   * that case the initial concentration is updated.
   * @param std::set< const CCopasiObject * > & changedObjects
   * @return CObjectInterface::UpdateSequence initialRefreshSequence
   */
  CObjectInterface::UpdateSequence buildInitialRefreshSequence(std::set< const CCopasiObject * > & changedObjects);

  /**
   * Builds and executes the the update sequence used to calculate all initial
   * values depending on the changed objects. For metabolites the initial particle
   * number is updated by default unless itself is in the list of changed objects. In
   * that case the initial concentration is updated.
   *
   * @param std::set< const CCopasiObject * > & changedObjects

   * @see buildInitialRefreshSequence(std::set< const CCopasiObject * > & changedObjects)
   */
  void updateInitialValues(std::set< const CCopasiObject * > & changedObjects);

  /**
   * Builds and executes the the update sequence used to calculate all initial
   * values depending on the changed objects For metabolites the initial particle
   * number is updated by default unless itself is in the list of changed objects. In
   * that case the initial concentration is updated.
   *
   * @param std::set< const CCopasiObject * > & changedObjects

   * @see updateInitialValues(std::set< const CCopasiObject * > & changedObjects)
   */
  void updateInitialValues(const CCopasiObject * changedObject);

  /**
   * Initialize a vector of individual absolute tolerances
   * @param const C_FLOAT64 & baseTolerance
   * @param const bool & reducedModel
   * @return CVector< C_FLOAT64 > absoluteTolerances
   */
  CVector< C_FLOAT64 > initializeAtolVector(const C_FLOAT64 & baseTolerance, const bool & reducedModel) const;

  /**
   * generates a string that contains a text description of all model parameters
   * (initial values and reaction parameters)
   */
  // this member is no longer implemented, commenting it out
  //std::string printParameterOverview();

  /**
   * List all trees which introduce discrete changes.
   * @return std::vector< const CEvaluationTree * > treesWithDiscontinuities
   */
  std::vector< const CEvaluationTree * > getTreesWithDiscontinuities() const;

private:

  bool compile();

  /**
   * Handles unused metabolites and moves them to the end of mMetabolites.
   * Rows of the stoichiometry matrix dealing with unused metabolites are removed.
   * @return bool found
   */
  bool handleUnusedMetabolites();

  /**
   * Initialize the contained CCopasiObjects
   */
  void initObjects();

  /**
   * Clear all references to moieties
   */
  void clearMoieties();

  /**
   * Build the state template for the model.
   * @return bool success
   */
  bool buildStateTemplate();

  /**
   * Build the user order for the state template
   * @return bool success
   */
  bool buildUserOrder();

  /**
   * This updates the annotations of the link matrix and the stoichiometry matrix
   */
  void updateMatrixAnnotations();

  /**
   * Compile the events
   * @return bool success
   */
  bool compileEvents();

  // Attributes
private:
  /**
   * The state template for the model
   */
  CStateTemplate mStateTemplate;

  CMathDependencyGraph mPhysicalDependencies;

  /**
   * The volume unit used in the Model
   */
  std::string mVolumeUnit;

  /**
   * The volume unit used in the Model
   */
  std::string mAreaUnit;

  /**
   * The volume unit used in the Model
   */
  std::string mLengthUnit;

  /**
   * The time unit used in the Model
   */
  std::string mTimeUnit;

  /**
   * The quantity unit used in the Model
   */
  std::string mQuantityUnit;

  /**
   * The type of the model
   */
  ModelType mType;

  /**
   *  for array of compartments
   */
  CCopasiVectorNS < CCompartment > mCompartments;

  /**
   *  Vector of reference to metabolites
   */
  CCopasiVector< CMetab > mMetabolites;

  /**
   *  Vector of reference to metabolites in reduced model representation
   */
  CCopasiVector< CMetab > mMetabolitesX;

  /**
   *  for array of steps
   */
  CCopasiVectorNS< CReaction > mSteps;

  /**
   *  for array of events
   */
  CCopasiVectorN< CEvent > mEvents;

  /**
   *  Vectors of fluxes of the reactions.
   */
  CVector< C_FLOAT64 > mParticleFluxes;

  /**
   *  vector of non concentration values in the model
   */
  CCopasiVectorN< CModelValue > mValues;

  /**
   * The parameter set of the model itself
   */
  CModelParameterSet mParameterSet;

  /**
   * Vector of parameter sets
   */
  CCopasiVectorN< CModelParameterSet > mParameterSets;

  /**
   * The key of the currently active parameter set.
   */
  std::string mActiveParameterSetKey;

  /**
   *  for array of conserved moieties
   */
  CCopasiVector< CMoiety > mMoieties;

  /**
   * Column and Row Annotation for the reduced Stoichiometry Matrix
   */
  CArrayAnnotation * mpStoiAnnotation;

  /**
   *   Stoichiometry Matrix
   */
  CMatrix< C_FLOAT64 > mStoi;

  /**
   *   Reduced Stoichiometry Matrix
   */
  CMatrix< C_FLOAT64 > mRedStoi;

  /**
   * Column and Row Annotation for the reduced Stoichiometry Matrix
   */
  CArrayAnnotation * mpRedStoiAnnotation;

  /**
   * The elasticity matrix d(Flux_i)/dx_j
   */
  CMatrix< C_FLOAT64 > mElasticities;

  /**
   * Vector for storing the row interchanges during LU-Decomposition
   */
  // CVector< size_t > mRowLU;

  /**
   * Vector for storing the row and column interchanges needed to calculate
   * the full Jacobian in user order.
   */
  CVector< size_t > mJacobianPivot;

  /**
   * The number of unused metabs in the model
   */
  size_t mNumMetabolitesUnused;

  /**
   * The number of metabs determined by ODEs in the model
   */
  size_t mNumMetabolitesODE;

  /**
   * The number of metabs determined by reactions in the model
   */
  size_t mNumMetabolitesReaction;

  /**
   * The number of metabs determined by assignments in the model
   */
  size_t mNumMetabolitesAssignment;

  /**
   * The number of metabs determined by reactions which can be calculated
   * through moieties
   */
  size_t mNumMetabolitesReactionIndependent;

  /**
   *   This matrix stores L
   */
  CLinkMatrix mL;

  /**
   * Column and Row Annotation for the Link Matrix
   */
  CArrayAnnotation * mpLinkMatrixAnnotation;

  /**
   *   This is used to return a view to L
   */
  CLinkMatrixView mLView;

  /**
   *  The Avogadro number used for this model.
   */
  C_FLOAT64 mAvogadro;
  CCopasiObject * mpAvogadroReference;

  /**
   *  Factor to convert from quantity to particle number
   *  taking into account the unit for substance quantities
   */
  C_FLOAT64 mQuantity2NumberFactor;
  CCopasiObject * mpQuantity2NumberFactorReference;

  /**
   *  Factor to convert from  particle number to quantity
   *  taking into account the unit for substance quantities
   */
  C_FLOAT64 mNumber2QuantityFactor;

  /**
   * indicates whether a recalculation of the stoichiometry matrix decomposition is
   * necessary
   */
  bool mCompileIsNecessary;

  /**
   * A pointer to the process report. If not NULL the compile progress is
   * reported to it.
   */
  CProcessReport * mpCompileHandler;

  /**
   * A flag indicating whether the state template has to be reordered
   */
  bool mReorderNeeded;

  /**
   * A flag indicating whether the model is autonomous.
   */
  bool mIsAutonomous;

  /**
   * A Boolean value indicating whether we need to rebuild the initial
   * value refresh sequence
   */
  bool mBuildInitialSequence;

  /****** Below will be removed when the math model completed ******/

  /**
   * The container of the mathematical model.
   */
  CMathContainer * mpMathContainer;

  // Operations
public:
  /**
   * Retrieve the container of all mathematical objects
   * @return const CMathContainer & mathContainer
   */
  const CMathContainer & getMathContainer() const;

  /**
   * Retrieve the container of all mathematical objects
   * @return CMathContainer & mathContainer
   */
  CMathContainer & getMathContainer();

  //bool prepareSymbolicJacobian();

  CEvaluationNode* prepareElasticity(const CReaction * pReaction, const CModelEntity* pVar, bool simplify);

  CCopasiObject::DataObjectSet getUnitSymbolUsage(std::string symbol) const;

  void changeUnitExpressionSymbols(std::string oldSymbol, std::string newSymbol);

  std::map< std::string, CUnit > getUsedUnits() const;
};

#endif // CModel
