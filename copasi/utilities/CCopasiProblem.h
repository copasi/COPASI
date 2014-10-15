// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiProblem class.
 *  This class is used to describe a problem in COPASI. This class is
 *  intended to be used as the parent class for all problems whithin COPASI.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiProblem
#define COPASI_CCopasiProblem

#include <string>

#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CVector.h"
#include "utilities/CCopasiTask.h"
//#include "model/CState.h"

class CMathContainer;
class CProcessReport;
class CReport;

class CCopasiProblem : public CCopasiParameterGroup
{
  // Operations
private:
  /**
   * Default constructor
   */
  CCopasiProblem();

protected:
  /**
   * Specific constructor
   * @param const CTaskEnum::Task & type
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CCopasiProblem(const CTaskEnum::Task & type,
                 const CCopasiContainer * pParent = NULL);

public:
  /**
   * Copy constructor
   * @param const CCopasiProblemr & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CCopasiProblem(const CCopasiProblem & src,
                 const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CCopasiProblem();

  /**
   * Retrieve the type of the problem
   * @return  const string & type
   */
  const CTaskEnum::Task & getType() const;

  /**
   * Set the model of the problem
   * @param CMathContainer * pContainer
   * @result bool success
   */
  void setMathContainer(CMathContainer * pContainer);

  /**
   * Retrieve the model of the problem
   * @result CMathContainer * pContainer
   */
  CMathContainer * getMathContainer() const;

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
   * Do all necessary restore procedures so that the
   * model is in the same state as before
   * @param const bool & updateModel
   * @result bool success
   */
  virtual bool restore(const bool & updateModel);

  /**
   * calculate function for optimization
   * @result bool fulfilled
   */
  // virtual bool checkParametricConstraints();

  /**
   * calculate function for optimization
   * @result bool fulfilled
   */
  // virtual bool checkFunctionalConstraints();

  /**
   * This is the output method for any object. The default implementation
   * provided with CCopasiObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * re-implement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const;

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CCopasiProblem & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const CCopasiProblem & o);

  /**
   * This is the output method for any result of a problem. The default implementation
   * provided with CCopasiProblem. Does only print "Not implemented." To override this
   * default behavior one needs to re-implement the virtual printResult function.
   * @param std::ostream * ostream
   */
  virtual void printResult(std::ostream * ostream) const;

protected:
  /**
   * Signal that the math container has changed
   */
  virtual void signalMathContainerChanged();

  // Attributes
private:
  /**
   * The type of the problem
   */
  CTaskEnum::Task mType;

protected:
  /**
   * The model of the problem
   */
  CMathContainer * mpContainer;

  /**
   * a pointer to the callback
   */
  CProcessReport * mpCallBack;

  /**
   * A pointer to the report
   */
  CReport * mpReport;
};

#endif // COPASI_CCopasiProblem
