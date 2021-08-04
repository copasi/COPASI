// Copyright (C) 2020 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/math/CJitCompiler.h"
#include "copasi/math/CMathExpression.h"
#include "copasi/utilities/CNodeIterator.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/core/CRootContainer.h"

#ifdef USE_JIT
#include <cpu_features/cpuinfo_x86.h>
#endif

// static
bool * CJitCompiler::pSSE4support = NULL;

// static
bool CJitCompiler::JitEnabled()
{
#ifdef USE_JIT

  if (pSSE4support == NULL)
    {
      pSSE4support = new bool(cpu_features::GetX86Info().features.sse4_2);
    }

  return *pSSE4support && !CRootContainer::getConfiguration()->getDisableJIT();
#else
  return false;
#endif // USE_JIT
}

// static
size_t CJitCompiler::InitalBufferSize = 8192;

// static
void CJitCompiler::SetJitBufferSize(const size_t size)
{
  InitalBufferSize = size;
}

// static
const size_t & CJitCompiler::GetJitBufferSize()
{
  return InitalBufferSize;
}

#ifdef USE_JIT

// static
std::string CJitCompiler::where(std::runtime_error & e)
{
  std::string where = e.what();
  std::string::size_type start = where.find_last_of("/\\") + 1;
  std::string::size_type end = where.find_first_of(":", start);
  where = where.substr(start, end - start);

  return where;
}

CJitCompiler::CJitCompiler()
  : mpAllocator(NULL)
  , mpExecutionBuffer(NULL)
  , mpExpression(NULL)
  , mExpressions()
  , mExecutionBufferSize(InitalBufferSize)
  , mInsufficentExecutionBuffer(false)
  , mFunctionBufferSize(InitalBufferSize)
{
  JitEnabled();
}

CJitCompiler::CJitCompiler(const CJitCompiler & src)
  : mpAllocator(NULL)
  , mpExecutionBuffer(NULL)
  , mpExpression(NULL)
  , mExpressions()
  , mExecutionBufferSize(src.mExecutionBufferSize)
  , mInsufficentExecutionBuffer(src.mInsufficentExecutionBuffer)
  , mFunctionBufferSize(src.mFunctionBufferSize)
{
  JitEnabled();
}

// virtual
CJitCompiler::~CJitCompiler()
{
  release();

  while (mExpressions.size())
    (*mExpressions.begin())->setCompiler(NULL);
}

bool CJitCompiler::compile()
{
  bool success = allocateExecutionBuffer(mExecutionBufferSize);

  while (success)
    {
      std::set< CJitExpression * >::iterator it = mExpressions.begin();
      std::set< CJitExpression * >::iterator end = mExpressions.end();

      try
        {
          for (; it != end && !mInsufficentExecutionBuffer; ++it)
            (*it)->compileJit();
        }

      catch (std::runtime_error & e)
        {
          CCopasiMessage(CCopasiMessage::WARNING, MCJitCompilation + 3, e.what());
          success = false;
          continue;
        }

      catch (CCopasiMessage & msg)
        {
          CCopasiMessage(CCopasiMessage::WARNING, msg.getText().c_str());
          success = false;
          continue;
        }

      if (success)
        break;

      success = allocateExecutionBuffer(2 * mExecutionBufferSize);
    }

  if (!success)
    {
      release();
    }

  return success;
}

