// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi/model/CProcessQueue.h"
#include "copasi/model/CModelParameterSet.h"

#include "copasi/utilities/CVector.h"
#include "copasi/utilities/CMatrix.h"
#include "copasi/utilities/CLinkMatrix.h"
#include "copasi/report/CCopasiContainer.h"
#include "copasi/utilities/CUnit.h"

#include "copasi/math/CMathTrigger.h"
#include "copasi/math/CMathDependencyGraph.h"

#ifdef USE_MATH_CONTAINER
class CMathContainer;
#endif // USE_MATH_CONTAINER

//class CCompartment;
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

private:
  /**
   *  Copy constructor
   *  @param "const CModel &" src
   */
  CModel(const CModel & src);

  CModel& operator=(const CModel& src);

public:
  /**
   *  constructor
   */
  CModel(CCopasiContainer* pParent);

  /**
   * Destructor
   */
  ~CModel();        // destructor (deallocation code here)

  /**
   * Retrieve the units of the child object.
   * @return std::string units
   */
  virtual std::string getChildObjectUnits(const CCopasiObject * pObject) const;

  /**
   * Converts the set of reactions to a set of reactions where all reactions are irreversible.
  */
  bool convert2NonReversible();

#if WITH_PE_EVENT_CREATION
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
   *  Build the core of the link matrix L
   *  @param const CMatrix< C_FLOAT64 > & LU
   */
  //void buildL(const CMatrix< C_FLOAT64 > & LU);

#ifdef XXXX
  /**
   *  LU-Decomposition of the stoichiometry matrix
   *  @param CMatrix< C_FLOAT64 > & LU
   */
  void lUDecomposition(CMatrix< C_FLOAT64 > & LU);
