// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CQReportListItem
#define COPASI_CQReportListItem

#include <QtGui/QListWidgetItem>
#include "report/CCopasiObjectName.h"

class CCopasiObject;
class CCopasiDataModel;

class CQReportListItem : public QListWidgetItem
{
  // Operations
public:
  CQReportListItem(const std::string & cn, CCopasiDataModel * pDataModel);

  CQReportListItem(const CCopasiObject * pObject);

  ~CQReportListItem();

  const CCopasiObjectName & getCN() const;

  void setObject(const CCopasiObject* pObject);

  void refreshText(CCopasiDataModel * pDataModel);

  // Attributes
private:
  CRegisteredObjectName mCN;
};

#endif // COPASI_CQReportListItem
