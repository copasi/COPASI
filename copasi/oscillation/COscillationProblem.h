// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/oscillation/COscillationProblem.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/11/11 16:47:54 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COSCPROBLEM_H
#define COSCPROBLEM_H

#include "utilities/CCopasiProblem.h"

class COscillationProblem : public CCopasiProblem
  {
  public:

    /**
     * Default constructor
     * @param const CCopasiTask::Type & type (default: optimization)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COscillationProblem(const CCopasiTask::Type & type = CCopasiTask::oscillation,
                        const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const COscillationProblem & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COscillationProblem(const COscillationProblem & src,
                        const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COscillationProblem();

    /**
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    /**
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool success
     */
    virtual bool setModel(CModel * pModel);

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
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To override this default behavior one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

    /**
     * Output stream operator
     * @param ostream & os
     * @param const COscillationProblem & A
     * @return ostream & os
     */
    friend std::ostream &operator<<(std::ostream &os, const COscillationProblem & o);

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

  protected:
  };

#endif  // the end
