// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQNotes.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/08/12 15:37:52 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQNotes.cpp
 *
 *  Created on: Aug 11, 2010
 *      Author: shoops
 */

#include <QWebFrame>

#include "CQNotes.h"
#include "CQIcons.h"
#include "qtUtilities.h"

#include "model/CModelValue.h"
#include "model/CReaction.h"
#include "function/CFunction.h"
#include "report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"

CQNotes::CQNotes(QWidget* parent, const char* name) :
    CopasiWidget(parent, name)
{
  setupUi(this);

  mEditMode = false;
  mpEdit->hide();
  mpWebView->show();
  mpBtnToggleEdit->setIcon(CQIcons::getIcon(CQIcons::Edit));
}

CQNotes::~CQNotes()
{}

// virtual
bool CQNotes::update(ListViews::ObjectType /* objectType */, ListViews::Action action, const std::string & key)
{
  if (key == mKey &&
      action == ListViews::CHANGE)
    {
      load();
    }

  return true;
}

// virtual
bool CQNotes::leave()
{
  mpBtnToggleEdit->setFocus();
  save();

  return true;
}

// virtual
bool CQNotes::enterProtected()
{
  load();

  return true;
}

void CQNotes::slotToggleMode()
{
  mEditMode = !mEditMode;

  if (mEditMode)
    {
      mpWebView->hide();
      mpEdit->show();
      mpBtnToggleEdit->setIcon(CQIcons::getIcon(CQIcons::View));
    }
  else
    {
      save();
      load();

      mpEdit->hide();
      mpWebView->show();
      mpBtnToggleEdit->setIcon(CQIcons::getIcon(CQIcons::Edit));
    }
}

void CQNotes::load()
{
  if (mpObject != NULL)
    {
      const std::string * pNotes = NULL;

      if (dynamic_cast< CModelEntity * >(mpObject))
        pNotes =
          &dynamic_cast< CModelEntity * >(mpObject)->getNotes();

      /*
      else if (dynamic_cast< CReaction * >(mpObject))
        pNotes =
          &dynamic_cast< CReaction * >(mpObject)->getNotes();
      else if (dynamic_cast< CFunction * >(mpObject))
        pNotes =
          &dynamic_cast< CFunction * >(mpObject)->getNotes();
      */

      if (pNotes && *pNotes != "")
        {
          // The notes are UTF8 encoded however the html does not specify an encoding
          // thus Qt uses locale settings.
          mpWebView->setHtml(FROM_UTF8(*pNotes));
          mpEdit->setPlainText(FROM_UTF8(*pNotes));
        }
    }

  mChanged = false;

  return;
}

void CQNotes::save()
{
  if (mpObject != NULL)
    {
      const std::string * pNotes = NULL;

      if (dynamic_cast< CModelEntity * >(mpObject))
        pNotes =
          &static_cast< CModelEntity * >(mpObject)->getNotes();

      /*
      else if (dynamic_cast< CReaction * >(mpObject))
        pNotes =
          &static_cast< CReaction * >(mpObject)->getNotes();
      else if (dynamic_cast< CFunction * >(mpObject))
        pNotes =
          &static_cast< CFunction * >(mpObject)->getNotes();
      */

      if (pNotes &&
          mpEdit->toPlainText() != FROM_UTF8(*pNotes))
        {
          if (dynamic_cast< CModelEntity * >(mpObject))
            static_cast< CModelEntity * >(mpObject)->setNotes(TO_UTF8(mpEdit->toPlainText()));

          /*
          else if (dynamic_cast< CReaction * >(mpObject))
            static_cast< CReaction * >(mpObject)->setNotes(TO_UTF8(mpEdit->toPlainText()));
          else if (dynamic_cast< CFunction * >(mpObject))
            static_cast< CFunction * >(mpObject)->setNotes(TO_UTF8(mpEdit->toPlainText()));
          */

          mChanged = true;
        }
    }

  if (mChanged)
    {
      if (mpDataModel != NULL)
        {
          mpDataModel->changed();
        }

      protectedNotify(ListViews::MODEL, ListViews::CHANGE, mKey);
    }

  mChanged = false;
  return;
}
