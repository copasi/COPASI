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
#include "copasi/core/CDataContainer.h"
#include "copasi/core/CEnumAnnotation.h"
#include "copasi/utilities/CUnit.h"

class CModel;
class CExpression;

/**
 * The base class for CCompartment, CMetab and CModelValue.
 * CModelEntity is a base class for CCompartment, CMetab and CModelValue.
 * These three classes have in common that (in the long run) they can each be model variables
 * (subject to ODEs), constant, or subject to algebraic assignments.
 * In addition, the CMetab objects can also be subject to reactions, and conservation rules.
 */
class CModelEntity : public CDataContainer, public CAnnotation
{
protected:
  /**
   * The id of the corresponding parameter in an SBML file.
   * This value is either set upon importing an SBML file,
   * or when the object is first exported to an SBML file.
   */
  mutable std::string mSBMLId;

  CModelEntity(const CModelEntity & src);

public:
  /**
   *  The valid states for metabolites
   */
  enum struct Status
  {
    FIXED = 0,  //the entity is constant (for species even if they are part of a reaction)
    ASSIGNMENT, //the entity is changed by an assignment rule
    REACTIONS, //applies only for species, the species concentration is changed by reactions
    ODE, //the entity is changed by an ordinary differential equation
    TIME,
    __SIZE
  };

  /**
   * String representation of the states
   */
  static const CEnumAnnotation< std::string, Status > StatusName;

  /**
   * XML representation of the states
   */
  static const CEnumAnnotation< std::string, Status > XMLStatus;

  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CModelEntity * pDataObject
   */
  static CModelEntity * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const override;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes) override;

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const override;

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CModelEntity(const std::string & name = "NoName",
               const CDataContainer * pParent = NO_PARENT,
               const std::string & type = "ModelEntity",
               const CFlags< Flag > & flag = CFlags< Flag >::None);

  /**
   * Copy constructor
   * @param const CModelValue & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CModelEntity(const CModelEntity & src,
               const CDataContainer * pParent);

  /**
   * Destructor.
   */
  ~CModelEntity();

  /**
   * Retrieve the key
   * @return std::string key
   */
  virtual const std::string & getKey() const override;

  /**
   * Retrieve the status of the entity.
   * @return const CModelEntity::Status & status
   */
  const CModelEntity::Status & getStatus() const;

  /**
   * Compile the model value. This is only needed for status ASIGNMENT and ODE.
   * @return CIssue issue
   */
  virtual CIssue compile();

  /**
   * Calculate the value or the rate depending whether we have an ASIGNMENT or ODE
   */
  virtual void calculate();

  /**
   * Check whether the entity is FIXED or not.
   * @return bool isFixed
   */
  inline bool isFixed() const {return mStatus == Status::FIXED;}

  /**
   * Retrieve the value
   */
  const C_FLOAT64 & getValue() const;

  /**
   * Retrieve the initial value
   */
  const C_FLOAT64 & getInitialValue() const;

  /**
   * Return rate of production of this entity
   */
  const C_FLOAT64 & getRate() const;

  /**
   * Set the status
   * @param const CModelEntity::Status & status
   */
  bool setStatus(const CModelEntity::Status & status);

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
  virtual const CDataObject * getValueObject() const override;

  /**
   * Retrieve a pointer to the value;
   */
  virtual void * getValuePointer() const override;

  /**
   * Set the object parent
   * @param const CDataContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CDataContainer * pParent) override;

  /**
   * Sets the SBMLId.
   */
  void setSBMLId(const std::string& id) const;

  /**
   * Returns a reference to the SBML Id.
   */
  const std::string& getSBMLId() const;

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
   * Retrieve the default expression for the noise.
   * @return std::string expression
   */
  std::string getDefaultNoiseExpression() const;

  /**
   * Set the expression for non FIXED model values
   * @param const std::string & expression
   * @return bool success
   */
  bool setNoiseExpression(const std::string & expression);

  /**
   * Retrieve the expression for non FIXED model values.
   * @return std::string expression
   */
  std::string getNoiseExpression() const;

  /**
   * Set the noise expression for ODE model values
   * @param CExpression*
   * @return bool success
   */
  bool setNoiseExpressionPtr(CExpression* pExpression);

  /**
   * Retrieve the pointer to the expression for ODE model values.
   * @return CExpression*
   */
  const CExpression* getNoiseExpressionPtr() const;

  /**
   * Retrieve the pointer to the expression for ODE model values.
   * @return CExpression*
   */
  CExpression* getNoiseExpressionPtr();

  /**
   * Set whether to add noise to the ODE
   * @param const bool & hasNoise
   */
  void setHasNoise(const bool & hasNoise);

  /**
   * Check whether noise is added to the ODE
   * @return const bool & hasNoise
   */
  const bool & hasNoise() const;

  /**
   * Set the expression for non FIXED model values
   * @param const std::string & expression
   * @return CIssue issue
   */
  CIssue setExpression(const std::string & expression);

  /**
   * Retrieve the expression for non FIXED model values.
   * @return std::string expression
   */
  std::string getExpression() const;

  /**
   * Set the expression for ODE or REACTION model values
   * @param const std::string & expression
   * @return CIssue issue
   */
  CIssue setInitialExpression(const std::string & expression);

  /**
   * Retrieve the expression for ODE or REACTION model values.
   * @return std::string expression
   */
  std::string getInitialExpression() const;

  /**
   * Set the unit.
   * @param const CUnit & unit
   * @return CIssue issue
   */
  virtual CIssue setUnitExpression(std::string unitExpression);

  /**
   * Get the unit.
   * @return CUnit &
   */
  virtual const std::string &getUnitExpression() const;

  /**
   * Retrieve the units of the child object.
   * @return const & CUnit units
   */
  virtual std::string getChildObjectUnits(const CDataObject * pObject) const override;

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
   * @return CDataObject * initialValueReference
   */
  CDataObject * getInitialValueReference() const;

  /**
   * Retrieve object referencing the value
   * @return CDataObject * valueReference
   */
  CDataObject * getValueReference() const;

  /**
   * Retrieve object referencing the rate
   * @return CDataObject * rateReference
   */
  CDataObject * getRateReference() const;

  /**
   * Retrieve object referencing the noise
   * @return CDataObject * rateReference
   */
  CDataObject * getNoiseReference() const;

  /**
   * Retrieve a pointer to the model the entity belongs too
   * @return CModel * pModel
   */
  CModel * getModel() const;

