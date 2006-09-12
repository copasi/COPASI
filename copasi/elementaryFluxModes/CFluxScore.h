/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CFluxScore.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/12 17:10:22 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CFluxScore class.
 *  Used to compare flux modes
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CFluxScore
#define COPASI_CFluxScore

#include <vector>

#include "utilities/CVector.h"

class CFluxScore
  {
    // Attributes

  private:
    /**
     *  The score of a flux mode
     */
    CVector< unsigned C_INT32 > mScore;

    // Operations

  public:
    /**
     *  Default constructor
     */
    CFluxScore();

    /**
     *  Specific constructor
     *  @param "const vector < C_FLOAT64 > &" fluxModes
     */
    CFluxScore(const std::vector < C_FLOAT64 > & fluxModes);

    /**
     *  Destructor();
     */
    ~CFluxScore();

    /**
     *  Comparison operator deciding whether lhs has a smaller flux score than
     *  rhs
     *  @param "const CFluxScore &" lhs
     *  @param "const CFluxScore &" rhs
     *  @return "bool"
     */
    bool operator < (const CFluxScore & rhs) const;
  };

#endif // COPASI_CFluxScore
