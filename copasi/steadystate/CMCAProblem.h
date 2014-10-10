// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "model/CState.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h"

class CSteadyStateTask;

class CMCAProblem: public CCopasiProblem
{
  // Attributes
private:
  /**
   *  The initial state, i.e., the starting conditions of the trajectroy.
   */
  CState mInitialState;

public:
  // Operations

  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CMCAProblem(const CCopasiContainer * pParent = NULL);

  /**
   *  Copy constructor.
   *  @param "const CMCAProblem &" src
   * @paramconst CCopasiContainer * pParent (default: NULL)
   */
  CMCAProblem(const CMCAProblem & src,
              const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  virtual ~CMCAProblem();

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
  virtual void printResult(std::ostream * ostream) const;

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
  virtual void print(std::ostream * ostream) const;

private:
};
#endif /* CMCAProblem_H__ */
