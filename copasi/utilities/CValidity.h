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
    Unknown,
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
    Success,
    Information,
    Warning,
    Error,
    __SIZE
  };

  static const std::array<const char *, static_cast< size_t >(CIssue::eKind::__SIZE) > kindNames;
  static const std::array<const char *, static_cast< size_t >(CIssue::eKind::__SIZE) > kindDescriptions;

  static const CIssue Success;
  static const CIssue Information;
  static const CIssue Warning;
  static const CIssue Error;

  CIssue(const eSeverity & severity = eSeverity::Success,
         const eKind & kind = eKind::Unknown);

  CIssue(const CIssue & src);

  ~CIssue();

  operator bool();

  /**
   * Utility method for language bindings where the bool operator is not
   * available. This method returns a flag indicating whether this issue
   * represents a success
   *
   * @return whether this issue represents a success or not
   */
  bool isSuccess() const;

  /**
   * Utility method for language bindings where the bool operator is not
   * available. This method returns a flag indicating whether this issue
   * represents an error
   *
   * @return whether this issue represents an error or not
   */
  bool isError() const;

  const eSeverity & getSeverity() const;

  const eKind & getKind() const;

private:
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

  CValidity operator | (const CValidity & rhs) const;

private:
  Kind mErrors;
  Kind mWarnings;
  Kind mInformation;

  const std::string generateIssueMessages(const CIssue::eSeverity & severity) const;
};

#endif // COPASI_CValidity
