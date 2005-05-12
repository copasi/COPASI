/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiStaticString.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/12 11:37:46 $
   End CVS Header */

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

std::string CCopasiStaticString::getObjectDisplayName(bool regular /*=true*/,
    bool richtext /*=false*/) const
  {return "'" + mStaticString + "'";}

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

std::string CCopasiReportSeparator::getObjectDisplayName(bool regular /*=true*/,
    bool richtext /*=false*/) const
  {return getObjectType();}

CCopasiReportSeparator & CCopasiReportSeparator::operator = (const std::string & rhs)
{
  * (CCopasiStaticString *) this = rhs;
  return *this;
}
