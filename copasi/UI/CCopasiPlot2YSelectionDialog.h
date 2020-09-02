// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CCopasiPlot2YSelectionDialog_H__
#define CCopasiPlot2YSelectionDialog_H__

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

class CCopasiPlot2YSelectionDialog: public QDialog
{
  Q_OBJECT

public:
  CCopasiPlot2YSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = false, Qt::WindowFlags f = Qt::WindowFlags());
  ~CCopasiPlot2YSelectionDialog();
  void setOutputVectors(std::vector< const CDataObject * > *outputVector1,
                        std::vector< const CDataObject * > * outputVector2,
                        std::vector< const CDataObject * > * outputVector3);
  void setModel(CModel *model,
                const CQSimpleSelectionTree::ObjectClasses &classes);

  void setXLabel(const QString & label);
  void setYLabel(const QString & label);
  void setY2Label(const QString & label);

  void setSingleSelectionX(bool isSingleSelection);
  void setSingleSelectionY(bool isSingleSelection);
  void setSingleSelectionY2(bool isSingleSelection);


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
  CCopasiSelectionWidget * mpY2AxisSelectionWidget;
  QSplitter *mpSplitter;
  QSplitter * mpSplitter2;
  QHBoxLayout *mpButtonBox;
  QVBoxLayout *mpMainLayout;
  QLabel *mpXAxisLabel;
  QLabel *mpYAxisLabel;
  QLabel * mpY2AxisLabel;
  QWidget *mpXAxisSelectionBox;
  QWidget *mpYAxisSelectionBox;
  QWidget * mpY2AxisSelectionBox;
  std::vector< const CDataObject * > *mpXAxisOutputVector;
  std::vector< const CDataObject * > *mpYAxisOutputVector;
  std::vector< const CDataObject * > * mpY2AxisOutputVector;
};

#endif // CCopasiPlot2YSelectionDialog_H__
