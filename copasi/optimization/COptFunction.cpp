
#include <sstream>
#include "copasi.h"
#include "FlexLexer.h"
#include "function/CFunction.h"
#include "COptFunction.h"
#include "COptMethod.h"
#include "COptProblem.h"

COptFunction::COptFunction(const std::string & name, const CCopasiContainer * pParent)
    : CKinFunction(name, pParent),
    mpMethod(new COptMethod),
    mpProblem(new COptProblem)
{
  mpMethod->setProblem(mpProblem);
  mParaList.clear();
  mMinList.clear();
  mMaxList.clear();
}

COptFunction::COptFunction(const COptFunction & src, CReadConfig * configBuffer, const CCopasiContainer * pParent)
    : CKinFunction(src, configBuffer, pParent) ,
    mpMethod(src.mpMethod),
    mpProblem(src.mpProblem)
{
  mpMethod->setProblem(mpProblem);
  mParaList.clear();
  mMinList.clear();
  mMaxList.clear();
}

COptFunction::~COptFunction()
{
  cleanup();
}

void COptFunction::cleanup()
{
  //static members will be deleted during the deconstruction of COptFunction
  mParaList.clear();
  mMinList.clear();
  mMaxList.clear();
}
