// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalCall.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:26:19 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CNormalCall
#define COPASI_CNormalCall

#include <string>
#include <vector>

#include "copasi/compareExpressions/CNormalBase.h"
#include "copasi/copasi.h"

class CNormalFraction;

/**
 * The class for function calls used in CNormal
 */
class CNormalCall : public CNormalBase
{
public:
  enum Type
  {
    FUNCTION,
    EXPRESSION,
    DELAY,
    INVALID
  };

private:
  /**
   * The name of the called function
   */
  std::string mName;

  /**
   * the call type
   */
  Type mType;

  /**
   * Enumeration of members
   * The members of a call have to be kept in the correct order since the
   * order of arguments to a call matters.
   */
  std::vector<CNormalFraction*> mFractions;

public:

  /**
   * Default constructor
   */
  CNormalCall();

  /**
   * Copy Constructor
   */
  CNormalCall(const CNormalCall& src);

  /**
   * Assignment operator
   */
  CNormalCall & operator=(const CNormalCall& src);

  /**
   * Smaller operator
   */
  bool operator<(const CNormalCall& rhs) const;

  /**
   * Destructor
   */
  virtual ~CNormalCall();

  virtual CNormalBase * copy() const;

  /**
   * Retrieve the number of summands of this sum.
   * @return int
   */
  int getSize() const;

  /**
   * Add fraction to this sum.
   * @return true.
   */
  bool add(const CNormalFraction& fraction);

  /**
   * Retrieve the set of fractions of this sum.
   * @return mFractions.
   */
  const std::vector<CNormalFraction*>& getFractions() const;

  /**
   * Examine equality of two sums.
   * @return bool.
   */
  bool operator==(const CNormalCall & rhs) const;

  /**
   * Sets the fractions of this product.
   */
  void setFractions(const std::vector<CNormalFraction*>& set);

  virtual std::string toString() const;

  virtual bool simplify();

  const std::string& getName() const;

  void setName(const std::string& name);

  Type getType() const;

  void setType(Type type);

  friend std::ostream & operator<< (std::ostream &os, const CNormalCall & d);
};

#endif // COPASI_CNormalCall
