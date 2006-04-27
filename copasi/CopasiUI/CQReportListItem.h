/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQReportListItem.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:42 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CQReportListItem
#define COPASI_CQReportListItem

#include <qlistbox.h>
#include "report/CCopasiObjectName.h"

class CCopasiObject;

class CQReportListItem : public QListBoxText
  {
    // Operations
  public:
    CQReportListItem(QListBox * listbox,
                     const std::string & cn);

    CQReportListItem(QListBox * listbox,
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
