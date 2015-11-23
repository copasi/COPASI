// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include <sstream>
#include "CCopasiStaticString.h"
#include "CCopasiObjectName.h"

CCopasiStaticString::CCopasiStaticString(const std::string & name,
    const CCopasiContainer * pParent,
    const std::string & type,
    const unsigned C_INT32 & flag):
  CCopasiObject(name, pParent, type, flag | CCopasiObject::StaticString),
  mStaticString(name)
{}

CCopasiStaticString::CCopasiStaticString(const CCopasiStaticString & src,
    const CCopasiContainer * pParent):
  CCopasiObject(src, pParent),
  mStaticString(src.mStaticString)
{}

CCopasiStaticString::~CCopasiStaticString() {}

CCopasiStaticString & CCopasiStaticString::operator = (const std::string & rhs)
{
  mStaticString = rhs;
  setObjectName(mStaticString);
  return *this;
}

void CCopasiStaticString::print(std::ostream * ostream) const
{(*ostream) << mStaticString;}

std::string CCopasiStaticString::getObjectDisplayName() const
{
  if (mStaticString == "\n")
    return "<linebreak>";

  return "'" + mStaticString + "'";
}

const std::string & CCopasiStaticString::getStaticString() const
{return mStaticString;}

CCopasiReportSeparator::CCopasiReportSeparator(const std::string & name,
    const CCopasiContainer * pParent):
  CCopasiStaticString(name, pParent, "Separator", CCopasiObject::Separator)
{}

CCopasiReportSeparator::CCopasiReportSeparator(const CCopasiStaticString & src,
    const CCopasiContainer * pParent):
  CCopasiStaticString(src, pParent)
{}

CCopasiReportSeparator::~CCopasiReportSeparator() {}

std::string CCopasiReportSeparator::getObjectDisplayName() const
{return getObjectType();}

CCopasiReportSeparator & CCopasiReportSeparator::operator = (const std::string & rhs)
{
  * (CCopasiStaticString *) this = rhs;
  return *this;
}
