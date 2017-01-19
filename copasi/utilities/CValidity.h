// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CValidity
#define COPASI_CValidity

#include "copasi/utilities/CFlags.h"

class CObjectInterface;

// An object can return an object of this class
// after it checks it's validity
class CIssue;

class CValidity
{
public:
  enum eKind
  {
    NoKind = 0x0,
    MissingInitialValue = 0x1,
    CalculationIssue = 0x2,
    EventMissingAssignment = 0x4,
    EventMissingTriggerExpression = 0x08,
    UnitUndefined = 0x10,
    UnitConflict = 0x20,
    UnitInvalid = 0x40,
    NaNissue = 0x80
  };

  enum eSeverity
  {
    Error = 0x80000000, //32 bit is guaranteed. Set at high end, in case one wanted to bitwise combine with eKind.
    Warning = 0x40000000,
    Information = 0x20000000,
    OK = 0x0
  };

  typedef CFlags< CValidity::eSeverity > Severity;
  typedef CFlags< CValidity::eKind > Kind;

  CValidity();

  CValidity(const CValidity & src);

  void add(const CIssue & issue);

  void remove(const CIssue & issue);

  eSeverity getHighestSeverity() const;

  const Kind & get(const eSeverity & severity) const;

private:
  Kind mErrors;
  Kind mWarnings;
  Kind mInformation;
};

class CIssue
{
public:

  CIssue(CValidity::eSeverity severity = CValidity::OK, CValidity::eKind kind = CValidity::NoKind);

  CIssue(const CIssue & src);

  ~CIssue();

  operator bool();

  CValidity::eSeverity mSeverity;
  CValidity::eKind mKind;
};

#endif // COPASI_CValidity
