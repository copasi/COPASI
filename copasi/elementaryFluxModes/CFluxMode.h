/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CFluxMode.h,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: shoops $
   $Date: 2011/03/07 19:27:36 $
   End CVS Header */

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CFluxMode class.
 *  Used to return the flux modes in human readable form
 *
 *  Created for Copasi by Stefan Hoops 2002-05-10
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CFluxMode
#define COPASI_CFluxMode

#include <map>

class CReaction;
class CModel;
class CTableauLine;

class CFluxMode
{
public:
  typedef std::map< size_t, C_FLOAT64 >::const_iterator const_iterator;

  // Attributes
private:
  /**
   *  Vector containing an index to a reaction and the multiplier
   *  for that reaction.
   */
  std::map< size_t, C_FLOAT64 > mReactions;

  /**
   *  Reversibility of the mode.
   */
  bool mReversible;

  // Operations

public:
  /**
   *  Default constructor
   */
  CFluxMode();

  /**
   *  Copy constructor
   *  @param "const CFluxMode &" src
   */
  CFluxMode(const CFluxMode & src);

  /**
   * Specific constructor
   * @param const std::map< size_t, C_FLOAT64 > & reactions
   * @param const bool & reversible
   */
  CFluxMode(const std::map< size_t, C_FLOAT64 > & reactions,
            const bool & reversible);

  /**
   *  Specific constructor
   *  @param "const CTableauLine &" line
   */
  CFluxMode(const CTableauLine * line);

  /**
   *  Destructor
   */
  ~CFluxMode();

  /**
   * Retrieve the iterator to the first element of the flux mode
   * @return CFluxMode::const_iterator begin;
   */
  const_iterator begin() const;

  /**
   * Retrieve the iterator pointing beyond the last element of the flux mode
   * @return CFluxMode::const_iterator end;
   */
  const_iterator end() const;

  /**
   *  Check whether the mode is reversible
   *  @return "bool" isReversible
   */
  bool isReversible() const;

  /**
   *  Retrieves the size of the mode
   *  @return "size_t" size
   */
  size_t size() const;

  /**
   * Determine whether the current mode is the reversed mode
   * @param const CFluxMode &mode
   * @return bool isReversed
   */
  bool isReversed(const CFluxMode &mode);

  /**
   * Retrieve the multiplier for the indexed reaction
   * @param const size_t & index
   * @return C_FLOAT64 multiplier
   */
  C_FLOAT64 getMultiplier(const size_t & index) const;
};

#endif // COPASI_CFluxMode
