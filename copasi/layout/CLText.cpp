// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>

#include <sbml/packages/render/sbml/Text.h>

#include "CLText.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

// Ctor
CLText::CLText(CDataContainer* pParent):
  CLGraphicalPrimitive1D(),
  CDataObject("RenderText", pParent),
  mX(CLRelAbsVector(0.0, 0.0)),
  mY(CLRelAbsVector(0.0, 0.0)),
  mZ(CLRelAbsVector(0.0, 0.0)),
  mFontFamily(""),
  mFontSize(CLRelAbsVector(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN())),
  mFontWeight(CLText::WEIGHT_UNSET),
  mFontStyle(CLText::STYLE_UNSET),
  mTextAnchor(CLText::ANCHOR_UNSET),
  mVTextAnchor(CLText::ANCHOR_UNSET),
  mText(""),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("RenderText", this);
}

/**
 * Constructor with optional coordinates.
 */
CLText::CLText(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z, CDataContainer* pParent):
  CLGraphicalPrimitive1D(),
  CDataObject("RenderText", pParent),
  mX(x),
  mY(y),
  mZ(z),
  mFontFamily(""),
  mFontSize(CLRelAbsVector(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN())),
  mFontWeight(CLText::WEIGHT_UNSET),
  mFontStyle(CLText::STYLE_UNSET),
  mTextAnchor(CLText::ANCHOR_UNSET),
  mVTextAnchor(CLText::ANCHOR_UNSET),
  mText(""),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("RenderText", this);
}

/**
 * Copy constructor.
 */
CLText::CLText(const CLText& source, CDataContainer* pParent):
  CLGraphicalPrimitive1D(source),
  CDataObject(source, pParent),
  mX(source.mX),
  mY(source.mY),
  mZ(source.mZ),
  mFontFamily(source.mFontFamily),
  mFontSize(source.mFontSize),
  mFontWeight(source.mFontWeight),
  mFontStyle(source.mFontStyle),
  mTextAnchor(source.mTextAnchor),
  mVTextAnchor(source.mVTextAnchor),
  mText(source.mText),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("RenderText", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLText::CLText(const Text& source, CDataContainer* pParent):
  CLGraphicalPrimitive1D(source),
  CDataObject("RenderText", pParent),
  mX(source.getX()),
  mY(source.getY()),
  mZ(source.getZ()),
  mFontFamily(source.getFontFamily()),
  mFontSize(source.getFontSize()),
  mText(source.getText()),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("RenderText", this);

  switch (source.getFontWeight())
    {
      case Text::WEIGHT_UNSET:
        this->setFontWeight(CLText::WEIGHT_UNSET);
        break;

      case Text::WEIGHT_BOLD:
        this->setFontWeight(CLText::WEIGHT_BOLD);
        break;

      default:
        this->setFontWeight(CLText::WEIGHT_NORMAL);
        break;
    }

  switch (source.getFontStyle())
    {
      case Text::STYLE_UNSET:
        this->setFontStyle(CLText::STYLE_UNSET);
        break;

      case Text::STYLE_ITALIC:
        this->setFontStyle(CLText::STYLE_ITALIC);
        break;

      default:
        this->setFontStyle(CLText::STYLE_NORMAL);
        break;
    }

  switch (source.getTextAnchor())
    {
      case Text::ANCHOR_UNSET:
        this->setTextAnchor(CLText::ANCHOR_UNSET);
        break;

      case Text::ANCHOR_END:
        this->setTextAnchor(CLText::ANCHOR_END);
        break;

      case Text::ANCHOR_MIDDLE:
        this->setTextAnchor(CLText::ANCHOR_MIDDLE);
        break;

      default:
        this->setTextAnchor(CLText::ANCHOR_START);
        break;
    }

  switch (source.getVTextAnchor())
    {
      case Text::ANCHOR_UNSET:
        this->setVTextAnchor(CLText::ANCHOR_UNSET);
        break;

      case Text::ANCHOR_BOTTOM:
        this->setVTextAnchor(CLText::ANCHOR_BOTTOM);
        break;

      case Text::ANCHOR_MIDDLE:
        this->setVTextAnchor(CLText::ANCHOR_MIDDLE);
        break;

      default:
        this->setVTextAnchor(CLText::ANCHOR_TOP);
        break;
    }
}

