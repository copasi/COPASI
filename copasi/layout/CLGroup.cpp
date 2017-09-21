// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>
#include <sstream>
#include <assert.h>

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/packages/render/sbml/RenderGroup.h>
#include <sbml/packages/render/sbml/Rectangle.h>
#include <sbml/packages/render/sbml/Ellipse.h>
#include <sbml/packages/render/sbml/Transformation2D.h>
#include <sbml/packages/render/sbml/RenderCurve.h>
#include <sbml/packages/render/sbml/Polygon.h>
#include <sbml/packages/render/sbml/Image.h>

#define sbmlEllipse Ellipse
#define sbmlPolygon Polygon
#define sbmlRectangle Rectangle

#include "CLGroup.h"

#include "CLRenderCurve.h"
#include "CLPolygon.h"
#include "CLEllipse.h"
#include "CLRectangle.h"
#include "CLText.h"
#include "CLImage.h"
#include "CLRenderPoint.h"
#include "CLRenderCubicBezier.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor.
 */
CLGroup::CLGroup(CDataContainer* pParent):
  CLGraphicalPrimitive2D(),
  CDataContainer("RenderGroup", pParent),
  mFontFamily(""),
  mFontSize(CLRelAbsVector(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN())),
  mFontWeight(CLText::WEIGHT_UNSET),
  mFontStyle(CLText::STYLE_UNSET),
  mTextAnchor(CLText::ANCHOR_UNSET),
  mVTextAnchor(CLText::ANCHOR_UNSET),
  mStartHead(""),
  mEndHead(""),
  mElements("GroupElements", this),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("RenderGroup", this);
}

/**
 * Copy constructor.
 */
CLGroup::CLGroup(const CLGroup& source, CDataContainer* pParent):
  CLGraphicalPrimitive2D(source),
  CDataContainer(source, pParent),
  mFontFamily(source.mFontFamily),
  mFontSize(source.mFontSize),
  mFontWeight(source.mFontWeight),
  mFontStyle(source.mFontStyle),
  mTextAnchor(source.mTextAnchor),
  mVTextAnchor(source.mVTextAnchor),
  mStartHead(source.mStartHead),
  mEndHead(source.mEndHead),
  mElements("GroupElements", this),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("RenderGroup", this);
  // copy the elements
  size_t i, iMax = source.mElements.size();
  const CDataObject* pChild = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pChild = &source.mElements[i];

      if (dynamic_cast<const CLRectangle*>(pChild))
        {
          this->mElements.add(new CLRectangle(*static_cast<const CLRectangle*>(pChild), this), true);
        }
      else if (dynamic_cast<const CLEllipse*>(pChild))
        {
          this->mElements.add(new CLEllipse(*static_cast<const CLEllipse*>(pChild), this), true);
        }
      else if (dynamic_cast<const CLRenderCurve*>(pChild))
        {
          this->mElements.add(new CLRenderCurve(*static_cast<const CLRenderCurve*>(pChild), this), true);
        }
      else if (dynamic_cast<const CLPolygon*>(pChild))
        {
          this->mElements.add(new CLPolygon(*static_cast<const CLPolygon*>(pChild), this), true);
        }
      else if (dynamic_cast<const CLText*>(pChild))
        {
          this->mElements.add(new CLText(*static_cast<const CLText*>(pChild), this), true);
        }
      else if (dynamic_cast<const CLImage*>(pChild))
        {
          this->mElements.add(new CLImage(*static_cast<const CLImage*>(pChild), this), true);
        }
      else if (dynamic_cast<const CLGroup*>(pChild))
        {
          this->mElements.add(new CLGroup(*static_cast<const CLGroup*>(pChild), this), true);
        }
    }
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLGroup::CLGroup(const RenderGroup& source, CDataContainer* pParent):
  CLGraphicalPrimitive2D(source),
  CDataContainer("RenderGroup", pParent),
  mFontFamily(source.getFontFamily()),
  mFontSize(source.getFontSize()),
  mStartHead(source.getStartHead()),
  mEndHead(source.getEndHead()),
  mElements("GroupElements", this),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("RenderGroup", this);

  // copy the elements
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

  size_t i, iMax = source.getNumElements();
  const Transformation2D* pChild = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pChild = dynamic_cast<const Transformation2D*>(source.getElement((unsigned int) i));

      if (dynamic_cast<const Rectangle*>(pChild))
        {
          this->mElements.add(new CLRectangle(*static_cast<const Rectangle*>(pChild), this), true);
        }
      else if (dynamic_cast<const Ellipse*>(pChild))
        {
          this->mElements.add(new CLEllipse(*static_cast<const Ellipse*>(pChild), this), true);
        }
      else if (dynamic_cast<const RenderCurve*>(pChild))
        {
          this->mElements.add(new CLRenderCurve(*static_cast<const RenderCurve*>(pChild), this), true);
        }
      else if (dynamic_cast<const Polygon*>(pChild))
        {
          this->mElements.add(new CLPolygon(*static_cast<const Polygon*>(pChild), this), true);
        }
      else if (dynamic_cast<const Text*>(pChild))
        {
          this->mElements.add(new CLText(*static_cast<const Text*>(pChild), this), true);
        }
      else if (dynamic_cast<const Image*>(pChild))
        {
          this->mElements.add(new CLImage(*static_cast<const Image*>(pChild), this), true);
        }
      else if (dynamic_cast<const RenderGroup*>(pChild))
        {
          this->mElements.add(new CLGroup(*static_cast<const RenderGroup*>(pChild), this), true);
        }
    }
}
/**
 * Destructor
 */
