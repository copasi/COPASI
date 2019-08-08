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

#include "CQFontRenderer.h"

#include <QtCore/QStringList>
#include <QFontMetrics>
#include <QImage>
#include <QPaintEngine>
#include <QtOpenGL/QGLWidget>
#include <QPainterPath>

#include <string.h>
#include <cmath>
#include <assert.h>

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

#include "copasi/layout/utility_classes.h"

/**
 * Static instance of CQFontRenderer for use in a static function that can be
 * used as a callback.
 */
CQFontRenderer CQFontRenderer::FONT_RENDERER;

/**
 * Constructor.
 */
CQFontRenderer::CQFontRenderer(): CLFontRendererBase(), mpFontDatabase(NULL)
{
}

/**
 * Destructor
 */
CQFontRenderer::~CQFontRenderer()
{
  if (this->mpFontDatabase != NULL)
    {
      delete this->mpFontDatabase;
    }
}

/**
 * Functor that returns a TextureSpec object with a texture
 * for the given font family, font size font weight, font style and text.
 * The caller is responsible to free the memory of the TextureSpec object
 * and of the pData in the TextureSpec.
 */
std::pair<CLTextTextureSpec*, GLubyte*> CQFontRenderer::operator()(const std::string& family, double fontSize, const std::string& text, CLText::FONT_WEIGHT weight, CLText::FONT_STYLE style, double zoomFactor)
{
  CLFontSpec spec;
  spec.mFamily = family;
  spec.mSize = fontSize * zoomFactor;
  spec.mWeight = weight;
  spec.mStyle = style;
  QFont font = this->getFont(spec);
  return getTexture(font, text, zoomFactor);
}

/**
 * Returns the font that matches the given FontSpec.
 */
