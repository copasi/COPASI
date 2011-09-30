// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGroup.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:35:20 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLGroup_H__
#define CLGroup_H__

#include "copasi/layout/CLGraphicalPrimitive2D.h"
#include "copasi/layout/CLText.h"

#include "copasi/report/CCopasiContainer.h"
#include "copasi/utilities/CCopasiVector.h"

#include <string>

class Group;

class CLImage;
class CLRectangle;
class CLEllipse;
class CLPolygon;
class CLRenderCurve;

class CLGroup : public CLGraphicalPrimitive2D, public CCopasiContainer
{
private:
  // prevent the compiler from generating the assignment operator
  CLGroup& operator=(const CLGroup& source);

protected:
  std::string mFontFamily;
  CLRelAbsVector mFontSize;
  CLText::FONT_WEIGHT mFontWeight;
  CLText::FONT_STYLE mFontStyle;
  CLText::TEXT_ANCHOR mTextAnchor;
  CLText::TEXT_ANCHOR mVTextAnchor;
  std::string mStartHead;
  std::string mEndHead;
  CCopasiVector<CCopasiObject> mElements;

  /**
   * key for the object.
   */
  std::string mKey;

public:
  /**
   * Constructor.
   */
  CLGroup(CCopasiContainer* pParent = NULL);

  /**
   * Copy constructor.
   */
  CLGroup(const CLGroup& source, CCopasiContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLGroup(const Group& source, CCopasiContainer* pParent = NULL);

  /**
   * Destructor.
   */
  ~CLGroup();

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
   * Sets the text anchor.
   */
  void setTextAnchor(CLText::TEXT_ANCHOR anchor);

  /**
   * Sets the vertical text anchor.
   */
  void setVTextAnchor(CLText::TEXT_ANCHOR anchor);

  /**
   * Sets the start head id.
   */
  void setStartHead(const std::string& key);

  /**
   * Sets the end head id.
   */
  void setEndHead(const std::string& key);

  /**
   * Returns the font family.
   */
  const std::string& getFontFamily() const;

  /**
   * Returns the font size.
   */
  CLRelAbsVector& getFontSize();

  /**
   * Returns the font size.
   */
  const CLRelAbsVector& getFontSize() const;

  /**
   * Returns the font weight.
   */
  CLText::FONT_WEIGHT getFontWeight() const;

  /**
   * Returns the font style.
   */
  CLText::FONT_STYLE getFontStyle() const;

  /**
   * Returns the text anchor.
   */
  CLText::TEXT_ANCHOR getTextAnchor() const;

  /**
   * Returns the vertical text anchor.
   */
  CLText::TEXT_ANCHOR getVTextAnchor() const;

  /**
   * Returns the start head id.
   */
  const std::string& getStartHead() const;

  /**
   * Returns the end head id.
   */
  const std::string& getEndHead() const;

  /**
   * Returns the number of elements in the group.
   */
  size_t getNumElements() const;

  /**
   * Returns the list of  elements.
   */
  const CCopasiVector<CCopasiObject>* getListOfElements() const;

  /**
   * Returns the list of  elements.
   */
  CCopasiVector<CCopasiObject>* getListOfElements();

  /**
   * Returns element with index n.
   * If there is no such element, NULL is returned.
   */
  CCopasiObject* getElement(size_t n);

  /**
   * Returns element with index n.
   * If there is no such element, NULL is returned.
   */
  const CCopasiObject* getElement(size_t n) const;

  /**
   * Returns true if the horizonal alignment attribute has been set.
   */
  bool isSetTextAnchor() const;

  /**
   * Returns true if the vertical alignment attribute has been set.
   */
  bool isSetVTextAnchor() const;

  /**
   * Creates an image object and adds it to the end of the list of child
   * elements.
   */
  CLImage* createImage();

  /**
   * Creates an image object and adds it to the end of the list of child
   * elements.
   */
  CLGroup* createGroup();

  /**
   * Creates a rectangle object and adds it to the end of the list of child
   * elements.
   */
  CLRectangle* createRectangle();

  /**
   * Creates an ellipse object and adds it to the end of the list of child
   * elements.
   */
  CLEllipse* createEllipse();

  /**
   * Creates a curve object and adds it to the end of the list of child
   * elements.
   */
  CLRenderCurve* createCurve();

  /**
   * Creates a polygon object and adds it to the end of the list of child
   * elements.
   */
  CLPolygon* createPolygon();

  /**
   * Creates a text object and adds it to the end of the list of child
   * elements.
   */
  CLText* createText();

  /**
   * Adds a copy of the given element to the end of the list of children elements.
   */
  void addChildElement(const CLTransformation2D* pChild);

  /**
   * Returns true if the start head is set or false otherwise.
   */
  bool isSetStartHead() const;

  /**
   * Returns true if the start head is set or false otherwise.
   */
  bool isSetEndHead() const;

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
  Group* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLGroup_H__ */
