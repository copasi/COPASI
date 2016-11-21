// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CValidity.h"

CIssue::CIssue(CValidity::eSeverity severity, CValidity::eKind kind):
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
  // evaluation, it will evaluate to "true" that there IS a
  // significant "issue", if it is at "Error" severity.
  return (mSeverity == CValidity::Error);
}

CValidity::CValidity():
  mErrors(NoKind),
  mWarnings(NoKind),
  mInformation(NoKind)
{}

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

void CValidity::remove(const CValidity::Kind & kind)
{
  mErrors & ~kind;
  mWarnings & ~kind;
  mInformation & ~kind;
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
