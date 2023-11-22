// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQMESSAGEBOX_H
#define CQMESSAGEBOX_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QMessageBox>

#include <copasi/UI/ui_CQMessageBox.h>


#include <set>

class QTabWidget;
class QTextEdit;
class QAbstractButton;
class QPushButton;
class QVBoxLayout;
class CDataObject;
class CFunctionDB;
class CDataModel;
class CObjectInterface;
class CDataContainer;

class CQMessageBox: public QDialog, public Ui::CQMessageBox
{
  Q_OBJECT

public:
  CQMessageBox(QMessageBox::Icon icon, const QString & title, const QString & text, QMessageBox::StandardButtons buttons = QMessageBox::NoButton, QWidget * parent = 0, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  ~CQMessageBox();

  static QMessageBox::StandardButton information(QWidget * parent, const QString & title, const QString & text, QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

  static QMessageBox::StandardButton question(QWidget * parent, const QString & title, const QString & text, QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

  static QMessageBox::StandardButton warning(QWidget * parent, const QString & title, const QString & text, QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

  static QMessageBox::StandardButton critical(QWidget * parent, const QString & title, const QString & text, QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

  static QMessageBox::StandardButton confirmDelete(QWidget * parent,
      const QString &objectType, const QString &objects,
      const CDataContainer * pContainer);

  static QString buildDeleteConfirmationMessage(const QString & objectType,
      const QString & objects,
      CFunctionDB * pFunctionDB,
      std::set< const CObjectInterface * > & DeletedObjects,
      const CDataModel * pDataModel,
      bool& isUsed);

  void setText(const QString & text);

  void setFilteredText(const QString & text);

  void setDefaultButton(QMessageBox::StandardButton defaultButton);
    
  void setDefaultButton(QPushButton* pButton);
    
  QAbstractButton* button(QMessageBox::StandardButton button);
    
  QPushButton* addButton(QMessageBox::StandardButton button);

  QAbstractButton* clickedButton();
    
  virtual int exec();

public slots:
  void slotButtonPressed(QAbstractButton * pButton);

private:

  QMessageBox::StandardButton mButton;
  QAbstractButton* mpClickedButton;

};

#endif // CQMESSAGEBOX_H
