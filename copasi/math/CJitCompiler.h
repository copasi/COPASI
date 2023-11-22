// Copyright (C) 2020 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CJitCompiler
#define COPASI_CJitCompiler

#include <set>

#include "copasi/core/CCore.h"

class CMathExpression;
class CJitExpression;

class CJitCompiler
{
public:
  static bool JitEnabled();

protected:
  // hide constructor
  CJitCompiler();

  CJitCompiler(const CJitCompiler & src);

private:
  /**
   * A pointer to a bool indicating whether the CPU supports the sse4.2 instruction set
   * required for JIT compilation
   */
  static bool * pSSE4support;

public:
  typedef C_FLOAT64(*Function)();

  static CJitCompiler * create();

  virtual ~CJitCompiler();

  void registerExpression(CJitExpression * pExpression);

  void deregisterExpression(CJitExpression * pExpression);

#if (defined USE_JIT) && defined (JIT_IMPLEMENTATION)

  virtual CJitCompiler * copy() const = 0;

  virtual bool compile() = 0;

  virtual Function compile(const CMathExpression & mathExpression) = 0;

#endif // defined USE_JIT and defined JIT_IMPLEMENTATION
protected:
  /**
   * A set of a compiled expression
   */
  std::set< CJitExpression * > mExpressions;
};

#endif // COPASI_CJitCompiler
