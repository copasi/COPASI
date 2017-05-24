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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEFMMethod
#define COPASI_CEFMMethod

#include <string>

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/elementaryFluxModes/CFluxMode.h"

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/core/CVector.h"

class CEFMMethod : public CCopasiMethod
{
  // Operations
private:
  /**
   * Default constructor.
   */
  CEFMMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: fluxMode)
   */
  CEFMMethod(const CDataContainer * pParent,
             const CTaskEnum::Method & methodType,
             const CTaskEnum::Task & taskType = CTaskEnum::Task::fluxMode);

  /**
   * Copy constructor
   * @param const CEFMMethod & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CEFMMethod(const CEFMMethod & src,
             const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CEFMMethod();

  /**
   * Execute the optimization algorithm calling simulation routine
   * when needed. It is noted that this procedure can give feedback
   * of its progress by the callback function set with SetCallback.
   * @ return success;
   */
  virtual bool calculate();

  /**
   * Initialize arrays and pointer.
   * @return bool success
   */
  virtual bool initialize();

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  // Attributes
protected:
  /**
   * The resulting elementary flux modes
   */
  std::vector< CFluxMode > *mpFluxModes;

  /**
   * Reactions in the order used in the analysis
   */
  std::vector< const CReaction * > *mpReorderedReactions;
};

#endif  // COPASI_CEFMMethod
