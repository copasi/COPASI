
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

// check if a parameter already existing inside the mParaList
bool COptFunction::bExisted(const std::string & name)
{
  int i;
  for (i = 0; i < mParaList.size(); i++)
    if (mParaList[i]->getCN() == name)
      return true;
  return false;
}

// add a new item inside
int COptFunction::addItem(CCopasiObject* pObject)
{
  if (bExisted(pObject->getCN())
      return - 1; //
      mParaList->push_back(pObject);
      mMinList->push_back("-inf");
      mMaxList->push_back("+inf");
      return mParaList->size();
    }
