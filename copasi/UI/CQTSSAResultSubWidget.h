// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/04/11 15:21:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTSSAResultSubWidget.ui'
 **
 ** Created: Fri Mar 20 15:33:58 2009
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQTSSARESULTSUBWIDGET_H
#define CQTSSARESULTSUBWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CTimeSeriesTable;
class CQArrayAnnotationsWidget;
class QComboBox;
class QPushButton;
class QTabWidget;
class QTextEdit;
class QSlider;
class QLabel;

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
  QWidget* TabPage_ILDM;
  QSlider* mSlider;
  QLabel* mLabel7;
  QLabel* pLabel1;
  QLabel* mLabel2;
  QLabel* mLabel3;
  QLabel* mLabel4;
  QLabel* mLabel5;
  QLabel* mLabel6;
  QTabWidget* mTabWidget;
  QWidget* tab_3;
  CQArrayAnnotationsWidget* pArrayWidget;
  QWidget* tab_4;
  CQArrayAnnotationsWidget* pArrayWidget2;
  QWidget* TabPage;
  CQArrayAnnotationsWidget* pArrayWidget3;
  QWidget* TabPage_2;
  CQArrayAnnotationsWidget* pArrayWidget4;
  QWidget* TabPage_3;
  CQArrayAnnotationsWidget* pArrayWidget_3_2;
  QWidget* TabPage_4;
  CQArrayAnnotationsWidget* pArrayWidgetTMP1;
  QWidget* TabPage_5;
  CQArrayAnnotationsWidget* pArrayWidgetTMP2;
  QWidget* TabPage_6;
  CQArrayAnnotationsWidget* pArrayWidgetTMP3;
  QWidget* TabPage_ILDMM;
  QLabel* pLabel1_6;
  QLabel* mLabel6_6;
  QLabel* mLabel4_6;
  QLabel* mLabel2_6;
  QLabel* mLabel3_6;
  QLabel* mLabel5_6;
  QSlider* mSlider_4;
  QTabWidget* mTabWidget_4;
  QWidget* tab_5;
  CQArrayAnnotationsWidget* pArrayWidget_5;
  QWidget* tab_6;
  CQArrayAnnotationsWidget* pArrayWidget2_5;
  QWidget* TabPage_7;
  CQArrayAnnotationsWidget* pArrayWidget3_5;
  QWidget* TabPage_8;
  CQArrayAnnotationsWidget* pArrayWidget4_5;
  QWidget* TabPage_CSP;
  QTabWidget* mTabWidget_3;
  QWidget* tab_7;
  CQArrayAnnotationsWidget* pArrayWidget_3;
  QWidget* tab_8;
  CQArrayAnnotationsWidget* pArrayWidget2_3;
  QWidget* TabPage_9;
  CQArrayAnnotationsWidget* pArrayWidget3_3;
  QWidget* TabPage_10;
  CQArrayAnnotationsWidget* pArrayWidget4_3;
  QWidget* TabPage_11;
  CQArrayAnnotationsWidget* pArrayWidgetNPIr;
  QWidget* TabPage_12;
  CQArrayAnnotationsWidget* pArrayWidgetNPIc;
  QWidget* TabPage_13;
  CQArrayAnnotationsWidget* pArrayWidget4_3_2;
  QWidget* TabPage_14;
  CQArrayAnnotationsWidget* pArrayWidgetNIIr;
  QLabel* pLabel1_3;
  QLabel* mLabel2_3;
  QLabel* mLabel3_3;
  QLabel* mLabel4_3;
  QLabel* mLabel5_3;
  QLabel* mLabel6_3;
  QSlider* mSlider_3;

  void displayOptimizationTab(bool displayOptTab);
  void setStepNumber();
  void discardOldResults();
  void setStepSelectionDisabled(bool set);
  void activateTab(int tab);
  void changeToCSP();
  void changeToILDM();
  virtual void changeToILDMModified();
  void displayCSPDevelopment(bool displayCSPTab);

public slots:
  virtual CTimeSeriesTable * table();
  void changeILDMInterval();
  void changeCSPInterval();
  void hideButtons();
  virtual void changeILDMModifiedInterval();

protected:
  QGridLayout* CQTSSAResultSubWidgetLayout;
  QHBoxLayout* toplayout;
  QSpacerItem* spacer;
  QVBoxLayout* tabLayout;
  QVBoxLayout* tabLayout_2;
  QGridLayout* TabPage_ILDMLayout;
  QSpacerItem* mSpacer;
  QGridLayout* tabLayout_3;
  QGridLayout* tabLayout_4;
  QGridLayout* TabPageLayout;
  QGridLayout* TabPageLayout_2;
  QGridLayout* TabPageLayout_3;
  QGridLayout* TabPageLayout_4;
  QGridLayout* TabPageLayout_5;
  QGridLayout* TabPageLayout_6;
  QGridLayout* TabPage_ILDMMLayout;
  QSpacerItem* mSpacer_6;
  QGridLayout* tabLayout_5;
  QGridLayout* tabLayout_6;
  QGridLayout* TabPageLayout_7;
  QGridLayout* TabPageLayout_8;
  QGridLayout* TabPage_CSPLayout;
  QSpacerItem* mSpacer_3;
  QGridLayout* tabLayout_7;
  QGridLayout* tabLayout_8;
  QGridLayout* TabPageLayout_9;
  QGridLayout* TabPageLayout_10;
  QGridLayout* TabPageLayout_11;
  QGridLayout* TabPageLayout_12;
  QGridLayout* TabPageLayout_13;
  QGridLayout* TabPageLayout_14;

protected slots:
  virtual void languageChange();

  void saveDataToFile();
  void toggleView();
  virtual void init();

private:
  QPixmap image0;
};

#endif // CQTSSARESULTSUBWIDGET_H
