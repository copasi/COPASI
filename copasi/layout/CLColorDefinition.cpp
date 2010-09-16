// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLColorDefinition.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/09/16 18:28:05 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sstream>
#include <iomanip>
#include <assert.h>

#include <sbml/layout/render/ColorDefinition.h>

#include "CLColorDefinition.h"

#ifndef WIN32
# include <inttypes.h>
#endif

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Contructor which sets the CLColorDefinition to completely opaque
 * black.
 */
CLColorDefinition::CLColorDefinition(CCopasiContainer* pParent)
    : CLBase(),
    CCopasiObject("ColorDefinition", pParent),
    mRed(0),
    mGreen(0),
    mBlue(0),
    mAlpha(255),
    mKey(""),
    mId("")
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("ColorDefinition", this);
}

/**
 * Constructor which sets the CLColorDefinition to the given RGBA values.
 */
CLColorDefinition::CLColorDefinition(unsigned char r, unsigned char g, unsigned char b, unsigned char a, CCopasiContainer* pParent)
    : CLBase(),
    CCopasiObject("ColorDefinition", pParent),
    mRed(r),
    mGreen(g),
    mBlue(b),
    mAlpha(a),
    mKey(""),
    mId("")
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("ColorDefinition", this);
}

/**
 * Copy Contructor
 */
CLColorDefinition::CLColorDefinition(const CLColorDefinition& source, CCopasiContainer* pParent):
    CLBase(source),
    CCopasiObject(source, pParent),
    mRed(source.mRed),
    mGreen(source.mGreen),
    mBlue(source.mBlue),
    mAlpha(source.mAlpha),
    mKey(""),
    mId(source.mId)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("ColorDefinition", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLColorDefinition::CLColorDefinition(const ColorDefinition& source, CCopasiContainer* pParent):
    CLBase(),
    CCopasiObject("ColorDefinition", pParent),
    mRed(source.getRed()),
    mGreen(source.getGreen()),
    mBlue(source.getBlue()),
    mAlpha(source.getAlpha()),
    mKey(""),
    mId(source.getId())
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("ColorDefinition", this);
}

/**
 * Dtor.
 */
CLColorDefinition::~CLColorDefinition()
{
  CCopasiRootContainer::getKeyFactory()->remove(this->mKey);
}

/**
 * Returns the red color component.
 */
unsigned char CLColorDefinition::getRed() const
{
  return mRed;
}

/**
 * Returns the green color component.
 */
unsigned char CLColorDefinition::getGreen() const
{
  return mGreen;
}

/**
 * Returns the blue color component.
 */
unsigned char CLColorDefinition::getBlue() const
{
  return mBlue;
}

/**
 * Returns the alpha color component.
 */
unsigned char CLColorDefinition::getAlpha() const
{
  return mAlpha;
}

/**
 * Sets the red color component.
 */
void CLColorDefinition::setRed(unsigned char c)
{
  this->mRed = c;
}

/**
 * Sets the green color component.
 */
void CLColorDefinition::setGreen(unsigned char c)
{
  this->mGreen = c;
}

/**
 * Sets the blue color component.
 */
void CLColorDefinition::setBlue(unsigned char c)
{
  this->mBlue = c;
}

/**
 * Sets alpha red color component.
 */
void CLColorDefinition::setAlpha(unsigned char c)
{
  this->mAlpha = c;
}

/**
 * Sets the red green, blue and alpha color component.
 * The alpha value is optional and defaults to 255 if not given.
 */
void CLColorDefinition::setRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
  this->mRed = r;
  this->mGreen = g;
  this->mBlue = b;
  this->mAlpha = a;
}

/**
 * Sets the color value from a given string.
 * If the string is not a valid value string, the color value is set to
 * black and false is returned.
 */
bool CLColorDefinition::setColorValue(const std::string& valueString)
{
  bool result = true;
  size_t first_letter = valueString.find_first_not_of(std::string(" \t\r\n"));

  if (first_letter == std::string::npos)
    {
      result = false;
    }
  else
    {
      std::string trimmed = valueString.substr(first_letter, valueString.find_last_not_of(" \t\r\n") - first_letter + 1);

      if (trimmed[0] == '#' && (trimmed.size() == 7 || trimmed.size() == 9) && trimmed.find_first_not_of("0123456789ABCDEFabcdef", 1) == std::string::npos)
        {
          this->mRed = (unsigned char)strtol(trimmed.substr(1, 2).c_str(), NULL, 16);
          this->mGreen = (unsigned char)strtol(trimmed.substr(3, 2).c_str(), NULL, 16);
          this->mBlue = (unsigned char)strtol(trimmed.substr(5, 2).c_str(), NULL, 16);

          if (trimmed.size() == 9)
            {
              // set the alpha value
              this->mAlpha = (unsigned char)strtol(trimmed.substr(7, 2).c_str(), NULL, 16);
            }
          else
            {
              // if no alpha is given, the color is completely opaque
              this->mAlpha = 255;
            }
        }
      else
        {
          result = false;
        }
    }

  if (result == false)
    {
      this->mRed = 0;
      this->mGreen = 0;
      this->mBlue = 0;
      this->mAlpha = 255;
    }

  return result;
}

/**
 * Creates a string the represents the current color value.
 */
std::string CLColorDefinition::createValueString() const
{
  std::ostringstream os;
  os << "#" << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)mRed << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)mGreen << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)mBlue;

  if (mAlpha != 255)
    {
      os  << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)mAlpha;
    }

  return os.str();
}

/**
 * Returns the key of the color definition.
 */
const std::string& CLColorDefinition::getKey() const
{
  return this->mKey;
}

/**
 * Converts this object to the corresponding SBML object.
 */
ColorDefinition* CLColorDefinition::toSBML(unsigned int level, unsigned int version) const
{
  ColorDefinition* pCD = new ColorDefinition(level, version);
  pCD->setId(this->mId);
  pCD->setRGBA(this->mRed, this->mGreen, this->mBlue, this->mAlpha);
  return pCD;
}

/**
 * Returns the id of the object.
 */
const std::string& CLColorDefinition::getId() const
{
  return this->mId;
}

/**
 * Sets the id of the object.
 */
void CLColorDefinition::setId(const std::string& id)
{
  this->mId = id;
}
