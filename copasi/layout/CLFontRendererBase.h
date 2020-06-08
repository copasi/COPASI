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

#ifndef CLFontRendererBase_H__
#define CLFontRendererBase_H__

#include <string>
#include <utility>

// opengl includes
#ifdef WIN32
# ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
# endif // WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif // WIN32

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#ifdef HAVE_GL_EXT
# include <GL/glext.h>
#else
# include <copasi/GL/glext.h>
#endif // HAVE_GL_EXT
#endif // __APPLE__


#include "copasi/layout/CLText.h"

struct CLTextTextureSpec;
struct CLFontSpec;

/**
 * A static abstract class that is the base class for a font renderer implementation.
 */
class CLFontRendererBase
{
public:
  /**
   * Destructor
   */
  virtual ~CLFontRendererBase() {};

  /**
   * Functor that returns a TextureSpec object with a texture
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