CJitCompiler::Function CJitCompiler::compile(const CMathExpression & mathExpression)
{
  Function ReturnFunction = NULL;

  if (mpExecutionBuffer->Available() == 0)
    return ReturnFunction;

  NativeJIT::FunctionBuffer ExecutionBuffer(*mpExecutionBuffer,  mpExecutionBuffer->Available());
  allocateFunctionBuffer(mFunctionBufferSize);

  while (ReturnFunction == NULL)
    {
      try
        {
          mpExpression = new NativeJIT::Function< C_FLOAT64 >(*mpAllocator, ExecutionBuffer);

          // mpExpression->EnableDiagnostics(std::cout);
          // ExecutionBuffer.EnableDiagnostics(std::cout);
        }

      catch (std::runtime_error & e)
        {
          std::string Where = where(e);

          if (Where == "Allocator.cpp")
            {
              allocateFunctionBuffer(mFunctionBufferSize * 2);
              ReturnFunction = NULL;
              continue;
            }
          else if (Where == "CodeBuffer.h")
            {
              mInsufficentExecutionBuffer = true;
              break;
            }

          CCopasiMessage(CCopasiMessage::EXCEPTION, MCJitCompilation + 1, Where.c_str(), mathExpression.getInfix().c_str());
        }

      CNodeContextIterator< const CEvaluationNode, std::vector< Node * > > itNode(mathExpression.getRoot());
      Node * pNode = NULL;

      while (itNode.next() != itNode.end())
        {
          if (*itNode == NULL)
            {
              continue;
            }

          try
            {
              switch (itNode->mainType())
                {
                  case CEvaluationNode::MainType::NUMBER:
                    pNode = compile(static_cast< const CEvaluationNodeNumber * >(*itNode));
                    break;

                  case CEvaluationNode::MainType::CONSTANT:
                    pNode = compile(static_cast< const CEvaluationNodeConstant * >(*itNode));
                    break;

                  case CEvaluationNode::MainType::OPERATOR:
                    pNode = compile(static_cast< const CEvaluationNodeOperator * >(*itNode), itNode.context());
                    break;

                  case CEvaluationNode::MainType::OBJECT:
                    pNode = compile(static_cast< const CEvaluationNodeObject * >(*itNode));
                    break;

                  case CEvaluationNode::MainType::FUNCTION:
                    pNode = compile(static_cast< const CEvaluationNodeFunction * >(*itNode), itNode.context());
                    break;

                  case CEvaluationNode::MainType::CHOICE:
                    pNode = compile(static_cast< const CEvaluationNodeChoice * >(*itNode), itNode.context());
                    break;

                  case CEvaluationNode::MainType::LOGICAL:
                    pNode = compile(static_cast< const CEvaluationNodeLogical * >(*itNode), itNode.context());
                    break;

                  case CEvaluationNode::MainType::VECTOR:
                  case CEvaluationNode::MainType::DELAY:
                  case CEvaluationNode::MainType::WHITESPACE:
                  case CEvaluationNode::MainType::VARIABLE:
                  case CEvaluationNode::MainType::CALL:
                  case CEvaluationNode::MainType::MV_FUNCTION:
                  case CEvaluationNode::MainType::STRUCTURE:
                  case CEvaluationNode::MainType::UNIT:
                  case CEvaluationNode::MainType::INVALID:
                  case CEvaluationNode::MainType::__SIZE:
                    pNode = NULL;
                    break;
                }
            }

          catch (std::runtime_error & e)
            {
              std::string Where = where(e);

              if (Where == "Allocator.cpp")
                {
                  allocateFunctionBuffer(mFunctionBufferSize * 2);
                  pNode = NULL;
                  break;
                }

              CCopasiMessage(CCopasiMessage::EXCEPTION, MCJitCompilation + 1, Where.c_str(), mathExpression.getInfix().c_str());
              break;
            }

          if (pNode == NULL)
            {
              // CCopasiMessage(CCopasiMessage::WARNING, MCJitCompilation + 2, mathExpression.getInfix().c_str());
              break;
            }

          if (itNode.parentContextPtr() != NULL)
            {
              itNode.parentContextPtr()->push_back(pNode);
            }
        }

      try
        {
          if (dynamic_cast< NativeJIT::Node< C_FLOAT64 > * >(pNode) != NULL)
            {
              ReturnFunction = mpExpression->Compile(*static_cast< NativeJIT::Node< C_FLOAT64 > * >(pNode));
            }
          else if (dynamic_cast< NativeJIT::Node< bool > * >(pNode) != NULL)
            {
              // We must return a function which returns a double
              ReturnFunction = mpExpression->Compile(fromBool(*static_cast< NativeJIT::Node< bool > * >(pNode)));
            }
          else if (pNode != NULL)
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCJitCompilation + 2, mathExpression.getInfix().c_str());
            }
          else
            {
              if (mpExpression != NULL)
                {
                  delete mpExpression;
                  mpExpression = NULL;
                }

              break;
            }
        }

      catch (std::runtime_error & e)
        {
          std::string Where = where(e);

          if (Where == "Allocator.cpp")
            {
              allocateFunctionBuffer(mFunctionBufferSize * 2);
              ReturnFunction = NULL;
              continue;
            }
          else if (Where == "CodeBuffer.h")
            {
              mInsufficentExecutionBuffer = true;
              break;
            }

          CCopasiMessage(CCopasiMessage::EXCEPTION, MCJitCompilation + 1, Where.c_str(), mathExpression.getInfix().c_str());
        }

      if (mpExpression != NULL)
        {
          delete mpExpression;
          mpExpression = NULL;
        }
    }

  return ReturnFunction;
}

