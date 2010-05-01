// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLColorDefinition.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/05/01 14:35:03 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLColorDefinition_H__
#define CLColorDefinition_H__

#include <copasi/layout/CLBase.h>
#include <copasi/report/CCopasiObject.h>

#include <string>

#include <sbml/layout/render/ColorDefinition.h>

class CCopasiContainer;

class CLColorDefinition : public CLBase, public CCopasiObject
{
private:
  // preent the compiler from generating the assignment operator
  CLColorDefinition& operator=(const CLColorDefinition& source);

protected:
  // id is inherited from SBase
  unsigned char mRed;
  unsigned char mGreen;
  unsigned char mBlue;
  unsigned char mAlpha;

  /**
   * The color definition needs a key.
   */
  std::string mKey;

  /**
   * The color definition needs an id in addition to the key.
   * The id corresponds to the id in the SBML render extension and it does not have to
   * be globally unique. As a matter of fact, it is sometimes needed that color definitions of
   * different render information have the same id.
   */
  std::string mId;

public:
  /**
   * Contructor which sets the ColorDefinition to completely opaque
   * black.
   */
  CLColorDefinition(CCopasiContainer* pParent = NULL);

  /**
   * Constructor which sets the ColorDefinition to the given RGBA values.
   */
  CLColorDefinition(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255, CCopasiContainer* pParent = NULL);

  /**
   * Copy Contructor
   */
  CLColorDefinition(const CLColorDefinition& source, CCopasiContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLColorDefinition(const ColorDefinition& source, CCopasiContainer* pParent = NULL);

  virtual ~CLColorDefinition();

  /**
   * Returns the red color component.
   */
  unsigned char getRed() const;

  /**
   * Returns the green color component.
   */
  unsigned char getGreen() const;

  /**
   * Returns the blue color component.
   */
  unsigned char getBlue() const;

  /**
   * Returns the alpha color component.
   */
  unsigned char getAlpha() const;

  /**
   * Sets the red color component.
   */
  void setRed(unsigned char c);

  /**
   * Sets the green color component.
   */
  void setGreen(unsigned char c);

  /**
   * Sets the blue color component.
   */
  void setBlue(unsigned char c);

  /**
   * Sets alpha red color component.
   */
  void setAlpha(unsigned char c);

  /**
   * Sets the red green, blue and alpha color component.
   * The alpha value is optional and defaults to 255 if not given.
   */
  void setRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

  /**
   * Sets the color value from a given string.
   * If the string is not a valid value string, the color value is set to
   * black and false is returned.
   */
  bool setColorValue(const std::string& valueString);

  /**
   * Creates a string the represents the current color value.
   */
  std::string createValueString() const;

  /**
   * Returns the key of the color definition.
   */
  const std::string& getKey() const;

  /**
   * Converts this object to the corresponding SBML object.
   */
  ColorDefinition* toSBML(unsigned int level, unsigned int version) const;

  /**
   * Returns the id of the object.
   */
  const std::string& getId() const;

  /**
   * Sets the id of the object.
   */
  void setId(const std::string& id);
};

#endif /* CLColorDefinition_H__ */
