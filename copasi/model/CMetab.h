/**
 *  CMetab class.
 *  Derived from Gepasi's cmetab.cpp. (C) Pedro Mendes 1995-2000.
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CMetab
#define COPASI_CMetab

#include <string>
#include <iostream>

class CCompartment;
class CReadConfig;
class CWriteConfig;
class CMetabOld;
class CModel;

//constants for use with Status
#define METAB_FIXED 0
#define METAB_VARIABLE 1
#define METAB_DEPENDENT 2
#define METAB_MOIETY 7

class CMetab
  {
    // Attributes
  private:
    /**
     *  Name of the metabolite
     */
    std::string mName;

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
    CCompartment * mCompartment;

    /**
     *  pointer to the model the metabolite is located in.
     *  The metab needs to know about the unit for concentrations.
     */
    const CModel * mpModel;

    /**
     * This the default parent compartmnet used on creation
     */
    static const CCompartment *mpParentCompartment;

    // Operations
  public:
    /**
     *  Default constructor
     */
    CMetab(const CModel * pModel = NULL);

    /**
     *  Copy constructor
     */
    CMetab(const CMetab & src);

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

    /**
     *  Assignment operator.
     */
    CMetab & operator=(const CMetab & rhs);

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
     *  Sets the name of the metabolite.
     */
    void setName(const std::string & name);

    /**
     *  Retrieve the name of the metabolite.
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
    void setCompartment(CCompartment * compartment);

    /**
     *
     */
    CCompartment * getCompartment();

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
    const C_FLOAT64 & getRate();

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

      if (d.mCompartment)
        os << "        mCompartment == " << d.mCompartment << std::endl;
      else
        os << "        mCompartment == 0 " << std::endl;

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

    /*
     *
     */
    C_INT16 isValidName();
  };

class CMetabOld
  {
    friend class CMetab;

    // Attributes

  private:
    /**
     *  Name of the metabolite
     */
    std::string mName;

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
     *  Default constructor
     */
    CMetabOld();

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

    std::string getName() const;
  };

/**
 * Non member less than operator. This is needed, for example, when searching for an 
 * instance CMetab in a set of CMetab.
 */
bool operator< (const CMetab &lhs, const CMetab &rhs);

#endif // COPASI_CMetab
