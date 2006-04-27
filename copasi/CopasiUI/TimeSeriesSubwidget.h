/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TimeSeriesSubwidget.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:46 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'TimeSeriesSubwidget.ui'
 **
 ** Created: Mon Oct 24 12:45:56 2005
 **      by: The User Interface Compiler ($Id: TimeSeriesSubwidget.h,v 1.9 2006/04/27 01:27:46 shoops Exp $)
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
class QComboBox;
class QPushButton;
class QTabWidget;
class QTextEdit;

class TimeSeriesSubWidget : public QWidget
  {
    Q_OBJECT

  public:
    TimeSeriesSubWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TimeSeriesSubWidget();

    QComboBox* comboBox;
    QPushButton* ButtonSaveData;
    QTabWidget* tabWidget2;
    QWidget* tab;
    QTextEdit* optimizationResultText;
    QWidget* tab_2;
    CTimeSeriesTable* dataTable;

    bool clear();
    void displayOptimizationTab(bool displayOptTab);

  public slots:
    virtual CTimeSeriesTable * table();

  protected:
    QVBoxLayout* TimeSeriesSubWidgetLayout;
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

#endif // TIMESERIESSUBWIDGET_H
