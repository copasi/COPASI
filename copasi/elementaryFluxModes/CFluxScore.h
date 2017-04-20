// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/core/CVector.h"

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
