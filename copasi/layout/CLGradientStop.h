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

#ifndef CLGradientStop_H__
#define CLGradientStop_H__

#include <string>

#include "copasi/layout/CLBase.h"
#include "copasi/layout/CLRelAbsVector.h"
#include "copasi/core/CDataObject.h"

class CDataContainer;

LIBSBML_CPP_NAMESPACE_BEGIN
class GradientStop;
LIBSBML_CPP_NAMESPACE_END

class CLGradientStop : public CLBase, public CDataObject
{
private:
  // prevent the compiler from generating the assignment operator
  CLGradientStop& operator=(const CLGradientStop& source);

protected:
  CLRelAbsVector mOffset;
  std::string mStopColor;

  /**
   * key string for the gradient stop.
   */
  std::string mKey;

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CLGradientStop * pDataObject
   */
  static CLGradientStop * fromData(const CData & data, CUndoObjectInterface * pParent);

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
  CLGradientStop(CDataContainer* pParent = NULL);

  /**
   * Copy Constructor
   */
  CLGradientStop(const CLGradientStop& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLGradientStop(const GradientStop& source, CDataContainer* pParent = NULL);

  /**
   * Virtual destructor to satify the linker.
   */
  virtual ~CLGradientStop();

  /**
   * Returns the offset.
   */
  const CLRelAbsVector& getOffset() const;

  /**
   * Sets the offset.
   */
  void setOffset(double x, double y);

  /**
   * Sets the offset.
   */
  void setOffset(const std::string&);

  /**
   * Sets the offset.
   */
  void setOffset(const CLRelAbsVector& co);

  /**
   * Returns the stop color id.
   */
  const std::string& getStopColor() const;

  /**
   * Sets the stop color id.
   */
  void setStopColor(const std::string& key);

  /**
   * Returns the key of the color definition.
   */
  const std::string& getKey() const;

  /**
   * Converts this object to the corresponding SBML object.
   */
  GradientStop* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLGradientStop */
