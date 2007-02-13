// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CListOfLayouts.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/13 17:14:30 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef LOLAYOUT_H
#define LOLAYOUT_H

#include "utilities/CCopasiVector.h"
#include "CLayout.h"

class CListOfLayouts : public CCopasiVector<CLayout>
  {
  private:
    std::string mKey;

  public:
    CListOfLayouts(const std::string & name = "ListOfLayouts",
                   const CCopasiContainer* pParent = &RootContainer);

    ~CListOfLayouts();

    //CReportDefinition* createReportDefinition(const std::string & name, const std::string & comment);
    //bool removeReportDefinition(const std::string & key);

    const std::string& getKey();

    /**
     * Add a layout to the list.
     * At the moment the map is just ignored. Later it should be stored somewhere
     */
    void addLayout(CLayout * layout, const std::map<std::string, std::string> & m);
  };

#endif
