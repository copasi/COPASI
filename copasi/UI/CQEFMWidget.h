// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMWidget.h,v $
//   $Revision: 1.3.26.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/11 17:19:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQEFMWidget.ui'
 **
 ** Created: Tue Nov 11 12:09:50 2008
 **      by: The User Interface Compiler ($Id: CQEFMWidget.h,v 1.3.26.1 2008/11/11 17:19:46 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQEFMWIDGET_H
#define CQEFMWIDGET_H

#include <qvariant.h>
#include "TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QListView;
class QListViewItem;

class CQEFMWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQEFMWidget(QWidget* parent = 0, const char* name = 0);
    ~CQEFMWidget();

    QFrame* mpLine;
    QLabel* mpLblFluxModes;
    QLineEdit* mpEditFluxModes;
    QPushButton* mpBtnSave;
    QListView* mpListView;

    virtual bool runTask();
    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

  protected:
    QVBoxLayout* CQEFMWidgetLayout;
    QHBoxLayout* layout2;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();

  private:
    void init();
    void destroy();
    void loadFluxModes();

  private slots:
    void slotSave();
  };

#endif // CQEFMWIDGET_H
