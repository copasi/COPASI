// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGraphicalObject.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/13 17:14:30 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CLGO_H_
#define CLGO_H_

#include <string>
#include "report/CCopasiContainer.h"

#include "CLBase.h"

class GraphicalObject;

/**
 * This is the base class for the layout objects in copasi.
 * It is a CCopasiObject. It also has a key (which is used if one
 * layout object refers to another one)
 * It provides the mechanism for refering to a copasi model
 * object by key. This needs to be specialized in the derived
 * classes
 */
class CLGraphicalObject : public CLBase, public CCopasiContainer
  {
  private:

    /**
     *  The key of the layout object itself
     */
    std::string mKey;

    /**
     *  The key of an object of the copasi model. This is not used
     *  in this base class. It is provided as a service for the
     *  derived classes
     */
    std::string mModelObjectKey;

    /**
     * The assignment operator is private and not implemented. Just to
     * make sure it is not used.
     */
    CLGraphicalObject & operator= (const CLGraphicalObject &);

  protected:

    CLBoundingBox mBBox;

  public:

    CLGraphicalObject(const std::string & name = "GraphicalObject",
                      const CCopasiContainer * pParent = NULL);

    CLGraphicalObject(const CLGraphicalObject & src,
                      const CCopasiContainer * pParent = NULL);

    /**
     * constructor from libsbml object
     */
    CLGraphicalObject(const GraphicalObject & sbml,
                      std::map<std::string, std::string> & layoutmap,
                      const CCopasiContainer * pParent = NULL);

    ~CLGraphicalObject();

    /**
     *  Retrieves the key of the layout object
     */
    virtual const std::string & getKey() const
      {return mKey;};

    const CLBoundingBox & boundingBox() const {return mBBox;};
    CLBoundingBox & boundingBox() {return mBBox;};

    const std::string & modelObjectKey() const {return mModelObjectKey;};

    void setModelObjectKey(const std::string & k) {mModelObjectKey = k;};

    CCopasiObject * modelObject() const;

    std::string modelObjectName() const;

    std::string modelObjectDisplayName(bool regular = true, bool richtext = false) const;

    /**
      * insert operator
      */
    friend std::ostream & operator<<(std::ostream &os, const CLGraphicalObject & g);
    void print(std::ostream * ostream) const;
  };

#endif
