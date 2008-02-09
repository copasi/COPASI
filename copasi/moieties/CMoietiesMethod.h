// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/CMoietiesMethod.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/09 00:58:16 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMoietiesMethod
#define COPASI_CMoietiesMethod

#include "copasi/utilities/CCopasiMethod.h"

class CProcessReport;

class CMoietiesMethod : public CCopasiMethod
  {
  private:
    /**
     * Default constructor
     */
    CMoietiesMethod();

  protected:
    /**
     * Specific constructor
     * @param const CCopasiTask::Type & type
     * @param const CCopasiMethod::SubType & subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMoietiesMethod(const CCopasiTask::Type & taskType,
                    const SubType & subType,
                    const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a trajectory method for a special problem.
     * Note: the returned object has to be released after use with delete
     * a problem is also passed so that the method has a chance to choose an
     * appropriate simulation method.
     * @param const CCopasiMethod::SubType & subType (default: CCopasiMethod::Householder)
     * @return CMoietiesMethod *
     */
    static
    CMoietiesMethod * createMethod(const CCopasiMethod::SubType & subType = CCopasiMethod::Householder);

    /**
     * Copy constructor
     * @param const CMoietiesMethod & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMoietiesMethod(const CMoietiesMethod & src,
                    const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CMoietiesMethod();

    /**
     * Set the call back of the problem
     * @param CProcessReport * pCallBack
     * @result bool succes
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;
  };

#endif // COPASI_CMoietiesMethod
