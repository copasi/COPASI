/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMProblem.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2010/02/03 17:18:42 $
   End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  File name: CEFMProblem.h
 *
 *  Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the header file of the CEFMProblem class.
 *           It specifies the optimization problem with its own members and
 *           functions. It's used by CEFMAlgorithm class and CEFMimization class
 */

#ifndef COPASI_CEFMProblem
#define COPASI_CEFMProblem

#include <vector>

#include "utilities/CCopasiProblem.h"

class CFluxMode;
class CReaction;

/** @dia:pos -4.4,4.15 */
class CEFMProblem : public CCopasiProblem
{
  // Implementation

public:

  /**
   * Default constructor
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CEFMProblem(const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor.
   * @param const CEFMProblem & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CEFMProblem(const CEFMProblem & src,
              const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CEFMProblem();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * Set the call back of the problem
   * @param CProcessReport * pCallBack
   * @result bool success
   */
  virtual bool setCallBack(CProcessReport * pCallBack);

  /**
   * Do all necessary initialization so that calls to calculate will
   * be successful. This is called once from CCopasiTask::process()
   * @result bool success
   */
  virtual bool initialize();

  /**
   * Return the flux modes after a successful analysis.
   * @return const std::vector< CFluxMode > & fluxModes
   */
  const std::vector< CFluxMode > & getFluxModes() const;

  /**
   * Return the flux modes after a successful analysis.
   * @return std::vector< CFluxMode > & fluxModes
   */
  std::vector< CFluxMode > & getFluxModes();

  /**
   * Return the reactions in the order they are used in the flux modes
   * @return const std::vector< const CReaction * > & reorderedReactions
   */
  const std::vector< const CReaction * > & getReorderedReactions() const;

  /**
   * Return the reactions in the order they are used in the flux modes
   * @return std::vector< const CReaction * > & reorderedReactions
   */
  std::vector< const CReaction * > & getReorderedReactions();

  /**
   * This is the output method for any result of a problem. The default implementation
   * provided with CCopasiProblem. Does only print "Not implemented." To override this
   * default behavior one needs to reimplement the virtual printResult function.
   * @param std::ostream * ostream
   */
  virtual void printResult(std::ostream * ostream) const;

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

  void initObjects();

  // Attributes
protected:
  /**
   * The resulting elementary flux modes
   */
  std::vector< CFluxMode > mFluxModes;

  /**
   * Reactions in the order used in the analysis
   */
  std::vector< const CReaction * > mReorderedReactions;
};

#endif  // COPASI_CEFMProblem
