
#include <sstream>
#include "copasi.h"
#include "FlexLexer.h"
#include "function/CFunction.h"
#include "CExpression.h"

CExpression::CExpression(const std::string & name, const CCopasiContainer * pParent)
    : CKinFunction(name, pParent)
{}

CExpression::CExpression(const CFunction & src, CReadConfig * configBuffer, const CCopasiContainer * pParent)
    : CKinFunction(src, configBuffer, pParent)
{}

CExpression::CExpression(const CKinFunction & src, const CCopasiContainer * pParent)
    : CKinFunction(src, pParent)
{}

CExpression::~CExpression()
{
  cleanup();
}

void CExpression::cleanup()
{}
