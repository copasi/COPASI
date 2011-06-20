// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQDateTimeEditTableItem.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/20 16:07:08 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQDateTimeEditTableItem.h"

CQDateTimeEditTableItem::CQDateTimeEditTableItem(CopasiTableWidget* table, int row, int col, QWidget * parent, const char * name)
    : QDateTimeEdit(parent)
{
  setObjectName(QString::fromUtf8(name));
  mpTable = table;
  mRow = row;
  mCol = col;
  //setDateTime(QDateTime::fromString("2000-01-01T00:00:00", Qt::ISODate));

  init();
}

CQDateTimeEditTableItem::CQDateTimeEditTableItem(CopasiTableWidget* table, int row, int col, const QDateTime & datetime, QWidget * parent, const char * name)
    : QDateTimeEdit(datetime, parent)
{
  setObjectName(QString::fromUtf8(name));
  mpTable = table;
  mRow = row;
  mCol = col;

  init();
}

void CQDateTimeEditTableItem::init()
{
  connect(this, SIGNAL(valueChanged(const QDateTime &)),
          this, SLOT(slotValueChanged(const QDateTime &)));
  connect(this, SIGNAL(valueChanged(int, int)),
          mpTable, SLOT(slotValueChanged(int, int)));
}

void CQDateTimeEditTableItem::slotValueChanged(const QDateTime& dateTime)
{
  std::string date = "";

  if (dateTime.date().toString("yyyy-MM-dd").ascii())
    {date = dateTime.date().toString("yyyy-MM-dd").ascii();}

  if (date != "")
    {emit valueChanged(mRow, mCol);}
}

CQDateTimeEditTableItem::~CQDateTimeEditTableItem(void)
{}
