// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
    const CDataContainer * pParent,
    const std::string & type,
    const CFlags< Flag > & flag):
  CDataObject(name, pParent, type, flag | CDataObject::StaticString),
  mStaticString(name)
{}

CCopasiStaticString::CCopasiStaticString(const CCopasiStaticString & src,
    const CDataContainer * pParent):
  CDataObject(src, pParent),
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
    const CDataContainer * pParent):
  CCopasiStaticString(name, pParent, "Separator", CDataObject::Separator)
{}

CCopasiReportSeparator::CCopasiReportSeparator(const CCopasiStaticString & src,
    const CDataContainer * pParent):
  CCopasiStaticString(src, pParent)
{}

CCopasiReportSeparator::~CCopasiReportSeparator() {}

std::string CCopasiReportSeparator::getObjectDisplayName() const
{return getObjectType();}

CCopasiReportSeparator & CCopasiReportSeparator::operator = (const std::string & rhs)
{
  CCopasiStaticString::operator =(rhs);
  return *this;
}
