/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationTree.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 17:48:57 $
   End CVS Header */

#include "copasi.h"

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

CEvaluationTree::CEvaluationTree():
    CCopasiTree<CEvaluationNode>()
{}

CEvaluationTree::~CEvaluationTree()
{}

C_FLOAT64 * CEvaluationTree::getVariableValue(const std::string & /* name */) const
  {return NULL;}

C_FLOAT64 * CEvaluationTree::getObjectValue(const CCopasiObjectName & /* CN */) const
  {return NULL;}
