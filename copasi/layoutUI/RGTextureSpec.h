// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/RGTextureSpec.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/10/04 17:22:45 $
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
    C_INT32 textWidth;
    C_INT32 textHeight;
    C_INT32 textureWidth;
    C_INT32 textureHeight;

    GLubyte* textureData;

    //RGTextureSpec();
  };

#endif
