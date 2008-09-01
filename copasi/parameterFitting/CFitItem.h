// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitItem.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/01 16:59:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CFitItem
#define COPASI_CFitItem

#include "optimization/COptItem.h"

class CFitItem : public COptItem
  {
    friend class CFitProblem;

    //Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: FitItem)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitItem(const std::string & name = "FitItem",
             const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CFitItem & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitItem(const CFitItem & src,
             const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor used for reading copasi files
     * @param const CCopasiParameterGroup & group
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitItem(const CCopasiParameterGroup & group,
             const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CFitItem();

    /**
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    /**
     * Retrieve the update method
     * @return UpdateMethod * pUpdateMethod
     */
    virtual UpdateMethod * getUpdateMethod() const;

    /**
     * Check the validity of the optimization item.
     * @return bool isValid
     */
    virtual bool isValid() const;

    /**
     * Check whether the group describes a valid optimization item.
     * @param CCopasiParameterGroup & group
     * @return bool isValid
     */
    static bool isValid(CCopasiParameterGroup & group);

    /**
     * Compile the optimization item. This function must be called
     * before any of the check functions are called.
     * @param const std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    virtual bool compile(const std::vector< CCopasiContainer * > listOfContainer =
                           CCopasiContainer::EmptyList);

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
     * Retreive the local value.
     * @return const C_FLOAT64 & value
     */
    const C_FLOAT64 & getLocalValue() const;

    /**
     * Retrieve the value of the optimization object.
     * @return const C_FLOAT64 * objectValue
     */
    virtual const C_FLOAT64 * getObjectValue() const;

    /**
     * Add an experiment to the list of affected experiments.
     * @param const std::string & key
     * @return bool success
     */
    bool addExperiment(const std::string & key);

    /**
     * Retreive the key of the indexed experiment.
     * @param const unsigned C_INT32 & index
     * @return const std::string & key
     */
    const std::string & getExperiment(const unsigned C_INT32 & index) const;

    /**
     * Remove the indexed experiment from the affected experiments
     * @param const unsigned C_INT32 & index
     * @return bool success
     */
    bool removeExperiment(const unsigned C_INT32 & index);

    /**
     * Retrieve the number of experiments
     * @return unsigned C_INT32 size
     */
    unsigned C_INT32 getExperimentCount() const;

    /**
     * Retrieve a string listing all experiments the item applies to
     * @return std::string experiments
     */
    std::string getExperiments() const;

#ifdef COPASI_CROSSVALIDATION
    /**
     * Add an experiment to the list of affected cross validations.
     * @param const std::string & key
     * @return bool success
     */
    bool addCrossValidation(const std::string & key);

    /**
     * Retreive the key of the indexed experiment.
     * @param const unsigned C_INT32 & index
     * @return const std::string & key
     */
    const std::string & getCrossValidation(const unsigned C_INT32 & index) const;

    /**
     * Remove the indexed experiment from the affected cross validations
     * @param const unsigned C_INT32 & index
     * @return bool success
     */
    bool removeCrossValidation(const unsigned C_INT32 & index);

    /**
     * Retrieve the number of cross validations
     * @return unsigned C_INT32 size
     */
    unsigned C_INT32 getCrossValidationCount() const;

    /**
     * Retrieve a string listing all cross validations the item applies to
     * @return std::string crossValidations
     */
    std::string getCrossValidations() const;
#endif // COPASI_CROSSVALIDATION

    /**
     * Update bounds
     * @param std::vector<COptItem * >::iterator it
     * @return bool success
     */
    bool updateBounds(std::vector<COptItem * >::iterator it);

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

#ifdef COPASI_CROSSVALIDATION
    /**
     * A pointer to the value of the CCopasiParameterGroup holding the
     * list of Affected Cross Validation Experiments
     */
    CCopasiParameterGroup * mpGrpAffectedCrossValidations;
#endif // COPASI_CROSSVALIDATION

    /**
     * The value for local items, which affect the experiments in the list.
     */
    C_FLOAT64 mLocalValue;

    /**
     * A pointer to the local update method
     */
    UpdateMethod * mpLocalMethod;
  };

class CFitConstraint : public CFitItem
  {
    //Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: FitItem)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitConstraint(const std::string & name = "FitItem",
                   const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CFitConstraint & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitConstraint(const CFitConstraint & src,
                   const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor used for reading copasi files
     * @param const CCopasiParameterGroup & group
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitConstraint(const CCopasiParameterGroup & group,
                   const CCopasiContainer * pParent = NULL);

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
