// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalBase.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/03/03 15:57:53 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#ifdef COPASI_DEBUG
    virtual void refresh() const;
  protected:
    mutable std::string mInfix;
#endif /* COPASI_DEBUG */

  };

#endif /* CNormalBase_H__ */
