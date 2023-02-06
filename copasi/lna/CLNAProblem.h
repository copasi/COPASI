// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 *  CLNAProblem class.
 *  This class describes the LNA analysis problem.
 *
 *  Created for Copasi by Juergen Pahle 2010
 */

#ifndef COPASI_CLNAProblem_H__
#define COPASI_CLNAProblem_H__

#include <string>

#include "copasi/model/CState.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CReadConfig.h"

class CSteadyStateTask;

class CLNAProblem: public CCopasiProblem
{
public:
  // Operations

  /**
   * Default constructor.
   * @param const CDataContainer * pParent (default: NULL)
   */
  CLNAProblem(const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor.
   * @param "const CLNAProblem &" src
   * @paramconst CDataContainer * pParent (default: NULL)
   */
  CLNAProblem(const CLNAProblem & src,
              const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  virtual ~CLNAProblem();

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
   * Load a LNA problem
   * @param "CReadConfig &" configBuffer
   * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
   */
  void load(CReadConfig & configBuffer,
            CReadConfig::Mode mode = CReadConfig::NEXT);

  /**
   * This is the output method for any result of a problem. The default implementation
   * is provided with CCopasiProblem. Does only print "Not implemented." To overide this
   * default behaviour one needs to reimplement the virtual printResult function.
   * @param std::ostream * ostream
   */
  virtual void printResult(std::ostream * ostream) const override;

  /**
   * Output stream operator. Prints description of the problem incl. the subtask
   * @param ostream & os
   * @param const CLNAProblem & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const CLNAProblem & o);

  /**
   * This is the output method for any object. It calls the insert operator<<
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const override;

private:
};
#endif /* COPASI_CLNAProblem_H__ */
