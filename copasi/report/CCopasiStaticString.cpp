
#include <sstream>
#include "CCopasiStaticString.h"

using std::string;

CCopasiStaticString::CCopasiStaticString()
    : string()
{}

CCopasiStaticString::CCopasiStaticString(const std::string & name)
    : string(name)
{}

CCopasiStaticString::~CCopasiStaticString()
{
  cleanup();
}

void CCopasiStaticString::cleanup()
{}
