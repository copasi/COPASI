// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_COptItem
#define COPASI_COptItem

#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/math/CMathUpdateSequence.h"

class CCommonName;
class COptProblem;
class CDataModel;
class CMathObject;
class CRandom;

class COptItem: public CCopasiParameterGroup
{
  //Operations
protected:
  /**
   * Default constructor
   */
  COptItem();

  COptItem(const COptItem & src);

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const std::string & name (default: OptimizationItem)
   */
  COptItem(const CDataContainer * pParent,
           const std::string & name = "OptimizationItem");

  /**
   * Copy constructor
   * @param const COptItem & src
   * @param const CDataContainer * pParent (default: src data model)
   */
  COptItem(const COptItem & src,
           const CDataContainer * pParent);

  /**
   * Specific constructor used for reading COPASI files
   * @param const CCopasiParameterGroup & group
   * @param const CDataContainer * pParent (default: group data model)
   */
  COptItem(const CCopasiParameterGroup & group,
           const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptItem();

  /**
   * Calculate the objects value.
   */
  virtual void calculateValue() override;

  /**
   * Retrieve a pointer to the value of the object
   */
  virtual void * getValuePointer() const override;

  /**
   * Set the object of the optimization item.
   * @param const CCommonName & objectCN
   * @return bool success
   */
  bool setObjectCN(const CCommonName & objectCN);

  /**
   * Retrieve the object of the optimization item.
   * @return const CCommonName objectCN
   */
  const CCommonName getObjectCN() const;

  /**
   * Retrieve the item object. This may only be called after compile
   * @return const CObjectInterface *
   */
  const CObjectInterface * getObject() const;

  /**
   * Retrieve the display name of the optimization item.
   * @return std::string displayName
   */
  std::string getObjectDisplayName() const override;

  /**
   * Set the lower bound.
   * @param const CCommonName & lowerBound
   * @return bool success
   */
  bool setLowerBound(const CCommonName & lowerBound);

  /**
   * Retrieve the lower bound.
   * @return const std::string lowerBound
   */
  const std::string getLowerBound() const;

  /**
   * Set the upper bound.
   * @param const CCommonName & upperBound
   * @return bool success
   */
  bool setUpperBound(const CCommonName & upperBound);

  /**
   * Retrieve the upper bound.
   * @return const std::string upperBound
   */
  const std::string getUpperBound() const;

  /**
   * Check the validity of the optimization item.
   */
  virtual bool isValid() const;

  /**
   * Check whether the group describes a valid optimization item.
   * @return bool isValid
   */
  static bool isValid(CCopasiParameterGroup & group);

  /**
   * Compile the optimization item. This function must be called
   * before any of the check functions are called.
   * @param const CObjectInterface::ContainerList listOfContainer
   * @return bool success
   */
  virtual bool compile(CObjectInterface::ContainerList listOfContainer =
                         CDataContainer::EmptyList);

  /**
   * This functions check whether the current value is within the limits
   * of the optimization item.
   * @return C_INT32 result (-1: to small, 0: within boundaries, 1 to large)
   */
  virtual C_INT32 checkConstraint() const;

  /**
   * Retrieve the magnitude of the constraint violation
   * This is always a positive number
   * @return C_FLOAT64 constraintViolation;
   */
  virtual C_FLOAT64 getConstraintViolation() const;

  /**
   * This functions check whether the value is within the limits
   * of the optimization item.
   * @param const C_FLOAT64 & value
   * @return C_INT32 result (-1: to small, 0: within boundaries, 1 to large)
   */
  C_INT32 checkConstraint(const C_FLOAT64 & value) const;

  /**
   * Checks whether the value fulfills the lower bound constraint.
   * @param const C_FLOAT64 & value
   * @return bool fulfills
   */
  bool checkLowerBound(const C_FLOAT64 & value) const;

  /**
   * Checks whether the value fulfills the upper bound constraint.
   * @param const C_FLOAT64 & value
   * @return bool fulfills
   */
  bool checkUpperBound(const C_FLOAT64 & value) const;

  /**
   * Checks whether we have a valid interval.
   * @return bool fulfills
   */
  bool checkInterval() const;

  /**
   * Checks whether we have a valid initial value item.
   * @return bool fulfills
   */
  bool checkIsInitialValue() const;

  /**
   * Update the prerequisites to point to the optimization items controlling the boundary object
   * @param const std::vector< COptItem * > & influencingIntervals
   */
  void updatePrerequisites(const std::vector< COptItem * > & influencingIntervals);

  /**
   * Retrieve the value of the optimization object.
   * @return const C_FLOAT64 * objectValue
   */
  virtual const C_FLOAT64 * getObjectValue() const;

  /**
   * Retrieve the value of the lower bound.
   * @return const C_FLOAT64 * lowerBoundValue
   */
  inline const C_FLOAT64 * getLowerBoundValue() const
  {return mpLowerBound;}

  /**
   * Retrieve the value of the upper bound.
   * @return const C_FLOAT64 * upperBoundValue
   */
  inline const C_FLOAT64 * getUpperBoundValue() const
  {return mpUpperBound;}

  /**
   * Set the value start value.
   * @param const C_FLOAT64 & startValue
   * @return bool success
   */
  bool setStartValue(const C_FLOAT64 & value);

  /**
   * Retrieve the start value of the optimization object.
   * @return const C_FLOAT64 & startValue
   */
  const C_FLOAT64 & getStartValue() const;

  /**
   * Retrieve the start value use in the last optimization.
   * @return const C_FLOAT64 & startValue
   */
  const C_FLOAT64 & getLastStartValue() const;

  /**
   * Remember the current start value
   */
  void rememberStartValue();

  /**
   * Retrieve a random value in the interval (lower bound, upper bound).
   * Optionally one may provide a random number generator to be used
   * to create the random value.
   * @param CRandom & Random
   * @return C_FLOAT64 randomValue
   */
  C_FLOAT64 getRandomValue(CRandom & Random) const;

  /**
   * Output stream operator
   * @param ostream & os
   * @param const COptItem & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const COptItem & o);

  /**
   * Check whether the item influences other intervals
   * @return bool influencesIntervals
   */
  bool influencesIntervals() const;

  void setIntervalUpdateSequence(const CCore::CUpdateSequence & updateSequence);

  const CCore::CUpdateSequence & getIntervalUpdateSequence() const;

  void addDependentItem(COptItem * pDependentItem);

  const std::set< COptItem * > & getDependentItems() const;

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

  /**
   * Compile the lower bound to hold the value given by the bound
   * @param const CObjectInterface::ContainerList & listOfContainer
   * @return bool success
   */
  bool compileLowerBound(const CObjectInterface::ContainerList & listOfContainer);

  /**
   * Compile the upper bound to hold the value given by the bound
   * @param const CObjectInterface::ContainerList & listOfContainer
   * @return bool success
   */
  bool compileUpperBound(const CObjectInterface::ContainerList & listOfContainer);

  //Attributes:
protected:
  /**
   * A pointer to the value of the CCopasiParameter holding the ObjectCN
   */
  std::string * mpParmObjectCN;

  /**
   * A pointer to the value of the CCopasiParameter holding the LowerBound
   */
  std::string * mpParmLowerBound;

  /**
   * A pointer to the value of the CCopasiParameter holding the UpperBound
   */
  std::string * mpParmUpperBound;

  /**
   * A pointer to the value of the CCopasiParameter holding the start value
   */
  C_FLOAT64 * mpParmStartValue;

  /**
   * A pointer to the object
   */
  const CObjectInterface * mpObject;

  /**
   * A pointer to the object value
   */
  const C_FLOAT64 * mpObjectValue;

  /**
   * A pointer to the object for the lower bound
   */
  const CObjectInterface * mpLowerObject;

  /**
   * A pointer to the lower bound value
   */
  const C_FLOAT64 * mpLowerBound;

  /**
   * The value of the lower bound (only if not on object)
   */
  C_FLOAT64 mLowerBound;

  /**
   * A pointer to the object for the upper bound
   */
  const CObjectInterface * mpUpperObject;

  /**
   * A pointer to the upper bound value
   */
  const C_FLOAT64 * mpUpperBound;

  /**
   * The value of the upper bound (only if not on object)
   */
  C_FLOAT64 mUpperBound;

  /**
   * The start value use for last calculation
   */
  C_FLOAT64 mLastStartValue;

  /**
   * A value indicating whether the interval is valid
   */
  C_FLOAT64 mInterval;

  std::set< COptItem * > mDependentItems;

  CCore::CUpdateSequence mUpdateInterval;
};

#endif // COPASI_COptItem
