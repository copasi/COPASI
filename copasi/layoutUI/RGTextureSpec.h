// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef RGTEXTURESPEC_H_
#define RGTEXTURESPEC_H_

#include <QtOpenGL/QtOpenGL>

#include "copasi.h"

#ifdef COPASI_DEBUG
#include <string>
#endif // COPASI_DEBUG

class RGTextureSpec
{
public:
  double textWidth;
  double textHeight;
  double textureWidth;
  double textureHeight;
  double textYOffset;

  GLubyte* textureData;

#ifdef COPASI_DEBUG
  // save as BW TGA file
  bool save(const std::string& filename);
#endif // COPASI_DEBUG
};

#endif
