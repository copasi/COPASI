// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CQRDFListViewWidget.ui.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/24 16:08:49 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CRDFListViewItem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "model/CModelValue.h"
#include "MIRIAM/CRDFGraph.h"
#include "MIRIAM/CRDFNode.h"
#include "MIRIAM/CRDFParser.h"

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

  CRDFGraph * pGraph = NULL;
  CModelEntity * pEntity = NULL;

  if ((pEntity = dynamic_cast< CModelEntity * >(GlobalKeys.get(mKey))) != NULL)
    pGraph = CRDFParser::graphFromXml(pEntity->getMiriamAnnotation());

  if (pGraph == NULL)
    return;

  const CRDFNode * pAbout = NULL;

  if ((pAbout = pGraph->getAboutNode()) != NULL)
    {
      CRDFListViewItem * pItem = new CRDFListViewItem(mpListView, NULL);
      pItem->setNode(pAbout);
    }
}

void CQRDFListViewWidget::save()
{
  qWarning("CQRDFListViewWidget::save(): Not implemented yet");
}

void CQRDFListViewWidget::destroy()
{}

bool CQRDFListViewWidget::update(ListViews::ObjectType, ListViews::Action, const std::string&)
{
  qWarning("CQRDFListViewWidget::update(ListViews::ObjectType,ListViews::Action,const std::string&): Not implemented yet");
  return FALSE;
}
