/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CUpDownSubwidget.ui.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/04 14:33:18 $
   End CVS Header */

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

void CUpDownSubwidget::init()
{
  setIndex(0, true, true);
}

void CUpDownSubwidget::slotUp()
{
  emit up(mIndex);
}

void CUpDownSubwidget::slotDown()
{
  emit down(mIndex);
}

void CUpDownSubwidget::slotDel()
{
  emit del(mIndex);
}

void CUpDownSubwidget::setIndex(int index, bool isFirst, bool isLast)
{
  mIndex = index;
  if ((mIndex == 0) || (isFirst))
    toolButtonUp->setEnabled(false);
  else
    toolButtonUp->setEnabled(true);

  if (isLast)
    toolButtonDown->setEnabled(false);
  else
    toolButtonDown->setEnabled(true);
}

int CUpDownSubwidget::getIndex() const
  {
    return mIndex;
  }
