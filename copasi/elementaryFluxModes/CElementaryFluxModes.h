/**
 *  CElementaryFluxModes class.
 *  Main class to calculate elementary flux modes.
 *  This is the adapter to the rest of COPASI
 *
 *  Created for Copasi by Stefan Hoops 2002-05-09
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CElementaryFluxModes
#define COPASI_CElementaryFluxModes

#include "CEFMAlgorithm.h"
class CModel;
class CElementaryFluxModes
{
  // Attributes
 private:  
  /**
   *  The resulting elementary flux modes
   */
  vector < vector <unsigned C_INT32> > mFluxModes;

  /**
   *  Vector to keep track of the rearangements neccessary to put the
   *  reversible reactions to the top of Stoi.
   */
  unsigned C_INT32 mReversible;
  
  /**
   *  Vector to keep track of the rearangements neccessary to put the
   *  reversible reactions to the top of Stoi
   */
  vector < unsigned C_INT32 > mIndex;

  /**
   *  The COPASI model we are acting on.
   */
  const CModel *mModel;

  //Operations
 public:    
  /**
   *  Default constructor
   */
  CElementaryFluxModes();
  
  /**
   *  Destructor
   */
  ~CElementaryFluxModes();

  /**
   *  calculate
   *  @param "const CModel *" model
   */
  void calculate(const CModel * model);
  
  /**
   *  Write the result
   *  @param "ostream &" output
   */
  void write(ostream & output) const;
};
#endif //COPASI_CElementaryFluxModes
