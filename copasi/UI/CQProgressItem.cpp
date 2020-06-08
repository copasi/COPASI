// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "CQProgressItem.h"

#include "copasi/core/CVector.h"
#include "copasi/copasi.h"

#include "copasi/utilities/CProcessReport.h"

/*
 *  Constructs a CQProgressItem as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQProgressItem::CQProgressItem(QWidget* parent, const char* name, Qt::WindowFlags fl)
  : QWidget(parent, fl)
{
  setObjectName(QString::fromUtf8(name));
  setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQProgressItem::~CQProgressItem()
{
  // no need to delete child widgets, Qt does it all for us
  pdelete(mpItem);
}

bool CQProgressItem::initFromProcessReportItem(CProcessReportItem * /* pItem */)
{return false;}

bool CQProgressItem::process()
{return false;}

bool CQProgressItem::reset()
{return false;}
