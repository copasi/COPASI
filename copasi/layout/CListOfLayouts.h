// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CListOfLayouts.h,v $
//   $Revision: 1.5.16.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/13 09:48:14 $
// End CVS Header

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

class ListOf;

/**
 * this class stores a list of layouts. It should also keep the maps
 * that translate from sbml IDs to copas keys
 */
class CListOfLayouts : public CCopasiVector<CLayout>
  {
  private:
    std::string mKey;

  public:
    CListOfLayouts(const std::string & name = "ListOfLayouts",
                   const CCopasiContainer* pParent = &RootContainer);

    ~CListOfLayouts();

    const std::string& getKey();

    /**
     * Add a layout to the list.
     * At the moment the map is just ignored. Later it should be stored somewhere
     */
    void addLayout(CLayout * layout, const std::map<std::string, std::string> & m);

    /**
     * This method writes the information of the copasi layout object into the
     * corresponding sbml object
     * copasimodelmap maps the copasi objects to libsbml objects in case the
     * model was imported from an sbml file. This is not used extensively for
     * the layout export
     * idSet should contain all sbml IDs that are used in the currently exported
     * model (not including the layout part of the sbml file).
     */
    void exportToSBML(ListOf * lol, std::map<CCopasiObject*, SBase*> & copasimodelmap,
                      const std::map<std::string, const SBase*>& idMap) const;
  };

#endif
