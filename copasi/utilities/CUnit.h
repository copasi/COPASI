// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
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

class CUnit : public CCopasiContainer
{
  
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

  // constructors
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CUnit(const std::string & name = "NoName",
        const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param const CUnit & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CUnit(const CUnit & src,
        const CCopasiContainer * pParent = NULL);

  ~CUnit();

  void fromEnum(VolumeUnit volEnum);
  void fromEnum(AreaUnit areaEnum);
  void fromEnum(LengthUnit lengthEnum);
  void fromEnum(TimeUnit timeEnum);
  void fromEnum(QuantityUnit quantityEnum);

  void setSymbol(std::string symbol);
  std::string getSymbol() const;
  bool isDimensionless() const;
  void addComponent(const CUnitComponent & component);
  bool simplifyComponents();
  std::string prefixFromScale(int scale);

private:

  std::string mSymbol;
  std::string mKey;
  std::vector < CUnitComponent > mComponents;

  void setup(); // initilizations common to all constructors

//  std::string getSimplifiedComponents const(); TODO

};

#endif // CUNIT_H
