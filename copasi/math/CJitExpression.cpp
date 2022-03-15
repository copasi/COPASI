// Copyright (C) 2020 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/math/CJitExpression.h"
#include "copasi/math/CJitCompiler.h"

CJitExpression::CJitExpression()
  : mpCompiler(NULL)
  , mpJitFunction(NULL)
{}

// virtual
CJitExpression::~CJitExpression()
{
  if (mpCompiler != NULL)
    mpCompiler->deregisterExpression(this);
}

double CJitExpression::calculateJit()
{
  return (*mpJitFunction)();
}

void CJitExpression::setCompiler(CJitCompiler * pCompiler)
{
  if (mpCompiler != pCompiler)
    {
      if (mpCompiler != NULL)
        mpCompiler->deregisterExpression(this);

      mpCompiler = pCompiler;

      if (mpCompiler != NULL)
        mpCompiler->registerExpression(this);

      mpJitFunction = NULL;
    }
}

CJitCompiler * CJitExpression::getCompiler()
{
  return mpCompiler;
}

void CJitExpression::release()
{
  mpJitFunction = NULL;
}
