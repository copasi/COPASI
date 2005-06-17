/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CExpression.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/17 15:14:18 $
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
{return mpRoot->value();}

C_FLOAT64 * CExpression::getObjectValue(const CCopasiObjectName & CN) const
  {return (C_FLOAT64 *) CCopasiContainer::ObjectFromName(*mpListOfContainer, CN)->getReference();}
