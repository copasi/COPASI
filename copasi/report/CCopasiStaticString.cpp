
#include <sstream>
#include "CCopasiStaticString.h"

using std::string;

CCopasiStaticString::CCopasiStaticString()
    : strObject()
{}

CCopasiStaticString::CCopasiStaticString(const std::string & name)
    : strObject(name)
{}

CCopasiStaticString::~CCopasiStaticString()
{
  cleanup();
}

void CCopasiStaticString::cleanup()
{}
