// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CDerive.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/13 13:48:54 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CDerive
#define COPASI_CDerive

#include "copasi.h"

class CEvaluationNode;
class CCopasiObject;
class CEvaluationTree;

class CDerive
  {
  public:

    //private:
    static CEvaluationNode* deriveBranch(const CEvaluationNode* node, unsigned C_INT32 variableIndex, const CCopasiObject * pObject = NULL);

    static void compileTree(CEvaluationNode* node, const CEvaluationTree * pTree);
  };

#endif
