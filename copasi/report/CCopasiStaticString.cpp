/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiStaticString.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/05 14:36:45 $
   End CVS Header */

#include "copasi.h"

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
