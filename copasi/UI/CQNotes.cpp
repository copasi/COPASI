// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

/*
 * CQNotes.cpp
 *
 *  Created on: Aug 11, 2010
 *      Author: shoops
 */

#include <QtWebKit/QWebFrame>
#include <QtXml/QXmlInputSource>
#include <QtXml/QXmlSimpleReader>
#include <QtGui/QDesktopServices>

#include "CQNotes.h"
#include "resourcesUI/CQIconResource.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "model/CModelValue.h"
#include "model/CReaction.h"
#include "model/CEvent.h"
#include "function/CFunction.h"
#include "report/CKeyFactory.h"
#include "report/CReportTemplate.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "commandline/CConfigurationFile.h"

CQValidatorXML::CQValidatorXML(QPlainTextEdit * parent, const char * name):
  CQValidator< QPlainTextEdit >(parent, &QPlainTextEdit::toPlainText, name),
  mIsFreeText(true),
  mNeedsWrap(false)
{}

// virtual
QValidator::State CQValidatorXML::validate(QString & input, int & pos) const
{
  QXmlSimpleReader Validator;
  QXmlInputSource Input;
  CQNotesContentHandler ContentHandler;

  Validator.setContentHandler(&ContentHandler);

  // We like to allow free text and therefore wrap the text to create valid XML.
  Input.setData("<Validate:XML xmlns:Validate=\"http://www.copasi.org/Validate\">" + input + "</Validate:XML>");

  if (Validator.parse(Input))
    {
      mIsFreeText = ContentHandler.isFreeText();
      mNeedsWrap = ContentHandler.needsWrap();
      return CQValidator< QPlainTextEdit >::validate(input, pos);
    }

  mIsFreeText = true;
  mNeedsWrap = false;
  setColor(Invalid);
  return Intermediate;
}

const bool & CQValidatorXML::isFreeText() const
{
  return mIsFreeText;
}

const bool & CQValidatorXML::needsWrap() const
{
  return mNeedsWrap;
}

CQNotesContentHandler::CQNotesContentHandler():
  QXmlDefaultHandler(),
  mIsFreeText(true),
  mNeedsWrap(true),
  mLevel(0)
{}

CQNotesContentHandler:: ~CQNotesContentHandler()
{}

// virtual
bool CQNotesContentHandler::startDocument()
{
  mIsFreeText = true;
  mNeedsWrap = true;
  mLevel = 0;
  return true;
}

// virtual
bool CQNotesContentHandler::startElement(const QString & namespaceURI,
    const QString & localName,
    const QString & qName,
    const QXmlAttributes & atts)
{
  if (namespaceURI != "http://www.copasi.org/Validate" ||
      qName != "Validate:XML")
    mIsFreeText = false;

  if (mLevel == 1 &&
      namespaceURI == "http://www.w3.org/1999/xhtml" &&
      (localName == "html" || localName == "body"))
    mNeedsWrap = false;

  mLevel++;

  return QXmlDefaultHandler::startElement(namespaceURI, localName, qName, atts);
}

// virtual
bool CQNotesContentHandler::endElement(const QString & namespaceURI,
                                       const QString & localName,
                                       const QString & qName)
{
  mLevel--;

  return QXmlDefaultHandler::endElement(namespaceURI, localName, qName);
}

const bool & CQNotesContentHandler::isFreeText() const
{
  return mIsFreeText;
}

bool CQNotesContentHandler::needsWrap() const
{
  return (mNeedsWrap && !mIsFreeText);
}

CQNotes::CQNotes(QWidget* parent, const char* name) :
  CopasiWidget(parent, name),
  mEditMode(false),
  mChanged(false),
  mpValidatorXML(NULL),
  mValidity(QValidator::Acceptable)

{
  setupUi(this);

  mpValidatorXML = new CQValidatorXML(mpEdit);

  mEditMode = false;
  mpEdit->hide();
  mpWebView->show();
  mpBtnToggleEdit->setIcon(CQIconResource::icon(CQIconResource::edit));

  mpWebView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}

CQNotes::~CQNotes()
{}

// virtual
bool CQNotes::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (action)
    {
      case ListViews::CHANGE:

        if (key == mKey)
          {
            load();
          }

        break;

      case ListViews::DELETE:

        if (key == mKey || objectType == ListViews::MODEL)
          {
            mpObject = NULL;
            mKey = "";
          }

        break;

      default:
        break;
    }

  if (objectType == ListViews::MODEL &&
      action == ListViews::DELETE)
    {
      mEditMode = false;
    }

  return true;
}

