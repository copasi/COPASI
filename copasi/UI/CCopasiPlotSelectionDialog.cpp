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

#include <QtGui/QLayout>
#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QCheckBox>
#include <QtGui/QLabel>
#include <QtGui/QSplitter>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QDialogButtonBox>

#include "copasi.h"

#include "CCopasiPlotSelectionDialog.h"
#include "CCopasiSelectionWidget.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "model/CModel.h"
#include "report/CCopasiObject.h"

CCopasiPlotSelectionDialog::CCopasiPlotSelectionDialog(QWidget* parent, const char* name, bool modal, Qt::WFlags f):
  QDialog(parent, f)
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
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  mpMainLayout = new QVBoxLayout(this);

  mpSplitter = new QSplitter(this);
  mpSplitter->setOrientation(Qt::Horizontal);
  mpMainLayout->addWidget(mpSplitter);

  mpButtonBox = new QHBoxLayout(this);
  mpMainLayout->addLayout(mpButtonBox);

  QDialogButtonBox* box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
  mpButtonBox->addWidget(box);

  mpExpertCheckBox = new QCheckBox(this);
  mpExpertCheckBox->setText("Expert Mode");
  mpExpertCheckBox->setChecked(false);
  mpButtonBox->addWidget(mpExpertCheckBox);

  mpXAxisSelectionBox = new QWidget(mpSplitter);
  QVBoxLayout *vBox1 = new QVBoxLayout(mpXAxisSelectionBox);
  mpXAxisSelectionBox->setLayout(vBox1);
  mpXAxisSelectionBox->layout()->setContentsMargins(5, 5, 5, 5);

  mpYAxisSelectionBox = new QWidget(mpSplitter);
  QVBoxLayout *vBox2 = new QVBoxLayout(mpYAxisSelectionBox);
  mpYAxisSelectionBox->setLayout(vBox2);
  mpYAxisSelectionBox->layout()->setContentsMargins(5, 5, 5, 5);

  mpXAxisLabel = new QLabel("X-Axis:", mpXAxisSelectionBox);
  mpXAxisLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  mpXAxisSelectionBox->layout()->addWidget(mpXAxisLabel);

  mpYAxisLabel = new QLabel("Y-Axis:", mpYAxisSelectionBox);
  mpYAxisLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  mpYAxisSelectionBox->layout()->addWidget(mpYAxisLabel);

  mpXAxisSelectionWidget = new CCopasiSelectionWidget(mpXAxisSelectionBox);
  mpXAxisSelectionWidget->setSingleSelection(true);
  mpXAxisSelectionWidget->setOutputVector(mpXAxisOutputVector);
  mpXAxisSelectionBox->layout()->addWidget(mpXAxisSelectionWidget);

  mpYAxisSelectionWidget = new CCopasiSelectionWidget(mpYAxisSelectionBox);
  mpYAxisSelectionWidget->setSingleSelection(false);
  mpYAxisSelectionWidget->setOutputVector(mpYAxisOutputVector);
  mpYAxisSelectionBox->layout()->addWidget(mpYAxisSelectionWidget);

  connect(box, SIGNAL(accepted()), this, SLOT(slotOKButtonClicked()));
  connect(box, SIGNAL(rejected()), this, SLOT(slotCancelButtonClicked()));
  connect(mpExpertCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotExpertCheckBoxToggled(bool)));

  setTabOrder();
}

CCopasiPlotSelectionDialog::~CCopasiPlotSelectionDialog()
{}

void CCopasiPlotSelectionDialog::setTabOrder()
{
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
      message = "You did not select anything for the " + message + "!\nDo you want to proceed anyway?";

      if (CQMessageBox::question(this, "Empty Selection", FROM_UTF8(message), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::No)
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
    const CQSimpleSelectionTree::ObjectClasses & classes)
{
  this->mpXAxisSelectionWidget->populateTree(pModel, classes);
  this->mpYAxisSelectionWidget->populateTree(pModel, classes);
}
