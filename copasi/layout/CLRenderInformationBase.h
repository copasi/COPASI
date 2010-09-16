// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLRenderInformationBase.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/09/16 18:28:06 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLRenderInformationBase_H__
#define CLRenderInformationBase_H__

#include <string>

#include <copasi/layout/CLBase.h>
#include <copasi/layout/CLColorDefinition.h>
#include <copasi/layout/CLGradientBase.h>
#include <copasi/layout/CLLinearGradient.h>
#include <copasi/layout/CLRadialGradient.h>
#include <copasi/layout/CLLineEnding.h>

#include <copasi/report/CCopasiContainer.h>

class RenderInformationBase;

class CLRenderInformationBase: public CLBase, public CCopasiContainer
{
private:
  // prevent the compiler from generating the assignment operator
  CLRenderInformationBase& operator=(const CLRenderInformationBase& source);

protected:
  // id is inherited from SBase
  std::string mReferenceRenderInformation;
  std::string mBackgroundColor;
  CCopasiVector<CLColorDefinition> mListOfColorDefinitions;
  CCopasiVector<CLGradientBase> mListOfGradientDefinitions;
  CCopasiVector<CLLineEnding> mListOfLineEndings;

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
  CLRenderInformationBase(const std::string& name, CCopasiContainer* pParent = NULL);

  /**
   * Copy constructor.
   */
  CLRenderInformationBase(const CLRenderInformationBase& source, CCopasiContainer* pParent);

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
                          CCopasiContainer* pParent = NULL);

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
  unsigned int getNumColorDefinitions() const;

  /**
   * Returns a pointer to the list of color definitions.
   */
  CCopasiVector<CLColorDefinition>* getListOfColorDefinitions();

  /**
   * Returns a const pointer to the list of color definitions.
   */
  const CCopasiVector<CLColorDefinition>* getListOfColorDefinitions() const;

  /**
   * Returns a pointer to the color definition with the given index, or NULL
   *if the index is invalid.
   */
  CLColorDefinition* getColorDefinition(unsigned int index);

  /**
   * Returns a const pointer to the color definition with the given index, or NULL
   *if the index is invalid.
   */
  const CLColorDefinition* getColorDefinition(unsigned int index) const;

  /**
   * Creates a new color definition.
   */
  CLColorDefinition* createColorDefinition();

  /**
   * Removes the color definition with the given index.
   */
  void removeColorDefinition(unsigned int index);

  /**
   * Adds a copy of the given color definition to the end of the list of
   * color definitions.
   */
  void addColorDefinition(const CLColorDefinition* cd);

  /**
   * Returns the number of gradient definitions.
   */
  unsigned int getNumGradientDefinitions() const;

  /**
   * Returns a pointer to the list of gradient definitions.
   */
  CCopasiVector<CLGradientBase>* getListOfGradientDefinitions();

  /**
   * Returns a const pointer to the list of gradient definitions.
   */
  const CCopasiVector<CLGradientBase>* getListOfGradientDefinitions() const;

  /**
   * Returns a pointer to the gradient definition with the given index, or NULL
   *if the index is invalid.
   */
  CLGradientBase* getGradientDefinition(unsigned int index);

  /**
   * Returns a const pointer to the gradient definition with the given index, or NULL
   *if the index is invalid.
   */
  const CLGradientBase* getGradientDefinition(unsigned int index) const;

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
  void removeGradientDefinition(unsigned int index);

  /**
   * Adds a copy of the given gradient definition to the end of the list of
   * gradient definitions.
   */
  void addGradientDefinition(const CLGradientBase* gradient);

  /**
   * Returns the number of line endings.
   */
  unsigned int getNumLineEndings() const;

  /**
   * Returns a pointer to the list of line endings.
   */
  CCopasiVector<CLLineEnding>* getListOfLineEndings();

  /**
   * Returns a const pointer to the list of line endings.
   */
  const CCopasiVector<CLLineEnding>* getListOfLineEndings() const;

  /**
   * Returns a pointer to the line ending with the given index, or NULL
   *if the index is invalid.
   */
  CLLineEnding* getLineEnding(unsigned int index);

  /**
   * Returns a const pointer to the line ending with the given index, or NULL
   *if the index is invalid.
   */
  const CLLineEnding* getLineEnding(unsigned int index) const;

  /**
   * Creates a new line ending.
   */
  CLLineEnding* createLineEnding();

  /**
   * Removes the line ending with the given index.
   */
  void removeLineEnding(unsigned int index);

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
};

#endif /* CLRenderInformationBase_H__ */
