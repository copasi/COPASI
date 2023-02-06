// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CObject
#define COPASI_CObject

#include <set>
#include <map>

#include "copasi/core/CDataObject.h"
#include "copasi/core/CVector.h"
#include "copasi/math/CMathEnum.h"
#include "copasi/utilities/CValidity.h"

class CMathExpression;
class CMathContainer;
class CJitCompiler;
class CExpression;
class CDataObject;
class CMetab;
class CEvaluationNode;

class CMathObject: public CObjectInterface
{
  friend std::ostream &operator<<(std::ostream &os, const CMathObject & o);

public:
  typedef void (CMathObject::*calculate)();

  /**
   * Default Constructor
   */
  CMathObject();

  /**
   * Copy constructor
   */
  CMathObject(const CMathObject & src);

  /**
   * Destructor
   */
  virtual ~CMathObject();

  /**
   * Copy an existing object
   * @param const CMathObject & src
   * @param CMathContainer & container
   */
  void copy(const CMathObject & src, CMathContainer & container);

  /**
   * Relocate an existing object
   * @param const CMathContainer * pContainer
   * @param const std::vector< CMath::sRelaocte > & relocations
   */
  void relocate(CMathContainer * pContainer,
                const std::vector< CMath::sRelocate > & relocations);

  /**
   * Retrieve the CN of the object
   * @return CCommonName
   */
  virtual CCommonName getCN() const override;

  /**
   * Retrieve the display name of the object
   * @param bool regular (default: true)
   * @param bool richtext (default: false)
   * @return std::string objectDisplayName
   */
  virtual std::string getObjectDisplayName() const override;

  /**
   * Retrieve a descendant object by its CN.
   * @param const CCommonName & cn
   * @return const CObjectInterface * pObject
   */
  virtual const CObjectInterface * getObject(const CCommonName & cn) const override;

  /**
   * Retrieve the prerequisites, i.e., the objects which need to be evaluated
   * before this.
   * @return const CObjectInterface::ObjectSet & prerequisites
   */
  virtual const CObjectInterface::ObjectSet & getPrerequisites() const override;

  /**
   * Check whether a given object is a prerequisite for a context.
   * @param const CObjectInterface * pObject
   * @param const CCore::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @return bool isPrerequisiteForContext
   */
  virtual bool isPrerequisiteForContext(const CObjectInterface * pObject,
                                        const CCore::SimulationContextFlag & context,
                                        const CObjectInterface::ObjectSet & changedObjects) const override;

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const override;

  /**
   * Retrieve a pointer to the value of the object
   */
  virtual void * getValuePointer() const override;

  /**
   * Set the pointer to the data object
   * @param const CDataObject * pDataObject
   */
  void setDataObject(const CDataObject * pDataObject);

  /**
   * Retrieve a pointer to the data object
   * @return const CDataObject * dataObject
   */
  virtual const CDataObject * getDataObject() const override;

  /**
   * Get the aggregation of any issues associated with this object
   * @return const CValidity & validity
   */
  virtual const CValidity & getValidity() const override;

  /**
   * This method is called whenever the validity object changes.
   * @param const CValidity & changedValidity
   */
  void validityChanged(const CValidity & changedValidity) override;

  /**
   * Calculate the objects value
   */
  virtual void calculateValue() override;

  /**
   * Retrieve the value of the object;
   */
  const C_FLOAT64 & getValue() const;

  /**
   * Check whether the object can calculate its value
   */
  bool canCalculateValue() const;

  /**
   * Initialize a single mathematical object and advance relevant pointers
   * @param CMathObject * pObject
   * @param C_FLOAT64 * pValue
   * @param const CMath::Value & valueType
   * @param const CMath::EntityType & entityType
   * @param const CMath::SimulationType & simulationType
   * @param const bool & isIntensiveProperty
   * @param const bool & isInitialValue
   * @param const CDataObject * pDataObject
   */
  static void initialize(CMathObject * pObject,
                         C_FLOAT64 * pValue,
                         const CMath::ValueType & valueType,
                         const CMath::EntityType & entityType,
                         const CMath::SimulationType & simulationType,
                         const bool & isIntensiveProperty,
                         const bool & isInitialValue,
                         const CDataObject * pDataObject);

#ifdef USE_JIT
  /**
   * Compile
   * @param CMathContainer & container
   * @param CJitCompiler & jitCompiler
   * @return bool §success
   */
  bool compile(CMathContainer & container, CJitCompiler & jitCompiler);

  /**
   * Set the JIT compiler for expression
   * @param CJitCompiler & jitCompiler
   */
  void setJITCompiler(CJitCompiler & jitCompiler);
#else
  /**
   * Compile
   * @param CMathContainer & container
   * @return bool §success
   */
  bool compile(CMathContainer & container);
#endif

