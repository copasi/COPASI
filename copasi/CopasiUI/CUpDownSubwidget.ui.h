/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CUpDownSubwidget.ui.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/12 20:22:03 $
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
  enableCopy(false);
}

void CUpDownSubwidget::slotCopy()
{
  emit copy(mIndex);
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

void CUpDownSubwidget::enableCopy(const bool & enable)
{
  if (enable) toolButtonCopy->show();
  else toolButtonCopy->hide();
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
