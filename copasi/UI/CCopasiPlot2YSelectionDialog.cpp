// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <QLayout>
#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>

#include "copasi/copasi.h"

#include "CCopasiPlot2YSelectionDialog.h"
#include "CCopasiSelectionWidget.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "copasi/model/CModel.h"
#include "copasi/core/CDataObject.h"
#include "copasi/resourcesUI/CQIconResource.h"

CCopasiPlot2YSelectionDialog::CCopasiPlot2YSelectionDialog(QWidget * parent, const char * name, bool modal, Qt::WindowFlags f)
  : QDialog(parent, f)
  , mpExpertCheckBox(NULL)
  , mpXAxisSelectionWidget(NULL)
  , mpYAxisSelectionWidget(NULL)
  , mpY2AxisSelectionWidget(NULL)
  , mpSplitter(NULL)
  , mpSplitter2(NULL)
  , mpButtonBox(NULL)
  , mpMainLayout(NULL)
  , mpXAxisLabel(NULL)
  , mpYAxisLabel(NULL)
  , mpY2AxisLabel(NULL)
  , mpXAxisSelectionBox(NULL)
  , mpYAxisSelectionBox(NULL)
  , mpY2AxisSelectionBox(NULL)
  , mpXAxisOutputVector(NULL)
  , mpYAxisOutputVector(NULL)
  , mpY2AxisOutputVector(NULL)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setMinimumHeight(480);

#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin

  mpMainLayout = new QVBoxLayout(this);
  mpSplitter = new QSplitter(this);
  mpSplitter->setOrientation(Qt::Horizontal);
  mpSplitter->setChildrenCollapsible(false);

  mpSplitter2 = new QSplitter(this);
  mpSplitter2->setOrientation(Qt::Horizontal);
  mpSplitter2->setChildrenCollapsible(false);

  mpMainLayout->addWidget(mpSplitter);
  mpButtonBox = new QHBoxLayout(this);
  mpMainLayout->addLayout(mpButtonBox);
  QDialogButtonBox * box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
  mpButtonBox->addWidget(box);
  mpExpertCheckBox = new QCheckBox(this);
  mpExpertCheckBox->setText("Expert Mode");
  mpExpertCheckBox->setChecked(false);
  mpButtonBox->addWidget(mpExpertCheckBox);

  mpXAxisSelectionBox = new QWidget(mpSplitter);
  QVBoxLayout * vBox1 = new QVBoxLayout(mpXAxisSelectionBox);
  mpXAxisSelectionBox->setLayout(vBox1);
  mpXAxisSelectionBox->layout()->setContentsMargins(0, 0, 0, 5);
  mpXAxisLabel = new QLabel("X-Axis:", mpXAxisSelectionBox);
  mpXAxisLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  mpXAxisSelectionBox->layout()->addWidget(mpXAxisLabel);
  mpXAxisSelectionWidget = new CCopasiSelectionWidget(mpXAxisSelectionBox);
  mpXAxisSelectionWidget->setSingleSelection(true);
  mpXAxisSelectionWidget->setOutputVector(mpXAxisOutputVector);
  mpXAxisSelectionBox->layout()->addWidget(mpXAxisSelectionWidget);

  mpYAxisSelectionBox = new QWidget(mpSplitter2);
  QVBoxLayout * vBox2 = new QVBoxLayout(mpYAxisSelectionBox);
  mpYAxisSelectionBox->setLayout(vBox2);
  mpYAxisSelectionBox->layout()->setContentsMargins(0, 0, 0, 5);
  mpYAxisLabel = new QLabel("Y-Axis:", mpYAxisSelectionBox);
  mpYAxisLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  mpYAxisSelectionBox->layout()->addWidget(mpYAxisLabel);
  mpYAxisSelectionWidget = new CCopasiSelectionWidget(mpYAxisSelectionBox);
  mpYAxisSelectionWidget->setSingleSelection(false);
  mpYAxisSelectionWidget->setOutputVector(mpYAxisOutputVector);
  mpYAxisSelectionBox->layout()->addWidget(mpYAxisSelectionWidget);

  mpY2AxisSelectionBox = new QWidget(mpSplitter2);
  QVBoxLayout * vBox3 = new QVBoxLayout(mpY2AxisSelectionBox);
  mpY2AxisSelectionBox->setLayout(vBox3);
  mpY2AxisSelectionBox->layout()->setContentsMargins(0, 0, 0, 5);
  mpY2AxisLabel = new QLabel("Y-Axis 2:", mpY2AxisSelectionBox);
  mpY2AxisLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  mpY2AxisSelectionBox->layout()->addWidget(mpY2AxisLabel);
  mpY2AxisSelectionWidget = new CCopasiSelectionWidget(mpY2AxisSelectionBox);
  mpY2AxisSelectionWidget->setSingleSelection(false);
  mpY2AxisSelectionWidget->setOutputVector(mpY2AxisOutputVector);
  mpY2AxisSelectionBox->layout()->addWidget(mpY2AxisSelectionWidget);

  mpSplitter->addWidget(mpSplitter2);

  connect(box, SIGNAL(accepted()), this, SLOT(slotOKButtonClicked()));
  connect(box, SIGNAL(rejected()), this, SLOT(slotCancelButtonClicked()));
  connect(mpExpertCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotExpertCheckBoxToggled(bool)));
  setTabOrder();
}

