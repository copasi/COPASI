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
const std::array<const char *, static_cast< size_t >(CIssue::eSeverity::__SIZE) > CIssue::severityNames =
{
  "success",
  "information",
  "warnings",
  "errors"
};

// static
const std::array<const char *, static_cast< size_t >(CIssue::eKind::__SIZE) > CIssue::kindNames =
{
  "unknown issue",
  "invalid expression",
  "empty expression",
  "missing initial value",
  "calculation problem",
  "missing event assignment",
  "missing event trigger expression",
  "undefined unit",
  "unit conflict",
  "invalid unit",
  "undefined or unrepresentable value",
  "unfound object",
  "unfound value",
  "unfound variable",
  "Invalid structure",
  "excess arguments",
  "circular dependency",
  "invalid expression data type",
  "variable in expression",
  "unfound CExpression",
  "unfound CFunction",
  "mismatched variables",
  "inconsistent value types"
};

// static
const std::array<const char *, static_cast< size_t >(CIssue::eKind::__SIZE) > CIssue::kindDescriptions =
{
  "Unknown issue.",
  "Invalid expression.",
  "Empty expression.",
  "Missing initial value.",
  "Problem with calculation.",
  "Missing event assignment.",
  "Missing event trigger expression.",
  "Unit is undefined.",
  "Conflicting units.",
  "Invalid unit.",
  "Value is undefined or unrepresentable.",
  "Object not found.",
  "Value not found.",
  "Variable not found.",
  "Invalid structure.",
  "Too many arguments.",
  "Has circular dependency.",
  "Invalid expression data type.",
  "Expression contains a variable.",
  "CExpression not found.",
  "CFunction not found.",
  "Variables are mismatched.",
  "Inconsistent value types encountered."
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

CIssue & CIssue::operator &= (const CIssue & rhs)
{
  if (rhs.mSeverity > mSeverity)
    {
      mSeverity = rhs.mSeverity;
      mKind = rhs.mKind;
    }

  return *this;
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
  mErrors.reset();
  mWarnings.reset();
  mInformation.reset();
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

const std::string CValidity::getIssueMessages(const Severity & severityFilter,
    const Kind & kindFilter) const
{
  std::string severityString = "";
  std::vector< const char * > descriptions;
  std::string messages = "";
  std::vector< const char * >::const_iterator it, end;

  if (severityFilter.isSet(CIssue::eSeverity::Error))
    {
      severityString = "Error: ";
      descriptions = mErrors.getAnnotations(CIssue::kindDescriptions, kindFilter);

      it = descriptions.begin();
      end = descriptions.end();

      for (; it != end; ++it)
        {
          messages += severityString + *it + "\n";
        }
    }

  if (severityFilter.isSet(CIssue::eSeverity::Warning))
    {
      severityString = "Warning: ";
      descriptions = mWarnings.getAnnotations(CIssue::kindDescriptions, kindFilter);

      it = descriptions.begin();
      end = descriptions.end();

      for (; it != end; ++it)
        {
          messages += severityString + *it + "\n";
        }
    }

  if (severityFilter.isSet(CIssue::eSeverity::Information))
    {
      severityString = "Information: ";
      descriptions = mInformation.getAnnotations(CIssue::kindDescriptions, kindFilter);

      it = descriptions.begin();
      end = descriptions.end();

      for (; it != end; ++it)
        {
          messages += severityString + *it + "\n";
        }
    }

  // Remove last newline
  if (!messages.empty())
    messages = messages.substr(0, messages.size() - 1);

  return messages;
}