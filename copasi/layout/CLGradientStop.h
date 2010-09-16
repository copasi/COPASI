// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGradientStop.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/09/16 18:28:05 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLGradientStop_H__
#define CLGradientStop_H__

#include <string>

#include <copasi/layout/CLBase.h>
#include <copasi/layout/CLRelAbsVector.h>
#include <copasi/report/CCopasiObject.h>

class CCopasiContainer;
class GradientStop;

class CLGradientStop : public CLBase, public CCopasiObject
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
   * Constructor.
   */
  CLGradientStop(CCopasiContainer* pParent = NULL);

  /**
   * Copy Constructor
   */
  CLGradientStop(const CLGradientStop& source, CCopasiContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLGradientStop(const GradientStop& source, CCopasiContainer* pParent = NULL);

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
