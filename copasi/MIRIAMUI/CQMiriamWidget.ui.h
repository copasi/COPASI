// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CQMiriamWidget.ui.h,v $
//   $Revision: 1.3.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/08/19 13:42:26 $
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
  connect(mpTblAuthors, SIGNAL(delKeyPressed()), this, SLOT(slotBtnDeleteClicked()));

  mWidgets.push_back(mpTblReferences);
  connect(mpTblReferences, SIGNAL(delKeyPressed()), this, SLOT(slotBtnDeleteClicked()));

  mWidgets.push_back(mpTblDescription);
  connect(mpTblDescription, SIGNAL(delKeyPressed()), this, SLOT(slotBtnDeleteClicked()));

  mWidgets.push_back(mpTblModified);
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
  if (mpDTCreated->hasFocus())
    {
      delete mpDTCreated;

      mpDTCreated = new QDateTimeEdit(this, "mpDTCreated");
      CQMiriamWidgetLayout->addWidget(mpDTCreated, 0, 1);
      mpDTCreated->show();
      return;
    }

  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
    if ((*it)->isTableInFocus())
      (*it)->slotBtnClearClicked();
}

bool CQMiriamWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  if (getIgnoreUpdates())
    return true;

  if (objectType != ListViews::MIRIAM)
    return true;

  if (key != mpMIRIAMInfo->getKey())
    return true;

  bool success = true;
  mpMIRIAMInfo->load(key);

  if (mpMIRIAMInfo->getCreatedDT() != "")
    mpDTCreated->setDateTime(QDateTime::fromString(FROM_UTF8(mpMIRIAMInfo->getCreatedDT()), Qt::ISODate));

  std::vector< CopasiTableWidget * >::const_iterator it = mWidgets.begin();
  std::vector< CopasiTableWidget * >::const_iterator end = mWidgets.end();

  for (; it != end; it++)
    (*it)->update(objectType, action, key);

  return success;
}

bool CQMiriamWidget::leave()
{

  // First Ignore updates for all widgets or else we will
  // lose user entered data if data is entered/updated for more than one widget.
  setIgnoreUpdates(true);

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

  if (changed)
    {
      mpMIRIAMInfo->save();

      protectedNotify(ListViews::MIRIAM, ListViews::CHANGE, mpMIRIAMInfo->getKey());
    }

  // Reset the mIgnoreUpdates.
  setIgnoreUpdates(false);
  for (it = mWidgets.begin(); it != end; it++)
    (*it)->setIgnoreUpdates(false);

  return true;
}

bool CQMiriamWidget::enter(const std::string & key)
{
  bool success = true;
  mpMIRIAMInfo->load(key);

  QDateTime DTCreated;
  if (mpMIRIAMInfo->getCreatedDT() != "")
    DTCreated = QDateTime::fromString(FROM_UTF8(mpMIRIAMInfo->getCreatedDT()), Qt::ISODate);

  if (DTCreated.isValid())
    mpDTCreated->setDateTime(DTCreated);
  else
    {
      delete mpDTCreated;

      mpDTCreated = new QDateTimeEdit(this, "mpDTCreated");
      CQMiriamWidgetLayout->addWidget(mpDTCreated, 0, 1);
      mpDTCreated->show();
    }

  std::vector< CopasiTableWidget * >::const_iterator it = mWidgets.begin();
  std::vector< CopasiTableWidget * >::const_iterator end = mWidgets.end();

  for (; it != end; it++)
    success &= (*it)->enter(key);

  return success;
}

void CQMiriamWidget::updateCreatedWidget()
{}

CMIRIAMInfo & CQMiriamWidget::getMIRIAMInfo()
{return *mpMIRIAMInfo;}