CLGroup::~CLGroup()
{
  CRootContainer::getKeyFactory()->remove(this->mKey);
}

/**
 * Sets the font family.
 */
void CLGroup::setFontFamily(const std::string& family)
{
  this->mFontFamily = family;
}

/**
 * Sets the font size.
 */
void CLGroup::setFontSize(const CLRelAbsVector& size)
{
  this->mFontSize = size;
}

/**
 * Sets the font weight.
 */
void CLGroup::setFontWeight(CLText::FONT_WEIGHT weight)
{
  this->mFontWeight = weight;
}

/**
 * Sets the font style.
 */
void CLGroup::setFontStyle(CLText::FONT_STYLE style)
{
  this->mFontStyle = style;
}

/**
 * Sets the text anchor.
 */
void CLGroup::setTextAnchor(CLText::TEXT_ANCHOR anchor)
{
  this->mTextAnchor = anchor;
}

/**
 * Sets the vertical text anchor.
 */
void CLGroup::setVTextAnchor(CLText::TEXT_ANCHOR anchor)
{
  this->mVTextAnchor = anchor;
}

/**
 * Sets the start head id.
 */
void CLGroup::setStartHead(const std::string& key)
{
  this->mStartHead = key;
}

/**
 * Sets the end head id.
 */
void CLGroup::setEndHead(const std::string& key)
{
  this->mEndHead = key;
}

/**
 * Returns the font family.
 */
const std::string& CLGroup::getFontFamily() const
{
  return this->mFontFamily;
}

/**
 * Returns the font size.
 */
CLRelAbsVector& CLGroup::getFontSize()
{
  return this->mFontSize;
}

/**
 * Returns the font size.
 */
const CLRelAbsVector& CLGroup::getFontSize() const
{
  return this->mFontSize;
}

/**
 * Returns the font weight.
 */
CLText::FONT_WEIGHT CLGroup::getFontWeight() const
{
  return this->mFontWeight;
}

/**
 * Returns the font style.
 */
CLText::FONT_STYLE CLGroup::getFontStyle() const
{
  return this->mFontStyle;
}

/**
 * Returns the text anchor.
 */
CLText::TEXT_ANCHOR CLGroup::getTextAnchor() const
{
  return this->mTextAnchor;
}

/**
 * Returns the vertical text anchor.
 */
CLText::TEXT_ANCHOR CLGroup::getVTextAnchor() const
{
  return this->mVTextAnchor;
}

/**
 * Returns the start head id.
 */
const std::string& CLGroup::getStartHead() const
{
  return this->mStartHead;
}

