/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQProgressItemText.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:13:22 $
   End CVS Header */

#include "qtUtilities.h"

bool CQProgressItemText::initFromProcessReportItem(CProcessReportItem * pItem)
{
  mpItem = pItem;
  mItemName->setText(FROM_UTF8(mpItem->getObjectName()));

  return false;
}

bool CQProgressItemText::process()
{return false;}

bool CQProgressItemText::reset()
{return false;}
