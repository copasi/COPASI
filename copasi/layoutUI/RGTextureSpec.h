// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/RGTextureSpec.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/10/08 19:16:41 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef RGTEXTURESPEC_H_
#define RGTEXTURESPEC_H_

#include <qgl.h>

#include "copasi.h"

class RGTextureSpec
  {
  public:
    C_FLOAT64 textWidth;
    C_FLOAT64 textHeight;
    C_FLOAT64 textureWidth;
    C_FLOAT64 textureHeight;

    GLubyte* textureData;

    //RGTextureSpec();
  };

#endif
