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

using namespace std;

class CTableauMatrix
  {
    // Attributes

  private:
    /**
     *  Vector containing the lines of the Matrix
     *  @associates <{CTableauLine}>
     *  @supplierCardinality 0..*
     */
    list < const CTableauLine * > mLine;

    /**
     *  Iterator pointing to the first irreversible reaction
     */
    list < const CTableauLine * >::iterator mFirstIrreversible;

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
    CTableauMatrix(const vector < vector < double > > & stoi,
                   C_INT32 reversibleNumber);

    /**
     *  Destructor
     */
    ~CTableauMatrix();

    /**
     *  Retrieves the first line from the matrix
     *  @return "list < const CTableauLine * >::iterator" iterator
     */
    list < const CTableauLine * >::iterator getFirst();

    /**
     *  Retrieves the last line from the matrix
     *  @return "list < const CTableauLine * >::iterator" iterator
     */
    list < const CTableauLine * >::iterator getEnd();

    /**
     *  Add a line to the matrix
     *  @param "const CTableauLine *" src
     */
    void addLine(const CTableauLine * src);

    /**
     *  Remove the indexed line of the matrix
     *  @param "list < const CTableauLine * >::const_iterator" line
     */
    void removeLine(list < const CTableauLine * >::iterator line);

  private:
    /**
     *  Check whether the new line fullfills the constraints
     *  @param "const CTableauLine *" src
     */
    bool isValid(const CTableauLine * src);
  };

#endif // COPASI_CTableauMatrix
