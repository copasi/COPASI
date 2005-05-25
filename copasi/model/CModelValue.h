/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelValue.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/05/25 09:48:48 $
   End CVS Header */

/**
 *  CMetab class.
 *  Derived from Gepasi's cmetab.cpp. (C) Pedro Mendes 1995-2000.
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CModelValue
#define COPASI_CModelValue

#include <string>
#include <iostream>

#include "report/CCopasiContainer.h"

class CModel;

// #define METAB_MOIETY 7

class CModelValue : public CCopasiContainer
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

    /**
     *  pointer to the model the metabolite is located in.
     *  The metab needs to know about the unit for concentrations.
     */
    /** @dia:route 15,38; h,108.729,55.8961,170.684,44.1423,177.081 */
    //const CModel * mpModel;
    //TODO

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
     *  Assignment operator.
     */ 
    //CModelValue & operator=(const CModelValueOld & rhs);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */ 
    //C_INT32 load(CReadConfig & configbuffer);

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
    const CModelValue::Status & getStatus() const;

    /**
     *
     */
    void setValue(const C_FLOAT64 v);

    /**
     *
     */
    const C_FLOAT64 & getValue() const;

    /**
     *
     */
    bool setInitialValue(const C_FLOAT64 & iV);

    /**
     *
     */
    const C_FLOAT64 & getInitialValue() const;

    /**
     *
     */ 
    //void setModel(CModel * model);

    /**
     *
     */ 
    //const CModel * getModel() const;

    /**
     * Return rate of production of this metaboLite
     */
    const C_FLOAT64 & getRate() const;

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
