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

void CJitExpression::setCompiler(CJitCompiler * pCompiler)
{
  if (mpCompiler != pCompiler)
    {
      if (mpCompiler != NULL)
        mpCompiler->deregisterExpression(this);

      mpCompiler = pCompiler;

      if (mpCompiler != NULL)
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
  mFunction = NULL;
}
