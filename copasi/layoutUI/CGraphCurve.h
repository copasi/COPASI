// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphCurve.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/12/10 12:18:58 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CGRAPHCURVE_H_
#define CGRAPHCURVE_H_

#include <string>

#include "copasi.h"

#include "layout/CLGlyphs.h"
#include "layout/CLCurve.h"
#include "layout/CLReactionGlyph.h"

#include "layoutUI/CArrow.h"

class CGraphCurve : public CLCurve
  {
  private:
    CArrow mArrow;
    bool mHasArrow;
    CLMetabReferenceGlyph::Role mRole;

  public:

    CGraphCurve();

    CGraphCurve(const CLCurve & c);

    /**
     * copy constructor (should make deep copy)
     */
    CGraphCurve(const CGraphCurve & c);

    bool hasArrowP(){return mHasArrow;}
    void setArrowP(bool b){mHasArrow = b;}
    void setArrow(CArrow ar){mArrow = ar;}
    void setRole(CLMetabReferenceGlyph::Role r){mRole = r;}
    CLMetabReferenceGlyph::Role getRole(){return mRole;}
    CArrow getArrow(){return mArrow;}

    void scale (const double & scaleFactor);
  };

#endif
