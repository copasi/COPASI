// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CGRAPHCURVE_H_
#define CGRAPHCURVE_H_

#include <string>

#include "copasi/copasi.h"

#include "copasi/layout/CLGlyphs.h"
#include "copasi/layout/CLCurve.h"
#include "copasi/layout/CLReactionGlyph.h"

#include "copasi/layoutUI/CArrow.h"

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

  bool hasArrowP() {return mHasArrow;}
  void setArrowP(bool b) {mHasArrow = b;}
  void setArrow(CArrow ar) {mArrow = ar;}
  void setRole(CLMetabReferenceGlyph::Role r) {mRole = r;}
  CLMetabReferenceGlyph::Role getRole() {return mRole;}
  CArrow getArrow() {return mArrow;}

  void scale(const double & scaleFactor);
  void invertOrderOfPoints();
};

#endif
