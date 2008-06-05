// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CQMiriamWidget.ui.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/05 15:33:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

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

#include "copasi.h"

#include "UI/qtUtilities.h"

#include "MIRIAM/CModelMIRIAMInfo.h"

void CQMiriamWidget::init()
{
  // Create the MIRIAM Info
  mpMIRIAMInfo = new CMIRIAMInfo;

  // Connect the table widgets
  mWidgets.push_back(mpTblAuthors);
  connect(mpTblAuthors, SIGNAL(setEnableOKAndCancel(bool)), this, SLOT(slotEnableOKAndCancel(bool)));
  connect(mpTblAuthors, SIGNAL(delKeyPressed()), this, SLOT(slotBtnDeleteClicked()));

  mWidgets.push_back(mpTblReferences);
  connect(mpTblReferences, SIGNAL(setEnableOKAndCancel(bool)), this, SLOT(slotEnableOKAndCancel(bool)));
  connect(mpTblReferences, SIGNAL(delKeyPressed()), this, SLOT(slotBtnDeleteClicked()));

  mWidgets.push_back(mpTblDescription);
  connect(mpTblDescription, SIGNAL(setEnableOKAndCancel(bool)), this, SLOT(slotEnableOKAndCancel(bool)));
  connect(mpTblDescription, SIGNAL(delKeyPressed()), this, SLOT(slotBtnDeleteClicked()));

  mWidgets.push_back(mpTblModified);
  connect(mpTblModified, SIGNAL(setEnableOKAndCancel(bool)), this, SLOT(slotEnableOKAndCancel(bool)));
  connect(mpTblModified, SIGNAL(delKeyPressed()), this, SLOT(slotBtnDeleteClicked()));
}

void CQMiriamWidget::destroy()
{
  pdelete(mpMIRIAMInfo);
}

void CQMiriamWidget::slotBtnOKClicked()
{
  // This forces that changes to the current table cell are commited.
  mpBtnCommit->setFocus();

  leave();
  enter(mpMIRIAMInfo->getKey());
}

void CQMiriamWidget::slotBtnCancelClicked()
{
  enter(mpMIRIAMInfo->getKey());
}

void CQMiriamWidget::slotBtnDeleteClicked()
{
  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
    if ((*it)->isTableInFocus())
      (*it)->slotBtnDeleteClicked();
}

void CQMiriamWidget::slotBtnNewClicked()
{
  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
    if ((*it)->isTableInFocus())
      (*it)->slotBtnNewClicked();
}

void CQMiriamWidget::slotBtnClearClicked()
{
  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
    if ((*it)->isTableInFocus())
      (*it)->slotBtnClearClicked();
}

void CQMiriamWidget::slotEnableOKAndCancel(bool enable)
{
  mpBtnCommit->setEnabled(enable);
  mpBtnRevert->setEnabled(enable);
}

void CQMiriamWidget::slotCreatedValueChanged(const QDateTime &)
{
  slotEnableOKAndCancel(true);
}

bool CQMiriamWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  if (objectType != ListViews::MIRIAM)
    return true;

  if (key != mpMIRIAMInfo->getKey())
    return true;

  bool success = true;
  mpMIRIAMInfo->load(key);

  mpDTCreated->setDateTime(QDateTime::fromString(FROM_UTF8(mpMIRIAMInfo->getCreatedDT()), Qt::ISODate));

  std::vector< CopasiTableWidget * >::const_iterator it = mWidgets.begin();
  std::vector< CopasiTableWidget * >::const_iterator end = mWidgets.end();

  for (; it != end; it++)
    (*it)->update(objectType, action, key);

  slotEnableOKAndCancel(false);

  return success;
}

bool CQMiriamWidget::leave()
{
  // First Ignore updates for all widgets or else we will
  // lose user entered data if data is entered/updated for more than one widget.
  std::vector< CopasiTableWidget * >::const_iterator it;
  std::vector< CopasiTableWidget * >::const_iterator end = mWidgets.end();

  for (it = mWidgets.begin(); it != end; it++)
    (*it)->setIgnoreUpdates(true);

  bool changed = false;

  //Now update.
  // Created at
  std::string DT = "";
  if (mpDTCreated->dateTime().isValid())
    DT = mpDTCreated->dateTime().toString(Qt::ISODate).utf8() + "Z";

  if (DT != mpMIRIAMInfo->getCreatedDT())
    {
      mpMIRIAMInfo->setCreatedDT(DT);
      changed = true;
    }

  for (it = mWidgets.begin(); it != end; it++)
    {
      (*it)->saveTable();
      changed |= (*it)->isChanged();
    }

  // Reset the mIgnoreUpdates.
  for (it = mWidgets.begin(); it != end; it++)
    (*it)->setIgnoreUpdates(false);

  if (changed)
    {
      mpMIRIAMInfo->save();

      // We are catching our own update which is correct.
      protectedNotify(ListViews::MIRIAM, ListViews::CHANGE, mpMIRIAMInfo->getKey());
    }

  return true;
}

bool CQMiriamWidget::enter(const std::string & key)
{
  bool success = true;
  mpMIRIAMInfo->load(key);

  mpDTCreated->setDateTime(QDateTime::fromString(FROM_UTF8(mpMIRIAMInfo->getCreatedDT()), Qt::ISODate));

  std::vector< CopasiTableWidget * >::const_iterator it = mWidgets.begin();
  std::vector< CopasiTableWidget * >::const_iterator end = mWidgets.end();

  for (; it != end; it++)
    success &= (*it)->enter(key);

  slotEnableOKAndCancel(false);

  return success;
}

void CQMiriamWidget::updateCreatedWidget()
{}

CMIRIAMInfo & CQMiriamWidget::getMIRIAMInfo()
{return *mpMIRIAMInfo;}
