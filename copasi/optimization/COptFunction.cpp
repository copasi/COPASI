
#include <sstream>
#include "copasi.h"
#include "FlexLexer.h"
#include "function/CFunction.h"
#include "COptFunction.h"

COptFunction::COptFunction(const std::string & name, const CCopasiContainer * pParent)
    : CKinFunction(name, pParent)
{}

COptFunction::COptFunction(const CFunction & src, CReadConfig * configBuffer, const CCopasiContainer * pParent)
    : CKinFunction(src, configBuffer, pParent)
{}

COptFunction::COptFunction(const CKinFunction & src, const CCopasiContainer * pParent)
    : CKinFunction(src, pParent)
{}

COptFunction::~COptFunction()
{
  cleanup();
}

void COptFunction::cleanup()
{}
