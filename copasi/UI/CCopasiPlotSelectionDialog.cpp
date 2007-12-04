// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CCopasiPlotSelectionDialog.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/12/04 15:47:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qsplitter.h>
#include <qhbox.h>
#include <qvbox.h>

#include "copasi.h"

#include "CCopasiPlotSelectionDialog.h"
#include "CCopasiSelectionWidget.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "model/CModel.h"
#include "report/CCopasiObject.h"

CCopasiPlotSelectionDialog::CCopasiPlotSelectionDialog(QWidget* parent, const char* name, bool modal, WFlags f):
    QDialog(parent, name, modal, f)
    , mpOKButton(NULL)
    , mpCancelButton(NULL)
    , mpExpertCheckBox(NULL)
    , mpXAxisSelectionWidget(NULL)
    , mpYAxisSelectionWidget(NULL)
    , mpSplitter(NULL)
    , mpButtonBox(NULL)
    , mpMainLayout(NULL)
    , mpXAxisLabel(NULL)
    , mpYAxisLabel(NULL)
    , mpXAxisSelectionBox(NULL)
    , mpYAxisSelectionBox(NULL)
    , mpXAxisOutputVector(NULL)
    , mpYAxisOutputVector(NULL)
{
  mpMainLayout = new QVBoxLayout(this);

  mpSplitter = new QSplitter(this);
  mpSplitter->setOrientation(Qt::Horizontal);
  mpMainLayout->addWidget(mpSplitter);

  mpButtonBox = new QHBoxLayout(mpMainLayout);

  mpOKButton = new QPushButton(this);
  mpOKButton->setText("OK");
  mpOKButton->setDefault(true);
  mpButtonBox->add(mpOKButton);

  mpCancelButton = new QPushButton(this);
  mpCancelButton->setText("Cancel");
  mpButtonBox->add(mpCancelButton);

  mpExpertCheckBox = new QCheckBox(this);
  mpExpertCheckBox->setText("Expert Mode");
  mpExpertCheckBox->setChecked(false);
  mpButtonBox->add(mpExpertCheckBox);

  mpXAxisSelectionBox = new QVBox(mpSplitter);
  mpXAxisSelectionBox->layout()->setMargin(5);
  mpXAxisSelectionBox->layout()->setAutoAdd(false);

  mpYAxisSelectionBox = new QVBox(mpSplitter);
  mpYAxisSelectionBox->layout()->setMargin(5);
  mpYAxisSelectionBox->layout()->setAutoAdd(false);

  mpXAxisLabel = new QLabel("X-Axis:", mpXAxisSelectionBox);
  mpXAxisLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  mpXAxisSelectionBox->layout()->add(mpXAxisLabel);

  mpYAxisLabel = new QLabel("Y-Axis:", mpYAxisSelectionBox);
  mpYAxisLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  mpYAxisSelectionBox->layout()->add(mpYAxisLabel);

  mpXAxisSelectionWidget = new CCopasiSelectionWidget(mpXAxisSelectionBox);
  mpXAxisSelectionWidget->setSingleSelection(true);
  mpXAxisSelectionWidget->setOutputVector(mpXAxisOutputVector);
  mpXAxisSelectionBox->layout()->add(mpXAxisSelectionWidget);

  mpYAxisSelectionWidget = new CCopasiSelectionWidget(mpYAxisSelectionBox);
  mpYAxisSelectionWidget->setSingleSelection(false);
  mpYAxisSelectionWidget->setOutputVector(mpYAxisOutputVector);
  mpYAxisSelectionBox->layout()->add(mpYAxisSelectionWidget);

  connect(mpOKButton, SIGNAL(clicked()), this, SLOT(slotOKButtonClicked()));
  connect(mpCancelButton, SIGNAL(clicked()), this, SLOT(slotCancelButtonClicked()));
  connect(mpExpertCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotExpertCheckBoxToggled(bool)));

  setTabOrder();
}

CCopasiPlotSelectionDialog::~CCopasiPlotSelectionDialog()
{}

void CCopasiPlotSelectionDialog::setTabOrder()
{
  QWidget::setTabOrder(this->mpOKButton, this->mpCancelButton);
  QWidget::setTabOrder(this->mpCancelButton, this->mpExpertCheckBox);
  QWidget::setTabOrder(this->mpExpertCheckBox, this->mpXAxisSelectionWidget);
  QWidget::setTabOrder(this->mpXAxisSelectionWidget, this->mpYAxisSelectionWidget);
  this->mpXAxisSelectionWidget->setFocus();
}

void CCopasiPlotSelectionDialog::slotOKButtonClicked()
{
  // fill the selection vectors
  this->mpXAxisSelectionWidget->commit();
  this->mpYAxisSelectionWidget->commit();
  std::string message = "";
  bool showWarning = false;
  if (this->mpXAxisOutputVector->empty())
    {
      message += "X Axis";
      showWarning = true;
    }
  if (this->mpYAxisOutputVector->empty())
    {
      if (showWarning)
        {
          message += " and ";
        }
      showWarning = true;
      message += "Y Axis";
    }
  if (showWarning)
    {
      message = "You did not select anything for the " + message + "!\nDo you want to procceed anyway?";
      if (CQMessageBox::question(this, "Empty Selection", FROM_UTF8(message), QMessageBox::Yes | QMessageBox::Default, QMessageBox::No | QMessageBox::Escape) == QMessageBox::No)
        {
          return;
        }
    }
  QDialog::done(QDialog::Accepted);
}

void CCopasiPlotSelectionDialog::slotCancelButtonClicked()
{
  QDialog::done(QDialog::Rejected);
}

void CCopasiPlotSelectionDialog::slotExpertCheckBoxToggled(bool checked)
{
  this->mpXAxisSelectionWidget->setExpertMode(checked);
  this->mpYAxisSelectionWidget->setExpertMode(checked);
}

void CCopasiPlotSelectionDialog::setOutputVectors(std::vector< const CCopasiObject * > * outputVector1,
    std::vector< const CCopasiObject * > * outputVector2)
{
  this->mpXAxisOutputVector = outputVector1;
  this->mpXAxisSelectionWidget->setOutputVector(this->mpXAxisOutputVector);
  this->mpYAxisOutputVector = outputVector2;
  this->mpYAxisSelectionWidget->setOutputVector(this->mpYAxisOutputVector);
}

void CCopasiPlotSelectionDialog::setModel(CModel* pModel,
    const CCopasiSimpleSelectionTree::SelectionFlag & flag)
{
  this->mpXAxisSelectionWidget->populateTree(pModel, flag);
  this->mpYAxisSelectionWidget->populateTree(pModel, flag);
}
