// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CValidity.h"
#include "copasi/core/CObjectInterface.h"

// static
const CIssue CIssue::Success(CIssue::eSeverity::Success);

// static
const CIssue CIssue::Information(CIssue::eSeverity::Information);

// static
const CIssue CIssue::Warning(CIssue::eSeverity::Warning);

// static
const CIssue CIssue::Error(CIssue::eSeverity::Error);

// static
const CEnumAnnotation< std::string, CIssue::eSeverity > CIssue::severityNames(
{
  "success",
  "information",
  "warnings",
  "errors"
});

// static
const CEnumAnnotation< std::string, CIssue::eKind > CIssue::kindNames(
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
});

// static
const CEnumAnnotation< std::string, CIssue::eKind > CIssue::kindDescriptions(
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
});

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
  CValidity result(*this);

  result.mErrors |= rhs.mErrors;
  result.mWarnings |= rhs.mWarnings;
  result.mInformation |= rhs.mInformation;

  return result;
}

CValidity & CValidity::operator = (const CValidity & rhs)
{
  mErrors = rhs.mErrors;
  mWarnings = rhs.mWarnings;
  mInformation = rhs.mInformation;

  if (mpObjectInterface != NULL)
    {
      mpObjectInterface->validityChanged();
    }

  return *this;
}

const CIssue::eSeverity & CIssue::getSeverity() const
{
  return mSeverity;
}

const CIssue::eKind & CIssue::getKind() const
{
  return mKind;
}

CValidity::CValidity(CObjectInterface * pObjectInterface):
  mErrors(),
  mWarnings(),
  mInformation(),
  mpObjectInterface(pObjectInterface)
{}

CValidity::CValidity(const CValidity & src, CObjectInterface * pObjectInterface):
  mErrors(src.mErrors),
  mWarnings(src.mWarnings),
  mInformation(src.mInformation),
  mpObjectInterface(pObjectInterface)
{}

void CValidity::clear()
{
  // Only need to reset, if anything is set (i.e. not already clear)
  if (0 < mErrors.count() + mWarnings.count() + mInformation.count())
    {
      mErrors.reset();
      mWarnings.reset();
      mInformation.reset();

      // Given something changed, notify the parent
      // to do it's thing, if it exists.
      if (mpObjectInterface != NULL)
        {
          mpObjectInterface->validityChanged();
        }
    }
}

bool CValidity::empty() const
{
  return mErrors.count() + mWarnings.count() + mInformation.count() == 0;
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

  if (mpObjectInterface != NULL)
    {
      mpObjectInterface->validityChanged();
    }
}

void CValidity::remove(const CIssue & issue)
{
  size_t Count = 0;
  bool Changed = false;

  switch (issue.getSeverity())
    {
      case CIssue::eSeverity::Error:
        Count = mErrors.count();
        mErrors &= ~Kind(issue.getKind());
        Changed = Count > mErrors.count();
        break;

      case CIssue::eSeverity::Warning:
        Count = mWarnings.count();
        mWarnings &= ~Kind(issue.getKind());
        Changed = Count > mWarnings.count();
        break;

      case CIssue::eSeverity::Information:
        Count = mInformation.count();
        mInformation &= ~Kind(issue.getKind());
        Changed = Count > mInformation.count();
        break;

      case CIssue::eSeverity::__SIZE:
        break;
    }

  if (Changed &&
      mpObjectInterface != NULL)
    {
      mpObjectInterface->validityChanged();
    }
}

void CValidity::remove(const CValidity::Severity & severity,
                       const CValidity::Kind & kind)
{
  size_t Count = mErrors.count() + mWarnings.count() + mInformation.count();

  if (severity.isSet(CIssue::eSeverity::Error))
    mErrors &= ~kind;

  if (severity.isSet(CIssue::eSeverity::Warning))
    mWarnings &= ~kind;

  if (severity.isSet(CIssue::eSeverity::Information))
    mInformation &= ~kind;

  if (mpObjectInterface != NULL &&
      Count > mErrors.count() + mWarnings.count() + mInformation.count())
    {
      mpObjectInterface->validityChanged();
    }
}

CIssue::eSeverity CValidity::getHighestSeverity(const CValidity::Severity & filterSeverity,
    const CValidity::Kind & filterKind) const
{
  if (filterSeverity.isSet(CIssue::eSeverity::Error) &&
      (mErrors & filterKind)) return CIssue::eSeverity::Error;

  if (filterSeverity.isSet(CIssue::eSeverity::Warning) &&
      (mWarnings & filterKind)) return CIssue::eSeverity::Warning;

  if (filterSeverity.isSet(CIssue::eSeverity::Information) &&
      (mInformation & filterKind)) return CIssue::eSeverity::Information;

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
  std::vector< std::string > descriptions;
  std::string messages = "";
  std::vector< std::string >::const_iterator it, end;

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
