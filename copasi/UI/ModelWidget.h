/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ModelWidget.h,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/28 00:20:16 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 **  $ CopasiUI/ModelWidget.h
 **  $ Author  : Mudita Singhal
 **
 ** This is the header file for the Model Widget
 *****************************************************************************/
#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include "UI/copasiWidget.h"
#include <qtextbrowser.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QSpacerItem;
class QLineEdit;
class QLabel;
class QComboBox;
class QPushButton;
class CModel;

class ModelWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    ModelWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ModelWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();

  public slots:
    virtual void toggleEditorBox();

  protected:
    bool loadModel(CModel *model);
    bool saveToModel();
    std::string objKey;

    QGridLayout* ModelWidgetLayout;
    QHBoxLayout* Layout5;
    QVBoxLayout* showMarkupLayout;
    QSpacerItem* spacer;
    QLineEdit* LineEdit;
    // QTextBrowser* textBrowser;
    QTextEdit* mpEditComment;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel4;
    QLabel* mpLblModelType;
    QLabel* mpLblInitial;
    QLabel* mpLblCurrent;
    QLabel* mpLblTime;
    QLineEdit *mpInitialTime;
    QLineEdit *mpCurrentTime;
    QPushButton* mpToggleMarkup;
    QComboBox* ComboBox1;
    QComboBox* ComboBox2;
    QComboBox* ComboBox3;
    QComboBox* mpBoxModelType;

    QPushButton* commitChanges;
    QPushButton* cancelChanges;
  };

#endif // MODELWIDGET_H
