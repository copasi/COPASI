// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathObject.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/03/23 09:09:13 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CObject
#define COPASI_CObject

#include <set>
#include <map>

#include "copasi/report/CCopasiObject.h"
#include "copasi/math/CMathEnum.h"

class CMathExpression;
class CMathContainer;
class CExpression;
class CCopasiObject;
class CMetab;

class CMathObject: public CObjectInterface
{
public:
  /**
   * Default Constructor
   */
  CMathObject();

  /**
   * Destructor
   */
  virtual ~CMathObject();

  /**
   * Retrieve the CN of the object
   * @return CCopasiObjectName
   */
  virtual CCopasiObjectName getCN() const;

  /**
   * Retrieve a descendant object by its CN.
   * @param const CCopasiObjectName & cn
   * @return const CObjectInterface * pObject
   */
  virtual const CObjectInterface * getObject(const CCopasiObjectName & cn) const;

  /**
   * Retrieve the prerequisites, i.e., the objects which need to be evaluated
   * before this.
   * @return const CObjectInterface::ObjectSet & prerequisites
   */
  virtual const CObjectInterface::ObjectSet & getPrerequisites() const;

  /**
   * Check whether a given object is a prerequisite for a context.
   * @param const CObjectInterface * pObject
   * @param const CMath::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @return bool isPrerequisiteForContext
   */
  virtual bool isPrerequisiteForContext(const CObjectInterface * pObject,
                                        const CMath::SimulationContextFlag & context,
                                        const CObjectInterface::ObjectSet & changedObjects) const;

  /**
   * This is the output method for any object. The default implementation
   * provided with CCopasiObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const;

  /**
   * Retrieve a pointer to the value of the object
   */
  virtual void * getValuePointer() const;

  /**
   * Calculate the objects value
   */
  void calculate();

  /**
   * Initialize a single mathematical object and advance relevant pointers
   * @param CMathObject *& pObject
   * @param C_FLOAT64 *& pValue
   * @param const CMath::Value & valueType
   * @param const CMath::EntityType & entityType
   * @param const CMath::SimulationType & simulationType
   * @param const bool & isIntensiveProperty
   * @param const bool & isInitialValue
   * @param const CCopasiObject * pDataObject
   */
  static void initializeMathObject(CMathObject *& pObject,
                                   C_FLOAT64 *& pValue,
                                   const CMath::ValueType & valueType,
                                   const CMath::EntityType & entityType,
                                   const CMath::SimulationType & simulationType,
                                   const bool & isIntensiveProperty,
                                   const bool & isInitialValue,
                                   const CCopasiObject * pDataObject);

  /**
   * Compile
   * @param const CMathContainer & container
   * @return bool success
   */
  bool compile(const CMathContainer & container);

  /**
   * Retrieve the pointer to the data object
   * @return const CCopasiObject * pDataObject
   */
  const CCopasiObject * getDataObject() const;


private:
  /**
   * Compile initial value objects
   * @param const CMathContainer & container
   * @return bool success
   */
  bool compileInitialValue(const CMathContainer & container);

  /**
   * Compile value objects
   * @param const CMathContainer & container
   * @return bool success
   */
  bool compileValue(const CMathContainer & container);

  /**
   * Compile value rate objects
   * @param const CMathContainer & container
   * @return bool success
   */
  bool compileValueRate(const CMathContainer & container);

  /**
   * Compile the reactions flux
   * @param const CMathContainer & container
   * @return bool success
   */
  bool compileFlux(const CMathContainer & container);

  /**
   * Compile the reactions propensity
   * @param const CMathContainer & container
   * @return bool success
   */
  bool compilePropensity(const CMathContainer & container);

  /**
   * Compile the total mass of a moiety.
   * @param const CMathContainer & container
   * @return bool success
   */
  bool compileTotalMass(const CMathContainer & container);

  /**
   * Compile the dependent mass of a moiety.
   * @param const CMathContainer & container
   * @return bool success
   */
  bool compileDependentMass(const CMathContainer & container);

  /**
   * Create and compile an expression based on the given expression.
   * @param const CExpression * pExpression
   * @param const CMathContainer & container
   * @return bool success
   */
  bool createConvertedExpression(const CExpression * pExpression,
                                 const CMathContainer & container);

  /**
   * Create and compile an expression for an intensive value of a species.
   * @param const CMetab * pSpecies
   * @param const CMathContainer & container
   * @return bool success
   */
  bool createIntensiveValueExpression(const CMetab * pSpecies,
                                      const CMathContainer & container);

  /**
   * Create and compile an expression for an extensive value of a species.
   * @param const CMetab * pSpecies
   * @param const CMathContainer & container
   * @return bool success
   */
  bool createExtensiveValueExpression(const CMetab * pSpecies,
                                      const CMathContainer & container);

  /**
   * Create and compile an expression for an intensive rate of a species.
   * @param const CMetab * pSpecies
   * @param const CMathContainer & container
   * @return bool success
   */
  bool createIntensiveRateExpression(const CMetab * pSpecies,
                                     const CMathContainer & container);

  /**
   * Create and compile an expression for an extensive rate of a species determined
   * by an ODE.
   * @param const CMetab * pSpecies
   * @param const CMathContainer & container
   * @return bool success
   */
  bool createExtensiveODERateExpression(const CMetab * pSpecies,
                                        const CMathContainer & container);

  /**
   * Create and compile an expression for an extensive rate of a species determined
   * by reactions
   * @param const CMetab * pSpecies
   * @param const CMathContainer & container
   * @return bool success
   */
  bool createExtensiveReactionRateExpression(const CMetab * pSpecies,
      const CMathContainer & container);

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
   * A pointer to the corresponding intensive property if it exists otherwise NULL
   */
  const CMathObject * mpIntensiveProperty;

  /**
   * A pointer to the data object
   */
  const CCopasiObject * mpDataObject;
};

#endif // COPASI_CObject
