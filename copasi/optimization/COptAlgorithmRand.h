/***************************************************************************
                         COptAlgorithmRand.h  -  Random Optimizer
                            -------------------

   Programmer           : Rohan Luktuke
   email                : rluktuke@vt.edu
 ***************************************************************************/

/***************************************************************************
 * This is the implementation of the Random Algorithm for Optimization.  The
 * class is inherited from the COptAlgorithm class.                         *
 ***************************************************************************/

#include "COptAlgorithm.h"
#include "randomGenerator/CRandom.h"

class COptAlgorithmRand : public COptAlgorithm
  {
  private:
    /**
     * Pointer to CRandom object
     */
    CRandom *rand;

  public:
    /**
     * default constructor
     */
    COptAlgorithmRand();

    /**
     * copy constructor
     */
    COptAlgorithmRand(const COptAlgorithmRand & source);

    /**
     * overloaded assignment operator
     */
    COptAlgorithmRand& operator=(const COptAlgorithmRand & source);

    /**
     * destructor
     */
    ~COptAlgorithmRand();

    /**
     * optimize function
     */
    int optimise();
  };
