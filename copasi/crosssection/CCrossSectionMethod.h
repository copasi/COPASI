// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/crosssection/CCrossSectionMethod.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2010/05/14 22:20:54 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CCROSSSECTIONMETHOD_H
#define CCROSSSECTIONMETHOD_H

#include "utilities/CCopasiMethod.h"

class CCrossSectionProblem;

class CCrossSectionMethod : public CCopasiMethod
{
private:
  /**
   * Default constructor.
   */
  CCrossSectionMethod();

protected:
  /**
   * Specific constructor.
   * @param CCopasiMethod::SubType subType
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  explicit CCrossSectionMethod(CCopasiMethod::SubType subType,
                               const CCopasiContainer * pParent = NULL);

public:
  /**
   * Create a cross section method.
   * Note: the returned object has to be released after use with delete
   */
  static CCrossSectionMethod *
  createCrossSectionMethod(CCopasiMethod::SubType subType
                           = CCopasiMethod::crossSectionMethod);

  /**
   * Copy constructor.
   * @param "const CTSSMethod &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CCrossSectionMethod(const CCrossSectionMethod & src,
                      const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CCrossSectionMethod();

  /**
   */
  bool process(CProcessReport * handler);

  /**
   * initializes the subtask, creates the internal data structures of the method,
   * resizes the result arrays and creates the array annotations
   */
  bool initialize(CCrossSectionProblem* problem);

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);
};

#endif // CCROSSSECTIONMETHOD_H
