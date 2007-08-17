// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CListOfLayouts.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/17 12:35:28 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CListOfLayouts.h"
#include "report/CKeyFactory.h"

#include "sbml/layout/Layout.h"

CListOfLayouts::CListOfLayouts(const std::string & name,
                               const CCopasiContainer * pParent):
    CCopasiVector<CLayout>(name, pParent),
    mKey(GlobalKeys.add("Layout", this))
{}

CListOfLayouts::~CListOfLayouts()
{
  GlobalKeys.remove(mKey);
}

const std::string& CListOfLayouts::getKey()
{
  return mKey;
}

void CListOfLayouts::addLayout(CLayout * layout, const std::map<std::string, std::string> & m)
{
  if (layout)
    add(layout, true);

  //TODO: store map
}

void CListOfLayouts::exportToSBML(ListOf * lol, std::map<CCopasiObject*, SBase*> & copasimodelmap) const
  {
    unsigned C_INT32 i, imax = this->size();
    for (i = 0; i < imax; ++i)
      {
        CLayout * tmp = (*this)[i];

        //check if the layout exists in the libsbml data
        std::map<CCopasiObject*, SBase*>::const_iterator it;
        it = copasimodelmap.find(tmp);

        Layout * pLayout;
        if (it == copasimodelmap.end()) //not found
          {
            //create new object and add to libsbml data structures
            pLayout = new Layout;
            lol->append(pLayout);

            //add object to map
            copasimodelmap[tmp] = pLayout;
          }
        else
          {
            pLayout = dynamic_cast<Layout*>(it->second);
          }

        tmp->exportToSBML(pLayout, copasimodelmap);
      }

    //check if a something needs to be deleted from the sbml data structures
    //TODO
  }
