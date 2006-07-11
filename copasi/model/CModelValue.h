/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelValue.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/11 19:32:21 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CModelValue
#define COPASI_CModelValue

#include <string>
#include <iostream>

#include "report/CCopasiContainer.h"

class CModel;
class CExpression;

/**
 * CModelEntity is a base class for CCompartment, CMetab and CModelValue.
 * These three classes have in common that (in the long run) they can each be model variables
 * (subject to ODEs), constant, or subject to algebraic assignments.
 * In addition, the CMetab objects can also be subject to reactions, and conservation rules.
 *
 */
class CModelEntity : public CCopasiContainer
  {
  protected:
    /**
     *  Key of the model entity. It is stored here, but constructed in the derived classes.
     */
    std::string mKey;

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
      FIXED = 0,          //the entity is constant (for metabs even if they are part of a reaction)
      ASSIGNMENT,         //the entity is changed by an assignment rule
      ODE,                //the entity is changed by an ordinary differential equation
      REACTIONS,          //applies only for metabs, the metab concentration is changed by reactions
      DEPENDENT,          //applies only for metabs, the metab concentration is determined by conservation rules
      UNUSED,
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
     *  Destructor.
     */
    ~CModelEntity();

    /**
     *  Retrieve the key
     * @return std::string key
     */
    virtual const std::string & getKey() const;

    /**
     *
     */
    const CModelEntity::Status & getStatus() const;

    inline bool isFixed() const {return mStatus == FIXED;}

    /**
     *
     */
    const C_FLOAT64 & getValue() const;

    /**
     *
     */
    const C_FLOAT64 & getInitialValue() const;

    /**
     * Return rate of production of this entity
     */
    const C_FLOAT64 & getRate() const;

    /**
     *
     */
    virtual void setStatus(const CModelEntity::Status & status);

    /**
     *
     */
    virtual void setValue(const C_FLOAT64 & value);

    /**
     *
     */
    virtual void setInitialValue(const C_FLOAT64 & initialValue);

    /**
     *  Set the rate (dmValue/dt)
     *  @param "const C_FLOAT64 &" rate
     */
    void setRate(const C_FLOAT64 & rate);

    virtual void * getValuePointer() const;

    /**
     * Sets the SBMLId.
     */
    void setSBMLId(const std::string& id);

    /**
     * Returns a reference to the SBML Id.
     */
    const std::string& getSBMLId() const;

    void setInitialValuePtr(C_FLOAT64 * pInitialValue);
    void setValuePtr(C_FLOAT64 * pValue);
    virtual bool setObjectParent(const CCopasiContainer * pParent);

  protected:
    /**
     * Pointer to the value of the model entity.
     */
    C_FLOAT64 * mpValueData;

    /**
     * Pointer to access the data value of the model entity..
     * This is mpIValue for fixed and mpValueData otherwise.
     */
    C_FLOAT64 * mpValueAccess;

    /**
     * Pointer to the initial value of the model entity.
     */
    C_FLOAT64 * mpIValue;

    /**
     *  Rate of production of this metabolite
     *  (concentration/time).
     */
    C_FLOAT64 mRate;

    /**
     *  Status of the model entity.
     */
  private:
    Status mStatus;

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
ODE                     not implemented       constant=false, boundaryCondition=true, rate rule
ASSIGNMENT              not implemented       constant=false, boundaryCondition=true, assignment rule
TIME                    -








CCompartment:                                 Compartment








FIXED                   implemented           constant=true
UNUSED                  not implemented
SUBJECT_TO_REACTION     -
DEPENDENT               -
ODE                     not implemented       constant=false, rate rule
ASSIGNMENT              not implemented       constant=false, assignment rule
TIME                    -








CModelValue:                                  Parameter




FIXED                   implemented           constant=true
UNUSED                  not implemented
SUBJECT_TO_REACTION     -
DEPENDENT               -
ODE                     not implemented       constant=false, rate rule
ASSIGNMENT              not implemented       constant=false, rate rule
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
 * It correspondents to global parameters in sbml
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
     *
     */
    virtual void setStatus(const CModelEntity::Status & status);

    /**
     * Compile the model value. This is only needed for status ASIGNMENT and ODE.
     * @param std::vector< CCopasiContainer * > listOfContainer (Default: CCopasiContainer::EmptyList)
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer =
                           CCopasiContainer::EmptyList);

    /**
     * Calculate the value or the rate depending whether we have an ASIGNMENT or ODE
     */
    void calculate();

    /**
     * Retrieve the expression for non FIXED model values.
     * @return CExpression * expression
     */
    CExpression * getExpression();

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CModelValue & d);

  private:
    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();

    // Attributes
  private:
    /**
     *
     */
    CExpression * mpExpression;
  };

#endif
