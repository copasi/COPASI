/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQEFMWidget.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 06:57:33 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQEFMWidget.ui'
 **
 ** Created: Wed Aug 30 12:09:12 2006
 **      by: The User Interface Compiler ($Id: CQEFMWidget.h,v 1.2 2006/10/15 06:57:33 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQEFMWIDGET_H
#define CQEFMWIDGET_H

#include <qvariant.h>
#include "CopasiUI/TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLabel;
class QLineEdit;
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
    QListView* mpListView;

    virtual bool runTask();
    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

  protected:
    QVBoxLayout* CQEFMWidgetLayout;
    QHBoxLayout* mpLayoutFluxModes;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();

  private:
    void init();
    void destroy();
    void loadFluxModes();
  };

#endif // CQEFMWIDGET_H
