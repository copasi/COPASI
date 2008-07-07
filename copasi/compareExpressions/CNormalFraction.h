// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalFraction.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/07/07 18:26:49 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalFraction_H__
#define COPASI_CNormalFraction_H__

#include <string>

#include "copasi/copasi.h"
#include "copasi/compareExpressions/CNormalBase.h"

class CNormalSum;
class CNormalItemPower;
class CNormalLcm;

//class CNormalLogical;

class CNormalFraction : public CNormalBase
  {
  private:
    /**
     * Enumeration of members
     */
    CNormalSum* mpNumerator;
    CNormalSum* mpDenominator;

  public:
    /**
     * Default constructor
     */
    CNormalFraction();

    /**
     * Copy contructor
     */
    CNormalFraction(const CNormalFraction& src);

    /**
     * Assignment operator
     */
    CNormalFraction& operator=(const CNormalFraction& src);

    /**
     * smaller operator
     */
    bool operator<(const CNormalFraction& src) const;

    virtual CNormalBase * copy() const;

    /**
     * Dtor.
     */
    virtual ~CNormalFraction();

    /**
     * Set numerator of this fraction
     * @return true.
     */
    bool setNumerator(const CNormalSum& numerator);

    /**
     * Set denominator of this fraction.
     * @return true.
     */
    bool setDenominator(const CNormalSum& denominator);

    /**
     * Check if the numerator of this fraction equals 1.
     * @return bool
     */
    bool checkNumeratorOne() const;

    /**
     * Check if the denominator of this fraction equals 1.
     * @return bool
     */
    bool checkDenominatorOne() const;

    /**
     * Set the denominator of this fraction equal 1.
     * @return true.
     */
    bool setDenominatorOne();

    /**
     * Retrieve the numerator of this fraction.
     * @return mpNumerator.
     */
    CNormalSum& getNumerator();

    /**
     * Retrieve the denominator of this fraction.
     * @return mpDenominator.
     */
    CNormalSum& getDenominator();

    /**
     * Retrieve the numerator of this fraction.
     * @return mpNumerator.
     */
    const CNormalSum& getNumerator() const;

    /**
     * Retrieve the denominator of this fraction.
     * @return mpDenominator.
     */
    const CNormalSum& getDenominator() const;

    /**
     * Check if this fraction contains further fractions.
     * @return bool.
     */
    bool checkForFractions() const;

    /**
     * Expand this fraction by a lcm.
     * @return true.
     */
    bool expand(const CNormalLcm& lcm);

    /**
     * Cancel common items of mpNumerator and mpDenominator.
     * @return true.
     */
    bool cancel();

    /**
     * Multiply this fraction with a number.
     * @return true.
     */
    bool multiply(const C_FLOAT64& number);

    /**
     * Multiply a fraction with an itempower.
     * @return true.
     */
    bool multiply(const CNormalItemPower& itemPower);

    /**
     * Find lcm of denominators of respective fractions contained in this fraction.
     * @return pointer to lcm.
     */
    const CNormalLcm* findLcm() const;

    /**
     * Multiply this fraction by a lcm.
     * @return CNormalSum*, pointer to result of multiplication ie. a normal sum.
     * This fraction is useless now.
     */
    const CNormalSum* multiply(CNormalLcm lcm);

    /**
     * Check if numerator and denominator contain fractions,
     * find lcm of respective denominators, expand this fraction by lcm and cancel.
     * @return true
     */
    virtual bool simplify();

    bool operator==(const CNormalFraction & rhs) const;

    virtual std::string toString() const;

    //std::set<const CNormalLogical*> findLogicals() const;

    bool checkIsOne() const;

    bool checkIsZero() const;

    /**
     * Returns a fraction that is 1/1.
     * It creates a new fraction and sets the numerator and the denominator to
     * a unit sum.
     */
    static CNormalFraction* createUnitFraction();
  };

std::ostream & operator<< (std::ostream &os, const CNormalFraction & d);

#endif // COPASI_CNormalFraction_decl__
