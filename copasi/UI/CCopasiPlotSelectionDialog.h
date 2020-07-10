// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QDialog>
#include <QLabel>

#include "copasi/UI/CQSimpleSelectionTree.h"

class QWidget;
class QPushButton;
class QSplitter;
class QCheckBox;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class CDataObject;
class CModel;
class CCopasiSelectionWidget;

class CCopasiPlotSelectionDialog: public QDialog
{
  Q_OBJECT

public:
  CCopasiPlotSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = false, Qt::WindowFlags f = Qt::WindowFlags());
  ~CCopasiPlotSelectionDialog();
  void setOutputVectors(std::vector< const CDataObject * > *outputVector1,
                        std::vector< const CDataObject * > *outputVector2);
  void setModel(CModel *model,
                const CQSimpleSelectionTree::ObjectClasses &classes);

protected slots:
  void slotOKButtonClicked();
  void slotCancelButtonClicked();
  void slotExpertCheckBoxToggled(bool checked);

protected:
  void setTabOrder();

protected:
  QCheckBox *mpExpertCheckBox;
  CCopasiSelectionWidget *mpXAxisSelectionWidget;
  CCopasiSelectionWidget *mpYAxisSelectionWidget;
  QSplitter *mpSplitter;
  QHBoxLayout *mpButtonBox;
  QVBoxLayout *mpMainLayout;
  QLabel *mpXAxisLabel;
  QLabel *mpYAxisLabel;
  QWidget *mpXAxisSelectionBox;
  QWidget *mpYAxisSelectionBox;
  std::vector< const CDataObject * > *mpXAxisOutputVector;
  std::vector< const CDataObject * > *mpYAxisOutputVector;
};

#endif // CPlotSelectionDialog_H__
