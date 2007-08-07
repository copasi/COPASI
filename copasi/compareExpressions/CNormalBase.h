// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalBase.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/07 16:49:49 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CNormalBase_H__
#define CNormalBase_H__

#include <string>

class CNormalBase
  {
  public:
    virtual CNormalBase* copy() const = 0;
    virtual ~CNormalBase(){};

    virtual bool simplify() = 0;
    virtual std::string toString() const = 0;

    virtual bool areEqual(const CNormalBase& rhs) const;
  };

#endif /* CNormalBase_H__ */
