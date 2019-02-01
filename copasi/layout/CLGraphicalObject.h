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

#ifndef CLGO_H_
#define CLGO_H_

#include <string>
#include "copasi/core/CDataContainer.h"

#include "CLBase.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class GraphicalObject;
LIBSBML_CPP_NAMESPACE_END

/**
 * This is the base class for the layout objects in copasi.
 * It is a CDataObject. It also has a key (which is used if one
 * layout object refers to another one)
 * It provides the mechanism for refering to a copasi model
 * object by key. This needs to be specialized in the derived
 * classes
 */
class CLGraphicalObject : public CLBase, public CDataContainer
{
protected:

  /**
   *  The key of the layout object itself
   */
  std::string mKey;

  /**
   *  The key of an object of the COPASI model. This is not used
   *  in this base class. It is provided as a service for the
   *  derived classes
   */
  std::string mModelObjectKey;

  // attribute to store the object role
  std::string mObjectRole;

  CLBoundingBox mBBox;

  CLGraphicalObject(const CLGraphicalObject & src);

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CLGraphicalObject * pDataObject
   */
  static CLGraphicalObject * fromData(const CData & data, CUndoObjectInterface * pParent);

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

  CLGraphicalObject(const std::string & name = "GraphicalObject",
                    const CDataContainer * pParent = NO_PARENT);

  CLGraphicalObject(const CLGraphicalObject & src,
                    const CDataContainer * pParent);

  /**
   * constructor from libsbml object
   */
  CLGraphicalObject(const GraphicalObject & sbml,
                    std::map<std::string, std::string> & layoutmap,
                    const CDataContainer * pParent = NO_PARENT);

  ~CLGraphicalObject();

  /**
   * The assignment operator does not copy the key.
   */
  CLGraphicalObject & operator= (const CLGraphicalObject & rhs);

  /**
   *  Retrieves the key of the layout object
   */
  virtual const std::string & getKey() const
  {return mKey;};

  virtual CLGraphicalObject* clone() const {return new CLGraphicalObject(*this, NULL);};

  virtual void moveBy(const CLPoint &p);

  const CLBoundingBox & getBoundingBox() const {return mBBox;};
  CLBoundingBox & getBoundingBox() {return mBBox;};
  void setBoundingBox(const CLBoundingBox & bb) {mBBox = bb;};

  const CLPoint & getPosition() const {return mBBox.getPosition();};
  void setPosition(const CLPoint & p) {mBBox.setPosition(p);};

  const C_FLOAT64 & getX() const {return mBBox.getPosition().getX();};
  void setX(const C_FLOAT64 & x) {mBBox.getPosition().setX(x);};

  const C_FLOAT64 & getY() const {return mBBox.getPosition().getY();};
  void setY(const C_FLOAT64 & y) {mBBox.getPosition().setY(y);};

  const CLDimensions & getDimensions() const {return mBBox.getDimensions();};
  void setDimensions(const CLDimensions & d) {mBBox.setDimensions(d);};

  const C_FLOAT64 & getWidth() const {return mBBox.getDimensions().getWidth();};
  void setWidth(const C_FLOAT64 & w) {mBBox.getDimensions().setWidth(w);};

  const C_FLOAT64 & getHeight() const {return mBBox.getDimensions().getHeight();};
  void setHeight(const C_FLOAT64 & h) {mBBox.getDimensions().setHeight(h);};

  const std::string & getModelObjectKey() const {return mModelObjectKey;};

  void setModelObjectKey(const std::string & k) {mModelObjectKey = k;};

  CDataObject * getModelObject() const;

  /**
    * if the graphical object refers to a model object this method will return the
    * name of that object.
    */
  std::string getModelObjectName() const;

  /**
    * if the graphical object refers to a model object this method will return the
    * display name of that object.
    */
  std::string getModelObjectDisplayName(bool regular = true, bool richtext = false) const;

  /**
   * This method writes the information of the copasi layout object into the
   * corresponding sbml object
   */
  virtual void exportToSBML(GraphicalObject * sbmlobject,
                            const std::map<const CDataObject*, SBase*> & copasimodelmap,
                            std::map<std::string, const SBase*>& sbmlIDs) const;

  /**
   * Method to set the role of a graphical object.
   */
  void setObjectRole(const std::string& role);

  /**
   * Method to read the object role of an object.
   */
  const std::string& getObjectRole() const;

  /**
    * insert operator
    */
  friend std::ostream & operator<<(std::ostream &os, const CLGraphicalObject & g);
  void print(std::ostream * ostream) const;

  /**
   * This method is used for the export of several layout elements.
   * Layout elements can reference model elements, but when a referenced model element
   * is deleted, the layout is not infomred about this yet, so we end up with dangling
   * references.
   * If the key belongs to an object in the same datamodel, true is returned, else false is returned.
   */
  bool hasValidModelReference() const;
};

#endif
