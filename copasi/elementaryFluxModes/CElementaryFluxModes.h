/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/Attic/CElementaryFluxModes.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:54 $
   End CVS Header */

/**
 *  CElementaryFluxModes class.
 *  Main class to calculate elementary flux modes.
 *  This is the adapter to the rest of COPASI
 *
 *  Created for Copasi by Stefan Hoops 2002-05-09
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CElementaryFluxModes
#define COPASI_CElementaryFluxModes

#include <iostream>
#include <vector>

#include "model/CModel.h"
#include "model/CReaction.h"

// #include "CEFMAlgorithm.h"
#include "CFluxMode.h"

class CEFMAlgorithm;

class CElementaryFluxModes
  {
    // Attributes

  private:
    /**
     *  The resulting elementary flux modes
     * @supplierCardinality 0..*
     */
    std::vector< CFluxMode > mFluxModes;

    /**
     *  Vector to keep track of the rearangements neccessary to put the
     *  reversible reactions to the top of Stoi
     */
    std::vector< unsigned C_INT32 > mIndex;

    /**
     *  The COPASI model we are acting on.
     */
    const CModel *mModel;

    /** @link dependency */
    /*#  CEFMAlgorithm lnkCEFMAlgorithm; */
    //Operations

  public:
    /**
     *  Default constructor
     */
    CElementaryFluxModes();

    /**
     *  Destructor
     */
    ~CElementaryFluxModes();

    /**
     *  calculate
     *  @param "const CModel *" model
     */
    void calculate(const CModel * model);

    /**
     * Check the reversibility of the indexed Flux Mode
     * @param unsigned C_INT32 index
     * @return bool
     */ // should not be used
    bool isFluxModeReversible(unsigned C_INT32 index) const;

    /**
     * Retrieve the number of Flux Modes
     * @return unsigned C_INT32 size
     */
    unsigned C_INT32 getFluxModeSize() const;

    /**
     * Get one of the flux modes
     * @param unsigned C_INT32 index
     * @return reference to flux mode
     */ 
    //const CFluxMode & getFluxMode(unsigned C_INT32 index) const;

    /**
     * Retrieve the description of the indexed Flux Mode
     * @param unsigned C_INT32 index
     * @return std::string description
     */
    std::string getFluxModeDescription(unsigned C_INT32 index) const;

    unsigned C_INT32 getFluxModeSize(unsigned C_INT32 index) const;

    std::string getReactionEquation(unsigned C_INT32 index1,
                                    unsigned C_INT32 index2,
                                    const CModel * model) const;

    // Friend functions
    friend std::ostream &operator<<(std::ostream &os, const CElementaryFluxModes &A);
  };

#endif //COPASI_CElementaryFluxModes
