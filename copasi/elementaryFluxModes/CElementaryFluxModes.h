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

#include <iostream>

#include "utilities/utilities.h"
#include "model/model.h"

#include "CEFMAlgorithm.h"
#include "CFluxMode.h"

class CElementaryFluxModes
{
  // Attributes
 private:  
  /**
   *  The resulting elementary flux modes
   * @supplierCardinality 0..*
   */
  vector < CFluxMode > mFluxModes;

  /**
   *  Vector to keep track of the rearangements neccessary to put the
   *  reversible reactions to the top of Stoi
   */
  vector < unsigned C_INT32 > mIndex;

  /**
   *  The COPASI model we are acting on.
   */
  const CModel *mModel;

  /** @link dependency */
  /*#  CEFMAlgorithm lnkCEFMAlgorithm; */
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

  // Friend functions
  friend ostream &operator<<(ostream &os, CElementaryFluxModes &A)
    {
      /* Get the reactions from the model */
      const CCopasiVectorS < CReaction > & Reaction = A.mModel->getReactions();

      unsigned C_INT32 i, imax = A.mFluxModes.size();
      unsigned C_INT32 j, jmax;

      os << "Elementary Flux Modes of Model \"" 
         << A.mModel->getTitle() << "\":" << endl;
  
      for (i=0; i<imax; i++)
        {
          os << " Mode " << i+1 << ":  ";
          if (A.mFluxModes[i].isReversible())
            os << "(reversible)";
          else
            os << "(irreversible)";
          os << endl;

          jmax = A.mFluxModes[i].size();
          for (j=0; j<jmax; j++)
            {
              os << "   " << A.mFluxModes[i].getMultiplier(j) << " * " 
                 << Reaction[A.mIndex[A.mFluxModes[i].getReaction(j)]]
                             ->getName()
                 << endl;
            }
          
          os << endl;
        }
      return os;
    }
};
#endif //COPASI_CElementaryFluxModes
