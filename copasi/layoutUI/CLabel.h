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

#ifndef CLABEL_H_
#define CLABEL_H_

#include <string>

#include "copasi/copasi.h"
#include "copasi/layout/CLGlyphs.h"

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

  C_FLOAT64 getOrigHeight() {return this->orig_height;}
  C_FLOAT64 getOrigWidth() {return this->orig_width;}

  virtual void scale(const double & scaleFactor);
  void adaptToHeight(const double & h);
  void scalePosition(const double & hz);

  virtual std::string getText() const;
};

#endif
