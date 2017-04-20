// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef LOLAYOUT_H
#define LOLAYOUT_H

#include "copasi/core/CDataVector.h"
#include "CLayout.h"

#include "copasi/layout/CLGlobalRenderInformation.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class ListOf;
LIBSBML_CPP_NAMESPACE_END

/**
 * this class stores a list of layouts. It should also keep the maps
 * that translate from sbml IDs to COPASI keys
 */
class CListOfLayouts : public CDataVectorN< CLayout >
{
private:
  std::string mKey;

  CDataVector<CLGlobalRenderInformation> mvGlobalRenderInformationObjects;

public:
  CListOfLayouts(const std::string & name = "ListOfLayouts",
                 const CDataContainer* pParent = NULL);

  ~CListOfLayouts();

  const std::string& getKey();

  /**
   * Add a layout to the list.
   * At the moment the map is just ignored. Later it should be stored somewhere
   */
  void addLayout(CLayout * layout, const std::map<std::string, std::string> & m);

  /**
   * This method writes the information of the copasi layout object into the
   * corresponding sbml object.
   * copasimodelmap maps the copasi model objects to libsbml objects.
   * At the moment we don´t assume layout objects are in the copasimodelmap.
   * idSet should contain all sbml IDs that are used in the currently exported
   * model (including the layouts, but not the objects inside the layout).
   */
  void exportToSBML(ListOf * lol, std::map<const CDataObject*, SBase*> & copasimodelmap,
                    const std::map<std::string, const SBase*>& idMap, unsigned int level, unsigned int version) const;

  //*******************

  const CDataVector< CLGlobalRenderInformation > & getListOfGlobalRenderInformationObjects() const
  {return this->mvGlobalRenderInformationObjects;};

  CDataVector< CLGlobalRenderInformation > & getListOfGlobalRenderInformationObjects()
  {return this->mvGlobalRenderInformationObjects;};

  /**
   *  add local render information to layout. The layout takes ownership of the object.
   */
  void addGlobalRenderInformation(CLGlobalRenderInformation* pRenderInfo);

  /**
   *  Returns a pointer to the global render information object with the given index.
   *  If the index is invalid, NULL is returned.
   */
  CLGlobalRenderInformation* getRenderInformation(size_t index);

  /**
   *  Returns a const pointer to the global render information object with the given index.
   *  If the index is invalid, NULL is returned.
   */
  const CLGlobalRenderInformation* getRenderInformation(size_t index) const;
};

#endif
