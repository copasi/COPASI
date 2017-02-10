// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// This class defines a unit, which might be considered
// an enhanced form of metadata, in COPASI. It can merely
// contain the name and symbol of the unit, but is intended
// to also contain a list of the SI units it is derived from.
// This is intended to facilitate unit analysis, user input parsing,
// and easy compatibility to the SBML units representation.

#ifndef CUNIT_DEFINITION_H
#define CUNIT_DEFINITION_H

#include "copasi/utilities/CUnit.h"
#include "copasi/report/CCopasiContainer.h"
#include "model/CAnnotation.h"

class CUnitDefinitionDB;

class CUnitDefinition : public CCopasiContainer, public CUnit, public CAnnotation
{
  friend std::ostream &operator<<(std::ostream &os, const CUnitDefinition & o);

public:

  static CUnitDefinition * create(const CData & data);

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CUnitDefinition(const std::string & name = "NoName",
                  const CCopasiContainer * pParent = NO_PARENT);

  /**
  * Copy constructor
  * @param const CUnitDefinition::& src
  * @param const CCopasiContainer * pParent
  */
  CUnitDefinition(const CUnitDefinition & src,
                  const CCopasiContainer * pParent = NO_PARENT);
  ~CUnitDefinition();

  virtual const std::string & getKey() const;

  static CUnit getSIUnit(const std::string & symbol);

  static void updateSIUnitDefinitions(CUnitDefinitionDB * Units);

  bool setSymbol(const std::string & symbol);

  const std::string & getSymbol() const;

  virtual CIssue setExpression(const std::string & expression);

  CUnitDefinition & operator=(const CUnitDefinition & src);

  static bool isBuiltinUnitSymbol(std::string symbol);

  bool isReadOnly() const;

private:
  std::string mSymbol;
  bool mReadOnly;

  void setup();
};

#endif // CUNIT_DEFINITION_H