  /**
   * Retrieve the value type
   * @return const CMath::ValueType & valueType
   */
  const CMath::ValueType & getValueType() const;

  /**
   * Set the value type
   * @param const CMath::ValueType & valueType
   */
  void setValueType(const CMath::ValueType & valueType);

  /**
   * Retrieve the entity type
   * @return const CMath::EntityType & entityType
   */
  const CMath::EntityType & getEntityType() const;

  /**
   * Retrieve the simulation type
   * @return const CMath::SimulationType & simulationType
   */
  const CMath::SimulationType & getSimulationType() const;

  /**
   * Set the simulation type
   * @param const CMath::SimulationType & simulationType
   */
  void setSimulationType(const CMath::SimulationType & simulationType);

  /**
   * Check whether the object is an intensive property
   * @return const bool & isIntensiveProperty
   */
  const bool & isIntensiveProperty() const;

  /**
   * Check whether the object is an initial value
   * @return const bool & isInitialValue
   */
  const bool & isInitialValue() const;

  /**
   * Retrieve the corresponding extensive or intensive property
   * @return const CMathObject * correspondingProperty
   */
  const CMathObject * getCorrespondingProperty() const;

  /**
   * Retrieve the compartment value
   * @return const CMathObject * compartment
   */
  const C_FLOAT64 * getCompartmentValue() const;

  /**
   * Set the expression's infix  and compile the object.
   * @param const std::string & infix,
   * @param const bool & isBoolean,
   * @param CMathContainer & container
   * @return bool success
   */
  bool setExpression(const std::string & infix,
                     const bool & isBoolean,
                     CMathContainer & container);

  /**
   * Set the expression and compile the object.
   * @param const CExpression & expression,
   * @param CMathContainer & container
   * @return bool success
   */
  bool setExpression(const CExpression & expression,
                     CMathContainer & container);

  /**
   * Set the expression and compile the object.
   * @param CMathExpression * pMathExpression,
   * @return bool success
   */
  bool setExpressionPtr(CMathExpression * pMathExpression);

  /**
   * Retrieve a pointer to the math expression.
   * @return const CMathExpression * pExpression
   */
  const CMathExpression * getExpressionPtr() const;

  /**
   * Retrieve the number of delays involved in calculating the expression
   * @param CMath::DelayData & Delays
   */
  void appendDelays(CMath::DelayData & Delays) const;

private:
  void calculateExpression();
  void calculateExtensiveValue();
  void calculateIntensiveValue();
  void calculateParticleFlux();
  void calculateExtensiveReactionRate();
  void calculatePropensity();
  void calculateCorrectedPropensity();
  void calculateTransitionTime();

  /**
   * Compile initial value objects
   * @param CMathContainer & container
   * @return bool success
   */
  bool compileInitialValue(CMathContainer & container);

  /**
   * Compile value objects
   * @param CMathContainer & container
   * @return bool success
   */
  bool compileValue(CMathContainer & container);

  /**
   * Compile value rate objects
   * @param CMathContainer & container
   * @return bool success
   */
  bool compileRate(CMathContainer & container);

  /**
   * Compile the reactions particle flux
   * @param CMathContainer & container
   * @return bool success
   */
  bool compileParticleFlux(CMathContainer & container);

  /**
   * Compile the reactions flux
   * @param CMathContainer & container
   * @return bool success
   */
  bool compileFlux(CMathContainer & container);

  /**
   * Compile value noise objects
   * @param CMathContainer & container
   * @return bool success
   */
  bool compileNoise(CMathContainer & container);

  /**
   * Compile the reactions particle noise
   * @param CMathContainer & container
   * @return bool success
   */
  bool compileReactionParticleNoise(CMathContainer & container);

  /**
   * Compile the reactions noise
   * @param CMathContainer & container
   * @return bool success
   */
  bool compileReactionNoise(CMathContainer & container);

  /**
  * Compile the reactions propensity
  * @param CMathContainer & container
  * @return bool success
  */
  bool compilePropensity(CMathContainer & container);

  /**
   * Compile the total mass of a moiety.
   * @param CMathContainer & container
   * @return bool success
   */
  bool compileTotalMass(CMathContainer & container);

  /**
   * Compile the dependent mass of a moiety.
   * @param CMathContainer & container
   * @return bool success
   */
  bool compileDependentMass(CMathContainer & container);

  /**
   * Compile the transition time of a species.
   * @param CMathContainer & container
   * @return bool success
   */
  bool compileTransitionTime(CMathContainer & container);