// virtual
bool CQNotes::leave()
{
  mpBtnToggleEdit->setFocus();

  mpObject = CCopasiRootContainer::getKeyFactory()->get(mKey);

  if (mpObject != NULL)
    {
      save();
    }
  else
    {
      mKey = "";
      mpDataModel = NULL;
    }

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
      mpBtnToggleEdit->setIcon(CQIconResource::icon(CQIconResource::renderMarkup));
    }
  else
    {
      save();
      load();

      mpEdit->hide();
      mpWebView->show();
      mpBtnToggleEdit->setIcon(CQIconResource::icon(CQIconResource::edit));
    }
}

void CQNotes::slotValidateXML()
{
  QString Input = mpEdit->toPlainText();
  int pos = 0;

  mValidity = mpValidatorXML->validate(Input, pos);

  if (mpValidatorXML->isFreeText())
    {
      mEditMode = true;
      mpBtnToggleEdit->hide();
    }
  else
    {
      mpBtnToggleEdit->show();
    }

  if (mEditMode)
    {
      mpWebView->hide();
      mpEdit->show();
      mpBtnToggleEdit->setIcon(CQIconResource::icon(CQIconResource::renderMarkup));
    }
  else
    {
      mpEdit->hide();
      mpWebView->show();
      mpBtnToggleEdit->setIcon(CQIconResource::icon(CQIconResource::edit));
    }
}

void CQNotes::load()
{
  if (mpObject != NULL)
    {
      const std::string * pNotes = NULL;

      if (dynamic_cast< CModelEntity * >(mpObject))
        pNotes = &static_cast< CModelEntity * >(mpObject)->getNotes();
      else if (dynamic_cast< CEvent * >(mpObject))
        pNotes = &static_cast< CEvent * >(mpObject)->getNotes();
      else if (dynamic_cast< CReaction * >(mpObject))
        pNotes = &static_cast< CReaction * >(mpObject)->getNotes();
      else if (dynamic_cast< CFunction * >(mpObject))
        pNotes = &static_cast< CFunction * >(mpObject)->getNotes();
      else if (dynamic_cast< CReportTemplate * >(mpObject))
        pNotes = & static_cast< CReportTemplate * >(mpObject)->getComment();

      if (pNotes != NULL)
        {
          // The notes are UTF8 encoded however the html does not specify an encoding
          // thus Qt uses locale settings.
          mpWebView->setHtml(FROM_UTF8(*pNotes));
          mpEdit->setPlainText(FROM_UTF8(*pNotes));
          mpValidatorXML->saved();
          slotValidateXML();

          if (!mpValidatorXML->isFreeText() && mEditMode)
            {
              slotToggleMode();
            }

          mValidity = QValidator::Acceptable;
        }
    }

  mChanged = false;

  return;
}

void CQNotes::save()
{
  if (mpObject != NULL &&
      mValidity == QValidator::Acceptable)
    {
      const std::string * pNotes = NULL;

      if (dynamic_cast< CModelEntity * >(mpObject))
        pNotes = &static_cast< CModelEntity * >(mpObject)->getNotes();
      else if (dynamic_cast< CEvent * >(mpObject))
        pNotes = &static_cast< CEvent * >(mpObject)->getNotes();
      else if (dynamic_cast< CReaction * >(mpObject))
        pNotes = &static_cast< CReaction * >(mpObject)->getNotes();
      else if (dynamic_cast< CFunction * >(mpObject))
        pNotes = &static_cast< CFunction * >(mpObject)->getNotes();
      else if (dynamic_cast< CReportTemplate * >(mpObject))
        pNotes = & static_cast< CReportTemplate * >(mpObject)->getComment();

      if (pNotes &&
          mpEdit->toPlainText() != FROM_UTF8(*pNotes))
        {
          std::string PlainText = TO_UTF8(mpEdit->toPlainText());

          if (mpValidatorXML->needsWrap())
            {
              // We wrap the HTML in a body element if it does not contain a top level html or body element.
              PlainText = "<body xmlns=\"http://www.w3.org/1999/xhtml\">" + PlainText + "</body>";
            }

          if (dynamic_cast< CModelEntity * >(mpObject))
            static_cast< CModelEntity * >(mpObject)->setNotes(PlainText);
          else if (dynamic_cast< CEvent * >(mpObject))
            static_cast< CEvent * >(mpObject)->setNotes(PlainText);
          else if (dynamic_cast< CReaction * >(mpObject))
            static_cast< CReaction * >(mpObject)->setNotes(PlainText);
          else if (dynamic_cast< CFunction * >(mpObject))
            static_cast< CFunction * >(mpObject)->setNotes(PlainText);
          else if (dynamic_cast< CReportTemplate * >(mpObject))
            static_cast< CReportTemplate * >(mpObject)->setComment(PlainText);

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
      mChanged = false;
    }

  return;
}

void CQNotes::slotOpenUrl(const QUrl & url)
{
  QDesktopServices::openUrl(url);
  return;
}