QFont CQFontRenderer::getFont(const CLFontSpec& spec)
{
  // we only initialize the font database when it is needed for the first time,
  // hopefully this will resolve the crash under linux if it is instanciated to early.
  if (this->mpFontDatabase == NULL)
    {
      this->mpFontDatabase = new QFontDatabase();
    }

  // check if it is a generic font name (sand, serif or monospaced)
  // and try to find a fitting font
  // sans: helvetica or arial
  // serif: times, times new roman or garamond
  // monospaced: courier, courier new or monaco
  //std::cout << "Searching font for family \"" << spec.mFamily << "\" with size " << spec.mSize << " weight " << (spec.mWeight==CLText::WEIGHT_BOLD?(const char*)"bold":(const char*)"normal") << " and style " << (spec.mStyle==CLText::STYLE_ITALIC?(const char*)"italic":(const char*)"normal") << "." << std::endl;
  std::map<CLFontSpec, QFont>::iterator pos;
  pos = this->mFontMap.find(spec);
  QFont font;
  QString styleString;

  if (spec.mWeight == CLText::WEIGHT_BOLD)
    {
      styleString = "Bold";
    }

  if (spec.mStyle == CLText::STYLE_ITALIC)
    {
      styleString += " Italic";
    }

  styleString = styleString.trimmed();

  if (pos == this->mFontMap.end())
    {
      QString family(spec.mFamily.c_str());
      family = family.toLower();

      if (family == "sans")
        {
          // try helvetica and arial in this order
          QFont defaultFont;
          QString defaultFamily = defaultFont.defaultFamily();
          defaultFont = this->mpFontDatabase->font(defaultFamily, styleString, spec.mSize);
          CLFontSpec tempSpec = spec;
          tempSpec.mFamily = "helvetica";

          if (defaultFamily.contains(tempSpec.mFamily.c_str()))
            {
              font = defaultFont;
            }
          else
            {
              font = this->getFont(tempSpec);

              if (font == defaultFont)
                {
                  // if the font is the default font, we try the next one
                  tempSpec.mFamily = "arial";

                  if (defaultFamily.contains(tempSpec.mFamily.c_str()))
                    {
                      font = defaultFont;
                    }
                  else
                    {
                      font = this->getFont(tempSpec);
                    }
                }
            }
        }
      else if (family == "serif")
        {
          // try times, times new roman and garamond in this order
          QFont defaultFont;
          QString defaultFamily = defaultFont.defaultFamily();
          defaultFont = this->mpFontDatabase->font(defaultFamily, styleString, spec.mSize);
          CLFontSpec tempSpec = spec;
          tempSpec.mFamily = "times";

          if (defaultFamily.contains(tempSpec.mFamily.c_str()))
            {
              font = defaultFont;
            }
          else
            {
              font = this->getFont(tempSpec);

              if (font == defaultFont)
                {
                  // if the font is the default font, we try the next one
                  tempSpec.mFamily = "times new roman";

                  if (defaultFamily.contains(tempSpec.mFamily.c_str()))
                    {
                      font = defaultFont;
                    }
                  else
                    {
                      font = this->getFont(tempSpec);

                      if (font == defaultFont)
                        {
                          // if the font is the default font, we try the next one
                          tempSpec.mFamily = "garamond";

                          if (defaultFamily.contains(tempSpec.mFamily.c_str()))
                            {
                              font = defaultFont;
                            }
                          else
                            {
                              font = this->getFont(tempSpec);
                            }
                        }
                    }
                }
            }
        }
      else if (family == "monospaced")
        {
          // try courier, courier new and monaco in this order
          QFont defaultFont;
          QString defaultFamily = defaultFont.defaultFamily();
          defaultFont = this->mpFontDatabase->font(defaultFamily, styleString, spec.mSize);
          CLFontSpec tempSpec = spec;
          tempSpec.mFamily = "courier";

          if (defaultFamily.contains(tempSpec.mFamily.c_str()))
            {
              font = defaultFont;
            }
          else
            {
              font = this->getFont(tempSpec);

              if (font == defaultFont)
                {
                  // if the font is the default font, we try the next one
                  tempSpec.mFamily = "courier new";

                  if (defaultFamily.contains(tempSpec.mFamily.c_str()))
                    {
                      font = defaultFont;
                    }
                  else
                    {
                      font = getFont(tempSpec);

                      if (font == defaultFont)
                        {
                          // if the font is the default font, we try the next one
                          tempSpec.mFamily = "monaco";

                          if (defaultFamily.contains(tempSpec.mFamily.c_str()))
                            {
                              font = defaultFont;
                            }
                          else
                            {
                              font = this->getFont(tempSpec);
                            }
                        }
                    }
                }
            }
        }
      else
        {
          std::list<std::string> familyList;
          this->getFamilyList(spec.mFamily, familyList);
          // now create the font for one of the families in the list
          QFont defaultFont;
          QString defaultFamily = defaultFont.defaultFamily();
          defaultFont = this->mpFontDatabase->font(defaultFamily, styleString, spec.mSize);

          if (!familyList.empty())
            {
              // go through the list and check if there is a font in the that
              // does not return the default font for the given size and
              // style
              std::list<std::string>::const_iterator familyIt = familyList.begin(), familyEndit = familyList.end();

              while (familyIt != familyEndit)
                {
                  font = QFont(familyIt->c_str(), spec.mSize, (spec.mWeight == CLText::WEIGHT_BOLD) ? QFont::Bold : QFont::Normal, (spec.mStyle == CLText::STYLE_NORMAL) ? false : true);

                  if (font != defaultFont)
                    {
                      break;
                    }

                  ++familyIt;
                }
            }
          else
            {
              // return the default font
              font = defaultFont;
            }
        }

      this->mFontMap.insert(std::pair<CLFontSpec, QFont>(spec, font));
    }
  else
    {
      font = pos->second;
    }

  //std::cout << "Using font family \"" << font.mFamily().toLatin1().data() << "\" with size " << font.pointSize() << " weight " << (font.bold()?(const char*)"bold":(const char*)"normal") << " and style " << (font.italic()?(const char*)"italic":(const char*)"normal") << "." << std::endl;
  return font;
}

/**
 * Returns the size for a font given a font specification, a text and a zoom factor.
 */
std::pair<double, double> CQFontRenderer::getTextureSize(const QFont& font, const std::string& text)
{
  QFontMetrics fontMetrics(font);
  int textWidthInPixels = fontMetrics.width(text.c_str()) + 2;
  int textHeightInPixels = fontMetrics.height() + 2;
  return std::pair<double, double>(textWidthInPixels, textHeightInPixels);
}

/**
 * Returns the size for a font given a font, a text and a zoom factor.
 */
std::pair<double, double> CQFontRenderer::getTextureSize(const CLFontSpec& spec, const std::string& text)
{
  QFont font = this->getFont(spec);
  return this->getTextureSize(font, text);
}

/**
 * Creates a texture for the given text using the given font object.
 * The caller has to free the memory for the TextureSpec object and the
 * pData in the TextureSpec object.
 */
