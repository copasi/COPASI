/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMProblem.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/30 17:12:41 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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

#include "utilities/CCopasiProblem.h"

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
     * @paramconst CCopasiContainer * pParent (default: NULL)
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
     * @result bool succes
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

    /**
     * Do all neccessary initialization so that calls to caluclate will
     * be successful. This is called once from CCopasiTask::process()
     * @result bool succes
     */
    virtual bool initialize();

    /**
     * This is the output method for any rsult of a problem. The default implementation
     * provided with CCopasiProblem. Does only print "Not implmented." To overide this
     * default behaviour one needs to reimplement the virtual printResult function.
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
  };

#endif  // COPASI_CEFMProblem
