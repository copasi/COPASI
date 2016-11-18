// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CValidity
#define COPASI_CValidity

#include "copasi/utilities/CFlags.h"

class CObjectInterface;

enum eKind
{
  NoKind = 0x0,
  MissingInitialValue = 0x1,
  CalculationIssue = 0x2,
  EventMissingAssignment = 0x4,
  EventMissingTriggerExpression = 0x10,
  UnitUndefined = 0x20,
  UnitConflict = 0x40,
  NaNissue = 0x80
};

enum eSeverity
{
  Error = 0x80000000, //32 bit is guaranteed. Set at high end, in case one wanted to bitwise combine with eKind.
  Warning = 0x40000000,
  Information = 0x20000000,
  NoSeverity = 0x0
};

// An object can return an object of this class
// after it checks it's validity
class Issue
{
public:

  Issue(eKind kind = NoKind, eSeverity severity = NoSeverity);

  operator bool();

  CFlags< eKind > mKind;
  CFlags< eSeverity > mSeverity;
};

class CValidity
{
public:

  CValidity();

  void add(Issue issue);

  CFlags< eKind > mErrors;
  CFlags< eKind > mWarnings;
  CFlags< eKind > mInformation;
};

#endif // COPASI_CValidity
