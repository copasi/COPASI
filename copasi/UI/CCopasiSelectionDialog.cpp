/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CCopasiSelectionDialog.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/12/10 15:10:06 $
   End CVS Header */

#include "CCopasiSelectionDialog.h"
#include "qpushbutton.h"
#include "qcheckbox.h"
#include "qhbox.h"
#include "qvbox.h"
#include "qlayout.h"
#include "CCopasiSelectionWidget.h"

CCopasiSelectionDialog::CCopasiSelectionDialog(QWidget * parent , const char * name , bool modal): QDialog(parent, name, modal), mpOKButton(NULL), mpCancelButton(NULL), mpModeCheckBox(NULL), mpButtonBox(NULL), mpMainWidget(NULL), mpMainLayout(NULL), mpTmpVector(new std::vector<CCopasiObject*>()), mpOutputVector(NULL), mExpertMode(false), mExpertModeEnabled(true)
{
  this->setWFlags(this->getWFlags() | Qt::WDestructiveClose);
  this->mpMainLayout = new QVBoxLayout(this);
  this->mpMainLayout->setAutoAdd(true);
  this->mpSelectionWidget = new CCopasiSelectionWidget(this);
  this->mpButtonBox = new QHBox(this);
  this->mpButtonBox->layout()->setAutoAdd(false);
  ((QBoxLayout*)this->mpButtonBox->layout())->addStretch();
  this->mpOKButton = new QPushButton(this->mpButtonBox, "OK");
  ((QBoxLayout*)this->mpButtonBox->layout())->addWidget(this->mpOKButton);
  this->mpOKButton->setText("OK");
  this->mpOKButton->setDefault(true);
  this->mpOKButton->setAutoDefault(true);
  this->mpCancelButton = new QPushButton(this->mpButtonBox, "Cancel");
  ((QBoxLayout*)this->mpButtonBox->layout())->addWidget(this->mpCancelButton);
  this->mpCancelButton->setText("Cancel");
  this->mpModeCheckBox = new QCheckBox("expert mode", this->mpButtonBox, "expertMode");
  ((QBoxLayout*)this->mpButtonBox->layout())->addWidget(this->mpModeCheckBox);
  this->mpModeCheckBox->setChecked(false);
  ((QBoxLayout*)this->mpButtonBox->layout())->addSpacing(20);
  ((QBoxLayout*)this->mpButtonBox->layout())->addStretch();

  connect(this->mpOKButton, SIGNAL(clicked()), this, SLOT(okButton_clicked()));
  connect(this->mpCancelButton, SIGNAL(clicked()), this, SLOT(cancelButton_clicked()));
  connect(this->mpModeCheckBox, SIGNAL(toggled(bool)), this, SLOT(modeButton_toggled(bool)));

  this->mpSelectionWidget->setOutputVector(NULL);

  this->setTabOrder(this->mpOKButton, this->mpCancelButton);
  this->setTabOrder(this->mpCancelButton, this->mpModeCheckBox);
  this->setTabOrder(this->mpModeCheckBox, this->mpMainWidget);
}

CCopasiSelectionDialog::~CCopasiSelectionDialog()
{
  delete this->mpOKButton;
  delete this->mpCancelButton;
  delete this->mpModeCheckBox;
  delete this->mpButtonBox;
  delete this->mpMainLayout;
  delete this->mpSelectionWidget;
}

void CCopasiSelectionDialog::setModel(CModel* model)
{
  this->mpSelectionWidget->populateTree(model);
}

void CCopasiSelectionDialog::setOutputVector(std::vector<CCopasiObject*>* outputVector)
{
  this->mpSelectionWidget->setOutputVector(outputVector);
}

void CCopasiSelectionDialog::okButton_clicked()
{
  // fill outputVector
  this->mpSelectionWidget->commit();
  done(QDialog::Accepted);
}

void CCopasiSelectionDialog::cancelButton_clicked()
{
  done(QDialog::Rejected);
}

void CCopasiSelectionDialog::modeButton_toggled(bool checked)
{
  this->mpSelectionWidget->setExpertMode(checked);
}

void CCopasiSelectionDialog::setSingleSelection(bool singleSelectionMode)
{
  this->mpSelectionWidget->setSingleSelection(singleSelectionMode);
}

void CCopasiSelectionDialog::enableExpertMode(bool enable)
{
  if (enable == this->mExpertModeEnabled) return;
  this->mExpertModeEnabled = enable;
  if (!this->mExpertModeEnabled)
    {
      this->mpModeCheckBox->setChecked(false);
      this->mpModeCheckBox->hide();
    }
  else
    {
      this->mpModeCheckBox->show();
    }
}
