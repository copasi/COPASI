// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sstream>
#include <assert.h>

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/packages/render/sbml/LineEnding.h>

#include "CLLineEnding.h"

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor.
 */
CLLineEnding::CLLineEnding(CCopasiContainer* pParent):
  CLGraphicalPrimitive2D(),
  CCopasiContainer("LineEnding", pParent),
  mEnableRotationalMapping(false),
  mpGroup(NULL),
  mKey(""),
  mId("")
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("LineEnding", this);
}

/**
 * Copy Constructor.
 */
CLLineEnding::CLLineEnding(const CLLineEnding& source, CCopasiContainer* pParent):
  CLGraphicalPrimitive2D(source),
  CCopasiContainer(source, pParent),
  mEnableRotationalMapping(source.mEnableRotationalMapping),
  mBoundingBox(source.mBoundingBox),
  mpGroup(NULL),
  mKey(""),
  mId(source.mId)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("LineEnding", this);

  if (source.mpGroup != NULL)
    {
      this->mpGroup = new CLGroup(*source.mpGroup, this);
    }
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLLineEnding::CLLineEnding(const LineEnding& source, CCopasiContainer* pParent):
  CLGraphicalPrimitive2D(source),
  CCopasiContainer("LineEnding", pParent),
  mEnableRotationalMapping(source.getIsEnabledRotationalMapping()),
  mBoundingBox(*source.getBoundingBox()),
  mpGroup(new CLGroup(*source.getGroup(), this)),
  mKey(""),
  mId(source.getId())
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("LineEnding", this);
}

/**
 * Sets whether rotational mapping is to be done or not.
 */
void CLLineEnding::setEnableRotationalMapping(bool enable)
{
  this->mEnableRotationalMapping = enable;
}

/**
 * Returns whether rotational mapping is enabled or not.
 */
bool CLLineEnding::getIsEnabledRotationalMapping() const
{
  return this->mEnableRotationalMapping;
}

/**
 * Sets the bounding box.
 */
void CLLineEnding::setBoundingBox(const CLBoundingBox* box)
{
  this->mBoundingBox = *box;
}

/**
 * Returns the bounding box.
 */
CLBoundingBox* CLLineEnding::getBoundingBox()
{
  return &this->mBoundingBox;
}

/**
 * Returns the bounding box.
 */
const CLBoundingBox* CLLineEnding::getBoundingBox() const
{
  return &this->mBoundingBox;
}

/**
 * Sets the group.
 */
void CLLineEnding::setGroup(const CLGroup* pGroup)
{
  if (pGroup)
    {
      if (this->mpGroup != NULL)
        {
          delete this->mpGroup;
        }

      this->mpGroup = new CLGroup(*pGroup, this);
    }
}

/**
 * Returns the group object.
 */
CLGroup* CLLineEnding::getGroup()
{
  return this->mpGroup;
}

/**
 * Returns the group object.
 */
const CLGroup* CLLineEnding::getGroup() const
{
  return this->mpGroup;
}

/**
 * Returns the key string for the line ending.
 */
const std::string& CLLineEnding::getKey() const
{
  return this->mKey;
}

/**
 * Returns the id of the object.
 */
const std::string& CLLineEnding::getId() const
{
  return this->mId;
}

/**
 * Sets the id of the object.
 */
void CLLineEnding::setId(const std::string& id)
{
  this->mId = id;
}

/**
 * Converts this object to the corresponding SBML object.
 */
LineEnding* CLLineEnding::toSBML(unsigned int level, unsigned int version) const
{
  LineEnding* pLE = new LineEnding(level, version);
  this->addSBMLAttributes(pLE);
  pLE->setId(this->mId);
  pLE->setEnableRotationalMapping(this->mEnableRotationalMapping);
  BoundingBox bb(level, version);
  bb.setId("bb");
  Point p(new LayoutPkgNamespaces(),
          this->mBoundingBox.getPosition().getX(),
          this->mBoundingBox.getPosition().getY());
  bb.setPosition(&p);
  Dimensions d(new LayoutPkgNamespaces(),
               this->mBoundingBox.getDimensions().getWidth(),
               this->mBoundingBox.getDimensions().getHeight());
  bb.setDimensions(&d);
  pLE->setBoundingBox(&bb);
  const RenderGroup* pG = this->mpGroup->toSBML(level, version);
  pLE->setGroup(pG);
  delete pG;
  return pLE;
}
