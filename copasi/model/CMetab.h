/**
 *  CMetab class.
 *  Derived from Gepasi's cmetab.cpp. (C) Pedro Mendes 1995-2000.
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CMetab
#define COPASI_CMetab

#include <string>

#include "copasi.h"
#include "utilities/utilities.h"

class CCompartment;

//constants for use with Status
#define METAB_FIXED	0
#define METAB_VARIABLE	1
#define METAB_DEPENDENT	2
#define METAB_MOIETY	7

class CMetabOld;


class CMetab
{
  // Attributes
 private:
  /**
   *  Name of the metabolite
   */
  string mName;

  /**
   *  Concentration of the metabolite.
   */
  C_FLOAT64 mConc;

  /**
   * Initial concentration of the metabolite
   */
  C_FLOAT64 mIConc;

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
   */
  CCompartment  * mCompartment;

  // Operations
 public:
  /**
   *  Default constructor
   */
  CMetab();

  /**
   *  Copy constructor
   */
  CMetab(const CMetab & src);

  /**
   *  Specific constructor. 
   *  @param name name of the metabolite.
   */
  CMetab(const string & name);

  /**
   *  Specific constructor.
   *  @param name name of the metabolite.
   *  @param status status of the metabolite 
   *     (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
   *  @param compartment name of the compartment the metabolite
   *     is located in.
   */
  // CMetab(const string & compartment, C_INT16 status, CCompartment & name);

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
   *
   */
  void setName(const string & name);

  /**
   *  Retrieve the name of the metabolite.
   */
  const string & getName() const;

  /**
   *
   */
  void setStatus(const C_INT16 status);
    
  /**
   *
   */
  const C_INT16 & getStatus() const;
    
  /**
   *
   */
  void setConcentration(const C_FLOAT64 concentration);
    
  /**
   *
   */
  C_FLOAT64 * getConcentration();

  /**
   *
   */
  void setNumber(const C_FLOAT64 number);
    
  /**
   *
   */
  C_FLOAT64 getNumber() const;

  /**
   *
   */
  void setInitialConcentration(const C_FLOAT64 initialConcentration);
    
  /**
   *
   */
  C_FLOAT64 * getInitialConcentration();

  /**
   *
   */
  C_FLOAT64 getInitialNumber() const;

  /**
   *
   */
  void setCompartment(CCompartment * compartment); 

  /**
   *
   */
  CCompartment * getCompartment();

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
   *  Reset the values of a metabolite as if CMetab(string name) was called.
   *  @return Fail
   */
  C_INT32 reset(const string & name);

  /**
   *	Returns the address of mIConc		Wei Sun
   */
  void * getIConcAddr();

  /**
   *	Returns the address of mConc
   */
  void * getConcAddr();

  /**
   *	Returns the address of mTT
   */
  void * getTTAddr();

 private:

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
  string mName;

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
  C_INT32  mCompartment;

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

  string getName() const;
};

/**
 * Non member less than operator. This is needed, for example, when searching for an 
 * instance CMetab in a set of CMetab.
 */
bool operator< (const CMetab &lhs, const CMetab &rhs);

#endif // COPASI_CMetab
