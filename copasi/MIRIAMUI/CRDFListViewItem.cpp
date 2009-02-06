// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CRDFListViewItem.cpp,v $
//   $Revision: 1.8.10.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/02/06 15:48:47 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "UI/qtUtilities.h"

#include "CRDFListViewItem.h"
#include "CRDFListView.h"
#include "MIRIAM/CRDFGraph.h"
#include "MIRIAM/CRDFObject.h"
#include "MIRIAM/CRDFLiteral.h"

#define COL_SUBJECT    0
#define COL_PREDICATE  1
#define COL_OBJECT     2

CRDFListViewItem::CRDFListViewItem(CRDFListView * pParent, CRDFListViewItem * pAfter):
    QListViewItem(pParent, pAfter),
    mTriplet()
{
  assert(pParent != NULL);
  setOpen(true);
}

CRDFListViewItem::CRDFListViewItem(CRDFListViewItem * pParent, CRDFListViewItem * pAfter):
    QListViewItem(pParent, pAfter),
    mTriplet()
{
  assert(pParent != NULL);
  setOpen(true);
}

CRDFListViewItem::~CRDFListViewItem()
{}

void CRDFListViewItem::setTriplet(const CRDFTriplet & triplet)
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
