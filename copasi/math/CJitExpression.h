// Copyright (C) 2020 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CJitExpression
#define COPASI_CJitExpression

#include "copasi/math/CJitCompiler.h"
class CJitCompiler;

class CJitExpression
{
public:
  CJitExpression();

  CJitExpression(const CJitExpression & src) = delete;

  virtual ~CJitExpression();

  double calculateJit();

  virtual void compileJit() = 0;

  void setCompiler(CJitCompiler * pCompiler);

  CJitCompiler * getCompiler();

  void release();

private:
  CJitCompiler * mpCompiler;

protected:
  CJitCompiler::Function mpJitFunction;
};

#endif // COPASI_CJitExpression