/**
 * Returns the end head id.
 */
const std::string& CLGroup::getEndHead() const
{
  return this->mEndHead;
}

/**
 * Returns the number of elements in the group.
 */
size_t CLGroup::getNumElements() const
{
  return this->mElements.size();
}

/**
 * Returns the list of  elements.
 */
const CDataVector<CDataObject>* CLGroup::getListOfElements() const
{
  return &this->mElements;
}

/**
 * Returns the list of  elements.
 */
CDataVector<CDataObject>* CLGroup::getListOfElements()
{
  return &this->mElements;
}

/**
 * Returns element with index n.
 * If there is no such element, NULL is returned.
 */
CDataObject* CLGroup::getElement(size_t n)
{
  if (n < this->mElements.size())
    {
      return &this->mElements[n];
    }
  else
    {
      return NULL;
    }
}

/**
 * Returns element with index n.
 * If there is no such element, NULL is returned.
 */
const CDataObject* CLGroup::getElement(size_t n) const
{
  if (n < this->mElements.size())
    {
      return &this->mElements[n];
    }
  else
    {
      return NULL;
    }
}

/**
 * Creates an image object and adds it to the end of the list of child
 * elements.
 */
CLImage* CLGroup::createImage()
{
  CLImage* pCLImage = new CLImage(this);
  this->mElements.add(pCLImage, true);
  return pCLImage;
}

/**
 * Creates an image object and adds it to the end of the list of child
 * elements.
 */
CLGroup* CLGroup::createGroup()
{
  CLGroup* pCLGroup = new CLGroup(this);
  this->mElements.add(pCLGroup, true);
  return pCLGroup;
}

/**
 * Creates a rectangle object and adds it to the end of the list of child
 * elements.
 */
CLRectangle* CLGroup::createRectangle()
{
  CLRectangle* pCLRectangle = new CLRectangle(this);
  this->mElements.add(pCLRectangle, true);
  return pCLRectangle;
}

/**
 * Creates an ellipse object and adds it to the end of the list of child
 * elements.
 */
CLEllipse* CLGroup::createEllipse()
{
  CLEllipse* pCLEllipse = new CLEllipse(this);
  this->mElements.add(pCLEllipse, true);
  return pCLEllipse;
}

/**
 * Creates a curve object and adds it to the end of the list of child
 * elements.
 */
CLRenderCurve* CLGroup::createCurve()
{
  CLRenderCurve* pCurve = new CLRenderCurve(this);
  this->mElements.add(pCurve, true);
  return pCurve;
}

/**
 * Creates a polygon object and adds it to the end of the list of child
 * elements.
 */
CLPolygon* CLGroup::createPolygon()
{
  CLPolygon* pCLPolygon = new CLPolygon(this);
  this->mElements.add(pCLPolygon, true);
  return pCLPolygon;
}

/**
 * Creates a text object and adds it to the end of the list of child
 * elements.
 */
CLText* CLGroup::createText()
{
  CLText* pCLText = new CLText(this);
  this->mElements.add(pCLText, true);
  return pCLText;
}

/**
 * Adds a copy of the given element to the end of the list of children elements.
 */
void CLGroup::addChildElement(const CLTransformation2D* pChild)
{
  if (dynamic_cast<const CLRectangle*>(pChild))
    {
      this->mElements.add(new CLRectangle(*static_cast<const CLRectangle*>(pChild), this), true);
    }
  else if (dynamic_cast<const CLEllipse*>(pChild))
    {
      this->mElements.add(new CLEllipse(*static_cast<const CLEllipse*>(pChild), this), true);
    }
  else if (dynamic_cast<const CLRenderCurve*>(pChild))
    {
      this->mElements.add(new CLRenderCurve(*static_cast<const CLRenderCurve*>(pChild), this), true);
    }
  else if (dynamic_cast<const CLPolygon*>(pChild))
    {
      this->mElements.add(new CLPolygon(*static_cast<const CLPolygon*>(pChild), this), true);
    }
  else if (dynamic_cast<const CLText*>(pChild))
    {
      this->mElements.add(new CLText(*static_cast<const CLText*>(pChild), this), true);
    }
  else if (dynamic_cast<const CLImage*>(pChild))
    {
      this->mElements.add(new CLImage(*static_cast<const CLImage*>(pChild), this), true);
    }
  else if (dynamic_cast<const CLGroup*>(pChild))
    {
      this->mElements.add(new CLGroup(*static_cast<const CLGroup*>(pChild), this), true);
    }
}

