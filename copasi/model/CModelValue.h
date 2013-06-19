// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
    \file CModelValue.h
    \brief Header file of class CModelEntity and CModelValue
 */

#ifndef COPASI_CModelValue
#define COPASI_CModelValue

#include <string>
#include <iostream>

#include "copasi/model/CAnnotation.h"
#include "copasi/report/CCopasiContainer.h"

class CModel;
class CExpression;

/**
 * The base class for CCompartment, CMetab and CModelValue.
 * CModelEntity is a base class for CCompartment, CMetab and CModelValue.
 * These three classes have in common that (in the long run) they can each be model variables
 * (subject to ODEs), constant, or subject to algebraic assignments.
 * In addition, the CMetab objects can also be subject to reactions, and conservation rules.
 */
class CModelEntity : public CCopasiContainer, public CAnnotation
{
protected:
  /**
   * The id of the corresponding parameter in an SBML file.
   * This value is either set upon importing an SBML file,
   * or when the object is first exported to an SBML file.
   */
  std::string mSBMLId;

public:
  /**
   *  The valid states for metabolites
   */
  enum Status
  {
    FIXED = 0, //the entity is constant (for species even if they are part of a reaction)
    ASSIGNMENT, //the entity is changed by an assignment rule
    REACTIONS, //applies only for species, the species concentration is changed by reactions
    //      DEPENDENT, //applies only for species, the species concentration is determined by conservation rules
    //      UNUSED,
    ODE, //the entity is changed by an ordinary differential equation
    TIME
  };

  /**
   * String representation of the states
   */
  static const std::string StatusName[];

  /**
   * XML representation of the states
   */
  static const char * XMLStatus[];

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CModelEntity(const std::string & name = "NoName",
               const CCopasiContainer * pParent = NULL,
               const std::string & type = "ModelEntity",
               const unsigned C_INT32 & flag = CCopasiObject::Container | CCopasiObject::ValueDbl);

  /**
   * Copy constructor
   * @param const CModelValue & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CModelEntity(const CModelEntity & src,
               const CCopasiContainer * pParent = NULL);

  /**
   * Destructor.
   */
  ~CModelEntity();

  /**
   * Retrieve the key
   * @return std::string key
   */
  virtual const std::string & getKey() const;

  /**
   * Retrieve the status of the entity.
   * @return const CModelEntity::Status & status
   */
  const CModelEntity::Status & getStatus() const;

  /**
   * Compile the model value. This is only needed for status ASIGNMENT and ODE.
   * @return bool success
   */
  virtual bool compile();

  /**
   * Calculate the value or the rate depending whether we have an ASIGNMENT or ODE
   */
  virtual void calculate();

  /**
   * Check whether the entity is FIXED or not.
   * @return bool isFixed
   */
  inline bool isFixed() const {return mStatus == FIXED;}

  /**
   * Retrieve the value
   */
  const C_FLOAT64 & getValue() const;

  /**
   * Retrieve the initial value
   */
  const C_FLOAT64 & getInitialValue() const;

  /**
   * Refresh the initial value
   */
  virtual void refreshInitialValue();

  /**
   * Return rate of production of this entity
   */
  const C_FLOAT64 & getRate() const;

  /**
   * Set the status
   * @param const CModelEntity::Status & status
   */
  virtual void setStatus(const CModelEntity::Status & status);

  /**
   * Set the value
   * @param const C_FLOAT64 & value
   */
  virtual void setValue(const C_FLOAT64 & value);

  /**
   * Set the initial value
   * @param const C_FLOAT64 & initialValue
   */
  virtual void setInitialValue(const C_FLOAT64 & initialValue);

  /**
   * Set the rate (dmValue/dt)
   * @param "const C_FLOAT64 &" rate
   */
  void setRate(const C_FLOAT64 & rate);

  /**
   * Retrieve the object representing the value;
   */
  virtual const CCopasiObject * getValueObject() const;

  /**
   * Retrieve a pointer to the value;
   */
  virtual void * getValuePointer() const;

  /**
   * Set the object parent
   * @param const CCopasiContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CCopasiContainer * pParent);

  /**
   * Retrieve the list of deleted numeric child objects;
   * @return std::set< const CCopasiObject * > deletedObjects
   */
  virtual std::set< const CCopasiObject * > getDeletedObjects() const;

  /**
   * Check whether an object must be deleted because its prerequisites can
   * no longer be fulfilled due to the given deleted objects
   * @param const DataObjectSet & deletedObjects
   * @return bool mustBeDeleted
   */
  virtual bool mustBeDeleted(const DataObjectSet & deletedObjects) const;

  /**
   * Sets the SBMLId.
   */
  void setSBMLId(const std::string& id);

  /**
   * Returns a reference to the SBML Id.
   */
  const std::string& getSBMLId() const;

  /**
   * Set the pointer to the initial value
   * @param C_FLOAT64 * pInitialValue
   */
  void setInitialValuePtr(C_FLOAT64 * pInitialValue);

  /**
   * Set the pointer to the value
   * @param C_FLOAT64 * pValue
   */
  void setValuePtr(C_FLOAT64 * pValue);

