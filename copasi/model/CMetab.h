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
class CWriteConfig;
class CMetabOld;
class CModel;

//constants for use with Status
// #define METAB_FIXED 0
// #define METAB_VARIABLE 1
// #define METAB_DEPENDENT 2
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
      METAB_DEPENDENT
    };

  public:
    /**
     * String representation od the states
     */
    static const std::string StatusName[];

    // Attributes
  private:
    /**
     *  Key of the metabolite
     */
    std::string mKey;

    /**
     *  Name of the metabolite
     */
    std::string & mName;

    /**
     *  Concentration of the metabolite as double.
     */
    C_FLOAT64 mConcDbl;

    /**
     *  Initial concentration of the metabolite as double
     */
    C_FLOAT64 mIConcDbl;

    /**
     *  Concentration of the metabolite as long.
     */
    C_INT32 mNumberInt;

    /**
     * Initial concentration of the metabolite as long.
     */
    C_INT32 mINumberInt;

    /**
     *  Rate of production of this metaboLite
     *  (here used for rate constant).
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
    C_INT16 mStatus;

    /**
     *  pointer to the compartment the metabolite is located in.
     *  The metab needs to know about volumes.
     */
    /** @dia:route 15,11; h,158.906,38.003,165.545,54.2961,117.263 */
    const CCompartment * mpCompartment;

    /**
     *  pointer to the model the metabolite is located in.
     *  The metab needs to know about the unit for concentrations.
     */
    /** @dia:route 15,38; h,117.263,55.8961,169.801,44.1423,177.081 */
    const CModel * mpModel;

    /**
     * This the default parent compartmnet used on creation
     */
    /** @dia:route 13,13; h,158.906,37.003,168.277,55.0961,117.263 */
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
     *  Specific constructor.
     *  @param name name of the metabolite.
     *  @param status status of the metabolite 
     *     (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
     *  @param compartment name of the compartment the metabolite
     *     is located in.
     */ 
    // CMetab(const std::string & compartment, C_INT16 status, CCompartment & name);

    /**
     *  Destructor.
     */
    ~CMetab();

    /**
     *  Cleanup
     */
    void cleanup();
    void initModel();
    void initCompartment(const CCompartment * pCompartment);

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
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 save(CWriteConfig & configbuffer);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  This saves the data in Gepasi 3.21 file format
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 saveOld(CWriteConfig & configbuffer);

    /**
     *  Saves the contents of the object to a ofstream object.
     *  Writes the data in SBML file format
     *  @param "std::ofstream &" fout ofstream that should be already open
     */
    void saveSBML(std::ofstream &fout);

    /**
     * Sets the name of the metabolite.
     * @param const std::string & name
     * @return bool Success
     */
    bool setName(const std::string & name);

    /**
     *  Retrieve the key of the metabolite.
     * @return std::string key
     */
    std::string getKey() const;

    /**
     *  Retrieve the name of the metabolite.
     * @return const std::string & name
     */
    const std::string & getName() const;

    /**
     *
     */
    void setStatus(const C_INT16 status);

    /**
     *
     */
    const C_INT16 & getStatus() const;

    /**
     *  Check if either concentration or particle number is invalid (e.g. negativ)
     *  and calculate it from the other
     */
    void checkConcentrationAndNumber();

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
    void setNumberDbl(const C_FLOAT64 number);

    /**
     *
     */
    C_FLOAT64 getNumberDbl() const;

    /**
     *
     */
    void setNumberInt(const C_INT32 number);

    /**
     *
     */
    const C_INT32 & getNumberInt() const;

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
    void setInitialNumberDbl(const C_FLOAT64 initialNumber);

    /**
     *
     */
    C_FLOAT64 getInitialNumberDbl() const;

    /**
     *
     */
    void setInitialNumberInt(const C_INT32 initialNumber);

    /**
     *
     */
    const C_INT32 & getInitialNumberInt() const;

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
    const C_FLOAT64 & getTransitionTime();

    /**
     * Returns the address of mIConc  Wei Sun
     */
    void * getIConcAddr();

    /**
     * Returns the address of mConc
     */
    void * getConcAddr();

    /**
     * Returns the address of mTT
     */
    void * getTTAddr();

    /**
     * Return rate of production of this metaboLite
     */
    const C_FLOAT64 & getRate() const;

    /**
     *  Set the rate (dmConc/dt)
     *  @param "const C_FLOAT64 &" rate (unit: particle/time)
     */
    void setRate(const C_FLOAT64 & rate);

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CMetab & d)
    {
      os << "    ++++CMetab: " << d.mName << std::endl;
      os << "        mConcDbl " << d.mConcDbl << " mIConcDbl " << d.mIConcDbl << std::endl;
      os << "        mNumberInt " << d.mNumberInt << " mINumberInt " << d.mINumberInt << std::endl;
      os << "        mRate " << d.mRate << " mTT " << d.mTT << " mStatus " << d.mStatus << std::endl;

      if (d.mpCompartment)
        os << "        mpCompartment == " << d.mpCompartment << std::endl;
      else
        os << "        mpCompartment == 0 " << std::endl;

      if (d.mpModel)
        os << "        mpModel == " << d.mpModel << std::endl;
      else
        os << "        mpModel == 0 " << std::endl;

      os << "    ----CMetab " << std::endl;

      return os;
    }

    /**
     * Set the default parent compartment
     * @param const CCompartment * parentCompartmnte
     */
    static void setParentCompartment(const CCompartment * parentCompartment);

  private:
    /**
     *  Calculate transition time
     */
    void calculateTransitionTime(void);

    /**
     * Check whether the name is valid.
     */
    bool isValidName(const std::string & name) const;

    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();
  };

/** @dia:pos 51.7045,51.8004 */
class CMetabOld : public CCopasiContainer
  {
    friend class CMetab;

    // Attributes

  private:
    /**
     *  Name of the metabolite
     */
    std::string & mName;

    /**
     *  Concentration of the metabolite.
     */
    C_FLOAT64 mIConc;

    /**
     *  Status of the metabolite.  
     *  One of (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
     */
    C_INT16 mStatus;

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
    C_INT32 save(CWriteConfig & configbuffer);

    C_INT32 getIndex() const;

    const std::string & getName() const;
  };

/**
 * Non member less than operator. This is needed, for example, when searching for an 
 * instance CMetab in a set of CMetab.
 */
bool operator< (const CMetab &lhs, const CMetab &rhs);

#endif // COPASI_CMetab
