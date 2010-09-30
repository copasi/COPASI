// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMessageBox.h,v $
//   $Revision: 1.6.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/09/30 17:02:30 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMESSAGEBOX_H
#define CQMESSAGEBOX_H

#include <QMessageBox>

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
