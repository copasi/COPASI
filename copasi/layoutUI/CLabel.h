// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CLabel.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/05/28 11:53:09 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CLABEL_H_
#define CLABEL_H_

#include <string>

#include "copasi.h"
#include "layout/CLGlyphs.h"

class CLabel : public CLTextGlyph
  {
  private:
    C_FLOAT64 orig_x;
    C_FLOAT64 orig_y;
    C_FLOAT64 orig_width;
    C_FLOAT64 orig_height;

    void initOrigValues();

  public:

    CLabel();
    CLabel(const CLTextGlyph & tg);
    CLabel(const CLabel & l);

    virtual void scale (const double & scaleFactor);
    void adaptToHeight (const double & h);
    void scalePosition(const double & hz);
  };

#endif
