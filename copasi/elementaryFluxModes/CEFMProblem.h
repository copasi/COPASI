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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/utilities/CCopasiProblem.h"

class CFluxMode;
class CReaction;

/** @dia:pos -4.4,4.15 */
class CEFMProblem : public CCopasiProblem
{
  // Implementation

public:

  /**
   * Default constructor
   * @param const CDataContainer * pParent (default: NULL)
   */
  CEFMProblem(const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor.
   * @param const CEFMProblem & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CEFMProblem(const CEFMProblem & src,
              const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CEFMProblem();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren() override;

  /**
   * Set the call back of the problem
   * @param CProcessReport * pCallBack
   * @result bool success
   */
  virtual bool setCallBack(CProcessReportLevel callBack) override;

  /**
   * Do all necessary initialization so that calls to calculate will
   * be successful. This is called once from CCopasiTask::process()
   * @result bool success
   */
  virtual bool initialize() override;

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
  virtual void printResult(std::ostream * ostream) const override;

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
