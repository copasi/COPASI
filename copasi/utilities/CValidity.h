// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CValidity
#define COPASI_CValidity

#include "copasi/core/CFlags.h"
#include "copasi/core/CEnumAnnotation.h"

#include <string>

class CObjectInterface;

// An object can return an object of this class
// after it checks it's validity
class CIssue
{
public:
  enum struct eKind
  {
    Unknown, // 0
    ExpressionInvalid, // 1
    ExpressionEmpty, // 2
    MissingInitialValue, // 3
    CalculationIssue, //  4
    EventMissingAssignment, //  5
    EventAlreadyHasAssignment, // 6
    EventMissingTriggerExpression, // 7
    UnitUndefined, // 8
    UnitConflict, //  9
    UnitInvalid, // 10
    NaNissue, //  11
    ObjectNotFound, //  12
    ValueNotFound, // 13
    VariableNotfound, //  14
    StructureInvalid, //  15
    TooManyArguments, //  16
    HasCircularDependency, // 17
    ExpressionDataTypeInvalid, // 18
    VariableInExpression, //  19
    CExpressionNotFound, // 20
    CFunctionNotFound, // 21
    VariablesMismatch, // 22
    ValueTypeMismatch, // 23
    InitialExpressionWithAssignment, // 24
    SettingFixedExpression, // 25
    KineticsUndefined, // 26
    __SIZE // 27
  };

  enum struct eSeverity
  {
    Success,
    Information,
    Warning,
    Error,
    __SIZE
  };

  static const CEnumAnnotation< std::string, CIssue::eSeverity > severityNames;
  static const CEnumAnnotation< std::string, CIssue::eKind > kindNames;
  static const CEnumAnnotation< std::string, CIssue::eKind > kindDescriptions;

  static const CIssue Success;
  static const CIssue Information;
  static const CIssue Warning;
  static const CIssue Error;

  CIssue(const eSeverity & severity = eSeverity::Success,
         const eKind & kind = eKind::Unknown);

  CIssue(const CIssue & src);

  ~CIssue();

  operator bool() const;

  CIssue & operator &= (const CIssue & rhs);

  /**
   * Utility method for language bindings where the bool operator is not
   * available. This method returns a flag indicating whether this issue
   * represents a success
   *
   * @return whether this issue represents a success or not
   */
  bool isSuccess() const;

  bool operator == (const CIssue & rhs) const;

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

  CValidity(CObjectInterface * pObjectInterface = NULL);

  CValidity(const CValidity & src, CObjectInterface * pObjectInterface = NULL);

  ~CValidity();

  // convenience function to reset CValidity
  void clear();

  bool empty() const;

  void add(const CIssue & issue);

  void remove(const CIssue & issue);

  void remove(const CValidity::Severity & severity,
              const CValidity::Kind & kind);

  CIssue::eSeverity getHighestSeverity(const CValidity::Severity & filterSeverity = CValidity::Severity::All,
                                       const CValidity::Kind & filterKind = CValidity::Kind::All) const;

  const Kind & get(const CIssue::eSeverity & severity) const;

  const std::string getIssueMessages(const Severity & severityFilter = Severity::All, const Kind & kindFilter = Kind::All) const;

  CValidity & operator = (const CValidity & rhs);

  CValidity & operator |= (const CValidity & rhs);

  const CIssue & getFirstWorstIssue() const;

private:
  Kind mErrors;
  Kind mWarnings;
  Kind mInformation;
  CObjectInterface * mpObjectInterface;
  CIssue mFirstWorstIssue;

  const std::string generateIssueMessages(const CIssue::eSeverity & severity) const;
};

#endif // COPASI_CValidity
