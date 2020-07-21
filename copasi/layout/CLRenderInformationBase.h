// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CLRenderInformationBase_H__
#define CLRenderInformationBase_H__

#include <string>

#include "copasi/layout/CLBase.h"
#include "copasi/layout/CLColorDefinition.h"
#include "copasi/layout/CLGradientBase.h"
#include "copasi/layout/CLLinearGradient.h"
#include "copasi/layout/CLRadialGradient.h"
#include "copasi/layout/CLLineEnding.h"

#include "copasi/core/CDataContainer.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class RenderInformationBase;
LIBSBML_CPP_NAMESPACE_END

class CLStyle;
class CLGraphicalObject;

class CLRenderInformationBase: public CLBase, public CDataContainer
{
private:
  // prevent the compiler from generating the assignment operator
  CLRenderInformationBase& operator=(const CLRenderInformationBase& source);

protected:
  // id is inherited from SBase
  std::string mReferenceRenderInformation;
  std::string mBackgroundColor;
  CDataVector<CLColorDefinition> mListOfColorDefinitions;
  CDataVector<CLGradientBase> mListOfGradientDefinitions;
  CDataVector<CLLineEnding> mListOfLineEndings;

  /**
   * key string for the render information.
   */
  std::string mKey;

  /**
   * The name of the render information, which is more informative
   * than the key.
   */
  std::string mName;

public:
  /**
   * Constructor.
   */
  CLRenderInformationBase(const std::string& name, CDataContainer* pParent = NULL);

  /**
   * Copy constructor.
   */
  CLRenderInformationBase(const CLRenderInformationBase& source, CDataContainer* pParent);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLRenderInformationBase(const RenderInformationBase& source,
                          const std::string& name,
                          /*
                          std::map<std::string,std::string>& colorIdToKeyMap,
                          std::map<std::string,std::string>& gradientIdToKeyMap,
                          std::map<std::string,std::string>& lineEndingIdToKeyMap,
                          */
                          CDataContainer* pParent = NULL);

  /**
   * Destructor
   */
  ~CLRenderInformationBase();

  /**
   * Returns the key of the referenced render information object..
   */
  const std::string& getReferenceRenderInformationKey() const;

  /**
   * Sets the key of the referenced render information object.
   */
  void setReferenceRenderInformationKey(const std::string& key);

  /**
   * Returns the number of color definitions.
   */
  size_t getNumColorDefinitions() const;

  /**
   * Returns a pointer to the list of color definitions.
   */
  CDataVector<CLColorDefinition>* getListOfColorDefinitions();

  /**
   * Returns a const pointer to the list of color definitions.
   */
  const CDataVector<CLColorDefinition>* getListOfColorDefinitions() const;

  /**
   * Returns a pointer to the color definition with the given index, or NULL
   *if the index is invalid.
   */
  CLColorDefinition* getColorDefinition(size_t index);

  /**
   * Returns a const pointer to the color definition with the given index, or NULL
   *if the index is invalid.
   */
  const CLColorDefinition* getColorDefinition(size_t index) const;

  /**
   * Creates a new color definition.
   */
  CLColorDefinition* createColorDefinition();

  /**
   * Removes the color definition with the given index.
   */
  void removeColorDefinition(size_t index);

  /**
   * Adds a copy of the given color definition to the end of the list of
   * color definitions.
   */
  void addColorDefinition(const CLColorDefinition* cd);

  /**
   * Returns the number of gradient definitions.
   */
  size_t getNumGradientDefinitions() const;

  /**
   * Returns a pointer to the list of gradient definitions.
   */
  CDataVector<CLGradientBase>* getListOfGradientDefinitions();

  /**
   * Returns a const pointer to the list of gradient definitions.
   */
  const CDataVector<CLGradientBase>* getListOfGradientDefinitions() const;

  /**
   * Returns a pointer to the gradient definition with the given index, or NULL
   *if the index is invalid.
   */
  CLGradientBase* getGradientDefinition(size_t index);

  /**
   * Returns a const pointer to the gradient definition with the given index, or NULL
   *if the index is invalid.
   */
  const CLGradientBase* getGradientDefinition(size_t index) const;

  /**
   * Creates a new linear gradient definition.
   */
  CLLinearGradient* createLinearGradientDefinition();

  /**
   * Creates a new radial gradient definition.
   */
  CLRadialGradient* createRadialGradientDefinition();

  /**
   * Removes the gradient definition with the given index.
   */
  void removeGradientDefinition(size_t index);

  /**
   * Adds a copy of the given gradient definition to the end of the list of
   * gradient definitions.
   */
  void addGradientDefinition(const CLGradientBase* gradient);

  /**
   * Returns the number of line endings.
   */
  size_t getNumLineEndings() const;

  /**
   * Returns a pointer to the list of line endings.
   */
  CDataVector<CLLineEnding>* getListOfLineEndings();

  /**
   * Returns a const pointer to the list of line endings.
   */
  const CDataVector<CLLineEnding>* getListOfLineEndings() const;

  /**
   * Returns a pointer to the line ending with the given index, or NULL
   *if the index is invalid.
   */
  CLLineEnding* getLineEnding(size_t index);

  /**
   * Returns a const pointer to the line ending with the given index, or NULL
   *if the index is invalid.
   */
  const CLLineEnding* getLineEnding(size_t index) const;

  /**
   * Creates a new line ending.
   */
  CLLineEnding* createLineEnding();

  /**
   * Removes the line ending with the given index.
   */
  void removeLineEnding(size_t index);

  /**
   * Adds a copy of the given line ending to the end of the list of line
   *endings.
   */
  void addLineEnding(const CLLineEnding* le);

  /**
   * Returns the background color which is either the id of a color in the
   * list of color definitions, or a color value.
   */
  const std::string& getBackgroundColor() const;

  /**
   * Sets the background color to either the id of a color in the list of
   * color definitions, or a color value.
   */
  void setBackgroundColor(const std::string& bg);

  /**
   * Returns the key of the render infomation object
   */
  const std::string& getKey() const;

  /**
   * Returns the id of the object.
   */
  const std::string& getName() const;

  /**
   * Sets the id of the object.
   */
  void setName(const std::string& name);

  /**
   * Adds the attributes for a graphical primitive 1D object to the passed in.
   * object.
   */
  void addSBMLAttributes(RenderInformationBase* pBase
                         /*
                         ,std::map<std::string,std::string>& colorKeyToIdMap
                         ,std::map<std::string,std::string>& gradientKeyToIdMap
                         ,std::map<std::string,std::string>& lineEndingKeyToIdMap
                         */
                        ) const;

  /**
   * Creates a new style, and adds it to the list of styles (where it is owned)
   *
   * @return the newly created style
   */
  virtual CLStyle * createStyle() = 0;

  /**
   * Returns the style for the graphical object or NULL
   *
   * @param pObject the graphical object
   * @return the style if one is available for the object
   */
  virtual const CLStyle * getStyleForGraphicalObject(const CLGraphicalObject* pObject) const = 0;

  /**
   * @return the number of styles
   */
  virtual size_t getNumStyles() const = 0;

  /**
   * @return the style with the given index, or NULL
   */
  virtual CLStyle * getStyle(size_t index) = 0;

  /**
   * @return the style with the given index, or NULL
   */
  virtual const CLStyle * getStyle(size_t index) const = 0;
};

#endif /* CLRenderInformationBase_H__ */
