// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CValidity.h"

// static
const CIssue CIssue::Success;

//static
const CIssue CIssue::Error = CIssue(CValidity::Error, CValidity::NoKind);

CIssue::CIssue(CValidity::Severity severity, CValidity::Kind kind):
  mSeverity(severity),
  mKind(kind)
{}

CIssue::CIssue(const CIssue & src):
  mSeverity(src.mSeverity),
  mKind(src.mKind)
{}

CIssue::~CIssue()
{}

CIssue::operator bool()
{
  // If this type is implicity cast to a bool, in a conditional
  // evaluation, it will evaluate to "true" that there IS NOT a
  // significant "issue", if it is not at "Error" severity.
  return (mSeverity != CValidity::Error);
}

CValidity::CValidity():
  mErrors(NoKind),
  mWarnings(NoKind),
  mInformation(NoKind)
{}

CValidity::CValidity(const CValidity & src):
  mErrors(src.mErrors),
  mWarnings(src.mWarnings),
  mInformation(src.mInformation)
{}

void CValidity::clear()
{
  mErrors = NoKind;
  mWarnings = NoKind;
  mInformation = NoKind;
}

void CValidity::add(const CIssue & issue)
{
  switch (issue.mSeverity)
    {
      case Error:
        mErrors |= issue.mKind;
        break;

      case Warning:
        mWarnings |= issue.mKind;
        break;

      case Information:
        mInformation |= issue.mKind;
        break;

      default:
        break;
    }
}

void CValidity::remove(const CIssue & issue)
{
  if (issue.mSeverity & Error) mErrors = mErrors & ~issue.mKind;

  if (issue.mSeverity & Warning) mWarnings = mWarnings & ~issue.mKind;

  if (issue.mSeverity & Information) mInformation = mInformation & ~issue.mKind;
}

CValidity::eSeverity CValidity::getHighestSeverity() const
{
  if (mErrors > 0) return Error;

  if (mWarnings > 0) return Warning;

  if (mInformation > 0) return Information;

  return OK;
}

const CValidity::Kind & CValidity::get(const CValidity::eSeverity & severity) const
{
  static Kind OK;

  switch (severity)
    {
      case Error:
        return mErrors;
        break;

      case Warning:
        return mWarnings;
        break;

      case Information:
        return mInformation;
        break;

      default:
        return OK;
        break;
    }
}

const std::string CValidity::getIssueMessages() const
{
  std::string messages = "";

  messages += generateIssueMessages(Error);
  messages += generateIssueMessages(Warning);
  messages += generateIssueMessages(Information);

  // Remove last newline
  if (!messages.empty())
    messages = messages.substr(0, messages.size() - 1);

  return messages;
}

const std::string CValidity::generateIssueMessages(const CValidity::eSeverity & severity) const
{
  std::string severityString = "";
  std::string messages = "";
  Kind tmpKind;

  switch (severity)
    {
      case Error:
        severityString = "Error: ";
        tmpKind = mErrors;
        break;

      case Warning:
        severityString = "Warning: ";
        tmpKind = mWarnings;
        break;

      case Information:
        severityString = "Information: ";
        tmpKind = mInformation;
        break;

      default:
        break;
    }

  if (tmpKind & ExpressionInvalid)
    messages += severityString + "Invalid expression.\n";

  if (tmpKind & ExpressionEmpty)
    messages += severityString + "Empty expression.\n";

  if (tmpKind & MissingInitialValue)
    messages += severityString + "Missing initial value.\n";

  if (tmpKind & CalculationIssue)
    messages += severityString + "Problem with calculation.\n";

  if (tmpKind & EventMissingAssignment)
    messages += severityString + "Missing event assignment.\n";

  if (tmpKind & EventMissingTriggerExpression)
    messages += severityString + "Missing event trigger expression.\n";

  if (tmpKind & UnitUndefined)
    messages += severityString + "Unit is undefined.\n";

  if (tmpKind & UnitConflict)
    messages += severityString + "Unit conflict.\n";

  if (tmpKind & UnitInvalid)
    messages += severityString + "Invalid unit.\n";

  if (tmpKind & NaNissue)
    messages += severityString + "Value is undefined or unrepresentable.\n";

  if (tmpKind & ObjectNotFound)
    messages += severityString + "Object not found.\n";

  if (tmpKind & ValueNotFound)
    messages += severityString + "Value not found.\n";

  if (tmpKind & VariableNotfound)
    messages += severityString + "Variable not found.\n";

  if (tmpKind & StructureInvalid)
    messages += severityString + "Invalid structure.\n";

  if (tmpKind & TooManyArguments)
    messages += severityString + "Too many arguments.\n";

  if (tmpKind & HasCircularDependency)
    messages += severityString + "Has circular dependency.\n";

  if (tmpKind & ExpressionDataTypeInvalid)
    messages += severityString + "Invalid expression data type.\n";

  if (tmpKind & VariableInExpression)
    messages += severityString + "Expression contains a variable.\n";

  if (tmpKind & CExpressionNotFound)
    messages += severityString + "CExpression not found.\n";

  if (tmpKind & CFunctionNotFound)
    messages += severityString + "CFunction not found.\n";

  if (tmpKind & VariablesMismatch)
    messages += severityString + "Variables are mismatched.\n";

  return messages;
}
