// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/14 11:09:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQProgressItem.h"

//#include <qvariant.h>
//#include "CQProgressItem.ui.h"
/*
 *  Constructs a CQProgressItem as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQProgressItem::CQProgressItem(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQProgressItem::~CQProgressItem()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQProgressItem::languageChange()
{
  retranslateUi(this);
}

bool CQProgressItem::initFromProcessReportItem(CProcessReportItem * /* pItem */)
{return false;}

bool CQProgressItem::process()
{return false;}

bool CQProgressItem::reset()
{return false;}
