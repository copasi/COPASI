// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQNotes.cpp
 *
 *  Created on: Aug 11, 2010
 *      Author: shoops
 */

#include <QDesktopServices>
#include <QXmlInputSource>
#include <QXmlSimpleReader>

#include "CQNotes.h"
#include "copasi/CopasiDataModel/CDataModel.h"


#if defined(QT_USE_TEXTBROWSER)
# include <QTextBrowser>
#elif !defined(QT5_USE_WEBENGINE)
# include <QWebView>
# include <QWebFrame>
#else  // QT5_USE_WEBENGINE
# include <QWebEngineView>
# include <QWebEnginePage>

CQWebEnginePage::CQWebEnginePage(QObject* parent)
  : QWebEnginePage(parent)
{
}

bool
CQWebEnginePage::acceptNavigationRequest(const QUrl & url,
    QWebEnginePage::NavigationType type, bool isMainFrame)
{
  if (type == QWebEnginePage::NavigationTypeLinkClicked)
    {
      QDesktopServices::openUrl(url);
      return false;
    }

  return true;
}

#endif // QT_USE_TEXTBROWSER

#include "copasi/resourcesUI/CQIconResource.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "copasi/model/CModelValue.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CEvent.h"
#include "copasi/function/CFunction.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"

#include <copasi/UI/copasiui3window.h>
#include <copasi/UI/CQCopasiApplication.h>

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
  mValidity(QValidator::Acceptable),
  mObjectCNToCopy()
  , mpWebView(NULL)

{
  setupUi(this);

  mpValidatorXML = new CQValidatorXML(mpEdit);

#if defined(QT_USE_TEXTBROWSER)
  mpWebView = new QTextBrowser(this);
  connect(mpWebView, SIGNAL(anchorClicked(QUrl)), this, SLOT(slotOpenUrl(QUrl)));
  static_cast< QTextBrowser * >(mpWebView)->setOpenLinks(false);

#elif !defined(QT5_USE_WEBENGINE)
  mpWebView = new QWebView(this);
  static_cast<QWebView*>(mpWebView)->
  page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
  connect(mpWebView, SIGNAL(linkClicked(QUrl)), this, SLOT(slotOpenUrl(QUrl)));
#else
  mpWebView = new QWebEngineView(this);
  static_cast<QWebEngineView*>(mpWebView)->setPage(new CQWebEnginePage);
  connect(mpWebView, SIGNAL(urlChanged(QUrl)), this, SLOT(slotOpenUrl(QUrl)));
#endif

  mpVerticalLayout->addWidget(mpWebView);

  mEditMode = false;
  mpEdit->hide();
  mpWebView->show();
  mpBtnToggleEdit->setIcon(CQIconResource::icon(CQIconResource::edit));
}

CQNotes::~CQNotes()
{}

void CQNotes::slotBtnCopy()
{
  mObjectCNToCopy = mObjectCN;
}

// virtual
bool CQNotes::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (mIgnoreUpdates || !isVisible())
    {
      return true;
    }

  switch (action)
    {
      case ListViews::CHANGE:

        if (cn == mObjectCN)
          {
            load();
          }

        break;

      case ListViews::DELETE:

        if (cn == mObjectCN || objectType == ListViews::ObjectType::MODEL)
          {
            mpObject = NULL;
            mObjectCN.clear();
          }

        break;

      default:
        break;
    }

  if (objectType == ListViews::ObjectType::MODEL &&
      action == ListViews::DELETE)
    {
      mEditMode = false;
    }

  return true;
}

// virtual
bool CQNotes::leaveProtected()
{
  if (mpObject != NULL)
    {
      save();
    }
  else
    {
      mObjectCN.clear();
    }

  return true;
}

// virtual
bool CQNotes::enterProtected()
{
  if (mObjectCNToCopy == "")
    {
      load();
    }
  else
    {
      CObjectInterface::ContainerList List;
      List.push_back(mpDataModel);

      // This will check the current data model and the root container for the object;
      mpObject = const_cast< CDataObject * >(CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(List, mObjectCNToCopy)));
      load();
      mpObject = const_cast< CDataObject * >(CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(List, mObjectCN)));
      save();
      mObjectCN.clear();
    }

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
      QString Notes;

      CAnnotation * pAnnotation = CAnnotation::castObject(mpObject);
      CReportDefinition * pReportDefinition = dynamic_cast< CReportDefinition * >(mpObject);

      if (pAnnotation != NULL)
        {
          Notes = FROM_UTF8(pAnnotation->getNotes());
        }
      else if (pReportDefinition != NULL)
        {
          Notes = FROM_UTF8(pReportDefinition->getComment());
        }

      // The notes are UTF8 encoded however the html does not specify an encoding
      // thus Qt uses locale settings.
#if defined(QT_USE_TEXTBROWSER)
      static_cast<QTextBrowser*>(mpWebView)->setHtml(Notes);
#elif !defined(QT5_USE_WEBENGINE)
      static_cast<QWebView*>(mpWebView)->setHtml(Notes);
#else
      static_cast<QWebEngineView*>(mpWebView)->setHtml(Notes);
#endif
      mpEdit->setPlainText(Notes);
      mLoadedText = mpEdit->toPlainText();

      mpValidatorXML->saved();
      slotValidateXML();

      if (!mpValidatorXML->isFreeText() && mEditMode)
        {
          slotToggleMode();
        }

      mValidity = QValidator::Acceptable;
    }

  mChanged = false;

  return;
}

void CQNotes::save()
{
  if (mpObject == NULL ||
      mValidity != QValidator::Acceptable)
    return;

  CAnnotation * pAnnotation = CAnnotation::castObject(mpObject);
  CReportDefinition * pReportDefinition = dynamic_cast<CReportDefinition *>(mpObject);

  std::string notes;

  if (pAnnotation != NULL)
    {
      notes = pAnnotation->getNotes();
    }
  else if (pReportDefinition != NULL)
    {
      notes = pReportDefinition->getComment();
    }

  QString currentPlainText = mpEdit->toPlainText();
  std::string plainText = TO_UTF8(mpEdit->toPlainText());

  if (plainText == notes)
    return;

  if (mLoadedText == currentPlainText)
    return;

  if (mpValidatorXML->needsWrap())
    {
      // We wrap the HTML in a body element if it does not contain a top level html or body element.
      plainText = "<body xmlns=\"http://www.w3.org/1999/xhtml\">" + plainText + "</body>";
    }

  CUndoData UndoData(CUndoData::Type::CHANGE, mpObject->toData());
  UndoData.addProperty(CData::Property::NOTES, notes, plainText);
  ListViews::addUndoMetaData(this, UndoData);

  slotNotifyChanges(mpDataModel->applyData(UndoData));
}

void CQNotes::slotOpenUrl(const QUrl & url)
{
  QString scheme = url.scheme();

  if (scheme == "about" || scheme == "data")
    return;

  if (scheme == "copasi")
    {
      dynamic_cast<CQCopasiApplication*>(qApp)->getMainWindow()->slotHandleCopasiScheme(url);
      return;
    }

  QDesktopServices::openUrl(url);
  return;
}
