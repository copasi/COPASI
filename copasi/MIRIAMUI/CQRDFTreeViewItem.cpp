// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQRDFTreeViewItem.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/08/13 01:40:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "UI/qtUtilities.h"

#include "CQRDFTreeViewItem.h"
#include "CQRDFTreeView.h"
#include "MIRIAM/CRDFGraph.h"
#include "MIRIAM/CRDFObject.h"
#include "MIRIAM/CRDFLiteral.h"

#define COL_SUBJECT    0
#define COL_PREDICATE  1
#define COL_OBJECT     2

CQRDFTreeViewItem::CQRDFTreeViewItem(QTreeWidget * pParent, CQRDFTreeViewItem * pAfter):
    QTreeWidgetItem(pParent, pAfter),
    mTriplet()
{
  assert(pParent != NULL);
  setExpanded(true);
}

CQRDFTreeViewItem::CQRDFTreeViewItem(CQRDFTreeViewItem * pParent, CQRDFTreeViewItem * pAfter):
    QTreeWidgetItem(pParent, pAfter),
    mTriplet()
{
  assert(pParent != NULL);
  setExpanded(true);
}

CQRDFTreeViewItem::~CQRDFTreeViewItem()
{}

void CQRDFTreeViewItem::setTriplet(const CRDFTriplet & triplet)
{
  mTriplet = triplet;

  // Set the predicate
  setText(COL_PREDICATE, FROM_UTF8(mTriplet.Predicate.getURI()));

  const CRDFObject & Object = mTriplet.pObject->getObject();

  switch (Object.getType())
    {
      case CRDFObject::LITERAL:
      {
        const CRDFLiteral & Literal = Object.getLiteral();

        switch (Literal.getType())
          {
            case CRDFLiteral::PLAIN:
            case CRDFLiteral::TYPED:
              setText(COL_OBJECT, FROM_UTF8(Literal.getLexicalData()));
              break;
          }
      }
      break;

      case CRDFObject::RESOURCE:
        setText(COL_OBJECT, FROM_UTF8(Object.getResource()));
        break;

      case CRDFObject::BLANK_NODE:

        if (mTriplet. Predicate.getURI() != "http://www.w3.org/1999/02/22-rdf-syntax-ns#subject")
          setText(COL_SUBJECT, FROM_UTF8(Object.getBlankNodeID()));
        else
          setText(COL_OBJECT, FROM_UTF8(Object.getBlankNodeID()));

        break;
    }
}
