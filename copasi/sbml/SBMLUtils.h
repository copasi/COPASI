// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLUtils.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/13 16:46:05 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SBMLUTILS_H__
#define SBMLUTILS_H__

#include <string>
//#include <map>
#include "sbml/math/ASTNode.h"

#include "function/CFunctionDB.h"
#include "sbml/StdException.h"
#include "sbml/UnitDefinition.h"
#include "model/CModel.h"

class SBase;

class SBMLUtils
  {
  public:

    /**
     * Return the sbml ID if the sbml object actually has one.
     * If not, it returns "".
     * It only handles core sbml objects. No layout objects yet.
     */
    static std::string getIdFromSBase(const SBase* s);

  protected:

    template<class CType>
    static std::string getId(const CType * pA, C_INT32 level = 2);
  };

#endif
