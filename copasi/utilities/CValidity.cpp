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
const CIssue CIssue::Success(CIssue::eSeverity::Success);

// static
const CIssue CIssue::Information(CIssue::eSeverity::Information);

// static
const CIssue CIssue::Warning(CIssue::eSeverity::Warning);

// static
const CIssue CIssue::Error(CIssue::eSeverity::Error);

// static
const std::array<const char *, static_cast< size_t >(CIssue::eKind::__SIZE) > CIssue::kindDescriptions =
{
  "Unknown.\n",
  "Invalid expression.\n",
  "Empty expression.\n",
  "Missing initial value.\n",
  "Problem with calculation.\n",
  "Missing event assignment.\n",
  "Missing event trigger expression.\n",
  "Unit is undefined.\n",
  "Unit conflict.\n",
  "Invalid unit.\n",
  "Value is undefined or unrepresentable.\n",
  "Object not found.\n",
  "Value not found.\n",
  "Variable not found.\n",
  "Invalid structure.\n",
  "Too many arguments.\n",
  "Has circular dependency.\n",
  "Invalid expression data type.\n",
  "Expression contains a variable.\n",
  "CExpression not found.\n",
  "CFunction not found.\n",
  "Variables are mismatched.\n"
};

CIssue::CIssue(const CIssue::eSeverity & severity,
               const CIssue::eKind & kind):
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
  return (mSeverity != CIssue::eSeverity::Error);
}

bool CIssue::isError() const
{
  return !isSuccess();
}

bool CIssue::isSuccess() const
{
  return (mSeverity != CIssue::eSeverity::Error);
}

CValidity CValidity::operator | (const CValidity & rhs) const
{
  CValidity result;

  result.mErrors |= rhs.mErrors;
  result.mWarnings |= rhs.mWarnings;
  result.mInformation |= rhs.mInformation;

  return result;
}

const CIssue::eSeverity & CIssue::getSeverity() const
{
  return mSeverity;
}

const CIssue::eKind & CIssue::getKind() const
{
  return mKind;
}

CValidity::CValidity():
  mErrors(),
  mWarnings(),
  mInformation()
{}

CValidity::CValidity(const CValidity & src):
  mErrors(src.mErrors),
  mWarnings(src.mWarnings),
  mInformation(src.mInformation)
{}

void CValidity::clear()
{
  mErrors.clear();
  mWarnings.clear();
  mInformation.clear();
}

void CValidity::add(const CIssue & issue)
{
  switch (issue.getSeverity())
    {
      case CIssue::eSeverity::Error:
        mErrors |= issue.getKind();
        break;

      case CIssue::eSeverity::Warning:
        mWarnings |= issue.getKind();
        break;

      case CIssue::eSeverity::Information:
        mInformation |= issue.getKind();
        break;

      default:
        break;
    }
}

void CValidity::remove(const CIssue & issue)
{
  switch (issue.getSeverity())
    {
      case CIssue::eSeverity::Error:
        mErrors &= ~Kind(issue.getKind());
        break;

      case CIssue::eSeverity::Warning:
        mWarnings &= ~Kind(issue.getKind());
        break;

      case CIssue::eSeverity::Information:
        mInformation &= ~Kind(issue.getKind());
        break;
    }
}

void CValidity::remove(const CValidity::Severity & severity,
                       const CValidity::Kind & kind)
{
  if (severity.isSet(CIssue::eSeverity::Error))
    mErrors &= ~kind;

  if (severity.isSet(CIssue::eSeverity::Warning))
    mWarnings &= ~kind;

  if (severity.isSet(CIssue::eSeverity::Information))
    mInformation &= ~kind;
}

CIssue::eSeverity CValidity::getHighestSeverity() const
{
  if (mErrors) return CIssue::eSeverity::Error;

  if (mWarnings) return CIssue::eSeverity::Warning;

  if (mInformation) return CIssue::eSeverity::Information;

  return CIssue::eSeverity::Success;
}

const CValidity::Kind & CValidity::get(const CIssue::eSeverity & severity) const
{
  static const Kind OK;

  switch (severity)
    {
      case CIssue::eSeverity::Error:
        return mErrors;
        break;

      case CIssue::eSeverity::Warning:
        return mWarnings;
        break;

      case CIssue::eSeverity::Information:
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

  messages += generateIssueMessages(CIssue::eSeverity::Error);
  messages += generateIssueMessages(CIssue::eSeverity::Warning);
  messages += generateIssueMessages(CIssue::eSeverity::Information);

  // Remove last newline
  if (!messages.empty())
    messages = messages.substr(0, messages.size() - 1);

  return messages;
}

const std::string CValidity::generateIssueMessages(const CIssue::eSeverity & severity) const
{
  std::string severityString = "";
  std::string messages = "";
  std::vector< const char * > descriptions;

  switch (severity)
    {
      case CIssue::eSeverity::Error:
        severityString = "Error: ";
        descriptions = mErrors.getAnnotations(CIssue::kindDescriptions);
        break;

      case CIssue::eSeverity::Warning:
        severityString = "Warning: ";
        descriptions = mWarnings.getAnnotations(CIssue::kindDescriptions);
        break;

      case CIssue::eSeverity::Information:
        severityString = "Information: ";
        descriptions = mInformation.getAnnotations(CIssue::kindDescriptions);
        break;

      default:
        break;
    }

  std::vector< const char * >::const_iterator it = descriptions.begin();
  std::vector< const char * >::const_iterator end = descriptions.end();

  for (; it != end; ++it)
    {
      messages += severityString + *it;
    }

  return messages;
}
