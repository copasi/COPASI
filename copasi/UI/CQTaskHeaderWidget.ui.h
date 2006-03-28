/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQTaskHeaderWidget.ui.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/28 23:08:45 $
   End CVS Header */

#include "copasi.h"

#include "qtUtilities.h"

#include "utilities/CCopasiTask.h"

bool CQTaskHeaderWidget::setTaskName(const std::string & name)
{
  mpLblName->setText("<h2>" + FROM_UTF8(name) + "</h2>");
  return true;
}

void CQTaskHeaderWidget::saved()
{
  mUpdateChanged = false;
  mpUpdateModel->setPaletteBackgroundColor(mSavedColor);

  mExecutableChanged = false;
  mpBoxExecutable->setPaletteBackgroundColor(mSavedColor);
}

void CQTaskHeaderWidget::slotUpdate()
{
  mUpdateChanged = !mUpdateChanged;

  if (mUpdateChanged)
    mpUpdateModel->setPaletteBackgroundColor(mChangedColor);
  else
    mpUpdateModel->setPaletteBackgroundColor(mSavedColor);
}

void CQTaskHeaderWidget::slotExecutable()
{
  mExecutableChanged = !mExecutableChanged;

  if (mExecutableChanged)
    mpBoxExecutable->setPaletteBackgroundColor(mChangedColor);
  else
    mpBoxExecutable->setPaletteBackgroundColor(mSavedColor);
}

void CQTaskHeaderWidget::init()
{
  mUpdateChanged = false;
  mExecutableChanged = false;

  int h, s, v;

  mSavedColor = paletteBackgroundColor();
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;
  mChangedColor.setHsv(240, s, v);
}
