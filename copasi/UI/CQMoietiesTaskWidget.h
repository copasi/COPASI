// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMoietiesTaskWidget.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 00:32:59 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMoietiesTaskWidget.ui'
 **
 ** Created: Wed Feb 20 14:47:08 2008
 **      by: The User Interface Compiler ($Id: CQMoietiesTaskWidget.h,v 1.2 2008/03/12 00:32:59 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQMOIETIESTASKWIDGET_H
#define CQMOIETIESTASKWIDGET_H

#include <qvariant.h>
#include "TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;

class CQMoietiesTaskWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQMoietiesTaskWidget(QWidget* parent = 0, const char* name = 0);
    ~CQMoietiesTaskWidget();

    virtual bool runTask();
    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

  protected:
    QVBoxLayout* CQMoietiesTaskWidgetLayout;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();

  private:
    void init();
    void destroy();
  };

#endif // CQMOIETIESTASKWIDGET_H
