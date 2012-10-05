// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/crosssection/CCrossSectionProblem.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2010/05/26 18:51:05 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CCROSSSECTIONPROBLEM_H
#define CCROSSSECTIONPROBLEM_H

#include "trajectory/CTrajectoryProblem.h"

class CCrossSectionProblem : public CTrajectoryProblem
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

  /**
   * Function to get mpFlagLimitCrossings
   */
  bool getFlagLimitCrossings() const;

  /**
   * Function to get mpCrossingsLimit
   */
  const unsigned C_INT32 &getCrossingsLimit() const;

  /**
   * Function to get mpFlagLimitTime
   */
  bool getFlagLimitTime() const;

  /**
   * Function to get mpTimeLimit
   */
  const C_FLOAT64 &getTimeLimit() const;

  /**
   * Function to set mpFlagLimitCrossings
   */
  void setFlagLimitCrossings(bool flagLimitCrossing);

  /**
   * Function to set mpCrossingsLimit
   */
  void setCrossingsLimit(const unsigned C_INT32 &crossingLimit);

  /**
   * Function to set mpFlagLimitTime
   */
  void setFlagLimitTime(bool flagLimitTime);

  /**
   * Function to set mpTimeLimit
   */
  void setTimeLimit(const C_FLOAT64 &timeLimit);

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
   * this variable holds the trigger expression
   *
   * this member variable is mapped to a CCopasiParameter
   */
  std::string * mpTriggerExpression;

};

#endif // CCROSSSECTIONPROBLEM_H