/**
 * Returns true if the start head is set or false otherwise.
 */
bool CLGroup::isSetStartHead() const
{
  return (!this->mStartHead.empty() && this->mStartHead != "none");
}

/**
 * Returns true if the start head is set or false otherwise.
 */
bool CLGroup::isSetEndHead() const
{
  return (!this->mEndHead.empty() && this->mEndHead != "none");
}

/**
 * Returns true if the font family has been set or false otherwise.
 */
bool CLGroup::isSetFontFamily() const
{
  return !this->mFontFamily.empty();
}

/**
 * Returns true if the font size has been set or false otherwise.
 */
bool CLGroup::isSetFontSize() const
{
  return (this->mFontSize.getAbsoluteValue() == this->mFontSize.getAbsoluteValue() && this->mFontSize.getRelativeValue() == this->mFontSize.getRelativeValue());
}

/**
 * Returns true if the font weight has been set or false otherwise.
 */
bool CLGroup::isSetFontWeight() const
{
  return (this->mFontWeight != CLText::WEIGHT_UNSET);
}

/**
 * Returns true if the font style has been set or false otherwise.
 */
bool CLGroup::isSetFontStyle() const
{
  return (this->mFontStyle != CLText::STYLE_UNSET);
}

/**
 * This methods imports a curve in the old format into the new format.
 * Since the old curves could have gaps, the original curve might have to be
 * split into several new curves.
void CLGroup::importOldCurve(const XMLNode& node)
{
    const XMLAttributes& curveAttributes=node.getAttributes();
    const XMLNode* child;
    size_t n=0,nMax = node.getNumChildren();
    const XMLNode* pOrigAnnotation=NULL;
    const XMLNode* pOrigNotes=NULL;
    while(n<nMax)
    {
  child=&node.getChild(n);
  std::string childName=child->getName();
  if(childName=="listOfCurveSegments")
  {
     size_t i,iMax=child->getNumChildren();
     const XMLNode* child2=NULL;
     CLRenderPoint start;
     CLRenderPoint end;
     CLRenderPoint lastEnd;
     CLRenderPoint bp1;
     CLRenderPoint bp2;
           bool startSet=false;
           bool endSet=false;
           bool bp1Set=false;
           bool bp2Set=false;
     std::string childName2;
     CLRenderCurve* pCurve=new CLRenderCurve();
           // read the attributes
           pCurve->Transformation2D::readAttributes(curveAttributes);
           pCurve->GraphicalPrimitive1D::readAttributes(curveAttributes);
           pCurve->readAttributes(curveAttributes);
     for(i=0;i<iMax;++i)
     {
    child2=&child->getChild(i);
    childName2=child2->getName();
                if(childName2=="curveSegment")
    {
                        startSet=false;
                        endSet=false;
                        bp1Set=false;
                        bp2Set=false;
      const XMLAttributes& innerAttributes=child2->getAttributes();
      int typeIndex=innerAttributes.getIndex("type");
      if(typeIndex==-1 || innerAttributes.getURI(typeIndex)!="http://www.w3.org/2001/XMLSchema-instance")
      {
        continue;
      }
      size_t j,jMax=child2->getNumChildren();
      for(j=0;j<jMax;++j)
      {
        const XMLNode* child3=&child2->getChild(j);
        std::string childName3=child3->getName();
        if(childName3=="start")
        {
          start=CLRenderPoint(*child3);
          startSet=true;
        }
        // add the basepoints and the endpoint
        else if(childName3=="end")
        {
          end=CLRenderPoint(*child3);
          endSet=true;
        }
        else if(innerAttributes.getValue(typeIndex)=="CubicBezier"  && childName3=="basePoint1")
        {
          bp1=CLRenderPoint(*child3);
          bp1Set=true;
        }
        else if(innerAttributes.getValue(typeIndex)=="CubicBezier" && childName3=="basePoint2")
        {
          bp2=CLRenderPoint(*child3);
          bp2Set=true;
        }
                        }
                        if(!startSet || !endSet)
                        {
                            // skip this point
                            // TODO this is an error
                            continue;
                        }
                        if(pCurve->getNumElements()==0)
                        {
                            // add the start point
                            pCurve->addCurveElement(&start);
                        }
                        else
                        {
                            // check if start is identical to lastEnd
                            // if not, we have to start a new curve
                            if(!(start == lastEnd))
                            {
                                if(pCurve->getNumElements() > 1)
                                {
                                    // add the curve to the goup
                                    this->mElements.add(pCurve,true);
                                }
                                else
                                {
                                    delete pCurve;
                                }
                                // we have do clear the endHead on the
                                // preceeding curve
                                pCurve->setEndHead("none");
                                pCurve=new CLRenderCurve();
                                // read the attributes
                                pCurve->Transformation2D::readAttributes(curveAttributes);
                                pCurve->GraphicalPrimitive1D::readAttributes(curveAttributes);
                                pCurve->readAttributes(curveAttributes);
                                // we have to clear the start head on this
                                // curve
                                pCurve->setStartHead("none");
                                pCurve->addCurveElement(&start);
                            }
                        }
                        if(innerAttributes.getValue(typeIndex)=="CubicBezier")
                        {
                            if(!bp1Set)
                            {
                                if(bp2Set)
                                {
                                    // basepoint1 is the same as basepoint2
                                    bp1=bp2;
                                }
                                else
                                {
                                    bp1=CLRenderPoint(CLRelAbsVector((start.x().getAbsoluteValue()+end.x().getAbsoluteValue())/2.0,(start.x().getRelativeValue()+end.x().getRelativeValue())/2.0)
                                            ,CLRelAbsVector((start.y().getAbsoluteValue()+end.y().getAbsoluteValue())/2.0,(start.y().getRelativeValue()+end.y().getRelativeValue())/2.0)
                                            ,CLRelAbsVector((start.z().getAbsoluteValue()+end.z().getAbsoluteValue())/2.0,(start.z().getRelativeValue()+end.z().getRelativeValue())/2.0)
                                            );
                                    bp1Set=true;
                                }
                            }
                            if(!bp2Set)
                            {
                                // at this time bp1 has to be set
                                bp2=bp1;
                            }
                            // add the cubic bezier element
                            CLRenderCubicBezier* pBezier=new CLRenderCubicBezier(bp1.x(),bp1.y(),bp1.z(),
                                    bp2.x(),bp2.y(),bp2.z(),
                                    end.x(),end.y(),end.z());
                            pCurve->addCurveElement(pBezier);
                            delete pBezier;
                            lastEnd=end;
                        }
                        else
                        {
                            // add the end point
                            pCurve->addCurveElement(&end);
                            lastEnd=end;
                        }
    }
     }
     if(pCurve->getNumElements() > 1)
     {
       // add the curve to the goup
       this->mElements.add(pCurve,true);
     }
  }
        else if(childName=="annotation")
        {
            pOrigAnnotation=child;
        }
        else if(childName=="notes")
        {
            pOrigNotes=child;
        }
        ++n;
    }
}
 */

