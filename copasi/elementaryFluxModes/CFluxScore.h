// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CFluxScore.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/15 17:27:11 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
    CVector< unsigned char > mScore;

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

    friend std::ostream & operator << (std::ostream & os, const CFluxScore & A);
  };

#endif // COPASI_CFluxScore
