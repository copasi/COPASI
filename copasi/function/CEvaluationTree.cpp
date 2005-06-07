/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationTree.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/07 15:18:54 $
   End CVS Header */

#include "copasi.h"

#include <sstream>
#include <vector>

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "CEvaluationLexer.h"

CEvaluationTree::CEvaluationTree():
    mDescription(),
    mErrorPosition(std::string::npos),
    mpRoot(NULL)
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

  CEvaluationLexer Scanner(&buffer);

  Scanner.yyparse();

  pdelete(mpRoot);

  mpRoot = Scanner.getRootNode();
  mpNodeList = Scanner.getNodeList();

  /*
  mErrorPosition = Scanner.yylex();
  if (mErrorPosition < mDescription.length())
    {
      CEvaluationLexer::freeNodeList(mpNodeList);
      mpNodeList = NULL;
      return false;
    }

  mErrorPosition = std::string::npos;
  */

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
