/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CExpression.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2005/06/21 20:58:56 $
   End CVS Header */

#include "copasi.h"

#include "CExpression.h"
#include "CFunctionDB.h"

#include "CopasiDataModel/CCopasiDataModel.h"

CExpression::CExpression(const std::string & name,
                         const CCopasiContainer * pParent):
    CEvaluationTree(name, pParent),
    mpListOfContainer(NULL)
{
  if (CCopasiDataModel::Global)
    CCopasiDataModel::Global->getFunctionList()->loadedFunctions().add(this, false);
}

CExpression::CExpression(const CExpression & src,
                         const CCopasiContainer * pParent):
    CEvaluationTree(src, pParent),
    mpListOfContainer(NULL)
{
  if (CCopasiDataModel::Global)
    CCopasiDataModel::Global->getFunctionList()->loadedFunctions().add(this, false);
}

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
