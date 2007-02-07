// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMCAWidget.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/07 20:49:58 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMCAWidget.ui'
 **
 ** Created: Wed Feb 7 14:54:17 2007
 **      by: The User Interface Compiler ($Id: CQMCAWidget.h,v 1.1.2.1 2007/02/07 20:49:58 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQMCAWIDGET_H
#define CQMCAWIDGET_H

#include <qvariant.h>
#include "TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QCheckBox;
class QFrame;

class CQMCAWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQMCAWidget(QWidget* parent = 0, const char* name = 0);
    ~CQMCAWidget();

    QCheckBox* mpCheckSteadyState;
    QFrame* mpLine;

    virtual bool runTask();

  public slots:
    virtual void slotSteadyStateChecked();

  protected:
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);
    virtual bool loadTask();
    virtual bool saveTask();

    QVBoxLayout* CQMCAWidgetLayout;
    QGridLayout* mpGridLayout;
    QSpacerItem* mpSacer;

  protected slots:
    virtual void languageChange();

  private:
    void init();
    bool loadParameterTable();
    bool saveParameterTable();
  };

#endif // CQMCAWIDGET_H
