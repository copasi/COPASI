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

#ifndef CLRenderResolver_H__
#define CLRenderResolver_H__

#include <map>
#include <string>

#include "copasi/layout/CLGlobalRenderInformation.h"
#include "copasi/layout/CLLocalRenderInformation.h"

class CLRenderInformationBase;
class CLStyle;
class CLColorDefinition;
class CLLineEnding;
class CLGradientBase;
class CLGraphicalObject;
class CLColorDefinition;
class CLMetabReferenceGlyph;

/**
 * Display list could be used to cache the styles.
 * For styles with only relative coordinates, a display list for a unit box can
 * be created. The display list only has to be scaled and translated.
 * For styles with only absolute coordinates, a display list can be created,
 * this display list may only be translated, but not scaled later on.
 * Styles that use relative and absolute coordinates are more difficult. Here
 * the bounding box has to be known in order to draw the elements.
 * We could still create one display list per use of the style if that would to
 * create to many display lists. Another optimization option for this would be to
 * collect all usages of the style where the boundinng box has the same size into one.
 * Display lists for line endings could also be useful, the same restriction as
 * for styles apply here.
 */

class CLRenderResolver
{
protected:
  /**
   * The render information object.
   * which is created by the flattener.
   */
  CLRenderInformationBase* mpRenderInformation;

  /**
   * Flag that determines if the resolver is for a local or a global
   * render information object.
   * Currently it is not used at all.
   */
  bool mLocal;

  // we create some maps to have faster access to elements

  /**
   * Map to store references to styles based on ids.
   */
  std::map<std::string, const CLStyle*> mKeyMap;

  /**
   * Map to store references to styles based on roles.
   */
  std::map<std::string, const CLStyle*> mRoleMap;

  /**
   * Map to store references to styles based on types.
   */
  std::map<std::string, const CLStyle*> mTypeMap;

  /**
   * Map to store references to colord definitions based on id.
   */
  std::map<std::string, const CLColorDefinition*> mColorMap;

  /**
   * Map to store references to colord definitions based on id.
   */
  std::map<std::string, const CLGradientBase*> mGradientMap;

  /**
   * Map to store references to color definitions based on id.
   */
  std::map<std::string, const CLLineEnding*> mLineEndingMap;

  CLColorDefinition* mpBackgroundColor;

  /**
   * Map to store object roles that were deduced by the renderer
   * and are used to suplement the layout information in case a default
   * stylesheet is used.
   */
  std::map<const CLMetabReferenceGlyph*, std::string> mDeducedObjectRoles;

private:
  // declare the copy constructor and the assignment operator private
  // so that they can't be called and that they won't be created by the
  // compiler.
  CLRenderResolver(const CLRenderResolver& /*src*/) {}
  CLRenderResolver& operator=(const CLRenderResolver& /*src*/) {return *this;};

public:
  /**
   * Constructor that takes a local render information object as the argument
   * as well as a list of local and a list of global render information objects
   * that are needed to resolve external references.
   */
  CLRenderResolver(const CLLocalRenderInformation& renderInformation,
                   const CDataVector<CLLocalRenderInformation>& localList,
                   const CDataVector<CLGlobalRenderInformation>& globalList);

  /**
   * Constructor that takes a global render information object as the argument
   * and a list of additional global render information objects that might be
   * needed to resolve external references.
   * means it should contain all information from referenced render information objects.
   */
  CLRenderResolver(const CLGlobalRenderInformation& renderInformation,
                   const CDataVector<CLGlobalRenderInformation>& globalList);

  /**
   * Destructor.
   */
  ~CLRenderResolver();

  /**
   * Method that tries to find the style for the given graphical
   * object that fits best.
   * If no style is found NULL is returned.
   */
  const CLStyle* resolveStyle(const CLGraphicalObject* pObject) const;

  /**
   * Method that tries to find the style for the given role.
   * If no style is found NULL is returned.
   */
  const CLStyle* resolveStyleForRole(const std::string& role) const;

  /**
   * Method that tries to find the style for the given type.
   * If no style is found NULL is returned.
   */
  const CLStyle* resolveStyleForType(const std::string& type) const;

  /**
   * Method that tries to find the style for the given key.
   * If no style is found NULL is returned.
   */
  const CLStyle* resolveStyleForKey(const std::string& key) const;

  /**
   * Returns the gradient definition for a given id.
   */
  const CLGradientBase* getGradientBase(const std::string& id) const;

  /**
   * Returns the color definition for a given id.
   */
  const CLColorDefinition* getColorDefinition(const std::string& id) const;

  /**
   * Returns the line ending for a given id.
   */
  const CLLineEnding* getLineEnding(const std::string& id) const;

  /**
   * Returns the background color.
   */
  const CLColorDefinition* getBackgroundColor() const;

  /**
   * Sets the deduced object roles.
   */
  void  setDeducedObjectRoles(const std::map<const CLMetabReferenceGlyph*, std::string>& deducedObjectRoles);


  /**
   * Removes the specified key, from the list of styles
   */
  void removeKeyFromMap(const std::string & key);

  /**
   * Adds the specified key to the list of styles
   */
  void addKeyToMap(const std::string & key, const CLStyle * pStyle);

  /**
   * Retrieve the COPASI Data Model
   * @return CDataModel * pObjectDataModel
   */
  CDataModel * getObjectDataModel() const;

protected:
  /**
   * This method fills the color, gradient and line ending maps for a render
   * information object.
   */
  void fill_base_maps(const CLRenderInformationBase* pRenderInformation);

  /**
   * This method fills the type and role maps for a global render information
   * object.
   */
  void fill_global_maps(const CLGlobalRenderInformation* pRenderInformation);

  /**
   * This method fills the type, role and id maps for a local render information
   * object.
   */
  void fill_local_maps(const CLLocalRenderInformation* pRenderInformation);

  /**
   * Sets the background color from the given render information.
   */
  void setBackgroundColor();
};

#endif // CLRenderResolver_H__