#endif // XXXX

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
   *  Get the number of metabolites determined by assigments
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
  const CModelParameterSet & getModelParameterSet() const;
  CModelParameterSet & getModelParameterSet();

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
   * Return the mMoieties of this model
   * @return CCopasiVectorN < CMoiety > &
   */
  const CCopasiVector < CMoiety > & getMoieties() const;

  /**
   * Returns the index of the metab
   * @param const std::string & Target
   * @return index
   */
  size_t findMetabByName(const std::string & Target) const;

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
   * @return const CMatrix< C_FLOAT64 > & L0
   */
  const CMatrix< C_FLOAT64 > & getL0() const;

  /**
   * initialize all values of the model with their initial values
   */
  void applyInitialValues();

  /**
   * Update all initial values.
   * @return bool success
   */
  bool updateInitialValues();

  /**
   * Get the current state of the model, i.e., all current model
   * quantities.
   * @return const CState & initialState
   */
  const CState & getInitialState() const;

  /**
   * Get the current state of the model, i.e., all current model
   * quantities.
   * @return const CState & currentState
   */
  const CState & getState() const;

  /**
   * Set all initial model quantities to the one given by the state and
   * updates moieties and metabolite concentrations.
   * @param const CState & state
   */
  void setInitialState(const CState & state);

  /**
   * Set all independent current model quantities to the one given by the
   * state.
   * @param const CState & state
   */
  void setState(const CState & state);

  /**
   * Construct an intitial update sequence for the given context
   * @param const CMath::SimulationContextFlag & context
   * @param const CCopasiObject::DataObjectSet & changedObjects
   * @param const CCopasiObject::DataObjectSet & requestedObjects
   * @param CCopasiObject::DataUpdateSequence & updateSequence)
   * @return bool success
   */
  bool getInitialUpdateSequence(const CMath::SimulationContextFlag & context,
                                const CCopasiObject::DataObjectSet & changedObjects,
                                const CCopasiObject::DataObjectSet & requestedObjects,
                                CCopasiObject::DataUpdateSequence & updateSequence) const;

  /**
   * Construct a transient update sequence for the given context
   * @param const CMath::SimulationContextFlag & context
   * @param const CCopasiObject::DataObjectSet & changedObjects
   * @param const CCopasiObject::DataObjectSet & requestedObjects
   * @param CCopasiObject::DataUpdateSequence & updateSequence)
   * @return bool success
   */
  bool getTransientUpdateSequence(const CMath::SimulationContextFlag & context,
                                  const CCopasiObject::DataObjectSet & changedObjects,
                                  const CCopasiObject::DataObjectSet & requestedObjects,
                                  CCopasiObject::DataUpdateSequence & updateSequence) const;

  /**
   * This method calculates all values needed for simulation based on the current
   * current state. If updateMoities is true the particle numbers of dependent metabolites
   * of type REACTION are calculated otherwise they are assumed to be synchronized.
   * @param const bool & updateMoieties
   */
  void updateSimulatedValues(const bool & updateMoieties);

  /**
   * Calling this method after updateSimulatedValues assure that all model values
   * even those not needed for simulation are consistent with the current state
   */
  void updateNonSimulatedValues(void);

  /**
   * Calculate the changes of all model quantities determined by ODEs
   * for the model in the current state.
   * The parameter derivatives must at least provide space for
   * state->getVariableNumberSize() double
   * &param C_FLOAT64 * derivatives (output)
   */
  void calculateDerivatives(C_FLOAT64 * derivatives);

  /**
   * Calculate the changes of all model quantities determined by ODEs
   * for the reduced model in the current state.
   * The parameter derivatives must at least provide space for
   * state->getDependentNumberSize() double
   * &param C_FLOAT64 * derivatives (output)
   */
  void calculateDerivativesX(C_FLOAT64 * derivativesX);

  /**
   * Calculates the elasticity matrix of the model for the current
   * state and stores it in the provided matrix.
   * @param CMatrix< C_FLOAT64 > & elasticityMatrix
   * @param const C_FLOAT64 & factor,
   * @param const C_FLOAT64 & resolution
   */
  void calculateElasticityMatrix(const C_FLOAT64 & factor,
                                 const C_FLOAT64 & resolution);

  /**
   * Calculates the jacobian of the full model for the current state
   * and stores it in the provided matrix. calculateElasticityMatrix()
   * needs to be called before.
   * @param CMatrix< C_FLOAT64 > & jacobian
   * @param const C_FLOAT64 & derivationFactor,
   * @param const C_FLOAT64 & resolution
   */
  void calculateJacobian(CMatrix< C_FLOAT64 > & jacobian,
                         const C_FLOAT64 & derivationFactor,
                         const C_FLOAT64 & resolution);

  /**
   * Calculates the Jacobian of the reduced model for the current
   * state and stores it in the provided matrix. calculateElasticityMatrix()
   * needs to be called before.
   * @param const C_FLOAT64 & derivationFactor,
   * @param const C_FLOAT64 & resolution
   * @param CMatrix< C_FLOAT64 > & jacobianX
   */
  void calculateJacobianX(CMatrix< C_FLOAT64 > & jacobianX,
                          const C_FLOAT64 & derivationFactor,
                          const C_FLOAT64 & resolution);

  /**
   * Calculates the divergence for the current state.
   * calculateElasticityMatrix() needs to be called before.
   * It makes only sense to use this method if the Jacobian
   * is not also calculated. In this case it would be more
   * efficient to use the trace of the Jacobian
   */
  C_FLOAT64 calculateDivergence() const;

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
  const CUnit * getVolumeUnit() const;

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
  const CUnit * getAreaUnit() const;

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
  const CUnit * getLengthUnit() const;

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
  const CUnit * getTimeUnit() const;

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
  bool setQuantityUnit(const std::string & name);

  /**
   * Set the unit for quantities. If COPASI recognizes
   * the unit the conversion factors are set accordingly
   * and true is returned.
   * @param const CModel::QuantityUnit & unit
   * @return bool success
   */
  bool setQuantityUnit(const CUnit::QuantityUnit & unitEnum);

  /**
   * Get the current quantity unit of the model
   * @return const CUnit & quantityunit
   */
  const CUnit * getQuantityUnit() const;

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
  void setAvogadro(const C_FLOAT64 & avogadro);

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
   * @return bool objectsAppended
   */
  bool appendDependentModelObjects(const std::set< const CCopasiObject * > & candidates,
                                   std::set< const CCopasiObject * > & dependentReactions,
                                   std::set< const CCopasiObject * > & dependentMetabolites,
                                   std::set< const CCopasiObject * > & dependentCompartments,
                                   std::set< const CCopasiObject * > & dependentModelValues,
                                   std::set< const CCopasiObject * > & dependentEvents) const;

  /**
   * Appends pointers to reactions which are dependent on the candidates to the
   * list.
   * @param std::set< const CCopasiObject * > candidates
   * @param std::set< const CCopasiObject * > & dependents
   * @return bool objectsAppended
   */
  bool appendDependentReactions(std::set< const CCopasiObject * > candidates,
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
   * Construct a update sequence for the given context
   * @param CMathDependencyGraph & dependencyGraph
   * @param const CMath::SimulationContextFlag & context
   * @param const CCopasiObject::DataObjectSet & changedObjects
   * @param const CCopasiObject::DataObjectSet & requestedObjects
   * @param CCopasiObject::DataUpdateSequence & updateSequence)
   * @return bool success
   */
  bool getUpdateSequence(CMathDependencyGraph & dependencyGraph,
                         const CMath::SimulationContextFlag & context,
                         const CCopasiObject::DataObjectSet & changedObjects,
                         const CCopasiObject::DataObjectSet & requestedObjects,
                         CCopasiObject::DataUpdateSequence & updateSequence) const;

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
   * Retrieve the state template
   * @return const CModel::CStateTemplate & stateTemplate
   */
  CStateTemplate & getStateTemplate();

  /**
   * Retrieve the list of objects which are up to date after a call
   * to apply assignment.
   * @return const std::set< const CCopasiObject * > & uptoDateObjects
   */
  const std::set< const CCopasiObject * > & getUptoDateObjects() const;

  /**
   * Retrieve the sequence of refresh calls to be executed for updating the
   * initial values
   * @return const std::vector< Refresh * > & initialRefreshSequence
   */
  const std::vector< Refresh * > & getListOfInitialRefreshes() const;

  /**
   * Retrieve the sequence of refresh calls to be executed for updating the
   * simulated values
   * @return const std::vector< Refresh * > & simulatedRefreshSequence
   */
  const std::vector< Refresh * > & getListOfSimulatedRefreshes() const;

  /**
   * Retrieve the sequence of refresh calls to be executed for updating the
   * constant values
   * @return const std::vector< Refresh * > & constantRefreshSequence
   */
  const std::vector< Refresh * > & getListOfConstantRefreshes() const;

  /**
   * Retrieve the sequence of refresh calls to be executed for updating the
   * non simulated values
   * @return const std::vector< Refresh * > & nonsimulatedRefreshSequence
   */
  const std::vector< Refresh * > & getListOfNonSimulatedRefreshes() const;

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
   * @return std::vector< Refresh * > initialRefreshSequence
   */
  std::vector< Refresh * > buildInitialRefreshSequence(std::set< const CCopasiObject * > & changedObjects);

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
  std::string printParameterOverview();

  /**
   * Retrieve the time units
   * @return std::string timeUnits
   */
  std::string getTimeUnitsDisplayString() const;

  /**
   * Retrieve the frequency units
   * @return std::string frequencyUnits
   */
  std::string getFrequencyUnitsDisplayString() const;

  /**
   * Retrieve the volume units
   * @return std::string volumeUnits
   */
  std::string getVolumeUnitsDisplayString() const;

  /**
   * Retrieve the area units
   * @return std::string volumeUnits
   */
  std::string getAreaUnitsDisplayString() const;

  /**
   * Retrieve the length units
   * @return std::string volumeUnits
   */
  std::string getLengthUnitsDisplayString() const;

  /**
   * Retrieve the volume rate units
   * @return std::string volumeRateUnits
   */
  std::string getVolumeRateUnitsDisplayString() const;

  /**
   * Retrieve the concentration units
   * @return std::string concentrationUnits
   */
  std::string getConcentrationUnitsDisplayString() const;

  /**
   * Retrieve the concentration rate units
   * @return std::string concentrationRateUnits
   */
  std::string getConcentrationRateUnitsDisplayString() const;

  /**
   * Retrieve the quantity units
   * @return std::string quantityUnits
   */
  std::string getQuantityUnitsDisplayString() const;

  /**
   * Retrieve the quantity rate units
   * @return std::string quantityRateUnits
   */
  std::string getQuantityRateUnitsDisplayString() const;

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
   * Build the update sequence used by updateInitialValues to update all
   * initial values.
   * @return bool success
   */
  bool buildInitialSequence();

  /**
   * Build the update sequence used by applyInitialValues to update values.
   * @return bool success
   */
  bool buildApplyInitialValuesSequence();

  /**
   * Build the update sequence used by updateSimulatedValues.
   * @return bool success
   */
  bool buildSimulatedSequence();

  /**
   * Build the update sequence used by updateNonSimulatedValues.
   * @return bool success
   */
  bool buildNonSimulatedSequence();

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
   * Determine whether the model is autonomous
   */
  void determineIsAutonomous();

  /**
   * Compile the events
   * @return bool success
   */
  bool compileEvents();

