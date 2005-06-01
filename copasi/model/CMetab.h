/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMetab.h,v $
   $Revision: 1.62 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/06/01 14:55:37 $
   End CVS Header */

/**
 *  CMetab class.
 *  Derived from Gepasi's cmetab.cpp. (C) Pedro Mendes 1995-2000.
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CMetab
#define COPASI_CMetab

#include <string>
#include <iostream>

#include "model/CModelValue.h"

class CCompartment;
class CReadConfig;
//class CWriteConfig;
class CMetabOld;
class CModel;

#define METAB_MOIETY 7

/** @dia:pos 80.8289,51.5961 */
class CMetab : public CModelEntity
  {
  public:

    /**
     * Converts the concentration to number
     * @param const C_FLOAT64 & concentration
     * @param const CCompartment & compartment
     * @param const CModel & model
     * @return C_FLOAT64 number
     */
    static C_FLOAT64 convertToNumber(const C_FLOAT64 & concentration,
                                     const CCompartment & compartment,
                                     const CModel & model);

    /**
     * Converts the number to concentration
     * @param const C_FLOAT64 & number
     * @param const CCompartment & compartment
     * @param const CModel & model
     * @return C_FLOAT64 concentration
     */
    static C_FLOAT64 convertToConcentration(const C_FLOAT64 & number,
                                            const CCompartment & compartment,
                                            const CModel & model);

    // Attributes
  private:
    /**
     *  Concentration of the metabolite as double.
     */
    C_FLOAT64 mConc;

    /**
     *  Initial concentration of the metabolite as double
     */
    C_FLOAT64 mIConc;

    /**
     *  Concentration of the metabolite as long.
     */ 
    //C_FLOAT64 mNumber;  replaced by CModelEntity::mValue

    /**
     * Initial concentration of the metabolite as long.
     */ 
    //C_FLOAT64 mINumber;  replaced by CModelEntity::mIValue

    /**
     *  Rate of production of this metabolite
     *  (concentration/time).
     */ 
    //C_FLOAT64 mRate;    replaced by CModelEntity::mRate

    /**
     *  Transition time of the metabolite
     */
    C_FLOAT64 mTT;

    /**
     *  Status of the metabolite.  
     *  One of (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
     */ 
    //Status mStatus;   replaced by CModelEntity::mStatus

    /**
     *  pointer to the compartment the metabolite is located in.
     *  The metab needs to know about volumes.
     */
    /** @dia:route 15,11; h,155.606,39.003,162.634,54.2961,108.729 */
    const CCompartment * mpCompartment;

    /**
     *  pointer to the model the metabolite is located in.
     *  The metab needs to know about the unit for concentrations.
     */
    /** @dia:route 15,38; h,108.729,55.8961,170.684,44.1423,177.081 */
    const CModel * mpModel;

    /**
     * This the default parent compartmnet used on creation
     */
    /** @dia:route 13,13; h,155.606,38.203,162.634,55.0961,108.729 */
    static const CCompartment *mpParentCompartment;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMetab(const std::string & name = "NoName",
           const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CMetab & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMetab(const CMetab & src,
           const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CMetab();

    virtual void * getReference() const;
    //TODO: discuss if it should be concentration or particle number...

    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    /**
     *  Cleanup
     */
    void cleanup();
    void initModel();
    void initCompartment(const CCompartment * pCompartment = NULL);

    /**
     *  Assignment operator.
     */
    CMetab & operator=(const CMetabOld & rhs);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     * Sets the parent of the metabolite;
     * @param const CCopasiContainer * pParent
     * @return bool success
     */
    virtual bool setObjectParent(const CCopasiContainer * pParent);

    /**
     *
     */
    void setStatus(const CMetab::Status & status);

    /**
     *
     */ 
    //const CMetab::Status & getStatus() const;

    /**
     *
     */
    void setConcentration(const C_FLOAT64 concentration);

    /**
     *
     */
    const C_FLOAT64 & getConcentration() const;

    /**
     *
     */
    inline void setNumber(const C_FLOAT64 number) {setValue(number);};

    virtual void setValue(const C_FLOAT64 number);

    /**
     *
     */
    inline const C_FLOAT64 & getNumber() const {return getValue();};

    /**
     *
     */
    bool setInitialConcentration(const C_FLOAT64 & initialConcentration);

    /**
     *
     */
    const C_FLOAT64 & getInitialConcentration() const;

    /**
     *
     */
    inline bool setInitialNumber(const C_FLOAT64 & initialNumber)
    {return setInitialValue(initialNumber);};

    virtual bool setInitialValue(const C_FLOAT64 & initialNumber);

    /**
     *
     */
    inline const C_FLOAT64 & getInitialNumber() const {return getInitialValue();};

    /**
     *
     */ 
    //void setCompartment(const CCompartment * compartment);

    /**
     *
     */
    const CCompartment * getCompartment() const;

    /**
     *
     */ 
    //void setModel(CModel * model);

    /**
     *
     */
    const CModel * getModel() const;

    /**
     *  Set transition time
     *  @param "const C_FLOAT64 &" transitionTime
     */
    void setTransitionTime(const C_FLOAT64 & transitionTime);

    /**
     *  Retrieves the transition time
     *  @return "const C_FLOAT64 &" transitionTime
     */
    const C_FLOAT64 & getTransitionTime() const;

    /**
     * Return rate of production of this metaboLite
     */
    C_FLOAT64 getConcentrationRate() const;

    inline const C_FLOAT64 & getNumberRate() const {return getRate();};

    /**
     *  Set the rate (dmConc/dt)
     *  @param "const C_FLOAT64 &" rate (unit: particle/time)
     */
    inline void setNumberRate(const C_FLOAT64 & rate) {setRate(rate);};

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CMetab & d);

    /**
     * Set the default parent compartment
     * @param const CCompartment * parentCompartmnte
     */
    static void setParentCompartment(const CCompartment * parentCompartment);

  private:
    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();
  };

/** @dia:pos 50.0045,52.5004 */
class CMetabOld : public CCopasiContainer
  {
    friend class CMetab;

    // Attributes

  private:
    /**
     *  Concentration of the metabolite.
     */
    C_FLOAT64 mIConc;

    /**
     *  Status of the metabolite.  
     *  One of (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
     */
    CMetab::Status mStatus;

    /**
     *  Index of the compartment the metabolite is located in.
     */
    C_INT32 mCompartment;

    // Operations

  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMetabOld(const std::string & name = "NoName",
              const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CMetabOld & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMetabOld(const CMetabOld & src,
              const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CMetabOld();

    /**
     *  cleanup()
     */
    void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     *  This function is only defined for completeness. We really never going 
     *  to save objects of class CMetabOld.
     */ 
    //    C_INT32 save(CWriteConfig & configbuffer);

    C_INT32 getIndex() const;

    //    const std::string & getName() const;
  };

/**
 * Non member less than operator. This is needed, for example, when searching for an 
 * instance CMetab in a set of CMetab.
 */ 
//bool operator< (const CMetab &lhs, const CMetab &rhs);

#endif // COPASI_CMetab
