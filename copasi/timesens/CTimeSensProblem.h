// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 *  CTimeSensProblem class.
 *  This class describes the time sensitivities problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 */

#ifndef COPASI_CTimeSensProblem
#define COPASI_CTimeSensProblem

#include <string>

#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/core/CDataArray.h"

class CTimeSensProblem : public CTrajectoryProblem
{
protected:
  CTimeSensProblem(const CTimeSensProblem & src);

public:
  // Operations

  /**
   * Default constructor.
   * @param const CDataContainer * pParent (default: NULL)
   */
  CTimeSensProblem(const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor.
   * @param const CTimeSensProblem & src
   * @paramconst CDataContainer * pParent (default: NULL)
   */
  CTimeSensProblem(const CTimeSensProblem & src,
                   const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CTimeSensProblem();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  // handling the parameters for which sensitivities are to be calculated:

  size_t getNumParameters();

  void addParameterCN(const CCommonName& cn);

  CCommonName getParameterCN(size_t index);

  void removeParameterCN(size_t index);

  void removeParameterCN(const CCommonName& cn);

  void clearParameterCNs();

  // handling the target objects for which sensitivities are requested.
  // note that sensitivities of the state variables are always calculated,
  // those specified here are additional

  size_t getNumTargets();

  void addTargetCN(const CCommonName& cn);

  CCommonName getTargetCN(size_t index);

  void removeTargetCN(size_t index);

  void removeTargetCN(const CCommonName& cn);

  void clearTargetCNs();

  // the results.

  //first the sensitivities of the state variables (particle numbers, etc.):

  CArray & getStateResult();
  const CArray & getStateResult() const;
  CDataArray * getStateResultAnnotated();
  const CDataArray * getStateResultAnnotated() const;

  //now the sensitivities of the explicitely requested targets:

  CArray & getTargetsResult();
  const CArray & getTargetsResult() const;
  CDataArray * getTargetsResultAnnotated();
  const CDataArray * getTargetsResultAnnotated() const;

  //now the same, but scaled
  CArray & getScaledStateResult();
  const CArray & getScaledStateResult() const;
  CDataArray * getScaledStateResultAnnotated();
  const CDataArray * getScaledStateResultAnnotated() const;

  CArray & getScaledTargetsResult();
  const CArray & getScaledTargetsResult() const;
  CDataArray * getScaledTargetsResultAnnotated();
  const CDataArray * getScaledTargetsResultAnnotated() const;

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  void initObjects();

  // Attributes
protected:

  /**
   *  These hold the results
   */
  CArray mStateResult;
  CDataArray * mpStateResultAnnotation;
  CArray mTargetsResult;
  CDataArray * mpTargetsResultAnnotation;

  CArray mScaledStateResult;
  CDataArray * mpScaledStateResultAnnotation;
  CArray mScaledTargetsResult;
  CDataArray * mpScaledTargetsResultAnnotation;

  //the parameters for the sensitivities
  CCopasiParameterGroup * mpParametersGroup;

  //the targets for the sensitivities
  CCopasiParameterGroup * mpTargetsGroup;

};

#endif // COPASI_CTimeSensProblem
