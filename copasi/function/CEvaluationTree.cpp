/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationTree.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 19:12:36 $
   End CVS Header */

#include "copasi.h"

#include <sstream>
#include <vector>

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#undef yyFlexLexer
#define yyFlexLexer CEvaluationFlexLexer
#include "CEvaluationFlexLexer.h"

CEvaluationTree::CEvaluationTree():
    CCopasiTree<CEvaluationNode>(),
    mDescription(),
    mErrorPosition(std::string::npos)
{}

CEvaluationTree::~CEvaluationTree()
{}

bool CEvaluationTree::setDescription(const std::string & description)
{
  mDescription = description;

  return compile();
}

bool CEvaluationTree::compile()
{
  if (!parse()) return false;
  if (!linkNodes()) return false;
  if (!compileNodes()) return false;

  return true;
}

C_FLOAT64 * CEvaluationTree::getVariableValue(const std::string & /* name */) const
{return NULL;}

C_FLOAT64 * CEvaluationTree::getObjectValue(const CCopasiObjectName & /* CN */) const
  {return NULL;}

bool CEvaluationTree::parse()
{
  std::istringstream buffer(mDescription);

  CEvaluationFlexLexer Scanner(&buffer);

  mErrorPosition = Scanner.yylex();
  mpNodeList = Scanner.getNodeList();
  if (mErrorPosition < mDescription.length())
    {
      CEvaluationFlexLexer::freeNodeList(mpNodeList);
      mpNodeList = NULL;
      return false;
    }

  mErrorPosition = std::string::npos;
  return true;
}

bool CEvaluationTree::linkNodes()
{
  return true;
}

bool CEvaluationTree::compileNodes()
{
  return true;
}
