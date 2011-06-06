/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CReportDefinitionSelect.h,v $
 $Revision: 1.21 $
 $Name:  $
 $Author: aekamal $
 $Date: 2011/06/06 16:14:08 $
 End CVS Header */

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description:
Date: 08/15
Comment : CReportDefinitionSelect to select the report definition for one task
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef CREPORTDEFINITIONSELECT_H
#define CREPORTDEFINITIONSELECT_H

#include <QVariant>
#include <QDialog>
#include <QVBoxLayout>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "UI/CopasiFileDialog.h"

class QPushButton;
class QComboBox;
class QLineEdit;
class QCheckBox;
class ListViews;
class CReport;

class CReportDefinitionSelect : public QDialog
{
  Q_OBJECT

public:
  CReportDefinitionSelect(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CReportDefinitionSelect();
  ListViews* pListView;

  void setReport(CReport* newReport);
  CReport* mpReport;

  void cleanup();
  void loadReportDefinitionVector();

  QPushButton* confirmButton;
  QPushButton* cancelButton;
  QFrame* frame5;
  QLabel* reportLabel;
  QComboBox* reportDefinitionNameList;
  QLineEdit* targetEdit;
  QLabel* targetLabel;
  QCheckBox* appendChecked;
  QPushButton* jumpButton;
  QPushButton* browseButton;

protected:
  QGridLayout* CReportDefinitionSelectLayout;
  QGridLayout* frame5Layout;

protected slots:
  void cancelClicked();
  void confirmClicked();
  void jumpToReportDefinitionEdit();
  void jumpToFileBrowser();

  // defined for cancel before showing
private:
  bool bShow;
public slots:
  int exec();
};

#endif // CREPORTDEFINITIONSELECT_H