/**
 * Destructor
 */
CLText::~CLText()
{
  CRootContainer::getKeyFactory()->remove(this->mKey);
}

/**
 * Sets the coordinates.
 */
void CLText::setCoordinates(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z)
{
  this->mX = x;
  this->mY = y;
  this->mZ = z;
}

/**
 * Sets the x coordinate.
 */
void CLText::setX(const CLRelAbsVector& coord)
{
  this->mX = coord;
}

/**
 * Sets the y coordinate.
 */
void CLText::setY(const CLRelAbsVector& coord)
{
  this->mY = coord;
}

/**
 * Sets the z coordinate.
 */
void CLText::setZ(const CLRelAbsVector& coord)
{
  this->mZ = coord;
}

/**
 * Returns the x coordinate.
 */
const CLRelAbsVector& CLText::getX() const
{
  return this->mX;
}

/**
 * Returns the y coordinate.
 */
const CLRelAbsVector& CLText::getY() const
{
  return this->mY;
}

/**
 * Returns the z coordinate.
 */
const CLRelAbsVector& CLText::getZ() const
{
  return this->mZ;
}

/**
 * Returns the x coordinate.
 */
CLRelAbsVector& CLText::getX()
{
  return this->mX;
}

/**
 * Returns the y coordinate.
 */
CLRelAbsVector& CLText::getY()
{
  return this->mY;
}

/**
 * Returns the z coordinate.
 */
CLRelAbsVector& CLText::getZ()
{
  return this->mZ;
}

/**
 * Sets the font family.
 */
void CLText::setFontFamily(const std::string& family)
{
  this->mFontFamily = family;
}

/**
 * Sets the font size.
 */
void CLText::setFontSize(const CLRelAbsVector& size)
{
  this->mFontSize = size;
}

/**
 * Sets the font weight.
 */
void CLText::setFontWeight(CLText::FONT_WEIGHT weight)
{
  this->mFontWeight = weight;
}

/**
 * Sets the font style.
 */
void CLText::setFontStyle(CLText::FONT_STYLE style)
{
  this->mFontStyle = style;
}

/**
 * Sets the text anchor.
 */
void CLText::setTextAnchor(CLText::TEXT_ANCHOR anchor)
{
  this->mTextAnchor = anchor;
}

/**
 * Sets the vertical text anchor.
 */
void CLText::setVTextAnchor(CLText::TEXT_ANCHOR anchor)
{
  this->mVTextAnchor = anchor;
}

/**
 * Returns the font family.
 */
const std::string& CLText::getFontFamily() const
{
  return this->mFontFamily;
}

/**
 * Returns the font size.
 */
CLRelAbsVector& CLText::getFontSize()
{
  return this->mFontSize;
}

/**
 * Returns the font size.
 */
const CLRelAbsVector& CLText::getFontSize() const
{
  return this->mFontSize;
}

/**
 * Returns the font weight.
 */
CLText::FONT_WEIGHT CLText::getFontWeight() const
{
  return this->mFontWeight;
}

/**
 * Returns the font style.
 */
CLText::FONT_STYLE CLText::getFontStyle() const
{
  return this->mFontStyle;
}

/**
 * Returns the text anchor.
 */
CLText::TEXT_ANCHOR CLText::getTextAnchor() const
{
  return this->mTextAnchor;
}

/**
 * Returns the vertical text anchor.
 */
CLText::TEXT_ANCHOR CLText::getVTextAnchor() const
{
  return this->mVTextAnchor;
}

/**
 * Returns the text for the text element.
 */
const std::string& CLText::getText() const
{
  return this->mText;
}

/**
 * Sets the text for the text element.
 */
void CLText::setText(const std::string& text)
{
  this->mText = text;
}

/**
 * Returns true if the text is set to something else than the empty string.
 */