bool CJitCompiler::allocateExecutionBuffer(const size_t & size)
{
  if (mpExpression != NULL)
    {
      delete mpExpression;
      mpExpression = NULL;
    }

  if (size == mExecutionBufferSize
      && mpExecutionBuffer != NULL)
    {
      mpExecutionBuffer->Reset();
      return true;
    }

  if (mpExecutionBuffer != NULL)
    {
      mpExecutionBuffer->Reset();
      delete mpExecutionBuffer;
    }

  mExecutionBufferSize = size;

  try
    {
      mpExecutionBuffer = new NativeJIT::ExecutionBuffer(mExecutionBufferSize);
      mExecutionBufferSize = mpExecutionBuffer->Available();
    }
  catch (...)
    {
      mpExecutionBuffer = NULL;
    }

  mInsufficentExecutionBuffer = false;

  return mpExecutionBuffer != NULL;
}

bool CJitCompiler::allocateFunctionBuffer(const size_t & size)
{
  if (mpExpression != NULL)
    {
      delete mpExpression;
      mpExpression = NULL;
    }

  if (size == mFunctionBufferSize
      && mpAllocator != NULL)
    {
      mpAllocator->Reset();
      return true;
    }

  if (mpAllocator != NULL)
    {
      mpAllocator->Reset();
      delete mpAllocator;
    }

  mFunctionBufferSize = size;

  try
    {
      mpAllocator = new NativeJIT::Allocator(mFunctionBufferSize);
      mFunctionBufferSize = mpAllocator->Available();
    }
  catch (...)
    {
      mpAllocator = NULL;
    }

  return mpAllocator != NULL;
}

void CJitCompiler::release()
{
  std::set< CJitExpression * >::iterator it = mExpressions.begin();
  std::set< CJitExpression * >::iterator end = mExpressions.end();

  for (; it != end; ++it)
    (*it)->release();

  if (mpExpression != NULL)
    {
      delete mpExpression;
      mpExpression = NULL;
    }

  if (mpAllocator != NULL)
    {
      mpAllocator->Reset();
      delete mpAllocator;
      mpAllocator = NULL;
    }

  if (mpExecutionBuffer != NULL)
    {
      mpExecutionBuffer->Reset();
      delete mpExecutionBuffer;
      mpExecutionBuffer = NULL;
    }
}

void CJitCompiler::registerExpression(CJitExpression * pExpression)
{
  if (JitEnabled())
    mExpressions.insert(pExpression);
}

void CJitCompiler::deregisterExpression(CJitExpression * pExpression)
{
  mExpressions.erase(pExpression);
}

CJitCompiler::Node * CJitCompiler::compile(const CEvaluationNodeNumber * pNode)
{
  return &mpExpression->Immediate(*pNode->getValuePointer());
}

CJitCompiler::Node * CJitCompiler::compile(const CEvaluationNodeConstant * pNode)
{
  if (pNode->getValueType() == CEvaluationNode::ValueType::Boolean)
    {
      if (*pNode->getValuePointer() > 0.5)
        return &mpExpression->Immediate(true);
      else
        return &mpExpression->Immediate(false);
    }

  return &mpExpression->Immediate(*pNode->getValuePointer());
}