CCopasiPlot2YSelectionDialog::~CCopasiPlot2YSelectionDialog()
{}

void CCopasiPlot2YSelectionDialog::setTabOrder()
{
  QWidget::setTabOrder(this->mpExpertCheckBox, this->mpXAxisSelectionWidget);
  QWidget::setTabOrder(this->mpXAxisSelectionWidget, this->mpYAxisSelectionWidget);
  QWidget::setTabOrder(this->mpYAxisSelectionWidget, this->mpY2AxisSelectionWidget);
  this->mpXAxisSelectionWidget->setFocus();
}

void CCopasiPlot2YSelectionDialog::slotOKButtonClicked()
{
  // fill the selection vectors
  this->mpXAxisSelectionWidget->commit();
  this->mpYAxisSelectionWidget->commit();
  this->mpY2AxisSelectionWidget->commit();
  std::stringstream message;
  message << "You did not select anything for the ";
  bool showWarning = false;

  if (this->mpXAxisOutputVector->empty())
    {
      message << TO_UTF8(mpXAxisLabel->text());
      showWarning = true;
    }

  if (this->mpYAxisOutputVector->empty())
    {
      if (showWarning)
        {
          message << " and ";
        }

      showWarning = true;
      message << TO_UTF8(mpYAxisLabel->text());
    }

  if (this->mpY2AxisOutputVector->empty())
    {
      if (showWarning)
        {
          message << " and ";
        }

      showWarning = true;
      message << TO_UTF8(mpY2AxisLabel->text());
    }

  if (showWarning)
    {
      message << "!\nDo you want to proceed anyway?";

      if (CQMessageBox::question(this, "Empty Selection", FROM_UTF8(message.str()), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::No)
        {
          return;
        }
    }

  QDialog::done(QDialog::Accepted);
}

void CCopasiPlot2YSelectionDialog::slotCancelButtonClicked()
{
  QDialog::done(QDialog::Rejected);
}

void CCopasiPlot2YSelectionDialog::slotExpertCheckBoxToggled(bool checked)
{
  this->mpXAxisSelectionWidget->setExpertMode(checked);
  this->mpYAxisSelectionWidget->setExpertMode(checked);
  this->mpY2AxisSelectionWidget->setExpertMode(checked);
}

void CCopasiPlot2YSelectionDialog::setOutputVectors(std::vector< const CDataObject * > * outputVector1,
    std::vector< const CDataObject * > * outputVector2,
    std::vector< const CDataObject * > * outputVector3)
{
  this->mpXAxisOutputVector = outputVector1;
  this->mpXAxisSelectionWidget->setOutputVector(this->mpXAxisOutputVector);
  this->mpYAxisOutputVector = outputVector2;
  this->mpYAxisSelectionWidget->setOutputVector(this->mpYAxisOutputVector);
  this->mpY2AxisOutputVector = outputVector3;
  this->mpY2AxisSelectionWidget->setOutputVector(this->mpY2AxisOutputVector);
}

void CCopasiPlot2YSelectionDialog::setModel(CModel * pModel,
    const CQSimpleSelectionTree::ObjectClasses & classes)
{
  this->mpXAxisSelectionWidget->populateTree(pModel, classes);
  this->mpYAxisSelectionWidget->populateTree(pModel, classes);
  this->mpY2AxisSelectionWidget->populateTree(pModel, classes);
}

void CCopasiPlot2YSelectionDialog::setXLabel(const QString & label)
{
  if (mpXAxisLabel == NULL)
    return;

  mpXAxisLabel->setText(label);
}

void CCopasiPlot2YSelectionDialog::setYLabel(const QString & label)
{
  if (mpYAxisLabel == NULL)
    return;

  mpYAxisLabel->setText(label);
}

void CCopasiPlot2YSelectionDialog::setY2Label(const QString & label)
{
  if (mpY2AxisLabel == NULL)
    return;

  mpY2AxisLabel->setText(label);
}

void CCopasiPlot2YSelectionDialog::setSingleSelectionX(bool isSingleSelection)
{
  if (mpXAxisSelectionWidget == NULL)
    return;

  mpXAxisSelectionWidget->setSingleSelection(isSingleSelection);
}

void CCopasiPlot2YSelectionDialog::setSingleSelectionY(bool isSingleSelection)
{
  if (mpYAxisSelectionWidget == NULL)
    return;

  mpYAxisSelectionWidget->setSingleSelection(isSingleSelection);
}


void CCopasiPlot2YSelectionDialog::setSingleSelectionY2(bool isSingleSelection)
{
  if (mpY2AxisSelectionWidget == NULL)
    return;

  mpY2AxisSelectionWidget->setSingleSelection(isSingleSelection);
}