#ifdef COPASI_DEBUG
public:
  void check() const;
#endif

  // Attributes
private:
  CState mInitialState;

  CState mCurrentState;

  /**
   * The state template for the model
   */
  CStateTemplate mStateTemplate;

  /**
   * This is the list of objects which contains all objects which
   * are up to date after a call to updateSimulatedValues
   */
  std::set< const CCopasiObject * > mSimulatedUpToDateObjects;

  mutable CMathDependencyGraph mInitialDependencies;
  mutable CMathDependencyGraph mTransientDependencies;
  CMathDependencyGraph mPhysicalDependencies;

  /**
   * The volume unit used in the Model
   */
  CUnit * mpVolumeUnit;

  /**
   * The volume unit used in the Model
   */
  CUnit * mpAreaUnit;

  /**
   * The volume unit used in the Model
   */
  CUnit * mpLengthUnit;

  /**
   * The time unit used in the Model
   */
  CUnit * mpTimeUnit;

  /**
   * The quantity unit used in the Model
   */
  CUnit * mpQuantityUnit;

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
   * Vector of defined unit
   */
  CCopasiVectorN< CUnit > mListOfUnits;

  /**
   * The key of the currently active parameter set.
   */
  std::string mActiveParameterSetKey;

  /**
   *  for array of conserved moieties
   */
  CCopasiVector< CMoiety > mMoieties;

  /**
   *   Stoichiometry Matrix
   */
  CMatrix< C_FLOAT64 > mStoiInternal;

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

  /**
   *  Factor to convert from quantity to particle number
   *  taking into account the unit for substance quantities
   */
  C_FLOAT64 mQuantity2NumberFactor;

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
   * An ordered list of refresh methods needed by the updateInitialValues
   */
  std::vector< Refresh * > mInitialRefreshes;

  /**
   * An ordered list of refresh methods needed by the updateSimulatedValues
   */
  std::vector< Refresh * > mSimulatedRefreshes;

  /**
   * An ordered list of refresh methods needed by the applyInitialValues
   * to update values which stay constant during simulation.
   */
  std::vector< Refresh * > mApplyInitialValuesRefreshes;

  /**
   * An ordered list of refresh methods needed to update all model values
   * which are not calculated during simulation
   */
  std::vector< Refresh * > mNonSimulatedRefreshes;

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
   * The mathematical model. This is currently part of the model. It is
   * envisioned that this will be the class all tasks will operate on, since it
   * eventually will have the all the mathematical relevant information.
   */
  CMathModel * mpMathModel;

