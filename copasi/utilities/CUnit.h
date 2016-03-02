// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// This class defines a unit, which might be considered
// an enhanced form of metadata, in COPASI. It can contains
// the expression of the unit, and a list of the SI units it is derived from.
// This is intended to facilitate unit analysis, user input parsing,
// and easy compatibility to the SBML units representation.

#ifndef CUNIT_H
#define CUNIT_H

#include "copasi/utilities/CUnitComponent.h"
#include "copasi/utilities/CCopasiVector.h"

class CUnit
{
  friend std::ostream &operator<<(std::ostream &os, const CUnit & o);

public:

  static C_FLOAT64 Avogadro;

  // Enum of valid volume units
  enum VolumeUnit {dimensionlessVolume = 0, m3, l, ml, microl, nl, pl, fl};

  // String representation of valid volume units
  static const char * VolumeUnitNames[];

  // Enum of valid area units
  enum AreaUnit {dimensionlessArea = 0, m2, dm2, cm2, mm2, microm2, nm2, pm2, fm2};

  // String representation of valid area units
  static const char * AreaUnitNames[];

  // Enum of valid length units
  enum LengthUnit {dimensionlessLength = 0, m, dm, cm, mm, microm, nm, pm, fm};

  // String representation of valid length units
  static const char * LengthUnitNames[];

  // Enum of valid time units
  enum TimeUnit {dimensionlessTime = 0, d, h, min, s, ms, micros, ns, ps, fs, OldMinute};

  // String representation of valid time units
  static const char * TimeUnitNames[];

  //  Enum of valid quantity units
  enum QuantityUnit {dimensionlessQuantity = 0, Mol, mMol, microMol, nMol, pMol, fMol, number, OldXML};

  // String representation of valid quantity units as used in old (up to Build 18)
  // COPASI files
  static const char * QuantityUnitOldXMLNames[];

  // String representation of valid quantity units
  static const char * QuantityUnitNames[];

  static std::string replaceSymbol(const std::string & expression,
                                   const std::string & oldSymbol,
                                   const std::string & newSymbol);

  // constructors
  /**
   * Default constructor
   */
  CUnit();

  /**
   * Kind constructor
   * @param const CBaseUnit::Kind & kind
   */
  CUnit(const CBaseUnit::Kind & kind);

  /**
   * Expression constructor
   * @param const CBaseUnit::Kind & kind
   */
  CUnit(std::string expression);

  /**
   * Copy constructor
   * @param const CUnit & src
   * @param const C_FLOAT64 & avogadro
   */
  CUnit(const CUnit & src,
        const C_FLOAT64 & avogadro);

  ~CUnit();

  void fromEnum(VolumeUnit volEnum);
  void fromEnum(AreaUnit areaEnum);
  void fromEnum(LengthUnit lengthEnum);
  void fromEnum(TimeUnit timeEnum);
  void fromEnum(QuantityUnit quantityEnum, C_FLOAT64 avogadro);

  bool setExpression(const std::string & expression,
                     const C_FLOAT64 & avogadro);

  std::string getExpression() const;

  const std::set< std::string > & getUsedSymbols() const;

  bool isDimensionless() const;
  bool isUndefined() const;
  void addComponent(const CUnitComponent & component);
  const std::set< CUnitComponent > & getComponents() const;

  bool compile(const C_FLOAT64 & avogadro = Avogadro);

  CUnit & exponentiate(double exp);
  CUnit operator*(const CUnit & rhs) const;
  bool operator==(const CUnit & rhs) const;
  bool isEquivalent(const CUnit & rhs) const;
  void buildExpression();

private:
  std::string mExpression;
  std::set< CUnitComponent > mComponents;
  std::set< std::string > mUsedSymbols;

  // Consolodate any components with exponent == 0
  // into a/the single dimensionless component
  void consolodateDimensionless();
};

#endif // CUNIT_H
