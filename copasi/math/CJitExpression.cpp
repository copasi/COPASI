// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/math/CJitExpression.h"

CJitExpression::CJitExpression()
  : mpCompiler(NULL)
  , mFunction(NULL)
{}

// virtual
CJitExpression::~CJitExpression()
{
  if (mpCompiler != NULL)
    mpCompiler->deregisterExpression(this);
}

double CJitExpression::calculateJit()
{
  return (*mFunction)();
}

void CJitExpression::setCompiler(CJitCompiler & compiler)
{
  if (mpCompiler != &compiler)
    {
      if (mpCompiler != NULL)
        mpCompiler->deregisterExpression(this);

      mpCompiler = &compiler;
      mpCompiler->registerExpression(this);

      mFunction = NULL;
    }
}

CJitCompiler * CJitExpression::getCompiler()
{
  return mpCompiler;
}

void CJitExpression::release()
{
  mpCompiler = NULL;
  mFunction = NULL;
}
