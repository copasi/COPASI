// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CMCAProblem class.
 *  This class describes the metabolic control analysis problem, i.e., it allows to specify
 *  for example initial conditions.
 *
 *  Created for Copasi by Ralph Gauges 2004
 */

#ifndef COPASI_CMCAProblem_H__
#define COPASI_CMCAProblem_H__

#include <string>

#include "copasi/model/CState.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CReadConfig.h"

class CSteadyStateTask;

class CMCAProblem: public CCopasiProblem
{
public:
  // Operations

  /**
   * Default constructor.
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMCAProblem(const CDataContainer * pParent = NO_PARENT);

  /**
   *  Copy constructor.
   *  @param "const CMCAProblem &" src
   * @paramconst CDataContainer * pParent (default: NULL)
   */
  CMCAProblem(const CMCAProblem & src,
              const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  virtual ~CMCAProblem();

  /**
   * Set whether the steady state analysis is requested.
   * @param const bool & steadyStateRequested
   */
  void setSteadyStateRequested(const bool & steadyStateRequested);

  /**
   * Retrieve whether a steady state analysis is requested.
   * @return bool steadyStateRequested
   */
  bool isSteadyStateRequested() const;

  /**
   * Retrieve the subtask
   * return CCopasiTask * pSubTask;
   */
  virtual CCopasiTask * getSubTask() const override;

  /**
   * Load a trajectory problem
   * @param "CReadConfig &" configBuffer
   * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
   */
  void load(CReadConfig & configBuffer,
            CReadConfig::Mode mode = CReadConfig::NEXT);

  /**
   * This is the output method for any result of a problem. The default implementation
   * is provided with CCopasiProblem. Does only print "Not implmented." To overide this
   * default behaviour one needs to reimplement the virtual printResult function.
   * @param std::ostream * ostream
   */
  virtual void printResult(std::ostream * ostream) const override;

  /**
   * Output stream operator. Prints description of the problem incl. the subtask
   * @param ostream & os
   * @param const CMCAProblem & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const CMCAProblem & o);

  /**
   * This is the output method for any object. It calls the insert operator<<
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const override;

private:
};
#endif /* CMCAProblem_H__ */
