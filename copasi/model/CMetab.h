/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMetab.h,v $
   $Revision: 1.66 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/04/11 21:57:26 $
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
#include <set>

#include "model/CModelValue.h"

class CCompartment;
class CReadConfig;
//class CWriteConfig;
class CMetabOld;
class CModel;
class CMoiety;

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
     *  Transition time of the metabolite
     */
    C_FLOAT64 mTT;

    /**
     *  pointer to the compartment the metabolite is located in.
     *  The metab needs to know about volumes.
     */
    const CCompartment * mpCompartment;

    /**
     * The set of moieties the metabolite is part of
     */
    std::set< CMoiety * > mMoieties;

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

    virtual void * getValuePointer() const;
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
    virtual void setStatus(const CModelEntity::Status & status);

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
    virtual void setValue(const C_FLOAT64 & value);

    /**
     *
     */
    void setInitialConcentration(const C_FLOAT64 & initialConcentration);

    /**
     *
     */
    const C_FLOAT64 & getInitialConcentration() const;

    /**
     *
     */
    virtual void setInitialValue(const C_FLOAT64 & initialValue);

    void refreshInitialConcentration();

    void refreshConcentration();

    /**
     *
     */
    const CCompartment * getCompartment() const;

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

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CMetab & d);

    /**
     * Add a moiety to the list
     * @param CMoiety * pMoiety
     */
    void addMoiety(CMoiety * pMoiety);

    /**
     * Clear the list of moieties
     */
    void clearMoieties();

  private:
    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();
  };

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

    C_INT32 getIndex() const;
  };

#endif // COPASI_CMetab
