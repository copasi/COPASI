// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLText_H__
#define CLText_H__

#include "copasi/layout/CLGraphicalPrimitive1D.h"
#include "copasi/layout/CLRelAbsVector.h"

#include "copasi/core/CDataObject.h"

#include <string>

class CDataContainer;

LIBSBML_CPP_NAMESPACE_BEGIN
class Text;
LIBSBML_CPP_NAMESPACE_END

class CLText : public CLGraphicalPrimitive1D, public CDataObject
{
private:
  // prevent the compiler from generating the assignment operator
  CLText& operator=(const CLText& source);

public:
  enum FONT_WEIGHT
  {
    WEIGHT_UNSET,
    WEIGHT_NORMAL,
    WEIGHT_BOLD
  };

  enum FONT_STYLE
  {
    STYLE_UNSET,
    STYLE_NORMAL,
    STYLE_ITALIC
  };

  enum TEXT_ANCHOR
  {
    ANCHOR_UNSET = 0,
    ANCHOR_START = 1,
    ANCHOR_MIDDLE = 2,
    ANCHOR_END = 3,
    ANCHOR_TOP = 1,
    ANCHOR_BOTTOM = 3
  };

protected:
  CLRelAbsVector mX;
  CLRelAbsVector mY;
  CLRelAbsVector mZ;
  std::string mFontFamily;
  CLRelAbsVector mFontSize;
  FONT_WEIGHT mFontWeight;
  FONT_STYLE mFontStyle;
  TEXT_ANCHOR mTextAnchor;
  TEXT_ANCHOR mVTextAnchor;
  std::string mText;

  /**
   * key for the object.
   */
  std::string mKey;

public:
  // Ctor
  CLText(CDataContainer* pParent);

  /**
   * Constructor with optional coordinates.
   */
  CLText(const CLRelAbsVector& x = CLRelAbsVector(0.0, 0.0), const CLRelAbsVector& y = CLRelAbsVector(0.0, 0.0), const CLRelAbsVector& z = CLRelAbsVector(0.0, 0.0), CDataContainer* pParent = NULL);

  /**
   * Copy constructor.
   */
  CLText(const CLText& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLText(const Text& source, CDataContainer* pParent = NULL);

  /**
   * Destructor.
   */
  ~CLText();

  /**
   * Sets the coordinates.
   */
  void setCoordinates(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z = CLRelAbsVector(0.0, 0.0));

  /**
   * Sets the x coordinate.
   */
  void setX(const CLRelAbsVector& coord);

  /**
   * Sets the y coordinate.
   */
  void setY(const CLRelAbsVector& coord);

  /**
   * Sets the z coordinate.
   */
  void setZ(const CLRelAbsVector& coord);

  /**
   * Returns the x coordinate.
   */
  const CLRelAbsVector& getX() const;

  /**
   * Returns the y coordinate.
   */
  const CLRelAbsVector& getY() const;

  /**
   * Returns the z coordinate.
   */
  const CLRelAbsVector& getZ() const;

  /**
   * Returns the x coordinate.
   */
  CLRelAbsVector& getX();

  /**
   * Returns the y coordinate.
   */
  CLRelAbsVector& getY();

  /**
   * Returns the z coordinate.
   */
  CLRelAbsVector& getZ();

  /**
   * Sets the font family.
   */
  void setFontFamily(const std::string& family);

  /**
   * Sets the font size.
   */
  void setFontSize(const CLRelAbsVector& size);

  /**
   * Sets the font weight.
   */
  void setFontWeight(CLText::FONT_WEIGHT weight);

  /**
   * Sets the font style.
   */
  void setFontStyle(CLText::FONT_STYLE style);

  /**
   * Sets the font anchor.
   */
  void setTextAnchor(CLText::TEXT_ANCHOR anchor);

  /**
   * Sets the font anchor.
   */
  void setVTextAnchor(CLText::TEXT_ANCHOR anchor);

  /**
   * Returns the font family.
   */
  const std::string& getFontFamily() const;

  /**
   * Returns the font size.
   */
  const CLRelAbsVector& getFontSize() const;

  /**
   * Returns the font size.
   */
  CLRelAbsVector& getFontSize();

  /**
   * Returns the font weight.
   */
  FONT_WEIGHT getFontWeight() const;

  /**
   * Returns the font style.
   */
  FONT_STYLE getFontStyle() const;

  /**
   * Returns the text anchor.
   */
  TEXT_ANCHOR getTextAnchor() const;

  /**
   * Returns the vertical text anchor.
   */
  TEXT_ANCHOR getVTextAnchor() const;

  /**
   * Returns true if the horizonal alignment attribute has been set.
   */
  bool isSetTextAnchor() const;

  /**
   * Returns true if the vertical alignment attribute has been set.
   */
  bool isSetVTextAnchor() const;

  /**
   * Returns the text for the text element.
   */
  const std::string& getText() const;

  /**
   * Sets the text for the text element.
   */
  void setText(const std::string& text);

  /**
   * Returns true if the text is set to something else than the empty string.
   */
  bool isSetText() const;

  /**
   * Returns true if the font family has been set or false otherwise.
   */
  bool isSetFontFamily() const;

  /**
   * Returns true if the font size has been set or false otherwise.
   */
  bool isSetFontSize() const;

  /**
   * Returns true if the font weight has been set or false otherwise.
   */
  bool isSetFontWeight() const;

  /**
   * Returns true if the font style has been set or false otherwise.
   */
  bool isSetFontStyle() const;

  /**
   * Returns the key string of the object.
   */
  const std::string& getKey() const;

  /**
   * Converts this object to the corresponding SBML object.
   */
  Text* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLText_H__ */
