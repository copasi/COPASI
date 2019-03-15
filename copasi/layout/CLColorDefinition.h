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

#ifndef CLColorDefinition_H__
#define CLColorDefinition_H__

#include <string>

#include "copasi/layout/CLBase.h"
#include "copasi/core/CDataObject.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class ColorDefinition;
LIBSBML_CPP_NAMESPACE_END

class CDataContainer;

class CLColorDefinition : public CLBase, public CDataObject
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
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CLColorDefinition * pDataObject
   */
  static CLColorDefinition * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Contructor which sets the ColorDefinition to completely opaque
   * black.
   */
  CLColorDefinition(CDataContainer* pParent = NULL);

  /**
   * Constructor which sets the ColorDefinition to the given RGBA values.
   */
  CLColorDefinition(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255, CDataContainer* pParent = NULL);

  /**
   * Copy Contructor
   */
  CLColorDefinition(const CLColorDefinition& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLColorDefinition(const ColorDefinition& source, CDataContainer* pParent = NULL);

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
