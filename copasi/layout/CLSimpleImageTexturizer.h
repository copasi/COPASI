// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLSimpleImageTexturizer.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:35:21 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLSIMPLEIMAGETEXTURIZER_H__
#define CLSIMPLEIMAGETEXTURIZER_H__

// libpng
// we have to include png.h before all other includes since it includes
// setjmp.h and if any other module that is imported before it includes setjmp.h as
// well, we get a compiler error.
#include <png.h>

#include <string>

#include "copasi/layout/CLImageTexturizer.h"

class CLTextureSpec;

class CLSimpleImageTexturizer : public CLImageTexturizer
{
public:
  virtual CLTextureSpec* operator()(const std::string& filename, const std::string& basedir);

protected:
  CLTextureSpec* create_texture_for_image(const std::string& filename, const std::string& basedir);

  /**
   * This method creates a texture from a given JPEG image file.
   * It is up to the caller to free the texture space once it is no longer needed.
   * If no texture could be created, NULL is returned.
   */
  CLTextureSpec* create_texture_for_jpeg_image(const std::string& filename);

  /**
   * This method creates a texture from a given PNG image file.
   * It is up to the caller to free the texture space once it is no longer needed.
   * If no texture could be created, NULL is returned.
   */
  CLTextureSpec* create_texture_for_png_image(const std::string& filename);
};

#endif // CLSIMPLEIMAGETEXTURIZER_H__
