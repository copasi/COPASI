/**
 * CBaseFunction
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CMassAction
#define COPASI_CMassAction

#include <string>
#include <vector>

#include "CBaseFunction.h"

class CMassAction: private CBaseFunction
{
  // Attributes
 private:

  // Operations
 public:
  /**
   *  Default constructor
   */
  CMassAction();

  /**
   *  Default constructor
   */
  CMassAction(C_INT16 reversible);

  /**
   *  Default destructor
   */
  ~CMassAction();

  /**
   *  Calculates the value of the function
   *  @param "vector < C_FLOAT64 * >" identifiers
   */
  C_FLOAT64 calcValue(vector < CCallParameter > & callParameters) const;

  /**
   *  Returns the index of an identifier. The index specifies the position in
   *  the identifier vector of the function call CalcValue.
   *  @param "const string" &name
   *  @return C_INT32
   */
  virtual pair < C_INT32, C_INT32 > findIdentifier(const string & name) const;
};

#endif // COPASI_CMassAction
