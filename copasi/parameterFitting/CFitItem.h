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

#ifndef COPASI_CFitItem
#define COPASI_CFitItem

#include "copasi/optimization/COptItem.h"

class CDataModel;

class CFitItem : public COptItem
{
  friend class CFitProblem;

  //Operations
protected:
  /**
   * Default constructor
   */
  CFitItem();

  CFitItem(const CFitItem & src);

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent  (default: NULL)
   * @param const std::string & name (default: FitItem)
   */
  CFitItem(const CDataContainer * pParent,
           const std::string & name = "FitItem");

  /**
   * Copy constructor
   * @param const CFitItem & src
   * @param const CDataContainer * pParent (default: src data model)
   */
  CFitItem(const CFitItem & src,
           const CDataContainer * pParent);

  /**
   * Specific constructor used for reading COPASI files
   * @param const CCopasiParameterGroup & group
   * @param const CDataContainer * pParent (default: group data model)
   */
  CFitItem(const CCopasiParameterGroup & group,
           const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CFitItem();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren() override;

  /**
   * Check the validity of the optimization item.
   * @return bool isValid
   */
  virtual bool isValid() const override;

  /**
   * Check whether the group describes a valid optimization item.
   * @param CCopasiParameterGroup & group
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
                         CDataContainer::EmptyList) override;

  /**
   * This functions check whether the current value is within the limits
   * of the optimization item.
   * @return C_INT32 result (-1: to small, 0: within boundaries, 1 to large)
   */
  virtual C_INT32 checkConstraint() const override;

  /**
   * Retrieve the magnitude of the constraint violation
   * This is always a positive number
   * @return C_FLOAT64 constraintViolation;
   */
  virtual C_FLOAT64 getConstraintViolation() const override;

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CFitItem & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const CFitItem & o);

  /**
   * Set the local value.
   * @param const C_FLOAT64 & value
   */
  void setLocalValue(const C_FLOAT64 & value);

  /**
   * Retrieve the local value.
   * @return const C_FLOAT64 & value
   */
  const C_FLOAT64 & getLocalValue() const;

  /**
   * Retrieve the value of the optimization object.
   * @return const C_FLOAT64 * objectValue
   */
  virtual const C_FLOAT64 * getObjectValue() const override;

  /**
   * Add an experiment to the list of affected experiments.
   * @param const std::string & key
   * @return bool success
   */
  bool addExperiment(const std::string & key);

  /**
   * Retrieve the key of the indexed experiment.
   * @param const size_t & index
   * @return const std::string & key
   */
  const std::string & getExperiment(const size_t & index) const;

  /**
   * Remove the indexed experiment from the affected experiments
   * @param const size_t & index
   * @return bool success
   */
  bool removeExperiment(const size_t & index);

  /**
   * Retrieve the number of experiments
   * @return size_t size
   */
  size_t getExperimentCount() const;

  /**
   * Retrieve a string listing all experiments the item applies to
   * @return std::string experiments
   */
  std::string getExperiments() const;

  /**
   * Add an experiment to the list of affected cross validations.
   * @param const std::string & key
   * @return bool success
   */
  bool addCrossValidation(const std::string & key);

  /**
   * Retrieve the key of the indexed experiment.
   * @param const size_t & index
   * @return const std::string & key
   */
  const std::string & getCrossValidation(const size_t & index) const;

  /**
   * Remove the indexed experiment from the affected cross validations
   * @param const size_t & index
   * @return bool success
   */
  bool removeCrossValidation(const size_t & index);

  /**
   * Retrieve the number of cross validations
   * @return size_t size
   */
  size_t getCrossValidationCount() const;

  /**
   * Retrieve a string listing all cross validations the item applies to
   * @return std::string crossValidations
   */
  std::string getCrossValidations() const;

  /**
   * Update bounds
   * @param const std::vector<COptItem * > & items
   * @return bool success
   */
  bool updateBounds(const std::vector<COptItem * > & items);

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

protected:
  // Attributes
  /**
   * A pointer to the value of the CCopasiParameterGroup holding the
   * list of AffectedExperiments
   */
  CCopasiParameterGroup * mpGrpAffectedExperiments;

  /**
   * A pointer to the value of the CCopasiParameterGroup holding the
   * list of Affected Validation Experiments
   */
  CCopasiParameterGroup * mpGrpAffectedCrossValidations;

  /**
   * The value for local items, which affect the experiments in the list.
   */
  C_FLOAT64 mLocalValue;
};

class CFitConstraint : public CFitItem
{
  //Operations
protected:
  /**
   * Default constructor
   */
  CFitConstraint();

  CFitConstraint(const CFitConstraint & src);

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const std::string & name (default: FitItem)
   */
  CFitConstraint(const CDataContainer * pParent,
                 const std::string & name = "FitItem");

  /**
   * Copy constructor
   * @param const CFitItem & src
   * @param const CDataContainer * pParent (default: src data model)
   */
  CFitConstraint(const CFitConstraint & src,
                 const CDataContainer * pParent);

  /**
   * Specific constructor used for reading COPASI files
   * @param const CCopasiParameterGroup & group
   * @param const CDataContainer * pParent (default: group data model)
   */
  CFitConstraint(const CCopasiParameterGroup & group,
                 const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CFitConstraint();

  /**
   * Reset the constraint violation
   */
  void resetConstraintViolation();

  /**
   * Calculate and save the constraint violation
   */
  void calculateConstraintViolation();

  /**
   * This functions check whether the current value is within the limits
   * of the constraint. The result depends on last performed
   * calculateConstraintViolation, i.e., it may not be trusted.
   * @return C_INT32 result (-1: to small, 0: within boundaries, 1 to large)
   */
  virtual C_INT32 checkConstraint() const;

  /**
   * Retrieve the magnitude of the constraint violation
   * This is always a positive number or 0. It is the sum of all
   * constraint violation for a single function evaluation.
   * @return C_FLOAT64 constraintViolation;
   */
  virtual C_FLOAT64 getConstraintViolation() const;

  // Attributes
private:
  /**
   * The value that will be returned by checkConstraint
   */
  C_INT32 mCheckConstraint;

  /**
   * The value that will be returned by getConstraintViolation
   */
  C_FLOAT64 mConstraintViolation;
};

#endif // COPASI_CFitItem
