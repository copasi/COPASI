/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CExpression.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/25 12:43:28 $
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

void CExpression::initObjects()
{
  CCopasiObject * pObject =
    const_cast< CCopasiObject * >(getObject(CCopasiObjectName("Reference=Value")));
  assert (pObject != NULL);

  pObject->setRefresh(this, &CExpression::refresh);
}

bool CExpression::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  mpListOfContainer = & listOfContainer;

  if (mpRoot)
    mDisplayString = mpRoot->getDisplayString(this);
  else
    mDisplayString = "";

  bool success = compileNodes();

  if (success)
    {
      const CCopasiObject * pObject;
      std::set< const CCopasiObject * > Dependencies;

      std::vector< CEvaluationNode * >::const_iterator it = mpNodeList->begin();
      std::vector< CEvaluationNode * >::const_iterator end = mpNodeList->end();

      for (; it != end; ++it)
        if (((*it)->getType() & 0xFF000000) == CEvaluationNode::CALL &&
            (pObject = getNodeObject((*it)->getData())) != NULL)
          Dependencies.insert(pObject);

      const_cast< CCopasiObject * >(getObject(CCopasiObjectName("Reference=Value")))->setDirectDependencies(Dependencies);
    }

  return success;
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

void CExpression::refresh()
{calcValue();}

const CCopasiObject * CExpression::getNodeObject(const CCopasiObjectName & CN) const
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
