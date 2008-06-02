// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CLabel.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/06/02 09:07:49 $
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

    C_FLOAT64 getOrigHeight(){return this->orig_height;}
    C_FLOAT64 getOrigWidth(){return this->orig_width;}

    virtual void scale (const double & scaleFactor);
    void adaptToHeight (const double & h);
    void scalePosition(const double & hz);
  };

#endif
