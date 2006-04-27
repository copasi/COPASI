/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQTaskHeaderWidget.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:42 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTaskHeaderWidget.ui'
 **
 ** Created: Mon Oct 24 11:02:10 2005
 **      by: The User Interface Compiler ($Id: CQTaskHeaderWidget.h,v 1.7 2006/04/27 01:27:42 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQTASKHEADERWIDGET_H
#define CQTASKHEADERWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include <string>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QCheckBox;
class CCopasiTask;

class CQTaskHeaderWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQTaskHeaderWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQTaskHeaderWidget();

    QLabel* mpLblName;
    QCheckBox* mpUpdateModel;
    QCheckBox* mpBoxExecutable;

    bool setTaskName(const std::string & name);
    void saved();

  protected:
    bool mExecutableChanged;
    bool mUpdateChanged;
    QColor mSavedColor;
    QColor mChangedColor;

    QHBoxLayout* CQTaskHeaderWidgetLayout;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();

    void slotUpdate();
    void slotExecutable();

  private:
    void init();
  };

#endif // CQTASKHEADERWIDGET_H
