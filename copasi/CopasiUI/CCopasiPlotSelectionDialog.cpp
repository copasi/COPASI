/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CCopasiPlotSelectionDialog.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/12/10 20:49:31 $
   End CVS Header */

#include "CCopasiPlotSelectionDialog.h"
#include "CCopasiSelectionWidget.h"
#include "qwidget.h"
#include "qpushbutton.h"
#include "qcheckbox.h"
#include "qlabel.h"
#include "qsplitter.h"
#include "qhbox.h"
#include "qvbox.h"
#include "model/CModel.h"
#include "report/CCopasiObject.h"
#include "copasi.h"
#include "qlayout.h"

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
  this->mpMainLayout = new QVBoxLayout(this);
  this->mpMainLayout->setAutoAdd(true);

  this->mpSplitter = new QSplitter(this);
  this->mpSplitter->setOrientation(Qt::Horizontal);

  this->mpButtonBox = new QHBox(this);
  this->mpButtonBox->layout()->setAutoAdd(false);

  ((QHBoxLayout*)this->mpButtonBox->layout())->addStretch();

  this->mpOKButton = new QPushButton(this->mpButtonBox);
  this->mpOKButton->setText("OK");
  this->mpOKButton->setDefault(true);
  this->mpButtonBox->layout()->add(this->mpOKButton);

  this->mpCancelButton = new QPushButton(this->mpButtonBox);
  this->mpCancelButton->setText("Cancel");
  this->mpButtonBox->layout()->add(this->mpCancelButton);

  this->mpExpertCheckBox = new QCheckBox(this->mpButtonBox);
  this->mpExpertCheckBox->setText("Expert Mode");
  this->mpExpertCheckBox->setChecked(false);
  this->mpButtonBox->layout()->add(this->mpExpertCheckBox);

  ((QHBoxLayout*)this->mpButtonBox->layout())->addStretch();

  this->mpXAxisSelectionBox = new QVBox(this->mpSplitter);
  this->mpXAxisSelectionBox->layout()->setMargin(5);
  this->mpXAxisSelectionBox->layout()->setAutoAdd(false);

  this->mpYAxisSelectionBox = new QVBox(this->mpSplitter);
  this->mpYAxisSelectionBox->layout()->setMargin(5);
  this->mpYAxisSelectionBox->layout()->setAutoAdd(false);

  this->mpXAxisLabel = new QLabel("X-Axis:", this->mpXAxisSelectionBox);
  this->mpXAxisLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  this->mpXAxisSelectionBox->layout()->add(this->mpXAxisLabel);

  this->mpYAxisLabel = new QLabel("Y-Axis:", this->mpYAxisSelectionBox);
  this->mpYAxisLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  this->mpYAxisSelectionBox->layout()->add(this->mpYAxisLabel);

  this->mpXAxisSelectionWidget = new CCopasiSelectionWidget(this->mpXAxisSelectionBox);
  this->mpXAxisSelectionWidget->setSingleSelection(true);
  this->mpXAxisSelectionWidget->setOutputVector(this->mpXAxisOutputVector);
  this->mpXAxisSelectionBox->layout()->add(this->mpXAxisSelectionWidget);

  this->mpYAxisSelectionWidget = new CCopasiSelectionWidget(this->mpYAxisSelectionBox);
  this->mpYAxisSelectionWidget->setOutputVector(this->mpYAxisOutputVector);
  this->mpYAxisSelectionBox->layout()->add(this->mpYAxisSelectionWidget);

  connect(this->mpOKButton, SIGNAL(clicked()), this, SLOT(slotOKButtonClicked()));
  connect(this->mpCancelButton, SIGNAL(clicked()), this, SLOT(slotCancelButtonClicked()));
  connect(this->mpExpertCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotExpertCheckBoxToggled(bool)));

  this->setTabOrder();
}

CCopasiPlotSelectionDialog::~CCopasiPlotSelectionDialog()
{
  pdelete(this->mpOKButton);
  pdelete(this->mpCancelButton);
  pdelete(this->mpExpertCheckBox);
  pdelete(this->mpXAxisLabel);
  pdelete(this->mpYAxisLabel);
  pdelete(this->mpXAxisSelectionWidget);
  pdelete(this->mpYAxisSelectionWidget);
  pdelete(this->mpXAxisSelectionBox);
  pdelete(this->mpYAxisSelectionBox);
  pdelete(this->mpSplitter);
  pdelete(this->mpButtonBox);
  pdelete(this->mpMainLayout);
}

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

void CCopasiPlotSelectionDialog::setOutputVectors(std::vector<CCopasiObject*>* outputVector1, std::vector<CCopasiObject*>* outputVector2)
{
  this->mpXAxisOutputVector = outputVector1;
  this->mpXAxisSelectionWidget->setOutputVector(this->mpXAxisOutputVector);
  this->mpYAxisOutputVector = outputVector2;
  this->mpYAxisSelectionWidget->setOutputVector(this->mpYAxisOutputVector);
}

void CCopasiPlotSelectionDialog::setModel(CModel* model)
{
  this->mpXAxisSelectionWidget->populateTree(model);
  this->mpYAxisSelectionWidget->populateTree(model);
}
