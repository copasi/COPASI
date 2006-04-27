/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ScanScrollView.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:45 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "ScanScrollView.h"

/****************************************
 * The implementation of ScanScrollView
 ****************************************/

ScanScrollView::ScanScrollView(QWidget* parent, const char* name, WFlags fl)
    : QScrollView(parent, name, fl)
{
  pSelectedList = NULL;
  mParent = (CopasiParametersWidget*)parent;
}

void ScanScrollView::contentsMousePressEvent(class QMouseEvent *e)
{
  QScrollView::contentsMousePressEvent(e);
  mParent->viewMousePressEvent(e);
}
void ScanScrollView:: resizeEvent(QResizeEvent * e)
{
  if (e)
    QScrollView::resizeEvent(e);
  if (!pSelectedList)
    return;
  QScrollView::repaintContents(true);
  unsigned i;
  for (i = 0; i < pSelectedList->size(); i++)
    {
      (*pSelectedList)[i]->setFixedWidth(visibleWidth());
    }
}

void ScanScrollView::setSelectedList(std::vector<QWidget*>* pNewSelectedList)
{
  pSelectedList = pNewSelectedList;
}

void ScanScrollView::viewportResizeEvent (QResizeEvent * e)
{
  if (e)
    QScrollView::viewportResizeEvent(e);
  if (!pSelectedList)
    return;
  QScrollView::repaintContents(true);
  unsigned i;
  for (i = 0; i < pSelectedList->size(); i++)
    {
      (*pSelectedList)[i]->setFixedWidth(visibleWidth());
    }
}
