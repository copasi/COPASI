// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphCurve.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/04/30 11:00:56 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CGRAPHNODE_H_
#define CGRAPHNODE_H_

#include <string>

#include "copasi.h"

#include "layout/CLGlyphs.h"
#include "layout/CLCurve.h"

class CGraphCurve : public CLCurve
  {
  private:
    string mKey;
    Carrow arrow;
    bool hasArrow;

  public:

    CLGraphCurve()
        : CLCurve() {};

    CLGraphCurve(const CLCurve & c);

    /**
     * copy constructor (should make deep copy)
     */
    CLGraphCurve(const CLGraphCurve & c);
  };

#endif
