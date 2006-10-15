/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CTableauLine.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 07:04:06 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
#include "elementaryFluxModes/CFluxScore.h"

class CTableauLine
  {
    // Attributes

  private:
    /**
     *
     */
    std::vector <C_FLOAT64> mReaction;

    /**
     *
     */
    bool mReversible;

    /**
     *
     */
    std::vector <C_FLOAT64> mFluxMode;

    /**
     *
     */
    CFluxScore *mpFluxScore;

    // Operations

  public:
    /**
     *  Default constructor
     */
    CTableauLine();

    /**
     *  Specific constructor
     */
    CTableauLine(const std::vector <C_FLOAT64> & reaction,
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
     * Retreive the multiplier for this reaction
     */
    const C_FLOAT64 & getMultiplier() const;

    /**
     *  Retreives the flux mode
     */
    const std::vector < C_FLOAT64 > & getFluxMode() const;

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
