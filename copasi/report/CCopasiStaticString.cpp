/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiStaticString.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/12 22:14:25 $
   End CVS Header */

#include "copasi.h"

#include <sstream>
#include "CCopasiStaticString.h"
#include "CCopasiObjectName.h"

CCopasiStaticString::CCopasiStaticString(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiObject(name, pParent, "String", CCopasiObject::StaticString),
    mStaticString(name)
{setObjectName(CCopasiObjectName::escape(mStaticString));}

CCopasiStaticString::CCopasiStaticString(const CCopasiStaticString & src,
    const CCopasiContainer * pParent):
    CCopasiObject(src, pParent),
    mStaticString(src.mStaticString)
{}

CCopasiStaticString::~CCopasiStaticString() {}

CCopasiStaticString & CCopasiStaticString::operator = (const std::string & rhs)
{
  mStaticString = rhs;
  setObjectName(CCopasiObjectName::escape(mStaticString));
  return *this;
}

void CCopasiStaticString::print(std::ostream * ostream) const
  {(*ostream) << mStaticString;}

const std::string & CCopasiStaticString::getStaticString() const
  {return mStaticString;}
