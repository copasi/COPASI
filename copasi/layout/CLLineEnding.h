// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi/report/CCopasiContainer.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class LineEnding;
LIBSBML_CPP_NAMESPACE_END

class CLLineEnding : public CLGraphicalPrimitive2D, public CCopasiContainer
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
  static CLLineEnding * create(const CData & data);

  /**
   * Constructor.
   */
  CLLineEnding(CCopasiContainer* pParent = NULL);

  /**
   * Copy Constructor.
   */
  CLLineEnding(const CLLineEnding& source, CCopasiContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLLineEnding(const LineEnding& source, CCopasiContainer* pParent = NULL);

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
