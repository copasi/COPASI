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
 *  CEFMAlgorithm class.
 *  Used to calculate elementary flux modes
 *
 *  Created for COPASI by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CEFMAlgorithm
#define COPASI_CEFMAlgorithm

#include <vector>

#include "copasi/core/CMatrix.h"
#include "copasi/elementaryFluxModes/CEFMMethod.h"
#include "copasi/elementaryFluxModes/CFluxMode.h"

#include "copasi/utilities/CCopasiNode.h"

class CTableauMatrix;

class CEFMAlgorithm: public CEFMMethod
{
private:
  class CSpeciesOrderNode : public CCopasiNode< size_t >
  {
  private:
    CSpeciesOrderNode();

  public:
    CSpeciesOrderNode(const CSpeciesOrderNode & src);

    CSpeciesOrderNode(const size_t & index,
                      const CTableauMatrix & matrix);

    ~CSpeciesOrderNode();

    void update(const CTableauMatrix & matrix);

  private:
    std::vector< size_t > mTableauLines;
  };

  /**
   * Default constructor.
   */
  CEFMAlgorithm();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: EFMAlgorithm)
   * @param const CTaskEnum::Task & taskType (default: fluxMode)
   */
  CEFMAlgorithm(const CDataContainer * pParent,
                const CTaskEnum::Method & methodType = CTaskEnum::Method::EFMAlgorithm,
                const CTaskEnum::Task & taskType = CTaskEnum::Task::fluxMode);

  /**
   * Copy Constructor
   * @param const CEFMAlgorithm & src
   */
  CEFMAlgorithm(const CEFMAlgorithm & src,
                const CDataContainer * pParent);

  /**
  *  Destructor
  */
  ~CEFMAlgorithm();

  /**
   * Execute the optimization algorithm calling simulation routine
   * when needed. It is noted that this procedure can give feedback
   * of its progress by the callback function set with SetCallback.
   * @ return success;
   */
  virtual bool calculate();

  /**
   * Do the actual calculation
   */
  void calculateFluxModes();

  virtual bool initialize();

private:
  void initObjects();

  /**
   * Initialize arrays and pointer called by calculate.
   */
  void calculateNextTableau();

  /**
   * Construct the flux modes
   */
  void buildFluxModes();

  /**
   * Find index containing smallest number of combinations
   */
  bool findMinimalCombinationIndex();

  /**
   * Calculate number of combinations for an index
   */
  double calculateCombinations(size_t index);

  // Attributes
protected:
  /**
   * A pointer to the model
   */
  const CModel * mpModel;

  /**
   * Matrix containing the reordered stoichiometry matrix.
   */
  std::vector< std::vector< C_FLOAT64 > > mStoi;

  /**
   * The number of reversible reactions.
   */
  size_t mReversible;

  /**
   * A pointer to the current tableau matrix
   */
  CTableauMatrix * mpCurrentTableau;

  /**
   * A pointer to the next tableaun matrix
   */
  CTableauMatrix * mpNextTableau;

  /**
   * The current step used for process report.
   */
  unsigned C_INT32 mStep;

  /**
   * The current step used for process report.
   */
  unsigned C_INT32 mStepProcess;

  /**
   * The max step used for process report.
   */
  unsigned C_INT32 mMaxStep;

  /**
   * Handle to the process report item "Current Step"
   */
  size_t mhSteps;

  /**
   * Vector set containing all step indexes for iteration when calculating flux modes.
   */
  std::vector<size_t> mIndexSet;
};

#endif // COPASI_CEFMAlgorithm
