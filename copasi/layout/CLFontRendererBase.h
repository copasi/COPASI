// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLFontRendererBase.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/10/06 04:31:17 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLFontRendererBase_H__
#define CLFontRendererBase_H__

#include <string>
#include <utility>

// opengl includes
#ifdef WIN32
# define WIN32_LEAN_AND_MEAN 1
# include <windows.h>
#endif // WIN32

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <copasi/GL/glext.h>
#endif // __APPLE__


#include <copasi/layout/CLText.h>

struct CLTextTextureSpec;
struct CLFontSpec;

/**
 * A static abstract class that is the base class for a font renderer implementation.
 */
class CLFontRendererBase
{
public:
  /**
   * Functor that returns a TextureSpec objct with a texture
   * for the given font family, font size font weight, font style and text.
   * The caller is responsible to free the memory of the TextureSpec object
   * and of the pData in the TextureSpec.
   */
  virtual std::pair<CLTextTextureSpec*, GLubyte*> operator()(const std::string& family, double fontSize, const std::string& text, CLText::FONT_WEIGHT weight = CLText::WEIGHT_NORMAL, CLText::FONT_STYLE style = CLText::STYLE_NORMAL, double zoomFactor = 1.0) = 0;

  /**
   * Returns the size for a font given a font, a text and a zoom factor.
   */
  virtual std::pair<double, double> getTextureSize(const CLFontSpec& spec, const std::string& text) = 0;
};

#endif /* CLFontRendererBase_H__ */
