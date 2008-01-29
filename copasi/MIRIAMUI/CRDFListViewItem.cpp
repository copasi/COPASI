// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CRDFListViewItem.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/29 20:16:42 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "UI/qtUtilities.h"

#include "CRDFListViewItem.h"
#include "CRDFListView.h"
#include "MIRIAM/CRDFNode.h"
#include "MIRIAM/CRDFSubject.h"
#include "MIRIAM/CRDFObject.h"
#include "MIRIAM/CRDFEdge.h"
#include "MIRIAM/CRDFLiteral.h"

#define COL_SUBJECT    0
#define COL_PREDICATE  1
#define COL_OBJECT     2

CRDFListViewItem::CRDFListViewItem(CRDFListView * pParent, CRDFListViewItem * pAfter):
    QListViewItem(pParent, pAfter),
    mpNode(NULL),
    mpEdge(NULL)
{
  assert(pParent != NULL);
  setOpen(true);
}

CRDFListViewItem::CRDFListViewItem(CRDFListViewItem * pParent, CRDFListViewItem * pAfter):
    QListViewItem(pParent, pAfter),
    mpNode(NULL),
    mpEdge(NULL)
{
  assert(pParent != NULL);
  setOpen(true);
}

CRDFListViewItem::~CRDFListViewItem()
{}

void CRDFListViewItem::setNode(const CRDFNode * pNode)
{
  mpNode = const_cast< CRDFNode * >(pNode);

  if (mpNode->isSubjectNode())
    {
      const CRDFSubject & Subject = mpNode->getSubject();
      switch (Subject.getType())
        {
        case CRDFSubject::RESOURCE:
          setText(COL_SUBJECT, FROM_UTF8(Subject.getResource()));
          break;

        case CRDFSubject::BLANK_NODE:
          setText(COL_SUBJECT, FROM_UTF8(Subject.getBlankNodeID()));
          break;
        }
    }

  // TODO We need to iterate over the edges and insert each predicate
  std::vector< CRDFEdge >::const_iterator it = pNode->getEdges().begin();
  std::vector< CRDFEdge >::const_iterator end = pNode->getEdges().end();

  for (; it != end; ++it)
    {
      CRDFListViewItem * pItem = new CRDFListViewItem(this, NULL);
      pItem->setText(COL_PREDICATE, FROM_UTF8(it->getPredicate()));

      const CRDFObject & Object = it->getPropertyNode()->getObject();
      switch (Object.getType())
        {
        case CRDFObject::LITERAL:
          {
            const CRDFLiteral & Literal = Object.getLiteral();
            switch (Literal.getType())
              {
              case CRDFLiteral::PLAIN:
              case CRDFLiteral::TYPED:
                pItem->setText(COL_OBJECT, FROM_UTF8(Literal.getLexicalData()));
                break;
              }
          }
          break;

        case CRDFObject::RESOURCE:
          pItem->setText(COL_OBJECT, FROM_UTF8(Object.getResource()));
        case CRDFObject::BLANK_NODE:
          if (!static_cast< CRDFListView * >(listView())->visited(it->getPropertyNode()))
            pItem->setNode(it->getPropertyNode());
          else
            pItem->setText(COL_OBJECT, pItem->text(COL_OBJECT) + " (recursive)");
          break;
        }
    }
}
