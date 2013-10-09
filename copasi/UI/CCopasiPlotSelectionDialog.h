// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCopasiPlotSelectionDialog_H__
#define CCopasiPlotSelectionDialog_H__

#include <vector>

#include <QtGui/QDialog>
#include <QtGui/QLabel>

#include "UI/CQSimpleSelectionTree.h"

class QWidget;
class QPushButton;
class QSplitter;
class QCheckBox;
class QHBoxLayout;
class QVBoxLayout;
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
                const CQSimpleSelectionTree::ObjectClasses & classes);

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
  QHBoxLayout* mpButtonBox;
  QVBoxLayout* mpMainLayout;
  QLabel* mpXAxisLabel;
  QLabel* mpYAxisLabel;
  QWidget* mpXAxisSelectionBox;
  QWidget* mpYAxisSelectionBox;
  std::vector< const CCopasiObject * > * mpXAxisOutputVector;
  std::vector< const CCopasiObject * > * mpYAxisOutputVector;
};

#endif // CPlotSelectionDialog_H__
