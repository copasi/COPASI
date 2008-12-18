/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportListItem.h,v $
 $Revision: 1.3 $
 $Name:  $
 $Author: shoops $
 $Date: 2008/12/18 19:57:10 $
 End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CQReportListItem
#define COPASI_CQReportListItem

#include <q3listbox.h>
#include "report/CCopasiObjectName.h"

class CCopasiObject;

class CQReportListItem : public Q3ListBoxText
  {
    // Operations
  public:
    CQReportListItem(Q3ListBox * listbox,
                     const std::string & cn);

    CQReportListItem(Q3ListBox * listbox,
                     const CCopasiObject * pObject);

    ~CQReportListItem();

    void setText(const QString & text);

    const CCopasiObjectName & getCN() const;

    void refreshText();

    // Attributes
  private:
    CRegisteredObjectName mCN;
  };

#endif // COPASI_CQReportListItem
