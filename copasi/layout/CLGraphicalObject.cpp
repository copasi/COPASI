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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/packages/render/extension/RenderGraphicalObjectPlugin.h>
#include <sbml/packages/layout/sbml/GraphicalObject.h>

#include "copasi/copasi.h"

#include "CLGraphicalObject.h"

#include "copasi/report/CKeyFactory.h"
#include "copasi/sbml/CSBMLExporter.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

// static
CLGraphicalObject * CLGraphicalObject::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLGraphicalObject(data.getProperty(CData::OBJECT_NAME).toString(),
                               NO_PARENT);
}

// virtual
CData CLGraphicalObject::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLGraphicalObject::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CLGraphicalObject::CLGraphicalObject(const std::string & name,
                                     const CDataContainer * pParent)
  : CLBase(),
    CDataContainer(name, pParent, "LayoutElement"),
    mKey(CRootContainer::getKeyFactory()->add("Layout", this)),
    mModelObjectKey(""),
    mObjectRole(""),
    mBBox()
{};

CLGraphicalObject::CLGraphicalObject(const CLGraphicalObject & src,
                                     const CDataContainer * pParent)
  : CLBase(src),
    CDataContainer(src, pParent),
    mKey(CRootContainer::getKeyFactory()->add("Layout", this)),
    mModelObjectKey(src.mModelObjectKey),
    mObjectRole(src.mObjectRole),
    mBBox(src.mBBox)
{};

CLGraphicalObject::CLGraphicalObject(const GraphicalObject & sbml,
                                     std::map<std::string, std::string> & layoutmap,
                                     const CDataContainer * pParent)
  : CLBase(sbml),
    CDataContainer(sbml.getId(), pParent, "LayoutElement"),
    mKey(CRootContainer::getKeyFactory()->add("Layout", this)),
    mModelObjectKey(""),
    mBBox(*sbml.getBoundingBox())
{
  RenderGraphicalObjectPlugin* rgoPlugin = (RenderGraphicalObjectPlugin*) sbml.getPlugin("render");

  if (rgoPlugin != NULL)
    mObjectRole = rgoPlugin->getObjectRole();

  //add the copasi key to the map
  layoutmap[sbml.getId()] = mKey;
};

CLGraphicalObject::~CLGraphicalObject()
{
  CRootContainer::getKeyFactory()->remove(mKey);
}

CLGraphicalObject & CLGraphicalObject::operator= (const CLGraphicalObject & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLBase::operator=(rhs);

  //warning: in this place we should call the assignment operator of
  //CDataContainer (which does not exist).
  //We handle this explicitly instead.
  setObjectName(rhs.getObjectName());
  //object flag cannot be accessed, it is private.

  mModelObjectKey = rhs.mModelObjectKey;
  this->mObjectRole = rhs.mObjectRole;
  mBBox = rhs.mBBox;

  return *this;
}

CDataObject * CLGraphicalObject::getModelObject() const
{
  CDataObject* pObject = NULL;

  // as an additional safeguard, we check
  // if the object is in the same datamodel
  // This is not foolproof, but should work in most cases.
  if (this->hasValidModelReference())
    {
      pObject = CRootContainer::getKeyFactory()->get(mModelObjectKey);
    }

  return pObject;
}

void CLGraphicalObject::moveBy(const CLPoint &p)
{
  mBBox.moveBy(p);
}

std::string CLGraphicalObject::getModelObjectName() const
{
  CDataObject * tmp = getModelObject();

  if (tmp)
    return tmp->getObjectName();
  else
    return "";
}

std::string CLGraphicalObject::getModelObjectDisplayName(bool /* regular */, bool /* richtext */) const
{
  CDataObject * tmp = getModelObject();

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
                                     const std::map<const CDataObject*, SBase*> & /* copasimodelmap */,
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

  if (this->mObjectRole.find_first_not_of(" \t\r\n") != std::string::npos)
    {
      RenderGraphicalObjectPlugin* rgoPlugin = (RenderGraphicalObjectPlugin*) sbmlobject->getPlugin("render");

      if (rgoPlugin != NULL)
        rgoPlugin->setObjectRole(this->mObjectRole);
    }
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

#/**
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
  CDataObject* pObj = CRootContainer::getKeyFactory()->get(this->mModelObjectKey);

  if (pObj != NULL)
    {
      // check if the object actually belongs to the same
      // model as the text glyph
      const CDataModel* pDM1 = NULL;
      const CDataModel* pDM2 = NULL;
      const CDataContainer* pParent = pObj->getObjectParent();

      while (pParent != NULL)
        {
          pDM1 = dynamic_cast<const CDataModel*>(pParent);

          if (pDM1 != NULL)
            {
              break;
            }

          pParent = pParent->getObjectParent();
        }

      pParent = this->getObjectParent();

      while (pParent != NULL)
        {
          pDM2 = dynamic_cast<const CDataModel*>(pParent);

          if (pDM2 != NULL)
            {
              break;
            }

          pParent = pParent->getObjectParent();
        }

      //assert(pDM2 != NULL);
      if (pDM1 != NULL && pDM2 == NULL)
        {
          // if we have been able to resolve the model reference, but
          // don't have a datamodel parent, that is good enough
          return true;
        }

      if (pDM1 != NULL && pDM1 == pDM2)
        {
          result = true;
        }
    }

  return result;
}