protected:
  /**
   * Pointer to the value of the model entity.
   */
  C_FLOAT64 mValue;

  /**
   * Pointer to the initial value of the model entity.
   */
  C_FLOAT64 mIValue;

  /**
   * Rate of change/time.
   */
  C_FLOAT64 mRate;

  /**
   * Noise
   */
  C_FLOAT64 mNoise;

  /**
   * The infix expression for objects of type ASSIGNMENT or ODE
   */
  CExpression * mpExpression;

  /**
   * Optional initial expression
   */
  CExpression * mpInitialExpression;

  /**
   * Optional noise term for entities of type ODE
   */
  CExpression * mpNoiseExpression;

  /**
   * A Boolean flag indicating whether to add noise to the reaction
   */
  bool mHasNoise;

  /**
   * Pointer to the Unit of the model entity.
   */
  std::string mUnitExpression;

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
  CDataObjectReference<C_FLOAT64> *mpIValueReference;
  CDataObjectReference<C_FLOAT64> *mpValueReference;
  CDataObjectReference<C_FLOAT64> *mpRateReference;
  CDataObjectReference<C_FLOAT64> *mpNoiseReference;
  mutable CModel * mpModel;

private:
  /**
   * Initialize the contained CDataObjects
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
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CModelValue * pDataObject
   */
  static CModelValue * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const;

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CModelValue(const std::string & name = "NoName",
              const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CModelValue & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CModelValue(const CModelValue & src,
              const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CModelValue();

  /**
   * Retrieve the units of the object.
   * @return std::string units
   */
  virtual const std::string getUnits() const;

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CModelValue & d);

private:
  /**
   * Initialize the contained CDataObjects
   */
  void initObjects();
};

#endif
