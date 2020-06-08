// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include <sstream>
#include "CDataString.h"
#include "CRegisteredCommonName.h"

CDataString::CDataString(const std::string & name,
                         const CDataContainer * pParent,
                         const std::string & type,
                         const CFlags< Flag > & flag):
  CDataObject(name, pParent, type, flag | CDataObject::StaticString),
  mStaticString(name)
{}

CDataString::CDataString(const CDataString & src,
                         const CDataContainer * pParent):
  CDataObject(src, pParent),
  mStaticString(src.mStaticString)
{}

CDataString::~CDataString() {}

CDataString & CDataString::operator = (const std::string & rhs)
{
  mStaticString = rhs;
  setObjectName(mStaticString);
  return *this;
}

void CDataString::print(std::ostream * ostream) const
{(*ostream) << mStaticString;}

std::string CDataString::getObjectDisplayName() const
{
  if (mStaticString == "\n")
    return "<linebreak>";

  return "'" + mStaticString + "'";
}

const std::string & CDataString::getStaticString() const
{return mStaticString;}

CCopasiReportSeparator::CCopasiReportSeparator(const std::string & name,
    const CDataContainer * pParent):
  CDataString(name, pParent, "Separator", CDataObject::Separator)
{}

CCopasiReportSeparator::CCopasiReportSeparator(const CDataString & src,
    const CDataContainer * pParent):
  CDataString(src, pParent)
{}

CCopasiReportSeparator::~CCopasiReportSeparator() {}

std::string CCopasiReportSeparator::getObjectDisplayName() const
{return getObjectType();}

CCopasiReportSeparator & CCopasiReportSeparator::operator = (const std::string & rhs)
{
  CDataString::operator =(rhs);
  return *this;
}
