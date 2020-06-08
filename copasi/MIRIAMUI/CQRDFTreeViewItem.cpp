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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQRDFTreeViewItem.h"
#include "CQRDFTreeView.h"

#include "copasi/copasi.h"

#include "copasi/UI/qtUtilities.h"

#include "copasi/MIRIAM/CRDFGraph.h"
#include "copasi/MIRIAM/CRDFObject.h"
#include "copasi/MIRIAM/CRDFLiteral.h"

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