CJitCompiler::Node * CJitCompiler::compile(const CEvaluationNodeOperator * pNode, const std::vector< CJitCompiler::Node * > & context)
{
  if (context.size() != 2)
    return NULL;

  Node * pNodeJIT = NULL;

  switch (pNode->subType())
    {
      case CEvaluationNode::SubType::POWER:
      {
        auto & Function = mpExpression->Immediate< F2 >(pow);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::MULTIPLY:
        pNodeJIT = &mpExpression->Mul(*static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
        break;

      case CEvaluationNode::SubType::DIVIDE:
      {
        auto & Function = mpExpression->Immediate< F2 >(__jit_divide);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::MODULUS:
      {
        auto & Function = mpExpression->Immediate< F2 >(__jit_modulus);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::PLUS:
        pNodeJIT = &mpExpression->Add(*static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
        break;

      case CEvaluationNode::SubType::MINUS:
        pNodeJIT = &mpExpression->Sub(*static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
        break;

      case CEvaluationNode::SubType::REMAINDER:
      {
        auto & Function = mpExpression->Immediate< F2 >(fmod);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      default:
        break;
    }

  return pNodeJIT;
}

CJitCompiler::Node * CJitCompiler::compile(const CEvaluationNodeObject * pNode)
{
  auto & Pointer = mpExpression->Immediate(const_cast< C_FLOAT64 * >(pNode->getValuePointer()));
  return &mpExpression->Deref(Pointer);
}

CJitCompiler::Node * CJitCompiler::compile(const CEvaluationNodeFunction * pNode, const std::vector< CJitCompiler::Node * > & context)
{
  Node * pNodeJIT = NULL;

  switch (pNode->subType())
    {
      case CEvaluationNode::SubType::LOG:
      {
        auto & Function = mpExpression->Immediate< F1 >(log);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::LOG10:
      {
        auto & Function = mpExpression->Immediate< F1 >(log10);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::EXP:
      {
        auto & Function = mpExpression->Immediate< F1 >(exp);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::SIN:
      {
        auto & Function = mpExpression->Immediate< F1 >(sin);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::COS:
      {
        auto & Function = mpExpression->Immediate< F1 >(cos);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::TAN:
      {
        auto & Function = mpExpression->Immediate< F1 >(tan);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::SEC:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::sec);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::CSC:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::csc);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::COT:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::cot);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::SINH:
      {
        auto & Function = mpExpression->Immediate< F1 >(sinh);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::COSH:
      {
        auto & Function = mpExpression->Immediate< F1 >(cosh);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::TANH:
      {
        auto & Function = mpExpression->Immediate< F1 >(tanh);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::SECH:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::sech);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::CSCH:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::csch);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::COTH:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::coth);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCSIN:
      {
        auto & Function = mpExpression->Immediate< F1 >(asin);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCCOS:
      {
        auto & Function = mpExpression->Immediate< F1 >(acos);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCTAN:
      {
        auto & Function = mpExpression->Immediate< F1 >(atan);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCSEC:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::arcsec);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCCSC:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::arccsc);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCCOT:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::arccot);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCSINH:
      {
        auto & Function = mpExpression->Immediate< F1 >(asinh);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCCOSH:
      {
        auto & Function = mpExpression->Immediate< F1 >(acosh);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCTANH:
      {
        auto & Function = mpExpression->Immediate< F1 >(atanh);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCSECH:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::asech);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCCSCH:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::acsch);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ARCCOTH:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::acoth);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::SIGN:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::sign);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::SQRT:
      {
        auto & Function = mpExpression->Immediate< F1 >(sqrt);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::ABS:
      {
        auto & Function = mpExpression->Immediate< F1 >(fabs);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::FLOOR:
      {
        auto & Function = mpExpression->Immediate< F1 >(floor);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::CEIL:
      {
        auto & Function = mpExpression->Immediate< F1 >(ceil);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::FACTORIAL:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::factorial);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::MINUS:
      {
        auto & Minus = mpExpression->Immediate(-1.0);
        pNodeJIT = &mpExpression->Mul(*static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), Minus);
      }
      break;

      case CEvaluationNode::SubType::PLUS:
      {
        pNodeJIT = context[0];
      }
      break;

      case CEvaluationNode::SubType::NOT:
      {
        pNodeJIT = &mpExpression->If(*static_cast< NativeJIT::Node< bool > * >(context[0]), mpExpression->Immediate(false), mpExpression->Immediate(true));
      }
      break;

      case CEvaluationNode::SubType::RUNIFORM:
      {
        auto & Function = mpExpression->Immediate< F2 >(CEvaluationNodeFunction::runiform);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::RNORMAL:
      {
        auto & Function = mpExpression->Immediate< F2 >(CEvaluationNodeFunction::rnormal);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::RPOISSON:
      {
        auto & Function = mpExpression->Immediate< F1 >(CEvaluationNodeFunction::rpoisson);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]));
      }
      break;

      case CEvaluationNode::SubType::RGAMMA:
      {
        auto & Function = mpExpression->Immediate< F2 >(CEvaluationNodeFunction::rgamma);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::MAX:
      {
        auto & Function = mpExpression->Immediate< F2 >(CEvaluationNodeFunction::max);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::MIN:
      {
        auto & Function = mpExpression->Immediate< F2 >(CEvaluationNodeFunction::min);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      default:
        break;
    }

  return pNodeJIT;
}

CJitCompiler::Node * CJitCompiler::compile(const CEvaluationNodeChoice * pNode, const std::vector< CJitCompiler::Node * > & context)
{
  /**
   * We have four different cases to consider:
   * 1) condition is boolean, true and false value are boolean
   * 2) condition is boolean, true and false value are double
   * 3) condition is double, true and false value are boolean
   * 4) condition is double, true and false value are double
   */

  if (dynamic_cast< NativeJIT::Node< bool > * >(context[0]) != NULL)
    {
      if (dynamic_cast< NativeJIT::Node< bool > * >(context[1]) != NULL)
        return &mpExpression->IfNotZero(*static_cast< NativeJIT::Node< bool > * >(context[0]),
                                        *static_cast< NativeJIT::Node< bool > * >(context[1]),
                                        *static_cast< NativeJIT::Node< bool > * >(context[2]));
      else if (dynamic_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]) != NULL)
        return &mpExpression->IfNotZero(*static_cast< NativeJIT::Node< bool > * >(context[0]),
                                        *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]),
                                        *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[2]));
    }
  else if (dynamic_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]) != NULL)
    {
      if (dynamic_cast< NativeJIT::Node< bool > * >(context[1]) != NULL)
        return &mpExpression->IfNotZero(*static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]),
                                        *static_cast< NativeJIT::Node< bool > * >(context[1]),
                                        *static_cast< NativeJIT::Node< bool > * >(context[2]));
      else if (dynamic_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]) != NULL)
        return &mpExpression->IfNotZero(*static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]),
                                        *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]),
                                        *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[2]));
    }

  return NULL;
}

