/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelValue.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/05/27 16:06:54 $
   End CVS Header */

#ifndef COPASI_CModelValue
#define COPASI_CModelValue

#include <string>
#include <iostream>

#include "report/CCopasiContainer.h"

class CModel;

/**
 * CModelEntity is a base class for CCompartment, CMetab and CModelValue.
 * These three classes have in common that (in the long run) they can each be model variables 
 * (subject to ODEs), constant, or subject to algebraic assignments.
 * In addition, the CMetab objects can also be subject to reactions, and conservation rules.
 *
 */
class CModelEntity : public CCopasiContainer
  {
  public:
    /**
     *  The valid states for metabolites
     */
    enum Status
    {
      FIXED = 0,  //the entity is constant (for metabs even if they are part of a reaction)
      REACTIONS,  //applies only for metabs, the metab concentration is changed by reactions
      DEPENDENT,  //applies only for metabs, the metab concentration is determined by conservation rules
      ODE,        //the entity is changed by an ordinary differential equation
      ASSIGNMENT, //the entity is changed by an assignment rule
      UNUSED
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
     *
     */
    const CModelEntity::Status & getStatus() const;

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

  protected:
    /**
     *  Concentration of the metabolite as double.
     */
    C_FLOAT64 mValue;

    /**
     *  Initial concentration of the metabolite as double
     */
    C_FLOAT64 mIValue;

    /**
     *  Rate of production of this metabolite
     *  (concentration/time).
     */
    C_FLOAT64 mRate;

    /**
     *  Transition time of the metabolite
     */ 
    //C_FLOAT64 mTT;

    /**
     *  Status of the metabolite.  
     *  One of (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
     */
    Status mStatus;
  };

/*
Table of possible CModelEntity objects with different Status
 
                        current status        corresponding sbml object
-------------------------------------------------------------------------------------------------
CMetab:                                       Species
 
FIXED                   implemented           constant=true
SUBJECT_TO_REACTION     implemented           constant=false, boundaryCondition=false
DEPENDENT               implemented           constant=false, boundaryCondition=false
ODE                     not implemented       constant=false, boundaryCondition=true, rate rule
ASSIGNMENT              not implemented       constant=false, boundaryCondition=true, assignment rule
 
 
CCompartment:                                 Compartment
 
FIXED                   implemented           constant=true
SUBJECT_TO_REACTION     -
DEPENDENT               -
ODE                     not implemented       constant=false, rate rule
ASSIGNMENT              not implemented       constant=false, assignment rule
  
 
CModelValue:                                  Parameter
 
FIXED                   in progress           constant=true
SUBJECT_TO_REACTION     -
DEPENDENT               -
ODE                     not implemented       constant=false, rate rule
ASSIGNMENT              not implemented       constant=false, rate rule
  
 */

/**
 * CModelValue represents an entity in the model that has a value but is not a concentration (like species) 
 * or a volume (like compartments).
 * It correspondents to global parameters in sbml
 */
class CModelValue : public CModelEntity
  {
    // Attributes
  private:
    /**
     *  Key of the metabolite
     */
    std::string mKey;

    // Operations
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

    virtual void * getReference() const;

    //virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    /**
     *  Cleanup
     */
    void cleanup();
    //void initModel();

    /**
     * Sets the parent of the metabolite;
     * @param const CCopasiContainer * pParent
     * @return bool success
     */ 
    //virtual bool setObjectParent(const CCopasiContainer * pParent);

    /**
     *  Retrieve the key of the metabolite.
     * @return std::string key
     */
    virtual const std::string & getKey() const;

    /**
     *
     */
    void setStatus(const CModelValue::Status & status);

    /**
     *
     */
    void setValue(const C_FLOAT64 v);

    /**
     *
     */
    bool setInitialValue(const C_FLOAT64 & iV);

    /**
     *  Set the rate (dmValue/dt)
     *  @param "const C_FLOAT64 &" rate 
     */
    void setRate(const C_FLOAT64 & rate);

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

#endif // COPASI_CMetab
