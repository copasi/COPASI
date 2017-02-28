// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQFontRenderer_H__
#define CQFontRenderer_H__

#include <QFont>
#include <QFontDatabase>

#include <string>
#include <map>
#include <set>
#include <list>
#include <utility>

#include "copasi/layout/CLText.h"
#include "copasi/layout/CLFontRendererBase.h"

struct CLTextTextureSpec;

class CQFontRenderer: public CLFontRendererBase
{
public:
  CQFontRenderer();

  /**
   * Destructor
   */
  virtual ~CQFontRenderer();

  /**
   * Functor that returns a TextureSpec objct with a texture
   * for the given font family, font size font weight, font style and text.
   * The caller is responsible to free the memory of the TextureSpec object
   * and of the pData in the TextureSpec.
   */
  virtual std::pair<CLTextTextureSpec*, GLubyte*> operator()(const std::string& family, double fontSize, const std::string& text, CLText::FONT_WEIGHT weight = CLText::WEIGHT_NORMAL, CLText::FONT_STYLE style = CLText::STYLE_NORMAL, double zoomFactor = 1.0);

  /**
   * static method that creates a texture with a static FontRenderer
   * object.
   * This method can be used as a callback.
   */
  static std::pair<CLTextTextureSpec*, GLubyte*> createTexture(const std::string& family, double fontSize, const std::string& text, CLText::FONT_WEIGHT weight = CLText::WEIGHT_NORMAL, CLText::FONT_STYLE style = CLText::STYLE_NORMAL, double zoomFactor = 1.0);

  /**
   * Returns the size for a font given a font, a text and a zoom factor.
   */
  virtual std::pair<double, double> getTextureSize(const CLFontSpec& spec, const std::string& text);

protected:
  /**
   * Returns the size for a font given a font specification, a text and a zoom factor.
   */
  std::pair<double, double> getTextureSize(const QFont& font, const std::string& text);

  /**
   * Returns the font that matches the given FontSpc.
   */
  QFont getFont(const CLFontSpec& spec);

  /**
   * Creates a texture for the given text using the given font object.
   * The caller has to free the memory for the TextureSpec object and the
   * pData in the TextureSpec object.
   */
  std::pair<CLTextTextureSpec*, GLubyte*> getTexture(QFont& font, const std::string& text, double zoomFactor);

  /**
   * Finds the font families that fit the given family name.
   * A family fits if the name is exactly the same or if the name is
   * contained in the family name.
   * For generic names like sans, serif or monospaced the algorithm tries
   * to find a suitable font family.
   */
  void findSimilarFamily(const std::string& name, std::set<std::string>& families) const;

  /**
   * Given a certain name and a set of font family names, the algorithm
   * tries to put them in an order from best match to worst match.
   */
  void orderFamilies(const std::string& name, const std::set<std::string>& familySet, std::list<std::string>& familyList) const;

  void getFamilyList(const std::string& family, std::list<std::string>& list) const;

protected:
  /**
   * An instance of the font database.
   * It has to be a pointer since there seems to be a problem under linux if an
   * instance of QFontDatabase is created before some other things have been instanciated.
   * At least the application crashed when I made this an object instead of a pointer.
   */
  QFontDatabase* mpFontDatabase;

  /**
   * A map that stores the font that matches a given spec the best.
   */
  std::map<CLFontSpec, QFont> mFontMap;

  static CQFontRenderer FONT_RENDERER;
};

#endif /* CQFontRenderer_H__ */
