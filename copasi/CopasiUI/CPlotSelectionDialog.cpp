/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CPlotSelectionDialog.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/11/18 15:36:01 $
   End CVS Header */

#include "CPlotSelectionDialog.h"
#include "qwidget.h"
#include "qpushbutton.h"
#include "qcheckbox.h"
#include "qlabel.h"
#include "qsplitter.h"
#include "SimpleSelectionWidget.h"
#include "ObjectBrowserWidget.h"
#include "qhbox.h"
#include "qvbox.h"
#include "model/CModel.h"
#include "report/CCopasiObject.h"
#include "copasi.h"
#include "qlayout.h"

CPlotSelectionDialog::CPlotSelectionDialog(QWidget* parent, const char* name, bool modal, WFlags f):
    QDialog(parent, name, modal, f)
    , mpOKButton(NULL)
    , mpCancelButton(NULL)
    , mpExpertCheckBox(NULL)
    , mpXAxisSimpleSelectionWidget(NULL)
    , mpYAxisSimpleSelectionWidget(NULL)
    , mpXAxisObjectBrowserWidget(NULL)
    , mpYAxisObjectBrowserWidget(NULL)
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
    , mpXAxisTmpVector(new std::vector<CCopasiObject*>())
    , mpYAxisTmpVector(new std::vector<CCopasiObject*>())
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

  this->mpXAxisSimpleSelectionWidget = new SimpleSelectionWidget(this->mpXAxisSelectionBox);
  this->mpXAxisSelectionWidget = this->mpXAxisSimpleSelectionWidget;
  this->mpXAxisSimpleSelectionWidget->setSingleSelection(true);
  this->mpXAxisSimpleSelectionWidget->setOutputVector(this->mpXAxisTmpVector);
  this->mpXAxisSelectionBox->layout()->add(this->mpXAxisSelectionWidget);

  this->mpYAxisSimpleSelectionWidget = new SimpleSelectionWidget(this->mpYAxisSelectionBox);
  this->mpYAxisSelectionWidget = this->mpYAxisSimpleSelectionWidget;
  this->mpYAxisSimpleSelectionWidget->setOutputVector(this->mpYAxisTmpVector);
  this->mpYAxisSelectionBox->layout()->add(this->mpYAxisSelectionWidget);

  connect(this->mpOKButton, SIGNAL(clicked()), this, SLOT(slotOKButtonClicked()));
  connect(this->mpCancelButton, SIGNAL(clicked()), this, SLOT(slotCancelButtonClicked()));
  connect(this->mpExpertCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotExpertCheckBoxToggled(bool)));

  this->setTabOrder();
}

CPlotSelectionDialog::~CPlotSelectionDialog()
{
  pdelete(this->mpOKButton);
  pdelete(this->mpCancelButton);
  pdelete(this->mpExpertCheckBox);
  pdelete(this->mpXAxisLabel);
  pdelete(this->mpYAxisLabel);
  pdelete(this->mpXAxisSimpleSelectionWidget);
  pdelete(this->mpYAxisSimpleSelectionWidget);
  pdelete(this->mpXAxisObjectBrowserWidget);
  pdelete(this->mpYAxisObjectBrowserWidget);
  pdelete(this->mpXAxisSelectionBox);
  pdelete(this->mpYAxisSelectionBox);
  pdelete(this->mpSplitter);
  pdelete(this->mpButtonBox);
  pdelete(this->mpMainLayout);
  pdelete(this->mpXAxisTmpVector);
  pdelete(this->mpYAxisTmpVector);
}

void CPlotSelectionDialog::setTabOrder()
{
  QWidget::setTabOrder(this->mpOKButton, this->mpCancelButton);
  QWidget::setTabOrder(this->mpCancelButton, this->mpExpertCheckBox);
  QWidget::setTabOrder(this->mpExpertCheckBox, this->mpXAxisSelectionWidget);
  QWidget::setTabOrder(this->mpXAxisSelectionWidget, this->mpYAxisSelectionWidget);
  this->mpXAxisSelectionWidget->setFocus();
}

