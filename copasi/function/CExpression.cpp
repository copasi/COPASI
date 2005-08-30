/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CExpression.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/08/30 15:40:05 $
   End CVS Header */

#include "copasi.h"

#include "CExpression.h"
#include "CFunctionDB.h"

#include "CopasiDataModel/CCopasiDataModel.h"

CExpression::CExpression(const std::string & name,
                         const CCopasiContainer * pParent):
    CEvaluationTree(name, pParent, Expression),
    mpListOfContainer(NULL),
    mDisplayString("")
{}

CExpression::CExpression(const CExpression & src,
                         const CCopasiContainer * pParent):
    CEvaluationTree(src, pParent),
    mpListOfContainer(NULL),
    mDisplayString(src.mDisplayString)
{}

CExpression::~CExpression() {}

bool CExpression::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  mpListOfContainer = & listOfContainer;

  if (mpRoot)
    mDisplayString = mpRoot->getDisplayString(this);
  else
    mDisplayString = "";

  return compileNodes();
}

const C_FLOAT64 & CExpression::calcValue()
{
  try
    {
      return mValue = mpRoot->value();
    }
  catch (...)
    {
      return mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }
}

const CCopasiObject * CExpression::getObject(const CCopasiObjectName & CN) const
  {return CCopasiContainer::ObjectFromName(*mpListOfContainer, CN);}

const std::vector< CCopasiContainer * > & CExpression::getListOfContainer() const
  {return *mpListOfContainer;}

bool CExpression::updateInfix()
{
  if (mpNodeList == NULL) return false;

  mInfix = mpRoot->getInfix();

  return true;
}

const std::string & CExpression::getDisplayString() const
{return mDisplayString;}
