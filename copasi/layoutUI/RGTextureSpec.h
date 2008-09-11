// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/RGTextureSpec.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/11 12:41:37 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef RGTEXTURESPEC_H_
#define RGTEXTURESPEC_H_

#include <qgl.h>

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
