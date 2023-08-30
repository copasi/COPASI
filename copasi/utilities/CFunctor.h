// Copyright (C) 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

template < class CReturn, class... Args >
class CStatic;
template < class CType, class CReturn, class... Args >
class CMember;

template < class CReturn, class... Args >
class CFunctor
{
public:
  virtual ~CFunctor() {}

  virtual CReturn operator()(Args... args) const = 0;

  static CFunctor * make_static(CReturn(*method)(Args...))
  {
    return new CStatic< CReturn, Args... >(method);
  }

  template < class CType >
  static CFunctor * make_member(CType * pType, CReturn(CType::*method)(Args...))
  {
    return new CMember< CType, CReturn, Args... >(pType, method);
  }
};

template < class CReturn, class... Args >
class CStatic
  : public CFunctor< CReturn, Args... >
{
public:
  typedef CReturn(*method_type)(Args...);

  CStatic(method_type pMethod)
    : mpMethod(pMethod)
  {}

  virtual ~CStatic() {}

  virtual CReturn operator()(Args... args) const override
  {
    return (*mpMethod)(args...);
  }

private:
  method_type mpMethod;
};

template < class CType, class CReturn, class... Args >
class CMember
  : public CFunctor< CReturn, Args... >
{
public:
  typedef CReturn(CType::*method_type)(Args... args);

  CMember(CType * pType,
          method_type pMethod)
    : mpType(pType)
    , mpMethod(pMethod)
  {}

  virtual ~CMember() {}

  virtual CReturn operator()(Args... args) const override
  {
    return (*mpType.*mpMethod)(args...);
  }

private:
  CType * mpType;
  method_type mpMethod;
};
