/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CExpression.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/17 16:18:33 $
   End CVS Header */

#include "copasi.h"

#include "CExpression.h"

CExpression::CExpression(const std::string & name,
                         const CCopasiContainer * pParent):
    CEvaluationTree(name, pParent),
    mpListOfContainer(NULL)
{}

CExpression::CExpression(const CExpression & src,
                         const CCopasiContainer * pParent):
    CEvaluationTree(src, pParent),
    mpListOfContainer(NULL)
{}

CExpression::~CExpression() {}

bool CExpression::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  mpListOfContainer = & listOfContainer;
  return compileNodes();
}

C_FLOAT64 CExpression::calcValue()
{
  try
    {
      return mpRoot->value();
    }
  catch (...)
    {
      return std::numeric_limits<C_FLOAT64>::signaling_NaN();
    }
}

C_FLOAT64 * CExpression::getObjectValue(const CCopasiObjectName & CN) const
  {return (C_FLOAT64 *) CCopasiContainer::ObjectFromName(*mpListOfContainer, CN)->getReference();}