std::pair<CLTextTextureSpec*, GLubyte*> CQFontRenderer::getTexture(QFont& font, const std::string& text, double zoomFactor)
{
  CLTextTextureSpec* pSpec = NULL;
  // find out what size the text will have
  font.setStyleStrategy(QFont::ForceOutline);
  QFontMetrics fontMetrics(font);
  std::pair<double, double> size = this->getTextureSize(font, text);
  //std::cout << "texture size: " << size.first << "," << size.second << std::endl;
  // make the size a power of 2
  unsigned int exponentWidth = (unsigned int)ceil(log(size.first /** zoomFactor*/ + 2) / log(2.0));
  unsigned int exponentHeight = (unsigned int)ceil(log(size.second /** zoomFactor*/ + 2) / log(2.0));
  unsigned int width = 1 << exponentWidth;
  unsigned int height = 1 << exponentHeight;
  // draw the text somewhere with white stroke on black background
  QImage image(width, height, QImage::Format_RGB32);
  QPainter painter(&image);
  painter.setBackground(Qt::black);
  painter.setPen(QPen(QColor(255, 255, 255, 255), 0.25, Qt::SolidLine, Qt::FlatCap, Qt::BevelJoin));
  painter.setBrush(Qt::NoBrush);
  painter.setFont(font);
  painter.eraseRect(0, 0, width, height);
  // move over by 1,1 to get a small edge around the text
  painter.translate(1.0, 1.0);
  // we scale after the erase so that we don't have to divide the width and
  // the height
  //painter.scale(zoomFactor, zoomFactor);
  painter.drawText(0.0, fontMetrics.ascent() + 1, text.c_str());
  painter.end();
  // convert the image to an OpenGL texture
  image = QGLWidget::convertToGLFormat(image);
  // create the texture spec
  pSpec = new CLTextTextureSpec();
  pSpec->mTextureWidth = width;
  pSpec->mTextureHeight = height;
  pSpec->mTextWidth = size.first;
  pSpec->mTextHeight = size.second;
  pSpec->mScale = zoomFactor;
  pSpec->mMaxScale = -1.0;
  pSpec->mNumComponents = 1;
  pSpec->mTextureName = 0;
  GLint w = 0;
  GLenum format = GL_ALPHA;
  glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
  glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);

  while (w == 0 && width > 1 && height > 1)
    {
      // divide the size by two in each direction
      width = width >> 1;
      height = height >> 1;
      glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
      glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    }

  GLubyte* textureData = NULL;

  if (w != 0)
    {
      if (w != pSpec->mTextureWidth)
        {
          pSpec->mTextureWidth = width;
          pSpec->mTextureHeight = height;
        }

      textureData = new GLubyte[width * height];
      pSpec->mAscent = (double)fontMetrics.ascent();
      unsigned int i, iMax = width * height;

      for (i = 0; i < iMax; ++i)
        {
          textureData[i] = image.bits()[4 * i];
        }
    }

  return std::pair<CLTextTextureSpec*, GLubyte*>(pSpec, textureData);
}

/**
 * Finds the font families that fit the given family name.
 * A family fits if the name is exactly the same or if the name is
 * contained in the family name.
 * For generic names like sans, serif or monospaced the algorithm tries
 * to find a suitable font family.
 */
void CQFontRenderer::findSimilarFamily(const std::string& name, std::set<std::string>& families) const
{
  QString qname(name.c_str());
  QStringList familyList = this->mpFontDatabase->families();
  QStringList::const_iterator constIterator;

  for (constIterator = familyList.constBegin(); constIterator != familyList.constEnd(); ++constIterator)
    {
      if ((*constIterator).contains(name.c_str(), Qt::CaseInsensitive))
        {
          families.insert((*constIterator).toLatin1().data());
        }
    }
}

/**
 * Given a certain name and a set of font family names, the algorithm
 * tries to put them in an order from best match to worst match.
 */
void CQFontRenderer::orderFamilies(const std::string& /*name*/, const std::set<std::string>& familySet, std::list<std::string>& familyList) const
{
  std::set<std::string>::const_iterator it = familySet.begin();
  std::set<std::string>::const_iterator endit = familySet.end();

  // simple version only copies the set
  while (it != endit)
    {
      // TODO If the name is equal to the current iterator, we insert it before
      // TODO the first item that is not equal
      // TODO If the current item starts with the name, we add it before the
      // TODO first one that starts with the name and has a longer string.
      // TODO If the name is somewhere in the items string, we add it before
      // TODO the first entry that does contain the name, but is longer.
      // TODO For this comparison, we should take thefoundary into account
      // TODO and maybe remove it befoe comparing
      familyList.push_back(*it);
      ++it;
    }
}

void CQFontRenderer::getFamilyList(const std::string& family, std::list<std::string>& list) const
{
  QString name(family.c_str());
  name = name.toLower();
  name = name.trimmed();
  // find a new font
  std::set<std::string> familySet;
  this->findSimilarFamily(family, familySet);

  if (!familySet.empty())
    {
      this->orderFamilies(family, familySet, list);
    }
}

std::pair<CLTextTextureSpec*, GLubyte*> CQFontRenderer::createTexture(const std::string& family, double fontSize, const std::string& text, CLText::FONT_WEIGHT weight, CLText::FONT_STYLE style, double zoomFactor)
{
  return FONT_RENDERER(family, fontSize, text, weight, style, zoomFactor);
}
