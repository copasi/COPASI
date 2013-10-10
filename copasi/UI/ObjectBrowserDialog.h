// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef OBJECTBROWSERDIALOG_H
#define OBJECTBROWSERDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QCloseEvent>
#include <vector>

class QPushButton;
class ObjectBrowserWidget;
class QGridLayout;
class QFrame;
class QSpacerItem;
class CopasiUI3Window;
class CCopasiObject;

class ObjectBrowserDialog : public QDialog
{
  Q_OBJECT

public:
  ObjectBrowserDialog(QWidget* parent = 0, const char* name = 0, bool modal = true, int state = 0);
  virtual ~ObjectBrowserDialog();
  void setOutputVector(std::vector< const CCopasiObject * > * pObjectVector);
  void selectObjects(std::vector< const CCopasiObject * > * pObjectVector);

protected:

  QPushButton* clearButton;
  QPushButton* toggleViewButton;
  QPushButton* cancelButton;
  QPushButton* okButton;
  QFrame* Line1;
  QSpacerItem* spacer;
  ObjectBrowserWidget* objectBrowserWidget;
  QGridLayout* ObjectBrowserDialogLayout;

public slots:
  void cancelClicked();
  void okClicked();
  void toggleViewClicked();
};
#endif // OBJECTBROWSERDIALOG_H
