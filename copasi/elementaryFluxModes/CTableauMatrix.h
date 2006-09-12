/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CTableauMatrix.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/12 20:02:43 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTableauMatrix class.
 *  Used to calculate elementary flux modes
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CTableauMatrix
#define COPASI_CTableauMatrix

#include <list>
#include "CTableauLine.h"

class CTableauMatrix
  {
    // Attributes

  private:
    /**
     *  Vector containing the lines of the Matrix
     *  @associates <{CTableauLine}>
     *  @supplierCardinality 0..*
     */
    std::list< const CTableauLine * > mLine;

    /**
     *  Iterator pointing to the first irreversible reaction
     */
    std::list< const CTableauLine * >::iterator mFirstIrreversible;

    // Operations

  public:
    /**
     *  Default constructor
     */
    CTableauMatrix();

    /**
     *  Specific constructor
     *  The first reversibleNumber lines of stoi must be reversible reactions.
     *  Note: stoi is actually the transpose of the stoichiometry matrix
     *  @param "const vector < vector < double > >" & stoi
     *  @param "C_INT32 " reversibleNumber
     */
    CTableauMatrix(const std::vector < std::vector < double > > & stoi,
                   C_INT32 reversibleNumber);

    /**
     *  Destructor
     */
    ~CTableauMatrix();

    /**
     * Retreive the number of tableau lines
     * @return unsigned C_INT32 size
     */
    unsigned C_INT32 size() const;

    /**
     *  Retrieves the first line from the matrix
     *  @return "list< const CTableauLine * >::iterator" iterator
     */
    std::list< const CTableauLine * >::iterator getFirst();

    /**
     *  Retrieves the last line from the matrix
     *  @return "list< const CTableauLine * >::iterator" iterator
     */
    std::list< const CTableauLine * >::iterator getEnd();

    /**
     *  Add a line to the matrix
     *  @param const CTableauLine * src
     *  @param const bool & check (Default: true)
     */
    void addLine(const CTableauLine * src,
                 const bool & check = true);

    /**
     *  Remove the indexed line of the matrix
     *  @param "list< const CTableauLine * >::const_iterator" line
     */
    void removeLine(std::list< const CTableauLine * >::iterator line);

  private:
    /**
     *  Check whether the new line fullfills the constraints
     *  @param "const CTableauLine *" src
     */
    bool isValid(const CTableauLine * src);
  };

#endif // COPASI_CTableauMatrix
