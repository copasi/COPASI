// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtOpenGL/QGLWidget>
#include <QtGui/QImage>
#include <algorithm>

#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glext.h>
# ifndef _WIN32
#  define GLX_GLXEXT_PROTOTYPES
#  include <GL/glx.h>
# endif // _WIN32
#endif // __APPLE__

#include "CQQtImageTexturizer.h"
#include "copasi/layout/utility_classes.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/utility.h"
#include "copasi/UI/qtUtilities.h"

// virtual
CLTextureSpec* CQQtImageTexturizer::operator()(const std::string& filename, const std::string& basedir)
{
  std::string reference = to_absolute_path(filename, basedir);
  CLTextureSpec* pTexture = NULL;
  // test if the filename ends in "JPG","JPEG","jpeg" or "jpg"
  std::string::size_type pos = reference.rfind(".");
  std::string ending;

  if (pos != std::string::npos)
    {
      ++pos;
      ending = reference.substr(pos);
      std::transform(ending.begin(), ending.end(), ending.begin(), &tolower);
    }

  if (!ending.empty())
    {
      if (ending == "jpeg" || ending == "jpg")
        {
          pTexture = create_texture_for_image(reference/*,"JPG"*/);
        }
      else if (ending == "png")
        {
          pTexture = create_texture_for_image(reference/*,"PNG"*/);
        }
    }

  return pTexture;
}

CLTextureSpec* CQQtImageTexturizer::create_texture_for_image(const std::string& filename, const char* format)
{
  CLTextureSpec* pResult = NULL;
  // use UTF8 strings for filenames since this seems to be safer across platforms
  QImage image(FROM_UTF8(filename), format);

  if (!image.isNull())
    {
      image = image.mirrored();
      QImage glImage = QGLWidget::convertToGLFormat(image);
      pResult = new CLTextureSpec;
      pResult->mTextureWidth = pResult->mTextWidth = glImage.width();
      pResult->mTextureHeight = pResult->mTextHeight = glImage.height();
      pResult->mNumComponents = 4;
      glGenTextures(1, &pResult->mTextureName);
      assert(pResult->mTextureName != 0);
      glBindTexture(GL_TEXTURE_2D, pResult->mTextureName);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)pResult->mTextureWidth, (GLsizei)pResult->mTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, glImage.bits());
    }
  else
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCLayout + 1, filename.c_str());
    }

  return pResult;
}
