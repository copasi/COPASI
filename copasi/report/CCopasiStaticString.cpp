/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiStaticString.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:31:47 $
   End CVS Header */

#include <sstream>
#include "CCopasiStaticString.h"

CCopasiStaticString::CCopasiStaticString(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiObject(name, pParent, "String", CCopasiObject::StaticString)
{}

CCopasiStaticString::CCopasiStaticString(const CCopasiStaticString & src,
    const CCopasiContainer * pParent):
    CCopasiObject(src, pParent)
{}

CCopasiStaticString::~CCopasiStaticString() {}

void CCopasiStaticString::cleanup() {}

const std::string & CCopasiStaticString::getStaticString() const
  {return getObjectName();}
