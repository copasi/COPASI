// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/crosssection/CCrossSectionProblem.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2010/05/24 12:45:49 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CCROSSSECTIONPROBLEM_H
#define CCROSSSECTIONPROBLEM_H

#include "utilities/CCopasiProblem.h"

class CCrossSectionProblem : public CCopasiProblem
{
public:
  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CCrossSectionProblem(const CCopasiContainer * pParent = NULL);

  /**
   *  Copy constructor.
   *  @param "const CCrossSectionProblem &" src
   * @paramconst CCopasiContainer * pParent (default: NULL)
   */
  CCrossSectionProblem(const CCrossSectionProblem & src,
                       const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  virtual ~CCrossSectionProblem();

  //TODO: add get/set methods for the parameters defined below


  /**
   * This is the output method for any result of a problem. The default implementation
   * provided with CCopasiProblem. Does only print "Not implemented." To overide this
   * default behaviour one needs to reimplement the virtual printResult function.
   * @param std::ostream * ostream
   */
  //virtual void printResult(std::ostream * ostream) const;

  /**
   * Output stream operator. Prints description of the problem
   * @param ostream & os
   * @param const Problem & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const CCrossSectionProblem & o);

  /**
   * This is the output method for any object. It calls the insert operator<<
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const;

private:

  void initObjects();

  /**
   * this flag indicates whether the calculation should be stopped after a given number
   * of detected crossings
   *
   * this member variable is mapped to a CCopasiParameter
   */
  bool * mpFlagLimitCrossings;

  /**
   * this variable indicates after how many crossings the calculation should be stopped
   * if the corresponding flag is true.
   *
   * this member variable is mapped to a CCopasiParameter
   */
  unsigned C_INT32 * mpCrossingsLimit;

  /**
   * this flag indicates whether the calculation should be stopped after a given time.
   *
   * this member variable is mapped to a CCopasiParameter
   */
  bool * mpFlagLimitTime;

  /**
   * this variable indicates how long the calculation should run
   * if the corresponding flag is true.
   *
   * this member variable is mapped to a CCopasiParameter
   */
  C_FLOAT64 * mpTimeLimit;

  /**
   * this variable indicates at what time the output is started
   *
   * this member variable is mapped to a CCopasiParameter
   */
  C_FLOAT64 * mpOutputStartTime;

  /**
   * this variable holds the trigger expression
   *
   * this member variable is mapped to a CCopasiParameter
   */
  std::string * mpTriggerExpression;

};

#endif // CCROSSSECTIONPROBLEM_H
