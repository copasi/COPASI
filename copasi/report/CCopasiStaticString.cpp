
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
