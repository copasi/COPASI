// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define USE_LAYOUT 1

#ifdef USE_CRENDER_EXTENSION
#define USE_RENDER 1

#include <sbml/packages/render/extension/RenderGraphicalObjectPlugin.h>

#endif // USE_CRENDER_EXTENSION

#include <sbml/packages/layout/sbml/GraphicalObject.h>

#include "CLGraphicalObject.h"

#include "report/CKeyFactory.h"
#include "sbml/CSBMLExporter.h"
#include "copasi/report/CCopasiRootContainer.h"

CLGraphicalObject::CLGraphicalObject(const std::string & name,
                                     const CCopasiContainer * pParent)
  : CLBase(),
    CCopasiContainer(name, pParent, "LayoutElement"),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Layout", this)),
    mModelObjectKey(""),
#ifdef USE_CRENDER_EXTENSION
    mObjectRole(""),
#endif // USE_CRENDER_EXTENSION
    mBBox()
{};

CLGraphicalObject::CLGraphicalObject(const CLGraphicalObject & src,
                                     const CCopasiContainer * pParent)
  : CLBase(src),
    CCopasiContainer(src, pParent),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Layout", this)),
    mModelObjectKey(src.mModelObjectKey),
#ifdef USE_CRENDER_EXTENSION
    mObjectRole(src.mObjectRole),
#endif // USE_CRENDER_EXTENSION
    mBBox(src.mBBox)
{};

CLGraphicalObject::CLGraphicalObject(const GraphicalObject & sbml,
                                     std::map<std::string, std::string> & layoutmap,
                                     const CCopasiContainer * pParent)
  : CLBase(sbml),
    CCopasiContainer(sbml.getId(), pParent, "LayoutElement"),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Layout", this)),
    mModelObjectKey(""),
    mBBox(*sbml.getBoundingBox())
{

#ifdef USE_CRENDER_EXTENSION
  RenderGraphicalObjectPlugin* rgoPlugin = (RenderGraphicalObjectPlugin*) sbml.getPlugin("render");

  if (rgoPlugin != NULL)
    mObjectRole = rgoPlugin->getObjectRole();

#endif // USE_CRENDER_EXTENSION

  //add the copasi key to the map
  layoutmap[sbml.getId()] = mKey;
};

CLGraphicalObject::~CLGraphicalObject()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

CLGraphicalObject & CLGraphicalObject::operator= (const CLGraphicalObject & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLBase::operator=(rhs);

  //warning: in this place we should call the assignment operator of
  //CCopasiContainer (which does not exist).
  //We handle this explicitly instead.
  setObjectName(rhs.getObjectName());
  //object flag cannot be accessed, it is private.

  mModelObjectKey = rhs.mModelObjectKey;
#ifdef USE_CRENDER_EXTENSION
  this->mObjectRole = rhs.mObjectRole;
#endif // USE_CRENDER_EXTENSION
  mBBox = rhs.mBBox;

  return *this;
}

CCopasiObject * CLGraphicalObject::getModelObject() const
{
  CCopasiObject* pObject = NULL;

  // as an additional safeguard, we check
  // if the object is in the same datamodel
  // This is not foolproof, but should work in most cases.
  if (this->hasValidModelReference())
    {
      pObject = CCopasiRootContainer::getKeyFactory()->get(mModelObjectKey);
    }

  return pObject;
}

std::string CLGraphicalObject::getModelObjectName() const
{
  CCopasiObject * tmp = getModelObject();

  if (tmp)
    return tmp->getObjectName();
  else
    return "";
}

std::string CLGraphicalObject::getModelObjectDisplayName(bool /* regular */, bool /* richtext */) const
{
  CCopasiObject * tmp = getModelObject();

  if (tmp)
    {
      return tmp->getObjectName();
    }
  else
    {
      return "";
    }
}

void CLGraphicalObject::exportToSBML(GraphicalObject * sbmlobject,
                                     const std::map<const CCopasiObject*, SBase*> & /* copasimodelmap */,
                                     std::map<std::string, const SBase*>& sbmlIDs) const
{
  if (!sbmlobject) return;

  //Name and ID
  std::string id = CSBMLExporter::createUniqueId(sbmlIDs, "layout_glyph", true);
  sbmlobject->setId(id);
  sbmlIDs.insert(std::pair<const std::string, const SBase*>(id, sbmlobject));

  //Bounding box
  BoundingBox tmpbox = mBBox.getSBMLBoundingBox();
  sbmlobject->setBoundingBox(&tmpbox);
#ifdef USE_CRENDER_EXTENSION

  if (this->mObjectRole.find_first_not_of(" \t\r\n") != std::string::npos)
    {
      RenderGraphicalObjectPlugin* rgoPlugin = (RenderGraphicalObjectPlugin*) sbmlobject->getPlugin("render");

      if (rgoPlugin != NULL)
        rgoPlugin->setObjectRole(this->mObjectRole);
    }

#endif // USE_CRENDER_EXTENSION
}

std::ostream & operator<<(std::ostream &os, const CLGraphicalObject & g)
{
  os << "GraphicalObject \"" << g.getObjectName() << "\" " << g.mBBox << std::endl;
  std::string tmp = g.getModelObjectDisplayName();

  if (tmp != "")
    os << "  refers to " << tmp << std::endl;

  return os;
}

void CLGraphicalObject::print(std::ostream * ostream) const
{*ostream << *this;}

#ifdef USE_CRENDER_EXTENSION
/**
 * Method to set the role of a graphical object.
 */
void CLGraphicalObject::setObjectRole(const std::string& role)
{
  this->mObjectRole = role;
}

/**
 * Method to read the object role of an object.
 */
const std::string& CLGraphicalObject::getObjectRole() const
{
  return this->mObjectRole;
}

#endif // USE_CRENDER_EXTENSION

/**
 * This method is used for the export of several layout elements.
 * Layout elements can reference model elements, but when a referenced model element
 * is deleted, the layout is not infomred about this yet, so we end up with dnagling
 * references.
 * In order to not write these dangling references to file, we check if the reference
 * belongs to a valid object in the same datamodel. If not, we issue a warning.
 * This warning is only issued once during a save process.
 *
 * If the key belongs to an object in the same datamodel, true is returned, else false is returned.
 */
bool CLGraphicalObject::hasValidModelReference() const
{
  bool result = false;
  // check if the object for this key actually exists
  // TODO This is only a workaround because it is theoretically
  // TODO possible that the key no longer belongs to the same object it
  // TODO originally did.
  CCopasiObject* pObj = CCopasiRootContainer::getKeyFactory()->get(this->mModelObjectKey);

  if (pObj != NULL)
    {
      // check if the object actually belongs to the same
      // model as the text glyph
      const CCopasiDataModel* pDM1 = NULL;
      const CCopasiDataModel* pDM2 = NULL;
      const CCopasiContainer* pParent = pObj->getObjectParent();

      while (pParent != NULL)
        {
          pDM1 = dynamic_cast<const CCopasiDataModel*>(pParent);

          if (pDM1 != NULL)
            {
              break;
            }

          pParent = pParent->getObjectParent();
        }

      pParent = this->getObjectParent();

      while (pParent != NULL)
        {
          pDM2 = dynamic_cast<const CCopasiDataModel*>(pParent);

          if (pDM2 != NULL)
            {
              break;
            }

          pParent = pParent->getObjectParent();
        }

      assert(pDM2 != NULL);

      if (pDM1 != NULL && pDM1 == pDM2)
        {
          result = true;
        }
    }

  return result;
}
