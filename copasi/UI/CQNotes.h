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

#ifndef COPASI_CQNotes
#define COPASI_CQNotes

#include <QWidget>
#include <QVariant>
#include <QXmlDefaultHandler>

#if defined(QT5_USE_WEBENGINE) && !defined(QT_USE_TEXTBROWSER)
# include <QWebEnginePage>

class CQWebEnginePage : public QWebEnginePage
{
  Q_OBJECT

public:
  CQWebEnginePage(QObject* parent = NULL);

protected:
  virtual bool acceptNavigationRequest(const QUrl & url,
                                       QWebEnginePage::NavigationType type,
                                       bool isMainFrame);
};
#else

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0) && !defined(WIN32) && !defined(QT_USE_TEXTBROWSER)
// for whatever reason this fails to compile on centos 7 with qt 5.6.1
#ifndef QWEBKITWIDGETS_EXPORT
#define QWEBKITWIDGETS_EXPORT Q_DECL_IMPORT
#endif
#endif

#endif // QT5_USE_WEBENGINE

#include "copasi/UI/ui_CQNotes.h"
#include "copasi/UI/CQValidator.h"

class CQValidatorXML : public CQValidator< QPlainTextEdit >
{
  // Operations
public:
  CQValidatorXML(QPlainTextEdit *parent, const char *name = 0);

  virtual State validate(QString &input, int &pos) const;

  const bool &isFreeText() const;

  const bool &needsWrap() const;

private:
  // Attributes
  mutable bool mIsFreeText;

  mutable bool mNeedsWrap;
};

class CQNotesContentHandler : public QXmlDefaultHandler
{
public:
  // Operations
  CQNotesContentHandler();

  ~CQNotesContentHandler();

  virtual bool startDocument();

  virtual bool startElement(const QString &namespaceURI,
                            const QString &localName,
                            const QString &qName,
                            const QXmlAttributes &atts);

  virtual bool endElement(const QString &namespaceURI,
                          const QString &localName,
                          const QString &qName);

  const bool &isFreeText() const;

  bool needsWrap() const;

private:
  // Attributes
  bool mIsFreeText;

  bool mNeedsWrap;

  size_t mLevel;
};

class CQNotes : public CopasiWidget, public Ui::CQNotes
{
  Q_OBJECT

public:
  CQNotes(QWidget *parent = 0, const char *name = 0);
  ~CQNotes();

protected slots:
  void slotToggleMode();
  void slotOpenUrl(const QUrl &url);
  void slotValidateXML();
  void slotBtnCopy();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

private:
  void load();
  void save();

  bool mEditMode;
  bool mChanged;
  CQValidatorXML *mpValidatorXML;
  QValidator::State mValidity;

  CCommonName mObjectCNToCopy;

  QWidget* mpWebView;

  /**
   * This string is the text last loaded into the text edit, this makes it easy
   * to recognize whether changes have been made to the element or not.
   */
  QString mLoadedText;
};

#endif // COPASI_CQNotes
