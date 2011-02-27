// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CListOfLayouts.h,v $
//   $Revision: 1.8.2.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/02/27 17:49:57 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef LOLAYOUT_H
#define LOLAYOUT_H

#include "utilities/CCopasiVector.h"
#include "CLayout.h"

#ifdef USE_CRENDER_EXTENSION
#include <copasi/layout/CLGlobalRenderInformation.h>
#endif /* USE_CRENDER_EXTENSION */

class ListOf;

/**
 * this class stores a list of layouts. It should also keep the maps
 * that translate from sbml IDs to copas keys
 */
class CListOfLayouts : public CCopasiVector<CLayout>
{
private:
  std::string mKey;

#ifdef USE_CRENDER_EXTENSION
  CCopasiVector<CLGlobalRenderInformation> mvGlobalRenderInformationObjects;
#endif /* USE_CRENDER_EXTENSION */

public:
  CListOfLayouts(const std::string & name = "ListOfLayouts",
                 const CCopasiContainer* pParent = NULL);

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
  void exportToSBML(ListOf * lol, std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                    const std::map<std::string, const SBase*>& idMap) const;

#ifdef USE_CRENDER_EXTENSION
  //*******************

  const CCopasiVector<CLGlobalRenderInformation> & getListOfGlobalRenderInformationObjects() const
  {return this->mvGlobalRenderInformationObjects;};

  CCopasiVector<CLGlobalRenderInformation> & getListOfGlobalRenderInformationObjects()
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

#endif /* USE_CRENDER_EXTENSION */
};

#endif
