/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptItem.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/18 02:54:18 $
   End CVS Header */

#ifndef COPASI_COptItem
#define COPASI_COptItem

#include "report/CCopasiObject.h"

class CCopasiParameterGroup;
class CCopasiObjectName;
class COptProblem;

class COptItem
  {
    friend class COptProblem;

    //Operations
  private:
    /**
     * Specific Constructor
     */
    COptItem(CCopasiParameterGroup & group);

    /**
     * Checks whether val1 < val2
     * @param const C_FLOAT64 & val1
     * @param const C_FLOAT64 & val2
     * @return bool fulfills
     */
    static bool less(const C_FLOAT64 & val1, const C_FLOAT64 & val2);

    /**
     * Checks whether val1 <= val2
     * @param const C_FLOAT64 & val1
     * @param const C_FLOAT64 & val2
     * @return bool fulfills
     */
    static bool lessOrEqual(const C_FLOAT64 & val1, const C_FLOAT64 & val2);

  public:
    /**
     * Copy Constructor
     * @param COptItem & src
     */
    COptItem(COptItem & src);

    /**
     * Destructor
     */
    ~COptItem();

    /**
     * Initialize the optimization item.
     * @param const CCopasiObjectName & objectCN
     * @return bool success
     */
    bool initialize(const CCopasiObjectName & objectCN);

    /**
     * Set the object of the optimization item.
     * @param const CCopasiObjectName & objectCN
     * @return bool success
     */
    bool setObjectCN(const CCopasiObjectName & objectCN);

    /**
     * Retrieve the object of the optimization item.
     * @return const CCopasiObjectName objectCN
     */
    const CCopasiObjectName getObjectCN() const;

    /**
     * Set the lower bound.
     * @param const std::string & lowerBound
     * @return bool success
     */
    bool setLowerBound(const std::string & lowerBound);

    /**
     * Retrieve the lower bound.
     * @return const std::string lowerBound
     */
    const std::string getLowerBound() const;

    /**
     * Set the lower relationship.
     * @param const std::string & lowerRel (< or <=)
     * @return bool success
     */
    bool setLowerRelation(const std::string & lowerRel);

    /**
     * Retrieve the lower relationship.
     * @return const std::string lowerRel
     */
    const std::string getLowerRelation() const;

    /**
     * Set the upper bound.
     * @param const std::string & upperBound
     * @return bool success
     */
    bool setUpperBound(const std::string & upperBound);

    /**
     * Retrieve the upper bound.
     * @return const std::string upperBound
     */
    const std::string getUpperBound() const;

    /**
     * Set the upper relationship.
     * @param const std::string & upperRel (< or <=)
     * @return bool success
     */
    bool setUpperRelation(const std::string & upperRel);

    /**
     * Retrieve the upper relationship.
     * @return const std::string upperRel
     */
    const std::string getUpperRelation() const;

    /**
     * Check the validity of the optimization item.
     * @return bool isValid
     */
    bool isValid() const;

    /**
     * Check whether the group describes a valid optimization item.
     * @param CCopasiParameterGroup & group
     * @return bool isValid
     */
    static bool isValid(CCopasiParameterGroup & group);

    /**
     * Compile the optimization item. This function must be called 
     * before any of the check functions are called.
     * @return bool success
     */
    bool compile();

    /**
     * This functions check whether the value is within the limits
     * of the optimization item.
     * @param const C_FLOAT64 & value
     * @return C_INT32 result (-1: to small, 0: within boundaries, 1 to large)
     */
    C_INT32 checkConstraint(const C_FLOAT64 & value);

    /**
     * Checks whether the value fulfills the lower bound constraint.
     * @param const C_FLOAT64 & value
     * @return bool fulfills
     */
    bool checkLowerBound(const C_FLOAT64 & value);

    /**
     * Checks whether the value fulfills the upper bound constraint.
     * @param const C_FLOAT64 & value
     * @return bool fulfills
     */
    bool checkUpperBound(const C_FLOAT64 & value);

    /**
     * Retrieve the value of the optimization object.
     * @return const C_FLOAT64 * objectValue
     */
    const C_FLOAT64 * getObjectValue() const;

    /**
     * Retrieve the value of the lower bound.
     * @return const C_FLOAT64 * lowerBoundValue
     */
    const C_FLOAT64 * getLowerBoundValue() const;

    /**
     * Retrieve the value of the upper bound.
     * @return const C_FLOAT64 * upperBoundValue
     */
    const C_FLOAT64 * getUpperBoundValue() const;

    //Attributes:
  private:
    /**
     * A pointer to the parameter group which stores the information.
     */
    CCopasiParameterGroup * mpGroup;

    /**
     * A pointer to the object value
     */
    const C_FLOAT64 * mpObjectValue;

    /**
     * A pointer to the lower bound value
     */
    const C_FLOAT64 * mpLowerBound;

    /**
     * The value of the lower bound (only if not on object) 
     */
    C_FLOAT64 mLowerBound;

    /**
     * A pointer to the function for checking the lower relationship
     * @param const C_FLOAT64 & val1
     * @param const C_FLOAT64 & val2
     * @return bool fulfills
     */
    bool (*mpLowerRel)(const C_FLOAT64 & val1, const C_FLOAT64 & val2);

    /**
     * A pointer to the upper bound value
     */
    const C_FLOAT64 * mpUpperBound;

    /**
     * The value of the upper bound (only if not on object) 
     */
    C_FLOAT64 mUpperBound;

    /**
     * A pointer to the function for checking the upper relationship
     * @param const C_FLOAT64 & val1
     * @param const C_FLOAT64 & val2
     * @return bool fulfills
     */
    bool (*mpUpperRel)(const C_FLOAT64 & val1, const C_FLOAT64 & val2);
  };

#endif // COPASI_COptItem
