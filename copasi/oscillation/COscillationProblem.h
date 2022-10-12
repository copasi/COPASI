// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COSCPROBLEM_H
#define COSCPROBLEM_H

#include "copasi/utilities/CCopasiProblem.h"

class COscillationProblem : public CCopasiProblem
{
public:

  /**
   * Default constructor
   * @param const CTaskEnum::Task & type (default: optimization)
   * @param const CDataContainer * pParent (default: NULL)
   */
  COscillationProblem(const CTaskEnum::Task & type = CTaskEnum::oscillation,
                      const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor.
   * @param const COscillationProblem & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COscillationProblem(const COscillationProblem & src,
                      const CDataContainer * pParent);

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
   * Set the call back of the problem
   * @param CProcessReportLevel * pCallBack
   * @result bool success
   */
  virtual bool setCallBack(CProcessReportLevel callBack) override;

  /**
   * Do all necessary initialization so that calls to calculate will
   * be successful. This is called once from CCopasiTask::process()
   * @result bool success
   */
  virtual bool initialize();

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
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
