// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CRDFListView.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/10 20:31:11 $
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
    QListView(pParent, name, flag),
    mNode2Item()
{
  addColumn("Subject");
  addColumn("Predicate");
  addColumn("Object");
}

CRDFListView::~CRDFListView()
{}

// virtual
void CRDFListView::clear()
{
  mNode2Item.clear();
  QListView::clear();
}

CRDFListViewItem * CRDFListView::find(const CRDFNode * pNode)
{
  std::map< const CRDFNode *, CRDFListViewItem * >::iterator it = mNode2Item.find(pNode);
  if (it != mNode2Item.end())
    return it->second;

  return NULL;
}

void CRDFListView::insert(const CRDFNode * pNode, CRDFListViewItem * pItem)
{
  mNode2Item[pNode] = pItem;
}
