// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Sven Sahle and University of Heidelberg
// All rights reserved.

#ifndef CUNIT
#define CUNIT

#include <string>

#include "copasi/copasi.h"

#include <sbml/UnitDefinition.h>

LIBSBML_CPP_NAMESPACE_BEGIN
class UnitDefinition;
LIBSBML_CPP_NAMESPACE_END

/**
 * The current implementation of the units is just a wrapper for the
 * libsbml UnitDefinition class.
 */
class CSBMLunit
{
public:
  ///Default constructor
  CSBMLunit(unsigned int sbmlLevel, unsigned int sbmlVersion);

  ///Copy constructor
  CSBMLunit(const CSBMLunit & src);

  ///Constructor from libsbml units
  CSBMLunit(const UnitDefinition* ud);

  virtual ~CSBMLunit();

  bool multiply(const CSBMLunit & unit);
  void invert();

  ///apply numeric exponent to the unit.
  /**
   * The current implementation only supports integer exponents.
   */
  void applyExponent(double exp);

  /**
   * This method applies a symbol as an exponent to the unit. The result is
   * not really a valid unit itself, but the exponent can cancel out later during
   * the calculations (via applyInverseExponent() ).
   * In the current implementation, a string and an integer (sbml id + frame stack index)
   * are sufficient to uniquely identify a symbol within one expression. In other words:
   * Once we know the frame index the ID is unique.
   */
  ///apply symbolic exponent to the unit
  void applyExponent(const std::string& id, size_t frame);

  /**
   * This method applies a symbol as a reverse exponent to the unit. The result is
   * not really a valid unit itself, but the exponent can cancel out later.
   * See applyExponent(std::string id, int frame)
   */
  ///apply inverse of symbolic exponent to the unit
  void applyInverseExponent(const std::string& id, size_t frame);

  static bool isEqual(const CSBMLunit & unit1, const CSBMLunit & unit2);

  virtual std::string getDisplayString() const;

  bool isDimensionless() const;

  UnitDefinition & getSBMLUnitDefinition() {return mUD;};
  const UnitDefinition & getSBMLUnitDefinition() const {return mUD;};

  int getSymbolicExpExp() const {return mSymExpExp;};
  const std::string & getSymbolicExponent() const {return mSymExp.mID;};

private:
  UnitDefinition mUD;

  /// this class uniquely (in a given context) identifies a symbol
  class SymbolicExponent
  {
  public:
    std::string mID;
    size_t mFrame;
    SymbolicExponent(): mID(), mFrame(0) {};
    SymbolicExponent(std::string id, size_t frame): mID(id), mFrame(frame) {};
    bool isEqual(const SymbolicExponent & se) const {return mID == se.mID && mFrame == se.mFrame;};
    //bool isEmpty() const {return (mID=="")&&(mFrame==0)};
  };

  SymbolicExponent mSymExp;
  int mSymExpExp;
};

/**
 * This class contains one unit definition plus some meta information,
 * e.g. whether the unit was provided or calculated, if it is unknown or
 * if there is a conflict.
 */
class CSBMLunitInformation: public CSBMLunit
{
public:
  ///this enum encodes the status of a units information
  enum INFO
  {
    /// the units is unknown
    UNKNOWN = 0,
    /// the units is determined from the sbml defaults
    DEFAULT,
    /// the units is determined from the model-wide definitions
    GLOBAL,
    ///the units if provided for a specific object explicitly
    PROVIDED,
    ///the units was determined by reasoning
    DERIVED
  };

  ///Default constructor
  CSBMLunitInformation(unsigned int sbmlLevel, unsigned int sbmlVersion);

  CSBMLunitInformation(unsigned int sbmlLevel, unsigned int sbmlVersion, INFO info, bool conflict = false);

  CSBMLunitInformation(const CSBMLunit& u, INFO info, bool conflict = false);

  CSBMLunitInformation(const UnitDefinition* ud, INFO info, bool conflict = false);

  ///set the status information
  void setInfo(INFO info) {mInfo = info;};

  ///get the status information
  INFO getInfo() const {return mInfo;};

  ///set the conflict flag
  void setConflict(bool c) {mConflict = c;};

  ///retrieve the conflict flag
  bool isConflict() const {return mConflict;};

  virtual std::string getDisplayString() const;

  static bool isEqual(const CSBMLunitInformation & unit1, const CSBMLunitInformation & unit2);

private:
  INFO mInfo;

  ///indicated whether a conflict occurred while trying to determine the unit.
  bool mConflict;
};

#endif