/**
 * Returns true if the horizonal alignment attribute has been set.
 */
bool CLGroup::isSetTextAnchor() const
{
  return this->mTextAnchor != CLText::ANCHOR_UNSET;
}

/**
 * Returns true if the vertical alignment attribute has been set.
 */
bool CLGroup::isSetVTextAnchor() const
{
  return this->mVTextAnchor != CLText::ANCHOR_UNSET;
}

/**
 * Returns the key of the color definition.
 */
const std::string& CLGroup::getKey() const
{
  return this->mKey;
}

/**
 * Converts this object to the corresponding SBML object.
 */
RenderGroup* CLGroup::toSBML(unsigned int level, unsigned int version) const
{
  RenderGroup* pGroup = new RenderGroup(level, version);
  this->addSBMLAttributes(pGroup);
  pGroup->setStartHead(this->mStartHead);
  pGroup->setEndHead(this->mEndHead);
  RelAbsVector* pV = this->getFontSize().toSBML();
  pGroup->setFontSize(*pV);
  delete pV;
  pGroup->setFontFamily(this->getFontFamily());

  switch (this->getFontWeight())
    {
      case CLText::WEIGHT_UNSET:
        pGroup->setFontWeight(Text::WEIGHT_UNSET);
        break;

      case CLText::WEIGHT_BOLD:
        pGroup->setFontWeight(Text::WEIGHT_BOLD);
        break;

      default:
        pGroup->setFontWeight(Text::WEIGHT_NORMAL);
        break;
    }

  switch (this->getFontStyle())
    {
      case CLText::STYLE_UNSET:
        pGroup->setFontStyle(Text::STYLE_UNSET);
        break;

      case CLText::STYLE_ITALIC:
        pGroup->setFontStyle(Text::STYLE_ITALIC);
        break;

      default:
        pGroup->setFontStyle(Text::STYLE_NORMAL);
        break;
    }

  switch (this->getTextAnchor())
    {
      case CLText::ANCHOR_UNSET:
        pGroup->setTextAnchor(Text::ANCHOR_UNSET);
        break;

      case CLText::ANCHOR_END:
        pGroup->setTextAnchor(Text::ANCHOR_END);
        break;

      case CLText::ANCHOR_MIDDLE:
        pGroup->setTextAnchor(Text::ANCHOR_MIDDLE);
        break;

      default:
        pGroup->setTextAnchor(Text::ANCHOR_START);
        break;
    }

  switch (this->getVTextAnchor())
    {
      case CLText::ANCHOR_UNSET:
        pGroup->setVTextAnchor(Text::ANCHOR_UNSET);
        break;

      case CLText::ANCHOR_BOTTOM:
        pGroup->setVTextAnchor(Text::ANCHOR_BOTTOM);
        break;

      case CLText::ANCHOR_MIDDLE:
        pGroup->setVTextAnchor(Text::ANCHOR_MIDDLE);
        break;

      default:
        pGroup->setVTextAnchor(Text::ANCHOR_TOP);
        break;
    }

  size_t i, iMax = this->mElements.size();
  int result;

  for (i = 0; i < iMax; ++i)
    {
      const Transformation2D* pChild = NULL;
      const CDataObject* pObject = &this->mElements[i];

      if (dynamic_cast<const CLRectangle*>(pObject))
        {
          pChild = static_cast<const CLRectangle*>(pObject)->toSBML(level, version);
        }
      else if (dynamic_cast<const CLEllipse*>(pObject))
        {
          pChild = static_cast<const CLEllipse*>(pObject)->toSBML(level, version);
        }
      else if (dynamic_cast<const CLRenderCurve*>(pObject))
        {
          pChild = static_cast<const CLRenderCurve*>(pObject)->toSBML(level, version);
        }
      else if (dynamic_cast<const CLPolygon*>(pObject))
        {
          pChild = static_cast<const CLPolygon*>(pObject)->toSBML(level, version);
        }
      else if (dynamic_cast<const CLText*>(pObject))
        {
          if (static_cast<const CLText*>(pObject)->getText().empty())
            continue;

          pChild = static_cast<const CLText*>(pObject)->toSBML(level, version);
        }
      else if (dynamic_cast<const CLImage*>(pObject))
        {
          pChild = static_cast<const CLImage*>(pObject)->toSBML(level, version);
        }
      else if (dynamic_cast<const CLGroup*>(pObject))
        {
          pChild = static_cast<const CLGroup*>(pObject)->toSBML(level, version);
        }

      result = pGroup->addChildElement(pChild);
      assert(result == LIBSBML_OPERATION_SUCCESS);
      delete pChild;
    }

  return pGroup;
}
