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

#ifndef CLLineEnding_H__
#define CLLineEnding_H__

#include <string>

#include "copasi/layout/CLGraphicalPrimitive2D.h"
#include "copasi/layout/CLGroup.h"
#include "copasi/layout/CLBase.h"
#include "copasi/core/CDataContainer.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class LineEnding;
LIBSBML_CPP_NAMESPACE_END

class CLLineEnding : public CLGraphicalPrimitive2D, public CDataContainer
{
private:
  // prevent the compiler from generating the assignment operator
  CLLineEnding& operator=(const CLLineEnding& source);

protected:
  bool mEnableRotationalMapping;
  CLBoundingBox mBoundingBox;
  CLGroup* mpGroup;

  /**
   * key string for the object.
   */
  std::string mKey;

  /**
   * The line ending needs an id in addition to the key.
   * The id corresponds to the id in the SBML render extension and it does not have to
   * be globally unique. As a matter of fact, it is sometimes needed that line ending of
   * different render information have the same id.
   */
  std::string mId;

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CLLineEnding * pDataObject
   */
  static CLLineEnding * fromData(const CData & data, CUndoObjectInterface * pParent);

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
   * Constructor.
   */
  CLLineEnding(CDataContainer* pParent = NULL);

  /**
   * Copy Constructor.
   */
  CLLineEnding(const CLLineEnding& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLLineEnding(const LineEnding& source, CDataContainer* pParent = NULL);

  /**
   * Sets whether rotational mapping is to be done or not.
   */
  void setEnableRotationalMapping(bool enable);

  /**
   * Returns whether rotational mapping is enabled or not.
   */
  bool getIsEnabledRotationalMapping() const;

  /**
   * Sets the bounding box.
   */
  void setBoundingBox(const CLBoundingBox* box);

  /**
   * Returns the bounding box.
   */
  CLBoundingBox* getBoundingBox();

  /**
   * Returns the bounding box.
   */
  const CLBoundingBox* getBoundingBox() const;

  /**
   * Sets the group.
   */
  void setGroup(const CLGroup* group);

  /**
   * Returns the group object.
   */
  const CLGroup* getGroup() const;

  /**
   * Returns the group object.
   */
  CLGroup* getGroup();

  /**
   * Returns the key string for the line ending.
   */
  const std::string& getKey() const;

  /**
   * Converts this object to the corresponding SBML object.
   */
  LineEnding* toSBML(unsigned int level, unsigned int version) const;

  /**
   * Returns the id of the object.
   */
  const std::string& getId() const;

  /**
   * Sets the id of the object.
   */
  void setId(const std::string& id);
};

#endif /* CLLineEnding_H__ */
