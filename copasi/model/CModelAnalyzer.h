// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelAnalyzer.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/22 16:53:54 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CModelAnalyzer
#define COPASI_CModelAnalyzer

#include <vector>

class CModel;
class CReaction;

class CModelAnalyzer
  {
  public:

    static void checkModel(std::ostream & os, const CModel* model);

    static void checkReaction(std::ostream & os, const CReaction* reaction, const CModel* model);
  };

#endif
