// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQMESSAGEBOX_H
#define CQMESSAGEBOX_H

#include <QtGui/QMessageBox>

#include <set>

class QTabWidget;
class QTextEdit;
class QVBoxLayout;
class CCopasiObject;

class CQMessageBox: public QMessageBox
{
  Q_OBJECT

public:
  CQMessageBox(Icon icon, const QString &title, const QString &text,
               StandardButtons buttons = NoButton, QWidget *parent = 0,
               Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  ~CQMessageBox();

  static StandardButton information(QWidget *parent, const QString &title,
                                    const QString &text, StandardButtons buttons = Ok,
                                    StandardButton defaultButton = NoButton);

  static StandardButton question(QWidget *parent, const QString &title,
                                 const QString &text, StandardButtons buttons = Ok,
                                 StandardButton defaultButton = NoButton);

  static StandardButton warning(QWidget *parent, const QString &title,
                                const QString &text, StandardButtons buttons = Ok,
                                StandardButton defaultButton = NoButton);

  static StandardButton critical(QWidget *parent, const QString &title,
                                 const QString &text, StandardButtons buttons = Ok,
                                 StandardButton defaultButton = NoButton);

  static StandardButton confirmDelete(QWidget *parent,
                                      const QString &objectType, const QString &objects,
                                      const std::set< const CCopasiObject * > & deletedObjects);

  void setText(const QString & text);

  void setFilteredText(const QString & text);

protected:
  QTabWidget *mpTabWidget;
  QWidget *mpPage1;
  QVBoxLayout *mpVerticalLayoutPage1;
  QTextEdit *mpText1;
  QWidget *mpPage2;
  QVBoxLayout *mpVerticalLayoutPage2;
  QTextEdit *mpText2;
};

#endif // CQMESSAGEBOX_H