#ifdef USE_MATH_CONTAINER
  CMathContainer * mpMathContainer;
#endif // USE_MATH_CONTAINER

  // Operations
public:
  /**
   * Evaluate all root values for the current state of the model. If
   * ignoreDiscrete is true discrete roots evaluate to 1.0.
   * @param CVectorCore< C_FLOAT64 > & rootValues
   * @param const bool & ignoreDiscrete
   */
  void evaluateRoots(CVectorCore< C_FLOAT64 > & rootValues,
                     const bool & ignoreDiscrete);

  /**
   * Process events scheduled at the given which a are checked for
   * equality or not
   * @param const C_FLOAT64 & time
   * @param const bool & equality
   * @param CProcessQueue::resolveSimultaneousAssignments pResolveSimultaneousAssignments
   * @return bool stateChanged
   */
  bool processQueue(const C_FLOAT64 & time,
                    const bool & equality,
                    CProcessQueue::resolveSimultaneousAssignments pResolveSimultaneousAssignments
                   );

  /**
   * Check whether the roots which have value 1 lead to firing of
   * events and schedule them if needed.
   * @param const C_FLOAT64 & time
   * @param const bool & equality
   * @param const bool & correct
   * @param const CVector< C_INT > & roots
   */
  void processRoots(const C_FLOAT64 & time,
                    const bool & equality,
                    const bool & correct,
                    const CVector< C_INT > & roots);

  /**
   * Retrieve the next execution time scheduled in the process queue
   * @return const C_FLOAT64 & processQueueExecutionTime
   */
  const C_FLOAT64 & getProcessQueueExecutionTime() const;

  /**
   * Retrieve the number of roots used in checking for discontinuities.
   * @return size_t numRoots
   */
  size_t getNumRoots() const;

  /**
   * Calculate the time derivative of all roots
   * @param CVector< C_FLOAT64 > & rootDerivatives
   */
  void calculateRootDerivatives(CVector< C_FLOAT64 > & rootDerivatives);

  /**
   * Retrieve a vector of root finders
   * @return const CVector< CMathTrigger::CRootFinder * > & rootFinders
   */
  const CVector< CMathTrigger::CRootFinder * > & getRootFinders() const;

  const CMathModel* getMathModel() const;
  CMathModel* getMathModel();

#ifdef USE_MATH_CONTAINER
  /**
   * Retrieve the container of all mathematical objects
   * @return const CMathContainer * pMathContainer
   */
  const CMathContainer* getMathContainer() const;

  /**
   * Retrieve the container of all mathematical objects
   * @return CMathContainer * pMathContainer
   */
  CMathContainer * getMathContainer();
#endif // USE_MATH_CONTAINER
};

#endif // CModel
