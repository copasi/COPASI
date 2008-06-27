// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 01:53:45 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'TimeSeriesSubwidget.ui'
 **
 ** Created: Fri Jun 27 10:19:46 2008
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef TIMESERIESSUBWIDGET_H
#define TIMESERIESSUBWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>
#include "copasi.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CTimeSeriesTable;
class QTabWidget;
class QTextEdit;
class QPushButton;

class TimeSeriesSubWidget : public QWidget
  {
    Q_OBJECT

  public:
    TimeSeriesSubWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TimeSeriesSubWidget();

    QTabWidget* tabWidget2;
    QWidget* tab;
    QTextEdit* optimizationResultText;
    QWidget* tab_2;
    CTimeSeriesTable* dataTable;
    QPushButton* ButtonSaveData;
    QPushButton* mpBtnPrintAsImage;

    void displayOptimizationTab(bool displayOptTab);
    void setFramework(const int & framework);

  public slots:
    virtual CTimeSeriesTable * table();

  protected:
    QVBoxLayout* TimeSeriesSubWidgetLayout;
    QVBoxLayout* tabLayout;
    QHBoxLayout* layout16;
    QSpacerItem* spacer;

  protected slots:
    virtual void languageChange();

    void saveDataToFile();
    virtual void init();
    void printTableAsImage();

  private:
    int mFramework;

    QPixmap image0;
  };

#endif // TIMESERIESSUBWIDGET_H
