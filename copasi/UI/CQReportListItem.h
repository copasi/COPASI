/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportListItem.h,v $
 $Revision: 1.4 $
 $Name:  $
 $Author: shoops $
 $Date: 2011/10/17 14:58:06 $
 End CVS Header */

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CQReportListItem
#define COPASI_CQReportListItem

#include <QtGui/QListWidgetItem>
#include "report/CCopasiObjectName.h"

class CCopasiObject;

class CQReportListItem : public QListWidgetItem
{
  // Operations
public:
  CQReportListItem(const std::string & cn);

  CQReportListItem(const CCopasiObject * pObject);

  ~CQReportListItem();

  const CCopasiObjectName & getCN() const;

  void refreshText();

  // Attributes
private:
  CRegisteredObjectName mCN;
};

#endif // COPASI_CQReportListItem
