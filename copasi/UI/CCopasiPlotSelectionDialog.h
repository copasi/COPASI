// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CCopasiPlotSelectionDialog.h,v $
//   $Revision: 1.8.4.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/10/25 16:12:45 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CCopasiPlotSelectionDialog_H__
#define CCopasiPlotSelectionDialog_H__

#include <vector>

#include <qdialog.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "UI/CCopasiSimpleSelectionTree.h"

class QWidget;
class QPushButton;
class QSplitter;
class QCheckBox;
class Q3VBox;
class Q3HBoxLayout;
class Q3VBoxLayout;
class QLabel;
class CCopasiObject;
class CModel;
class CCopasiSelectionWidget;

class CCopasiPlotSelectionDialog: public QDialog
{
  Q_OBJECT

public:
  CCopasiPlotSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = false, Qt::WFlags f = 0);
  ~CCopasiPlotSelectionDialog();
  void setOutputVectors(std::vector< const CCopasiObject * > * outputVector1,
                        std::vector< const CCopasiObject * > * outputVector2);
  void setModel(CModel* model,
                const CCopasiSimpleSelectionTree::ObjectClasses & classes);

protected slots:
  void slotOKButtonClicked();
  void slotCancelButtonClicked();
  void slotExpertCheckBoxToggled(bool checked);

protected:
  void setTabOrder();

protected:
  QPushButton* mpOKButton;
  QPushButton* mpCancelButton;
  QCheckBox* mpExpertCheckBox;
  CCopasiSelectionWidget* mpXAxisSelectionWidget;
  CCopasiSelectionWidget* mpYAxisSelectionWidget;
  QSplitter* mpSplitter;
  Q3HBoxLayout* mpButtonBox;
  Q3VBoxLayout* mpMainLayout;
  QLabel* mpXAxisLabel;
  QLabel* mpYAxisLabel;
  Q3VBox* mpXAxisSelectionBox;
  Q3VBox* mpYAxisSelectionBox;
  std::vector< const CCopasiObject * > * mpXAxisOutputVector;
  std::vector< const CCopasiObject * > * mpYAxisOutputVector;
};

#endif // CPlotSelectionDialog_H__
