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

#include "utilities/utilities.h"
#include "model/model.h"

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
     * @param const unsigned C_INT32 & index
     * @return bool
     */
    bool isFluxModeReversible(const unsigned C_INT32 & index) const;

    /**
     * Retrieve the description of the indexed Flux Mode
     * @param const unsigned C_INT32 & index
     * @return std::string description
     */
    std::string getFluxModeDescription(const unsigned C_INT32 & index) const;

    /**
     * Retrieve the number of Flux Modes
     * @return unsigned C_INT32 size
     */
    unsigned C_INT32 getFluxModeSize() const;

    // Friend functions
    friend std::ostream &operator<<(std::ostream &os, const CElementaryFluxModes &A)
    {
      /* Get the reactions from the model */
      const CCopasiVectorNS < CReaction > & Reaction = A.mModel->getReactions();

      unsigned C_INT32 i, imax = A.mFluxModes.size();
      unsigned C_INT32 j, jmax;

      os << "Elementary Flux Modes of Model \""
      << A.mModel->getTitle() << "\":" << std::endl;

      for (i = 0; i < imax; i++)
        {
          os << " Mode " << i + 1 << ":  ";

          if (A.mFluxModes[i].isReversible())
            os << "(reversible)";
          else
            os << "(irreversible)";

          os << std::endl;

          jmax = A.mFluxModes[i].size();

          for (j = 0; j < jmax; j++)
            {
              os << "   " << A.mFluxModes[i].getMultiplier(j) << " * "
              << Reaction[A.mIndex[A.mFluxModes[i].getReaction(j)]]
              ->getName()
              << std::endl;
            }

          os << std::endl;
        }

      return os;
    }
  };

#endif //COPASI_CElementaryFluxModes
