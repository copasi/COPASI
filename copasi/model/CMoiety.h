/**
 *  CMoiety
 *  
 *  New class created for Copasi by Stefan Hoops
 *  (C) Stefan Hoops 2001
 */

#ifndef COPASI_CMoiety
#define COPASI_CMoiety

#include <string>
#include <vector>

#include "CMetab.h"
#include "CChemEqElement.h"

class CMoiety
{
  // Attributes
 private:
  /**
   *
   */
  string mName;

  /**
   *  Number of Particles of Moietiy.
   */
  C_FLOAT64 mNumber;

  /**
   *  Initial Number of Particles of Moietiy.
   */
  C_FLOAT64 mINumber;

  /**
   *  Vector of linear dependent CChemEqElement
   * @supplierCardinality 0..*
   */
  CCopasiVector < CChemEqElement > mEquation;
    
  // Operations
 public:
  /**
   *  Default constructor
   */
  CMoiety();

  /**
   *  Copy constructor
   *  @param "const CMoiety &" src
   */
  CMoiety(const CMoiety & src);

  /**
   *
   */
  CMoiety(const string & name);
 
  /**
   *  Destructor
   */
 ~CMoiety();

  /**
   *
   */
  C_INT32 load(CReadConfig & configBuffer);

  /**
   *
   */
  C_INT32 save(CWriteConfig & configBuffer);

  /**
   *
   */
  void add(C_FLOAT64 value, CMetab & metabolite);

  /**
   *
   */
  void add(C_FLOAT64 value, CMetab * metabolite);

  /**
   *
   */
  void cleanup();

  /**
   *
   */
  void cleanup(const string & name);

  /**
   *
   */
  void cleanup(C_INT32 index);

  /**
   *
   */
  void change(C_INT32 index,
	      C_FLOAT64 value);

  /**
   *
   */
  void change(const string & name,
	      C_FLOAT64 value);

  /**
   *
   */
  void setName(const string name);

  /**
   *
   */
  void setInitialValue();

  /**
   *
   */
  string getName() const;

  /**
   *
   */
  string getDescription() const;

  /**
   *
   */
  C_FLOAT64 dependentNumber();

  /**
   *
   */
  C_FLOAT64 getNumber() const;

  /**
   *	Returns the address of mNumber
   */
  void * getNumberAddr();


};

#endif // COPASI_CMoiety
