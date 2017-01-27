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
  if (issue.mSeverity & Error) mErrors & ~issue.mKind;

  if (issue.mSeverity & Warning) mWarnings & ~issue.mKind;

  if (issue.mSeverity & Information) mInformation & ~issue.mKind;
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
