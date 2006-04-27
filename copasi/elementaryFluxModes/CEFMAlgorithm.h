/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMAlgorithm.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:28:09 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CEFMAlgorithm class.
 *  Used to calculate elementary flux modes
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CEFMAlgorithm
#define COPASI_CEFMAlgorithm

#include "CFluxMode.h"

class CTableauMatrix;

class CEFMAlgorithm
  {
    // Attributes

  private:
    /**
     *  @supplierCardinality 0..1
     */
    CTableauMatrix * mCurrentTableau;

    /**
     *  @supplierCardinality 0..1
     */
    CTableauMatrix * mNextTableau;

    /** @link dependency */
    /*#  CFluxMode lnkCFluxMode; */
    // Operations

  public:
    /**
     *  Default constructor
     */
    CEFMAlgorithm();

    /**
     *  Destructor
     */
    ~CEFMAlgorithm();

    /**
     *  Calculates the elementary flux modes
     *  The first reversibleNumber lines of stoi must be reversible reactions.
     *  Note: stoi is actually the transpose of the stoichiometry matrix
     *  @param "const vector < vector < double > >" & stoi
     *  @param "C_INT32 " reversibleNumber
     *  @param "vector < vector < C_INT32 > > &" fluxModes
     *  @return "bool" success
     */
    bool calculate(const std::vector < std::vector < C_FLOAT64 > > & stoi,
                   const unsigned C_INT32 & reversibleNumber,
                   std::vector < CFluxMode > & fluxModes);

  private:
    void calculateNextTableau();
    void buildFluxModes(std::vector < CFluxMode > & fluxModes);
  };

#endif // COPASI_CEFMAlgorithm
