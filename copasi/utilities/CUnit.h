// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// This class defines a unit, which might be considered
// an enhanced form of metadata, in COPASI. It can merely
// contain the name and symbol of the unit, but is intended
// to also contain a list of the SI units it is derived from.
// This is intended to facilitate unit analysis, user input parsing,
// and easy compatibility to the SBML units representation.

#ifndef CUNIT_H
#define CUNIT_H

#include "copasi/utilities/CUnitComponent.h"
#include "copasi/report/CCopasiContainer.h"
#include "copasi/utilities/CCopasiVector.h"
#include "model/CAnnotation.h"

class CUnit : public CCopasiContainer, public CAnnotation
{
  friend std::ostream &operator<<(std::ostream &os, const CUnit & o);

public:
  static CUnit EmptyUnit;

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

  static CUnit getSIUnit(const std::string & si,
                         const C_FLOAT64 & avogadro);

  static void updateSIUnits(CCopasiVectorN< CUnit > & Units,
                            const C_FLOAT64 & avogadro);

  // constructors
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CUnit(const std::string & name = "NoName",
        const CCopasiContainer * pParent = NULL);

  /**
   * Default constructor
   * @param const CBaseUnit::Kind & kind
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CUnit(const CBaseUnit::Kind & kind,
        const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param const CUnit & src
   * @param const C_FLOAT64 & avogadro
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CUnit(const CUnit & src,
        const C_FLOAT64 & avogadro,
        const CCopasiContainer * pParent = NULL);

  ~CUnit();

  virtual const std::string & getKey() const;

  void fromEnum(VolumeUnit volEnum);
  void fromEnum(AreaUnit areaEnum);
  void fromEnum(LengthUnit lengthEnum);
  void fromEnum(TimeUnit timeEnum);
  void fromEnum(QuantityUnit quantityEnum);

  void setSymbol(const std::string & symbol);
  std::string getSymbol() const;

  bool setInfix(const std::string & definition,
                     const C_FLOAT64 & avogadro);

  std::string getInfix() const;

  const std::set< std::string > & getUsedSymbols() const;

  bool isDimensionless() const;
  void addComponent(const CUnitComponent & component);
  const std::set< CUnitComponent > & getComponents() const;

  bool compile(const C_FLOAT64 & avogadro);

  CUnit & exponentiate(double exp);
  CUnit operator*(const CUnit & rhs) const;
  bool operator==(const CUnit & rhs) const;
  bool isEquivalent(const CUnit & rhs) const;

private:
  std::string mSymbol;
  std::string mInfix;
  std::set< CUnitComponent > mComponents;
  std::set< std::string > mUsedSymbols;

  void setup();
};

#endif // CUNIT_H
