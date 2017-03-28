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
class CIssue
{
public:
  enum struct eKind
  {
    NoKind,
    ExpressionInvalid,
    ExpressionEmpty,
    MissingInitialValue,
    CalculationIssue,
    EventMissingAssignment,
    EventMissingTriggerExpression,
    UnitUndefined,
    UnitConflict,
    UnitInvalid,
    NaNissue,
    ObjectNotFound,
    ValueNotFound,
    VariableNotfound,
    StructureInvalid,
    TooManyArguments,
    HasCircularDependency,
    ExpressionDataTypeInvalid,
    VariableInExpression,
    CExpressionNotFound,
    CFunctionNotFound,
    VariablesMismatch,
    __SIZE
  };

  enum struct eSeverity
  {
    OK,
    Information,
    Warning,
    Error,
    __SIZE
  };

  static const CIssue Success;

  // Use this to initialize a CIssue to "false"
  // ("not acceptable"), until it is found to be otherwise.
  static const CIssue Error;

  CIssue(const eSeverity & severity = eSeverity::OK,
         const eKind & kind = eKind::NoKind);

  CIssue(const CIssue & src);

  ~CIssue();

  operator bool();

  /**
   * @return whether this issue represents an error or not
   */
  bool isSuccess() const;
  bool isError() const;

  eSeverity mSeverity;
  eKind mKind;
};

class CValidity
{
public:

  typedef CFlags< CIssue::eSeverity > Severity;
  typedef CFlags< CIssue::eKind > Kind;

  CValidity();

  CValidity(const CValidity & src);

  // convenience function to reset CValidity
  void clear();

  void add(const CIssue & issue);

  void remove(const CIssue & issue);

  void remove(const CValidity::Severity & severity,
              const CValidity::Kind & kind);

  CIssue::eSeverity getHighestSeverity() const;

  const Kind & get(const CIssue::eSeverity & severity) const;

  const std::string getIssueMessages() const;

private:
  Kind mErrors;
  Kind mWarnings;
  Kind mInformation;

  const std::string generateIssueMessages(const CIssue::eSeverity & severity) const;
};

#endif // COPASI_CValidity
