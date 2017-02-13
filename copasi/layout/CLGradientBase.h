// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLGradientBase_H__
#define CLGradientBase_H__

#include <string>

#include "copasi/layout/CLBase.h"
#include "copasi/report/CCopasiContainer.h"
#include "copasi/layout/CLGradientStop.h"
#include "copasi/utilities/CCopasiVector.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class GradientBase;
LIBSBML_CPP_NAMESPACE_END

class CLGradientBase : public CLBase, public CCopasiContainer
{
public:
  enum SPREADMETHOD
  {
    PAD,
    REFLECT,
    REPEAT
  };

private:
  // prevent the compiler from generating the assignment operator
  CLGradientBase& operator=(const CLGradientBase& source);

protected:
  SPREADMETHOD mSpreadMethod;
  CCopasiVector<CLGradientStop> mGradientStops;

  /**
   * key string for the gradient.
   */
  std::string mKey;

  /**
   * The gradient base needs an id in addition to the key.
   * The id corresponds to the id in the SBML render extension and it does not have to
   * be globally unique. As a matter of fact, it is sometimes needed that gradient base of
   * different render information have the same id.
   */
  std::string mId;

public:
  static CLGradientBase * fromData(const CData & data);

  /**
   * Constructor.
   */
  CLGradientBase(const std::string& name, CCopasiContainer* pParent = NULL);

  /**
   * Copy Constructor.
   */
  CLGradientBase(const CLGradientBase& source, CCopasiContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLGradientBase(const GradientBase& source, const std::string& name, CCopasiContainer* pParent = NULL);

  /**
   * Destructor.
   */
  virtual ~CLGradientBase();

  /**
   * Returns the spreadmethod of the gradient.
   */
  SPREADMETHOD getSpreadMethod() const;

  /**
   * Sets the spread method.
   */
  void setSpreadMethod(SPREADMETHOD method);

  /**
   * Returns the number of gradient stops.
   */
  size_t getNumGradientStops() const;

  /**
   * Returns a pointer to the gradient stop vector.
   */
  CCopasiVector<CLGradientStop>* getListOfGradientStops();

  /**
   * Returns a const pointer to the gradient stop vector.
   */
  const CCopasiVector<CLGradientStop>* getListOfGradientStops() const;

  /**
   * Returns a pointer to the gradient stop with the given index or NULL
   * if the index is invalid.
   */
  CLGradientStop* getGradientStop(size_t i);

  /**
   * Returns a const pointer to the gradient stop with the given index or NULL
   * if the index is invalid.
   */
  const CLGradientStop* getGradientStop(size_t i) const;

  /**
   * Creates a new GradientStop.
   */
  CLGradientStop* createGradientStop();

  /**
   * Adds a copy of the given GradientStop object.
   */
  void addGradientStop(const CLGradientStop* pStop);

  /**
   * Returns the key of the color definition.
   */
  const std::string& getKey() const;

  /**
   * Adds gradient base attributes to the gradient passed as the argument.
   */
  virtual void addSBMLAttributes(GradientBase* pBase) const;

  /**
   * Returns the id of the object.
   */
  const std::string& getId() const;

  /**
   * Sets the id of the object.
   */
  void setId(const std::string& id);
};

#endif /* CLGradientBase_H__ */
