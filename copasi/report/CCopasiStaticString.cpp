/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiStaticString.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:01 $
   End CVS Header */

#include "copasi.h"

#include <sstream>
#include "CCopasiStaticString.h"
#include "CCopasiObjectName.h"

CCopasiStaticString::CCopasiStaticString(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiObject(name, pParent, "String", CCopasiObject::StaticString),
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

const std::string & CCopasiStaticString::getStaticString() const
  {return mStaticString;}
