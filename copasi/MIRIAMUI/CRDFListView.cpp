// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CRDFListView.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/24 16:08:50 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CRDFListView.h"

#define COL_SUBJECT    0
#define COL_PREDICATE  1
#define COL_OBJECT     2

CRDFListView::CRDFListView(QWidget * pParent, const char * name, WFlags flag):
    QListView(pParent, name, flag)
{
  addColumn("Subject");
  addColumn("Predicate");
  addColumn("Object");
}

CRDFListView::~CRDFListView()
{}
