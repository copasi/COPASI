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

#include "CQRDFTreeView.h"
#include "CQRDFTreeViewItem.h"

#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/qtUtilities.h"

#include "copasi/MIRIAM/CRDFGraph.h"
#include "copasi/MIRIAM/CRDFParser.h"
#include "copasi/MIRIAM/CRDFSubject.h"

#include "copasi/model/CModelValue.h"
#include "copasi/model/CEvent.h"
#include "copasi/model/CReaction.h"
#include "copasi/function/CFunction.h"
#include "copasi/core/CRootContainer.h"

#define COL_SUBJECT    0
#define COL_PREDICATE  1
#define COL_OBJECT     2

CQRDFTreeView::CQRDFTreeView(QWidget* parent, const char* name) :
  CopasiWidget(parent, name),
  mNode2Item(),
  mpGraph(NULL),
  mpAnnotation(NULL)
{
  setupUi(this);
}

CQRDFTreeView::~CQRDFTreeView()
{
  clear();
}

bool CQRDFTreeView::updateProtected(ListViews::ObjectType /* objectType */,
                                    ListViews::Action /* action */,
                                    const CCommonName & cn)
{
  // Assure that the pointer is still valid;
  mpAnnotation = CAnnotation::castObject(mpObject);

  if (mIgnoreUpdates || !isVisible())
    {
      return true;
    }

  if (cn == mObjectCN)
    {
      return enterProtected();
    }

  return true;
}

bool CQRDFTreeView::enterProtected()
{
  clear();

  mpAnnotation = CAnnotation::castObject(mpObject);

  if (mpAnnotation == NULL) return false;

  if (!mpAnnotation->getMiriamAnnotation().empty())
    {
      mpGraph = CRDFParser::graphFromXml(mpAnnotation->getMiriamAnnotation());
    }

  CCopasiMessage::clearDeque();

  if (CCopasiMessage::size() != 0)
    {
      QString Message = FROM_UTF8(CCopasiMessage::getAllMessageText());
      CQMessageBox::warning(this, QString("RDF Warning"), Message,
                            QMessageBox::Ok, QMessageBox::Ok);
    }

  if (mpGraph == NULL)
    mpGraph = new CRDFGraph;

  // We make sure that we always have an about node.
  mpGraph->createAboutNode(mpObject->getKey());

  // We iterate of all triplets
  std::set< CRDFTriplet >::const_iterator it = mpGraph->getTriplets().begin();
  std::set< CRDFTriplet >::const_iterator end = mpGraph->getTriplets().end();

  for (; it != end; ++it)
    {
      CQRDFTreeViewItem * pSubjectItem = find(it->pSubject);

      if (pSubjectItem == NULL)
        {
          pSubjectItem = new CQRDFTreeViewItem(mpTreeWidget, NULL);
          insert(it->pSubject, pSubjectItem);
          // Display the subject information

          const CRDFSubject & Subject = it->pSubject->getSubject();

          switch (Subject.getType())
            {
              case CRDFSubject::RESOURCE:
                pSubjectItem->setText(COL_SUBJECT, FROM_UTF8(Subject.getResource()));
                break;

              case CRDFSubject::BLANK_NODE:
                pSubjectItem->setText(COL_SUBJECT, FROM_UTF8(Subject.getBlankNodeID()));
                break;
            }
        }

      CQRDFTreeViewItem * pObjectItem = NULL;

      if (it->Predicate.getURI() == "http://www.w3.org/1999/02/22-rdf-syntax-ns#subject")
        {
          pObjectItem = new CQRDFTreeViewItem(pSubjectItem, NULL);
          insert(it->pObject, pObjectItem);
        }
      else
        pObjectItem = find(it->pObject);

      if (pObjectItem == NULL)
        {
          pObjectItem = new CQRDFTreeViewItem(pSubjectItem, NULL);
          insert(it->pObject, pObjectItem);
        }
      else
        {
          QTreeWidgetItem * pParent = pObjectItem->parent();

          if (pParent == NULL)
            {
              mpTreeWidget->invisibleRootItem()->removeChild(pObjectItem);
              pSubjectItem->addChild(pObjectItem);
            }
          else
            {
              pParent->removeChild(pObjectItem);
              pSubjectItem->addChild(pObjectItem);
            }
        }

      pObjectItem->setTriplet(*it);
    }

  //mpTreeWidget->setFocus();

  return true;
}

void CQRDFTreeView::clear()
{
  mNode2Item.clear();
  pdelete(mpGraph);
  mpTreeWidget->clear();
}

CQRDFTreeViewItem * CQRDFTreeView::find(const CRDFNode * pNode)
{
  std::map< const CRDFNode *, CQRDFTreeViewItem * >::iterator it = mNode2Item.find(pNode);

  if (it != mNode2Item.end())
    return it->second;

  return NULL;
}

void CQRDFTreeView::insert(const CRDFNode * pNode, CQRDFTreeViewItem * pItem)
{
  mNode2Item[pNode] = pItem;
}