  /**
   * Set the expression for non FIXED model values
   * @param CExpression*
   * @return bool success
   */
  bool setExpressionPtr(CExpression* pExpression);

  /**
   * Retrieve the pointer to the expression for non FIXED model values.
   * @return CExpression*
   */
  const CExpression* getExpressionPtr() const;

  /**
   * Retrieve the pointer to the expression for non FIXED model values.
   * @return CExpression*
   */
  CExpression* getExpressionPtr();

  /**
   * Set the expression for non FIXED model values
   * @param CExpression*
   * @return bool success
   */
  bool setInitialExpressionPtr(CExpression* pExpression);

  /**
   * Retrieve the pointer to the expression for non FIXED model values.
   * @return CExpression*
   */
  const CExpression* getInitialExpressionPtr() const;

  /**
   * Retrieve the pointer to the expression for non FIXED model values.
   * @return CExpression*
   */
  CExpression* getInitialExpressionPtr();

  /**
   * Set the expression for non FIXED model values
   * @param const std::string & expression
   * @return bool success
   */
  bool setExpression(const std::string & expression);

  /**
   * Retrieve the expression for non FIXED model values.
   * @return std::string expression
   */
  std::string getExpression() const;

  /**
   * Set the expression for ODE or REACTION model values
   * @param const std::string & expression
   * @return bool success
   */
  bool setInitialExpression(const std::string & expression);

  /**
   * Retrieve the expression for ODE or REACTION model values.
   * @return std::string expression
   */
  std::string getInitialExpression() const;

  /**
   * Set whether the model entity is used during simulation
   * @param const bool & used
   */
  void setUsed(const bool & used);

  /**
   * Retrieve whether the model value is used during simulation
   * @return const bool & used
   */
  const bool & isUsed() const;

  /**
   * Retrieve object referencing the initial value
   * @return CCopasiObject * initialValueReference
   */
  CCopasiObject * getInitialValueReference() const;

  /**
   * Retrieve object referencing the value
   * @return CCopasiObject * valueReference
   */
  CCopasiObject * getValueReference() const;

  /**
   * Retrieve object referencing the rate
   * @return CCopasiObject * rateReference
   */
  CCopasiObject * getRateReference() const;

protected:
  /**
   * Pointer to the value of the model entity.
   */
  C_FLOAT64 * mpValue;

  /**
   * Pointer to the initial value of the model entity.
   */
  C_FLOAT64 * mpIValue;

  /**
   * Rate of change/time.
   */
  C_FLOAT64 mRate;

  /**
   * The infix expression for objects of type ASSIGNMENT or ODE
   */
  CExpression * mpExpression;

  /**
   * Optional initial expression
   */
  CExpression * mpInitialExpression;

private:
  /**
   *  Status of the model entity.
   */
  Status mStatus;

  /**
   * Indicates whether the model value is used, i.e., must be
   * calculated during the simulation
   */
  bool mUsed;

protected:
  CCopasiObjectReference<C_FLOAT64> *mpIValueReference;
  CCopasiObjectReference<C_FLOAT64> *mpValueReference;
  CCopasiObjectReference<C_FLOAT64> *mpRateReference;
  CModel * mpModel;

private:
  /**
   * Initialize the contained CCopasiObjects
   */
  void initObjects();
};

/*
Table of possible CModelEntity objects with different Status

                        current status        corresponding sbml object
-------------------------------------------------------------------------------------------------
CMetab:                                       Species

FIXED                   implemented           constant=true
UNUSED                  implemented           ?
SUBJECT_TO_REACTION     implemented           constant=false, boundaryCondition=false
DEPENDENT               implemented           constant=false, boundaryCondition=false
ODE                     implemented           constant=false, boundaryCondition=true, rate rule
ASSIGNMENT              implemented           constant=false, boundaryCondition=true, assignment rule
TIME                    -

CCompartment:                                 Compartment

FIXED                   implemented           constant=true
UNUSED                  not implemented
SUBJECT_TO_REACTION     -
DEPENDENT               -
ODE                     implemented           constant=false, rate rule
ASSIGNMENT              implemented           constant=false, assignment rule
TIME                    -

CModelValue:                                  Parameter

FIXED                   implemented           constant=true
UNUSED                  not implemented
SUBJECT_TO_REACTION     -
DEPENDENT               -
ODE                     implemented           constant=false, rate rule
ASSIGNMENT              implemented           constant=false, rate rule
TIME                    -

CModel:                                       implicitly represented in sbml file

FIXED                   -
UNUSED                  -
SUBJECT_TO_REACTION     -
DEPENDENT               -
ODE                     -
ASSIGNMENT              -
TIME                    implemented
 */

/**
 * CModelValue represents an entity in the model that has a value but is
 * not a concentration (like species) or a volume (like compartments).
 * It correspondents to global parameters in SBML
 */
class CModelValue : public CModelEntity
{
public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CModelValue(const std::string & name = "NoName",
              const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param const CModelValue & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CModelValue(const CModelValue & src,
              const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CModelValue();

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CModelValue & d);

private:
  /**
   * Initialize the contained CCopasiObjects
   */
  void initObjects();
};

#endif
