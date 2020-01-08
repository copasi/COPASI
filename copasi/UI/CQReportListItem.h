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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CQReportListItem
#define COPASI_CQReportListItem

#include <QTableWidgetItem>
#include "copasi/core/CRegisteredCommonName.h"

class CDataObject;
class CDataModel;

class CQReportListItem : public QTableWidgetItem
{
  // Operations
public:
  CQReportListItem(const std::string & cn, CDataModel * pDataModel);

  CQReportListItem(const CDataObject * pObject);

  ~CQReportListItem();

  const CCommonName & getCN() const;

  void setObject(const CDataObject* pObject);

  void refreshText(CDataModel * pDataModel);

  // Attributes
private:
  CRegisteredCommonName mCN;
};

#endif // COPASI_CQReportListItem
