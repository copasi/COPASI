// Copyright (C) 2020 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <iostream>

#define JIT_IMPLEMENTATION

#include "copasi/math/CJitCompilerImplementation.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"

#ifdef USE_JIT
#include <cpu_features/cpuinfo_x86.h>
#endif

// static
bool * CJitCompiler::pSSE4support = NULL;

CJitCompiler::CJitCompiler()
  : mExpressions()
{}

CJitCompiler::CJitCompiler(const CJitCompiler & src)
  : mExpressions()
{}

// static
bool CJitCompiler::JitEnabled()
{
#ifdef USE_JIT

  if (pSSE4support == NULL)
    pSSE4support = new bool(cpu_features::GetX86Info().features.sse4_2);

  return *pSSE4support && !CRootContainer::getConfiguration()->getDisableJIT();
#else
  return false;
#endif // USE_JIT
}

// static
CJitCompiler * CJitCompiler::create()
{
#ifdef USE_JIT
  return new CJitCompilerImplementation;
#else
  return NULL;
#endif // USE_JIT
}

// virtual
CJitCompiler::~CJitCompiler()
{}

void CJitCompiler::registerExpression(CJitExpression * pExpression)
{
  if (JitEnabled())
    mExpressions.insert(pExpression);
}

void CJitCompiler::deregisterExpression(CJitExpression * pExpression)
{
  mExpressions.erase(pExpression);
}