CJitCompiler::Node * CJitCompiler::compile(const CEvaluationNodeLogical * pNode, const std::vector< CJitCompiler::Node * > & context)
{
  Node * pNodeJIT = NULL;

  switch (pNode->subType())
    {
      case CEvaluationNode::SubType::OR:
      {
        pNodeJIT = &mpExpression->Or(*static_cast< NativeJIT::Node< bool > * >(context[0]), *static_cast< NativeJIT::Node< bool > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::XOR:
      {
        auto & Function = mpExpression->Immediate< B2B >(__jit_xor);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< bool > * >(context[0]), *static_cast< NativeJIT::Node< bool > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::AND:
      {
        pNodeJIT = &mpExpression->And(*static_cast< NativeJIT::Node< bool > * >(context[0]), *static_cast< NativeJIT::Node< bool > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::EQ:

        // Equality may be between Boolean or double nodes
        if (dynamic_cast< NativeJIT::Node< bool > * >(context[0]) != NULL)
          {
            auto & Function = mpExpression->Immediate< B2B >(__jit_eq);
            pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< bool > * >(context[0]), *static_cast< NativeJIT::Node< bool > * >(context[1]));
          }
        else
          {
            auto & Function = mpExpression->Immediate< B2F >(__jit_eq);
            pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
          }

        break;

      case CEvaluationNode::SubType::NE:

        // Equality may be between Boolean or double nodes
        if (dynamic_cast< NativeJIT::Node< bool > * >(context[0]) != NULL)
          {
            auto & Function = mpExpression->Immediate< B2B >(__jit_neq);
            pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< bool > * >(context[0]), *static_cast< NativeJIT::Node< bool > * >(context[1]));
          }
        else
          {
            auto & Function = mpExpression->Immediate< B2F >(__jit_neq);
            pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
          }

        break;

      case CEvaluationNode::SubType::GT:
      {
        auto & Function = mpExpression->Immediate< B2F >(__jit_gt);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::GE:
      {
        auto & Function = mpExpression->Immediate< B2F >(__jit_ge);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::LT:
      {
        auto & Function = mpExpression->Immediate< B2F >(__jit_lt);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      case CEvaluationNode::SubType::LE:
      {
        auto & Function = mpExpression->Immediate< B2F >(__jit_le);
        pNodeJIT = &mpExpression->Call(Function, *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[0]), *static_cast< NativeJIT::Node< C_FLOAT64 > * >(context[1]));
      }
      break;

      default:
        break;
    }

  return pNodeJIT;
}
#endif // USE_JIT
