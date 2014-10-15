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
 *  CCopasiMethod class.
 *  This class is used to describe a method in COPASI. This class is
 *  intended to be used as the parent class for all methods within COPASI.
 *
 *  Created for COPASI by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiMethod
#define COPASI_CCopasiMethod

#include <string>

#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CReadConfig.h"

class CProcessReport;
class CMathContainer;

class CCopasiMethod : public CCopasiParameterGroup
{
public:
private:
  /**
   * Default constructor
   */
  CCopasiMethod();

protected:
  /**
   * Specific constructor
   * @param const CCopasiContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType
   */
  CCopasiMethod(const CCopasiContainer * pParent,
                const CTaskEnum::Method & methodType,
                const CTaskEnum::Task & taskType);

public:
  /**
   * Convenience method to create and actual instance
   * @param const CCopasiContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType
   */
  static CCopasiMethod * createMethod(const CCopasiContainer * pParent,
                                      const CTaskEnum::Method & methodType,
                                      const CTaskEnum::Task & taskType);

  /**
   * Copy constructor
   * @param const CCopasiMethodr & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CCopasiMethod(const CCopasiMethod & src,
                const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CCopasiMethod();

  /**
   * Set the model of the problem
   * @param CMathContainer * pContainer
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
   * @result bool succes
   */
  virtual bool setCallBack(CProcessReport * pCallBack);

  /**
   * Retrieve the type of the method
   * @return  const string & type
   */
  const CTaskEnum::Task & getType() const;

  /**
   * Retrieve the sub type of the method
   * @return CTaskEnum::Method & subType
   */
  const CTaskEnum::Method & getSubType() const;

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  /**
   * Load a list of parameters
   * @param "CReadConfig &" configBuffer
   * @param "CReadConfig::Mode" mode Default(CReadConfig::SEARCH)
   */
  virtual void load(CReadConfig & configBuffer,
                    CReadConfig::Mode mode = CReadConfig::SEARCH);

  /**
   * This is the output method for any object. The default implementation
   * provided with CCopasiObject uses the ostream operator<< of the object
   * to print the object.To overide this default behaviour one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const;

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CCopasiMethod & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const CCopasiMethod & o);

  /**
   *  This is the output method for any result of a method. The default implementation
   *  provided with CCopasiMethod. Does only print "Not implmented." To overide this
   *  default behaviour one needs to reimplement the virtual printResult function.
   *  @param std::ostream * ostream
   **/

  virtual void printResult(std::ostream * ostream) const;

protected:
  /**
   * Signal that the math container has changed
   */
  virtual void signalMathContainerChanged();

  // Attributes
private:
  /**
   * The type of the method
   */
  CTaskEnum::Task mTaskType;

  /**
   * The type of the method
   */
  CTaskEnum::Method mSubType;

protected:
  /**
   * The model of the problem
   */
  CMathContainer * mpContainer;

  /**
   * a pointer to the callback
   */
  CProcessReport * mpCallBack;
};

#endif // COPASI_CCopasiMethod