  /**
   * Common compile steps after an expression has been created.
   */
  void compileExpression();

  /**
   * Create and compile an expression based on the given expression.
   * @param const CExpression * pExpression
   * @param CMathContainer & container
   * @return bool success
   */
  bool createConvertedExpression(const CExpression * pExpression,
                                 CMathContainer & container);

  /**
   * Create and compile an expression for an intensive value of a species.
   * @param const CMetab * pSpecies
   * @param CMathContainer & container
   * @return bool success
   */
  bool createIntensiveValueExpression(const CMetab * pSpecies,
                                      CMathContainer & container);

  /**
   * Create and compile an expression for an extensive value of a species.
   * @param const CMetab * pSpecies
   * @param CMathContainer & container
   * @return bool success
   */
  bool createExtensiveValueExpression(const CMetab * pSpecies,
                                      CMathContainer & container);

  /**
   * Create and compile an expression for an intensive rate of a species.
   * @param const CMetab * pSpecies
   * @param CMathContainer & container
   * @return bool success
   */
  bool createIntensiveRateExpression(const CMetab * pSpecies,
                                     CMathContainer & container);

  /**
   * Create and compile an expression for an extensive rate of a species determined
   * by an ODE.
   * @param const CMetab * pSpecies
   * @param CMathContainer & container
   * @return bool success
   */
  bool createExtensiveODERateExpression(const CMetab * pSpecies,
                                        CMathContainer & container);

  /**
   * Create and compile an expression for an extensive rate of a species determined
   * by reactions
   * @param const CMetab * pSpecies
   * @param CMathContainer & container
   * @return bool success
   */
  bool createExtensiveReactionRateExpression(const CMetab * pSpecies,
      CMathContainer & container);

  /**
   * Create and compile an expression for the intensive noise of a species
   * @param const CMetab * pSpecies
   * @param CMathContainer & container
   * @return bool success
   */
  bool createIntensiveNoiseExpression(const CMetab * pSpecies,
                                      CMathContainer & container);

  /**
   * Create and compile an expression for an extensive noise of a species determined
   * by ODEs
   * @param const CMetab * pSpecies
   * @param CMathContainer & container
   * @return bool success
   */
  bool createExtensiveNoiseExpression(const CMetab * pSpecies,
                                      CMathContainer & container);

  /**
   * Create and compile an expression for an extensive noise of a species determined
   * by reactions
   * @param const CMetab * pSpecies
   * @param CMathContainer & container
   * @return bool success
   */
  bool createExtensiveReactionNoiseExpression(const CMetab * pSpecies,
      CMathContainer & container);

  static C_FLOAT64 InvalidValue;

  /**
   * The expression which determines the value of the object.
   */
  CMathExpression * mpExpression;

  /**
   * A pointer to value of the object
   */
  C_FLOAT64 *mpValue;

  /**
   * The prerequisites, i.e., the objects which need to be evaluated before this.
   */
  CObjectInterface::ObjectSet mPrerequisites;

  /**
   * The type of the object
   */
  CMath::ValueType mValueType;

  /**
   * The entity type the object belongs
   */
  CMath::EntityType mEntityType;

  /**
   * The simulation type
   */
  CMath::SimulationType mSimulationType;

  /**
   * A flag indicating whether this is an intensive or extensive property.
   */
  bool mIsIntensiveProperty;

  /**
   * A flag indicating whether this is an initial value, i.e, which dependency graph
   * is used to update the object.
   */
  bool mIsInitialValue;

  /**
   * A pointer to the corresponding intensive or extensive property value if it exists otherwise NULL
   */
  const CMathObject * mpCorrespondingProperty;

  /**
   * A pointer to the corresponding intensive or extensive property value if it exists otherwise NULL
   */
  const C_FLOAT64 * mpCorrespondingPropertyValue;

  /**
   * A pointer to the associated compartment value (NULL if no association).
   */
  const C_FLOAT64 * mpCompartmentValue;

  /**
   * A pointer to the quantity to number conversion factor.
   */
  const C_FLOAT64 * mpQuantity2NumberValue;

  /**
   * A vector conaining the stoichiometry values for the reactions modifying a species
   */
  CVector< C_FLOAT64 > mStoichiometryVector;

  /**
   * A vector conaining the pointers to the rates for the reactions modifying a species
   */
  CVector< const C_FLOAT64 * > mRateVector;

  /**
   * A pointer to the member function use to calculate the value
   */
  calculate mpCalculate;

  /**
   * A pointer to the data object
   */
  const CDataObject * mpDataObject;
};

std::ostream &operator<<(std::ostream &os, const CMathObject & o);

#endif // COPASI_CObject
