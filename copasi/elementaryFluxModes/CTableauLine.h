// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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
 *  CTableauLine class.
 *  This store one row of the Tableau Matrix
 *
 *  Created for COPASI by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CTableauLine
#define COPASI_CTableauLine

#include <vector>
#include "copasi/elementaryFluxModes/CFluxScore.h"

class CTableauLine
{
  friend std::ostream & operator << (std::ostream &, const CTableauLine &);
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
               const size_t & reactionCounter,
               const size_t & reactionNumber);

  /**
   *  Specific constructor
   */
  CTableauLine(C_FLOAT64 m1,
               const CTableauLine & src1,
               C_FLOAT64 m2,
               const CTableauLine & src2);

  /**
   *  Destructor
   */
  ~CTableauLine();

  /**
   *  Retrieves the flux score
   */
  const CFluxScore & getScore() const;

  /**
   * Retrieve the multiplier for this reaction for the indexed species
   * @param const size_t & index
   * @return const C_FLOAT64 & multiplier
   */
  const C_FLOAT64 & getMultiplier(const size_t & index) const;

  /**
   *  Retrieves the flux mode
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
  // void truncate();

private:
  /**
   * Divides m1 and m2 by the largest common factor.
   */
  static void reduce(C_FLOAT64 & r1, C_FLOAT64 & r2);
};

#endif // COPASI_CTableauLine
