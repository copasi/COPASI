// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CValidity.h"

Issue::Issue(eKind kind, eSeverity severity):
  mKind(kind),
  mSeverity(severity)
{}

Issue::operator bool()
{
  // If this type is implicity cast to a bool, in a conditional
  // evaluation, it will evaluate to "true" that there IS a
  // significant "issue", if it is at "Error" severity.
  return (mSeverity == Error);
}

CValidity::CValidity():
  mErrors(NoKind),
  mWarnings(NoKind),
  mInformation(NoKind)
{
}

void CValidity::add(Issue issue)
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
