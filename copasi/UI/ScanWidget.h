// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ScanWidget.h,v $
//   $Revision: 1.60 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/07/07 21:13:52 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SCANWIDGET_H
#define SCANWIDGET_H

#include "copasi.h"
#include "TaskWidget.h"

class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QComboBox;

class CScanContainerWidget;

class ScanWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    ScanWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ScanWidget();

    virtual bool runTask();

  protected:

    virtual bool loadTask();

    virtual bool saveTask();

    //dummy, should not be used in this widget
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & /*type*/) {return NULL;};

    CScanContainerWidget* scrollview;

    QPushButton* buttonNewItem;
    QComboBox* comboType;

    QGridLayout* ScanWidgetLayout;
    QHBoxLayout* Layout24;

  protected slots:
    bool slotAddItem();
  };

#endif
