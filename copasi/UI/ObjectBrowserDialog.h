// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ObjectBrowserDialog.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/03/13 19:56:56 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef OBJECTBROWSERDIALOG_H
#define OBJECTBROWSERDIALOG_H

#include <qdialog.h>
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

  private:
    void cleanup();
  };
#endif // OBJECTBROWSERDIALOG_H
