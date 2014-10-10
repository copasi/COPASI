// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "model/CState.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h"

class CSteadyStateTask;

class CLNAProblem: public CCopasiProblem
{
  // Attributes
private:
  /**
   *  The initial state, i.e., at which the LNA is calculated.
   */
  CState mInitialState;

public:
  // Operations

  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CLNAProblem(const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor.
   * @param "const CLNAProblem &" src
   * @paramconst CCopasiContainer * pParent (default: NULL)
   */
  CLNAProblem(const CLNAProblem & src,
              const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  virtual ~CLNAProblem();

  /**
   * Set the initial state of the problem.
   * @param const CState & InitialState
   */
  void setInitialState(const CState & initialState);

  /**
   * Retrieve the initial state of the problem.
   * @return "const CState &" pInitialState
   */
  //const CState & getInitialState() const;

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
   * return CSteadyStateTask * pSubTask;
   */
  CSteadyStateTask * getSubTask() const;

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
  virtual void printResult(std::ostream * ostream) const;

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
  virtual void print(std::ostream * ostream) const;

private:
};
#endif /* COPASI_CLNAProblem_H__ */
