/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMetab.h,v $
   $Revision: 1.52 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/01/12 15:59:33 $
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

#include "report/CCopasiContainer.h"

class CCompartment;
class CReadConfig;
//class CWriteConfig;
class CMetabOld;
class CModel;

#define METAB_MOIETY 7

/** @dia:pos 80.8289,51.5961 */
class CMetab : public CCopasiContainer
  {
  public:
    /**
     *  The valid states for metabolites
     */
    enum Status
    {
      METAB_FIXED = 0,
      METAB_VARIABLE,
      METAB_DEPENDENT,
      METAB_UNUSED
    };

  public:
    /**
     * String representation of the states
     */
    static const std::string StatusName[];

    /**
     * XML representation of the states
     */
    static const char * XMLStatus[];

    // Attributes
  private:
    /**
     *  Key of the metabolite
     */
    std::string mKey;

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
    C_FLOAT64 mNumber;

    /**
     * Initial concentration of the metabolite as long.
     */
    C_FLOAT64 mINumber;

    /**
     *  Rate of production of this metabolite
     *  (concentration/time).
     */
    C_FLOAT64 mRate;

    /**
     *  Transition time of the metabolite
     */
    C_FLOAT64 mTT;

    /**
     *  Status of the metabolite.  
     *  One of (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
     */
    Status mStatus;

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

    virtual bool setValueOfNamedReference(std::string name, C_FLOAT64 value);

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
     *  Retrieve the key of the metabolite.
     * @return std::string key
     */
    virtual const std::string & getKey() const;

    /**
     *
     */
    void setStatus(const CMetab::Status & status);

    /**
     *
     */
    const CMetab::Status & getStatus() const;

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
    void setNumber(const C_FLOAT64 number);

    /**
     *
     */
    const C_FLOAT64 & getNumber() const;

    /**
     *
     */
    void setInitialConcentration(const C_FLOAT64 initialConcentration);

    /**
     *
     */
    const C_FLOAT64 & getInitialConcentration() const;

    /**
     *
     */
    void setInitialNumber(const C_FLOAT64 initialNumber);

    /**
     *
     */
    const C_FLOAT64 & getInitialNumber() const;

    /**
     *
     */
    void setCompartment(const CCompartment * compartment);

    /**
     *
     */
    const CCompartment * getCompartment() const;

    /**
     *
     */
    void setModel(CModel * model);

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
    const C_FLOAT64 & getConcentrationRate() const;
    C_FLOAT64 getNumberRate() const;

    /**
     *  Set the rate (dmConc/dt)
     *  @param "const C_FLOAT64 &" rate (unit: particle/time)
     */
    void setConcentrationRate(const C_FLOAT64 & rate);
    void setNumberRate(const C_FLOAT64 & rate);

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
