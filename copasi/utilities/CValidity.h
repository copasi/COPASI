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

#include <string>

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
    ExpressionInvalid = 0x1,
    ExpressionEmpty = 0x2,
    MissingInitialValue = 0x4,
    CalculationIssue = 0x8,
    EventMissingAssignment = 0x10,
    EventMissingTriggerExpression = 0x20,
    UnitUndefined = 0x40,
    UnitConflict = 0x80,
    UnitInvalid = 0x100,
    NaNissue = 0x200,
    ObjectNotFound = 0x400,
    ValueNotFound = 0x800,
    VariableNotfound = 0x1000,
    StructureInvalid = 0x2000,
    TooManyArguments = 0x4000,
    HasCircularDependency = 0x8000,
    ExpressionDataTypeInvalid = 0x10000,
    VariableInExpression = 0x20000,
    CExpressionNotFound = 0x40000,
    CFunctionNotFound = 0x80000,
    VariablesMismatch = 0x1000000,
    AllKinds = 0xffffffff
  };

  enum eSeverity
  {
    AllSeverity = 0xffffffff,
    Error = 0x4,
    Warning = 0x2,
    Information = 0x1,
    OK = 0x0
  };

  typedef CFlags< CValidity::eSeverity > Severity;
  typedef CFlags< CValidity::eKind > Kind;

  CValidity();

  CValidity(const CValidity & src);

  // convenience function to reset CValidity
  void clear();

  void add(const CIssue & issue);

  void remove(const CIssue & issue);

  eSeverity getHighestSeverity() const;

  const Kind & get(const eSeverity & severity) const;

  const std::string getIssueMessages() const;

private:
  Kind mErrors;
  Kind mWarnings;
  Kind mInformation;

  const std::string generateIssueMessages(const eSeverity & severity) const;
};

class CIssue
{
public:
  static const CIssue Success;

  // Use this to initialize a CIssue to "false"
  // ("not acceptable"), until it is found to be otherwise.
  static const CIssue Error;

  CIssue(CValidity::Severity severity = CValidity::OK, CValidity::Kind kind = CValidity::NoKind);

  CIssue(const CIssue & src);

  ~CIssue();

  operator bool();

  /**
   * @return whether this issue represents an error or not
   */
  bool isSuccess() const;
  bool isError() const;

  CValidity::Severity mSeverity;
  CValidity::Kind mKind;
};

#endif // COPASI_CValidity
