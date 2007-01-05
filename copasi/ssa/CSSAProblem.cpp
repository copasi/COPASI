/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/ssa/Attic/CSSAProblem.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/09/12 15:16:20 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CSSAProblem.h"
#include "CopasiDataModel/CCopasiDataModel.h"

CSSAProblem::CSSAProblem(const CCopasiContainer * pParent)
    : CCopasiProblem(CCopasiTask::ssa, pParent)
{}

CSSAProblem::CSSAProblem(const CSSAProblem & src,
                          const CCopasiContainer * pParent)
    : CCopasiProblem(src, pParent)
{}

CSSAProblem::~CSSAProblem()
{DESTRUCTOR_TRACE;}