void CPlotSelectionDialog::slotOKButtonClicked()
{
  // fill the selection vectors
  if (this->mpXAxisOutputVector)
    {
      if (this->mpExpertCheckBox->isChecked())
        {
          this->mpXAxisTmpVector->clear();
          this->mpXAxisObjectBrowserWidget->commitClicked();
        }
      else
        {
          if (this->mpXAxisSimpleSelectionWidget->isSingleSelection())
            {
              this->mpXAxisTmpVector->clear();
              this->mpXAxisSimpleSelectionWidget->addButtonClicked();
            }
        }
      unsigned int counter;
      unsigned int maxCount = this->mpXAxisTmpVector->size();
      this->mpXAxisOutputVector->clear();
      for (counter = 0; counter < maxCount;++counter)
        {
          this->mpXAxisOutputVector->push_back(this->mpXAxisTmpVector->at(counter));
        }
    }
  if (this->mpYAxisOutputVector)
    {
      if (this->mpExpertCheckBox->isChecked())
        {
          this->mpYAxisTmpVector->clear();
          this->mpYAxisObjectBrowserWidget->commitClicked();
        }
      else
        {
          if (this->mpYAxisSimpleSelectionWidget->isSingleSelection())
            {
              this->mpYAxisTmpVector->clear();
              this->mpYAxisSimpleSelectionWidget->addButtonClicked();
            }
        }
      unsigned int counter;
      unsigned int maxCount = this->mpYAxisTmpVector->size();
      this->mpYAxisOutputVector->clear();
      for (counter = 0; counter < maxCount;++counter)
        {
          this->mpYAxisOutputVector->push_back(this->mpYAxisTmpVector->at(counter));
        }
    }
  QDialog::done(QDialog::Accepted);
}

void CPlotSelectionDialog::slotCancelButtonClicked()
{
  QDialog::done(QDialog::Rejected);
}

void CPlotSelectionDialog::slotExpertCheckBoxToggled(bool checked)
{
  this->mpXAxisSelectionWidget->hide();
  this->mpYAxisSelectionWidget->hide();
  this->mpXAxisSelectionBox->layout()->remove(this->mpXAxisSelectionWidget);
  this->mpYAxisSelectionBox->layout()->remove(this->mpYAxisSelectionWidget);
  if (checked)
    {
      if (!this->mpXAxisObjectBrowserWidget)
        {
          // create ObjectBrowserWidget objects
          this->mpXAxisObjectBrowserWidget = new ObjectBrowserWidget(this->mpXAxisSelectionBox);
          this->mpYAxisObjectBrowserWidget = new ObjectBrowserWidget(this->mpYAxisSelectionBox);
        }
      this->mpXAxisSelectionWidget = this->mpXAxisObjectBrowserWidget;
      this->mpYAxisSelectionWidget = this->mpYAxisObjectBrowserWidget;
    }

  else
    {
      this->mpXAxisSelectionWidget = this->mpXAxisSimpleSelectionWidget;
      this->mpYAxisSelectionWidget = this->mpYAxisSimpleSelectionWidget;
    }
  this->mpXAxisSelectionBox->layout()->add(this->mpXAxisSelectionWidget);
  this->mpYAxisSelectionBox->layout()->add(this->mpYAxisSelectionWidget);
  this->mpXAxisSelectionWidget->show();
  this->mpYAxisSelectionWidget->show();
  this->setTabOrder();
}

void CPlotSelectionDialog::setOutputVectors(std::vector<CCopasiObject*>* outputVector1, std::vector<CCopasiObject*>* outputVector2)
{
  this->mpXAxisOutputVector = outputVector1;
  this->mpYAxisOutputVector = outputVector2;
}

void CPlotSelectionDialog::setModel(CModel* model)
{
  this->mpXAxisSimpleSelectionWidget->populateTree(model);
  this->mpYAxisSimpleSelectionWidget->populateTree(model);
}
