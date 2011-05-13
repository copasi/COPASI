// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQRDFTreeView.cpp,v $
//   $Revision: 1.4.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/13 21:47:06 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQRDFTreeView.h"
#include "CQRDFTreeViewItem.h"

#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"

#include "MIRIAM/CRDFGraph.h"
#include "MIRIAM/CRDFParser.h"
// #include "MIRIAM/CRDFWriter.h"
#include "MIRIAM/CRDFSubject.h"

// #include "CopasiDataModel/CCopasiDataModel.h"
// #include "report/CKeyFactory.h"
// #include "model/CModel.h"
#include "model/CModelValue.h"
#include "model/CEvent.h"
#include "model/CReaction.h"
#include "function/CFunction.h"
// #include "utilities/CCopasiMessage.h"
#include "copasi/report/CCopasiRootContainer.h"

#define COL_SUBJECT    0
#define COL_PREDICATE  1
#define COL_OBJECT     2

CQRDFTreeView::CQRDFTreeView(QWidget* parent, const char* name) :
    CopasiWidget(parent, name),
    mNode2Item(),
    mpGraph(NULL)
{
  setupUi(this);
}

CQRDFTreeView::~CQRDFTreeView()
{
}

bool CQRDFTreeView::update(ListViews::ObjectType /* objectType */,
                           ListViews::Action /* action */,
                           const std::string & /* key */)
{
  return true;
}

bool CQRDFTreeView::enterProtected()
{
  clear();

  CCopasiObject *pObject = dynamic_cast< CCopasiObject * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (pObject != NULL)
    {
      CModelEntity * pEntity = NULL;
      CEvent * pEvent = NULL;
      CReaction * pReaction = NULL;
      CFunction * pFunction = NULL;
      const std::string * pMiriamAnnotation = NULL;

      if ((pEntity = dynamic_cast< CModelEntity * >(pObject)) != NULL)
        pMiriamAnnotation = &pEntity->getMiriamAnnotation();
      else if ((pEvent = dynamic_cast< CEvent * >(pObject)) != NULL)
        pMiriamAnnotation = &pEvent->getMiriamAnnotation();
      else if ((pReaction = dynamic_cast< CReaction * >(pObject)) != NULL)
        pMiriamAnnotation = &pReaction->getMiriamAnnotation();
      else if ((pFunction = dynamic_cast< CFunction * >(pObject)) != NULL)
        pMiriamAnnotation = &pFunction->getMiriamAnnotation();

      if (pMiriamAnnotation && *pMiriamAnnotation != "")
        mpGraph = CRDFParser::graphFromXml(*pMiriamAnnotation);
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
  mpGraph->createAboutNode(mKey);

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

  mpTreeWidget->setFocus();

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
