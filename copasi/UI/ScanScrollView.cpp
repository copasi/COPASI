/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ScanScrollView.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/22 15:16:19 $
   End CVS Header */

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
