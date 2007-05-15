// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/01/12 14:07:01 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTSSAResultSubWidget.ui'
 **
 ** Created: Tue May 15 09:22:44 2007
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQTSSARESULTSUBWIDGET_H
#define CQTSSARESULTSUBWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>
#include "copasi.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CTimeSeriesTable;
class QComboBox;
class QPushButton;
class QTabWidget;
class QTextEdit;

class CQTSSAResultSubWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQTSSAResultSubWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQTSSAResultSubWidget();

    QComboBox* comboBox;
    QPushButton* ButtonSaveData;
    QTabWidget* tabWidget2;
    QWidget* tab;
    QTextEdit* optimizationResultText;
    QWidget* tab_2;
    CTimeSeriesTable* dataTable;

    void displayOptimizationTab(bool displayOptTab);
    bool clear();

  public slots:
    virtual CTimeSeriesTable * table();

  protected:
    QVBoxLayout* CQTSSAResultSubWidgetLayout;
    QHBoxLayout* toplayout;
    QSpacerItem* spacer;
    QVBoxLayout* tabLayout;
    QVBoxLayout* tabLayout_2;

  protected slots:
    virtual void languageChange();

    void saveDataToFile();
    void toggleView();
    virtual void init();

  private:
    QPixmap image0;
  };

#endif // CQTSSARESULTSUBWIDGET_H
