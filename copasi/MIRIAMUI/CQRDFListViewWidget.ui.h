// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CQRDFListViewWidget.ui.h,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Creator: aekamal $
//   $Date: 2008/06/05 15:34:09 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CRDFListViewItem.h"

#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"

#include "MIRIAM/CRDFGraph.h"
#include "MIRIAM/CRDFNode.h"
#include "MIRIAM/CRDFParser.h"
#include "MIRIAM/CRDFWriter.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "model/CModel.h"
#include "model/CModelValue.h"
#include "utilities/CCopasiMessage.h"

#include "MIRIAM/CModelMIRIAMInfo.h"

void CQRDFListViewWidget::init()
{}

bool CQRDFListViewWidget::enter(const std::string & key)
{
  mKey = key;
  load();

  return true;
}

bool CQRDFListViewWidget::leave()
{
  save();

  return true;
}

void CQRDFListViewWidget::load()
{
  mpListView->clear();
  mpListView->clearVisitedNodes();

  CRDFGraph * pGraph = NULL;

  CCopasiObject *pObject = dynamic_cast< CCopasiObject * >(GlobalKeys.get(mKey));

  if (pObject != NULL)
    {
      CModelEntity * pEntity = NULL;
      CReaction * pReaction = NULL;
      CFunction * pFunction = NULL;
      const std::string * pMiriamAnnotation = NULL;

      if ((pEntity = dynamic_cast< CModelEntity * >(pObject)) != NULL)
        pMiriamAnnotation = &pEntity->getMiriamAnnotation();
      else if ((pReaction = dynamic_cast< CReaction * >(pObject)) != NULL)
        pMiriamAnnotation = &pReaction->getMiriamAnnotation();
      else if ((pFunction = dynamic_cast< CFunction * >(pObject)) != NULL)
        pMiriamAnnotation = &pFunction->getMiriamAnnotation();

      if (pMiriamAnnotation && *pMiriamAnnotation != "")
        pGraph = CRDFParser::graphFromXml(*pMiriamAnnotation);
    }

  CCopasiMessage::clearDeque();

  if (CCopasiMessage::size() != 0)
    {
      QString Message = FROM_UTF8(CCopasiMessage::getAllMessageText());
      CQMessageBox::warning(this, QString("RDF Warning"), Message,
                            QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
    }

  if (pGraph == NULL)
    pGraph = new CRDFGraph;

  // We make sure that we always have an about node.
  pGraph->createAboutNode(mKey);

  std::map< std::string, CRDFNode * >::const_iterator itMap = pGraph->getLocalResourceNodeMap().begin();
  std::map< std::string, CRDFNode * >::const_iterator endMap = pGraph->getLocalResourceNodeMap().end();

  const CRDFNode * pNode;
  for (;itMap != endMap; ++itMap)
    {
      pNode = itMap->second;
      if (pNode && pNode->isSubjectNode() && !pNode->isObjectNode())
        {
          CRDFListViewItem * pItem = new CRDFListViewItem(mpListView, NULL);
          pItem->setNode(pNode);
        }
    }

  //pdelete(pGraph);
}

void CQRDFListViewWidget::save()
{
  qWarning("CQRDFListViewWidget::save(): Not implemented yet");
}

void CQRDFListViewWidget::destroy()
{}

bool CQRDFListViewWidget::update(ListViews::ObjectType, ListViews::Action, const std::string&)
{
  load();
  //qWarning("CQRDFListViewWidget::update(ListViews::ObjectType,ListViews::Action,const std::string&): Not implemented yet");
  return FALSE;
}

void CQRDFListViewWidget::setMIRIAMInfo(CMIRIAMInfo* pMIRIAMInfo)
{mpMIRIAMInfo = pMIRIAMInfo;}
