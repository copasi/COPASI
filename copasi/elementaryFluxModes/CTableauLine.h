/**
 *  CTableauLine class.
 *  This store one row of the Tableau Matrix
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CTableauLine
#define COPASI_CTableauLine

#include <vector>
#include "CFluxScore.h"

using std::vector;

class CTableauLine
  {
    // Attributes

  private:
    /**
     *  
     */
    vector <double> mReaction;

    /**
     *  
     */
    bool mReversible;

    /**
     *  
     */
    vector <double> mFluxMode;

    /**
     *  
     */
    CFluxScore *mFluxScore;

    // Operations

  public:
    /**
     *  Default constructor
     */
    CTableauLine();

    /**
     *  Specific constructor
     */
    CTableauLine(const vector <C_FLOAT64> & reaction,
                 bool reversible,
                 const C_INT32 & reactionCounter,
                 const C_INT32 & reactionNumber);

    /**
     *  Specific constructor
     */
    CTableauLine(const C_FLOAT64 & m1,
                 const CTableauLine & src1,
                 const C_FLOAT64 & m2,
                 const CTableauLine & src2);

    /**
     *  Destructor
     */
    ~CTableauLine();

    /**
     *  Retreives the flux score
     */
    const CFluxScore & getScore() const;

    /**
     *  Retreives the "index" coefficient of the reaction
     *  @param "const unsigned C_INT32 &" index
     */
    const C_FLOAT64 & getReaction(const unsigned C_INT32 & index) const;

    /**
     *  Retreives the flux mode
     */
    const vector < C_FLOAT64 > & getFluxMode() const;

    /**
     *  Checks whether the reaction is reversible
     *  @return "bool" isReversible
     */
    bool isReversible() const;

    /**
     *  Remove the first entry from the reaction vector
     */
    void truncate();
  };

#endif // COPASI_CTableauLine
