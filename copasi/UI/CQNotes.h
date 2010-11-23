// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQNotes.h,v $
//   $Revision: 1.3.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/11/23 18:06:10 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQNotes
#define COPASI_CQNotes

#include <QWidget>
#include <QVariant>
#include <QXmlDefaultHandler>

#include "copasi/UI/ui_CQNotes.h"
#include "copasi/UI/CQValidator.h"

class CQValidatorXML : public CQValidator< QPlainTextEdit >
{
  // Operations
public:
  CQValidatorXML(QPlainTextEdit * parent, const char * name = 0);

  virtual State validate(QString & input, int & pos) const;

  const bool & isFreeText() const;

private:
  // Attributes
  mutable bool mIsFreeText;
};

class CQNotesContentHandler : public QXmlDefaultHandler
{
public:
  // Operations
  CQNotesContentHandler();

  ~CQNotesContentHandler();

  virtual bool startDocument();

  virtual bool startElement(const QString & namespaceURI,
                            const QString & localName,
                            const QString & qName,
                            const QXmlAttributes & atts);

  const bool & isFreeText() const;

private:
  // Attributes
  bool mIsFreeText;
};

class CQNotes : public CopasiWidget, public Ui::CQNotes
{
  Q_OBJECT

public:
  CQNotes(QWidget* parent = 0, const char* name = 0);
  ~CQNotes();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:
  void slotToggleMode();
  void slotOpenUrl(const QUrl & url);
  void slotValidateXML();

protected:
  virtual bool enterProtected();

private:
  void load();
  void save();

  bool mEditMode;
  bool mChanged;
  CQValidatorXML * mpValidatorXML;
  QValidator::State mValidity;
};



#endif // COPASI_CQNotes
