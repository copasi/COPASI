// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CCROSSSECTIONPROBLEM_H
#define CCROSSSECTIONPROBLEM_H

#include "copasi/trajectory/CTrajectoryProblem.h"

class CCrossSectionProblem : public CTrajectoryProblem
{
protected:
  CCrossSectionProblem(const CCrossSectionProblem & src);

public:
  /**
   * Default constructor.
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCrossSectionProblem(const CDataContainer * pParent = NO_PARENT);

  /**
   *  Copy constructor.
   *  @param "const CCrossSectionProblem &" src
   * @paramconst CDataContainer * pParent (default: NULL)
   */
  CCrossSectionProblem(const CCrossSectionProblem & src,
                       const CDataContainer * pParent);

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
   * Function to get mpFlagLimitOutCrossings
   */
  bool getFlagLimitOutCrossings() const;

  /**
   * Function to get mpOutCrossingsLimit
   */
  const unsigned C_INT32 &getOutCrossingsLimit() const;

  /**
   * Function to get mpFlagLimitOutTime
   */
  bool getFlagLimitOutTime() const;

  /**
   * Function to get mpTimeLimit
   */
  const C_FLOAT64 &getTimeLimit() const;

  /**
   * return the variable
   */
  const std::string& getSingleObjectCN() const;
  /*
   * set the variable
   */
  void setSingleObjectCN(const std::string& cn);
  void setSingleObjectCN(const CDataObject* pObject);
  const C_FLOAT64& getThreshold() const;
  void setThreshold(const C_FLOAT64 &threshold);

  /**
   * Function to get mpFlagLimitConvergence
   */
  bool getFlagLimitConvergence() const;

  /**
   * Function to get mpConvergenceTolerance
   */
  const C_FLOAT64 &getConvergenceTolerance() const;

  /**
  * Function to set mpFlagLimitConvergence
  */
  void setFlagLimitConvergence(bool flagLimitConvergence);

  /**
   * Function to set mpConvergenceTolerance
   */
  void setConvergenceTolerance(const C_FLOAT64 &convergenceTolerance);

  /**
   * Function to get mpFlagLimitOutConvergence
   */
  bool getFlagLimitOutConvergence() const;

  /**
   * Function to get mpConvergenceOutTolerance
   */
  const C_FLOAT64 &getConvergenceOutTolerance() const;

  /**
  * Function to set mpFlagLimitOutConvergence
  */
  void setFlagLimitOutConvergence(bool flagLimitConvergence);

  /**
   * Function to set mpConvergenceOutTolerance
   */
  void setConvergenceOutTolerance(const C_FLOAT64 &convergenceTolerance);

  bool isPositiveDirection() const;
  void setPositiveDirection(bool isPositive);

  /**
   * Function to set mpFlagLimitCrossings
   */
  void setFlagLimitCrossings(bool flagLimitCrossing);

  /**
   * Function to set mpCrossingsLimit
   */
  void setCrossingsLimit(const unsigned C_INT32 &crossingLimit);

  /**
   * Function to set mpFlagLimitOutCrossings
   */
  void setFlagLimitOutCrossings(bool flagLimitCrossing);

  /**
   * Function to set mpOutCrossingsLimit
   */
  void setOutCrossingsLimit(const unsigned C_INT32 &crossingLimit);

  /**
   * Function to set mpFlagLimitOutTime
   */
  void setFlagLimitOutTime(bool flagLimitTime);

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

  //overload these member functions just to make sure they are not used in this
  //derived class
  unsigned C_INT32 getStepNumber() const {return 0;}
  C_FLOAT64 getStepSize() const {return 0.0;}

  /**
   * Initialize the parameters
   */
  void initializeParameter();

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
   * this flag indicates whether the calculation should be stopped when convergence is reached
   *
   * this member variable is mapped to a CCopasiParameter
   */
  bool * mpFlagLimitConvergence;

  /**
   * this variable indicates the tolerance after which the calculation should be considered
   * converged
   *
   * this member variable is mapped to a CCopasiParameter
   */
  C_FLOAT64 * mpConvergenceTolerance;

  /**
   * this flag indicates whether the output should only be collected once
   * convergence is reached
   *
   * this member variable is mapped to a CCopasiParameter
   */
  bool * mpFlagLimitOutConvergence;

  /**
   * this variable indicates the tolerance after which the calculation should be considered
   * converged and output should commence
   *
   * this member variable is mapped to a CCopasiParameter
   */
  C_FLOAT64 * mpConvergenceOutTolerance;

  /**
  * this flag indicates whether the output should be collected after a given number
  * of detected crossings
  *
  * this member variable is mapped to a CCopasiParameter
  */
  bool * mpFlagLimitOutCrossings;

  /**
   * this variable indicates after how many crossings the output should start
   * if the corresponding flag is true.
   *
   * this member variable is mapped to a CCopasiParameter
   */
  unsigned C_INT32 * mpOutCrossingsLimit;

  /**
   * this flag indicates whether output should be selected after a delay
   *
   * this member variable is mapped to a CCopasiParameter
   */
  bool * mpFlagLimitOutTime;

  /**
   * this variable holds the trigger expression
   *
   * this member variable is mapped to a CCopasiParameter
   */
  std::string * mpTriggerExpression;
  std::string * mSingleObjectCN;
  bool * mpFlagPositiveDirection;
  C_FLOAT64 * mpThreshold;
};

#endif // CCROSSSECTIONPROBLEM_H
