/**
 *  CEFMAlgorithm class.
 *  Used to calculate elementary flux modes
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CEFMAlgorithm
#define COPASI_CEFMAlgorithm

#include "CTableauMatrix.h"
#include "CFluxMode.h"

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
  bool calculate(const vector < vector < C_FLOAT64 > > & stoi,
                 const unsigned C_INT32 & reversibleNumber,
                 vector < CFluxMode > & fluxModes);

 private:
  void calculateNextTableau(const unsigned C_INT32 & step);
  void buildFluxModes(vector < CFluxMode > & fluxModes,
                      const unsigned C_INT32 reactionNumber);
};
#endif // COPASI_CEFMAlgorithm