bool CLText::isSetText() const
{
  return !this->mText.empty();
}

/**
 * Returns true if the font family has been set or false otherwise.
 */
bool CLText::isSetFontFamily() const
{
  return !this->mFontFamily.empty();
}

/**
 * Returns true if the font size has been set or false otherwise.
 */
bool CLText::isSetFontSize() const
{
  return (this->mFontSize.getAbsoluteValue() == this->mFontSize.getAbsoluteValue() && this->mFontSize.getRelativeValue() == this->mFontSize.getRelativeValue());
}

/**
 * Returns true if the font weight has been set or false otherwise.
 */
bool CLText::isSetFontWeight() const
{
  return (this->mFontWeight != CLText::WEIGHT_UNSET);
}

/**
 * Returns true if the font style has been set or false otherwise.
 */
bool CLText::isSetFontStyle() const
{
  return (this->mFontStyle != CLText::STYLE_UNSET);
}

/**
 * Returns true if the horizonal alignment attribute has been set.
 */
bool CLText::isSetTextAnchor() const
{
  return this->mTextAnchor != CLText::ANCHOR_UNSET;
}

/**
 * Returns true if the vertical alignment attribute has been set.
 */
bool CLText::isSetVTextAnchor() const
{
  return this->mVTextAnchor != CLText::ANCHOR_UNSET;
}

/**
 * Returns the key of the text element
 */
const std::string& CLText::getKey() const
{
  return this->mKey;
}

/**
 * Converts this object to the corresponding SBML object.
 */
Text* CLText::toSBML(unsigned int level, unsigned int version) const
{
  Text* pText = new Text(level, version);
  this->addSBMLAttributes(pText);
  RelAbsVector* pV1 = this->mX.toSBML();
  RelAbsVector* pV2 = this->mY.toSBML();
  RelAbsVector* pV3 = this->mZ.toSBML();
  pText->setCoordinates(*pV1, *pV2, *pV3);
  delete pV1;
  delete pV2;
  delete pV3;
  pV1 = this->mFontSize.toSBML();
  pText->setFontSize(*pV1);
  delete pV1;
  pText->setFontFamily(this->getFontFamily());
  pText->setText(this->getText());

  switch (this->getFontWeight())
    {
      case CLText::WEIGHT_UNSET:
        pText->setFontWeight(Text::WEIGHT_UNSET);
        break;

      case CLText::WEIGHT_BOLD:
        pText->setFontWeight(Text::WEIGHT_BOLD);
        break;

      default:
        pText->setFontWeight(Text::WEIGHT_NORMAL);
        break;
    }

  switch (this->getFontStyle())
    {
      case CLText::STYLE_UNSET:
        pText->setFontStyle(Text::STYLE_UNSET);
        break;

      case CLText::STYLE_ITALIC:
        pText->setFontStyle(Text::STYLE_ITALIC);
        break;

      default:
        pText->setFontStyle(Text::STYLE_NORMAL);
        break;
    }

  switch (this->getTextAnchor())
    {
      case CLText::ANCHOR_UNSET:
        pText->setTextAnchor(Text::ANCHOR_UNSET);
        break;

      case CLText::ANCHOR_END:
        pText->setTextAnchor(Text::ANCHOR_END);
        break;

      case CLText::ANCHOR_MIDDLE:
        pText->setTextAnchor(Text::ANCHOR_MIDDLE);
        break;

      default:
        pText->setTextAnchor(Text::ANCHOR_START);
        break;
    }

  switch (this->getVTextAnchor())
    {
      case CLText::ANCHOR_UNSET:
        pText->setVTextAnchor(Text::ANCHOR_UNSET);
        break;

      case CLText::ANCHOR_BOTTOM:
        pText->setVTextAnchor(Text::ANCHOR_BOTTOM);
        break;

      case CLText::ANCHOR_MIDDLE:
        pText->setVTextAnchor(Text::ANCHOR_MIDDLE);
        break;

      default:
        pText->setVTextAnchor(Text::ANCHOR_TOP);
        break;
    }

  return pText;
}
