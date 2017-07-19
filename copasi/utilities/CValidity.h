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
    Unknown,
    ExpressionInvalid,
    ExpressionEmpty,
    MissingInitialValue,
    CalculationIssue,
    EventMissingAssignment,
    EventAlreadyHasAssignment,
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
    ValueTypeMismatch,
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

  operator bool();

  CIssue & operator &= (const CIssue & rhs);

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

private:
  Kind mErrors;
  Kind mWarnings;
  Kind mInformation;
  CObjectInterface * mpObjectInterface;

  const std::string generateIssueMessages(const CIssue::eSeverity & severity) const;
};

#endif // COPASI_CValidity
