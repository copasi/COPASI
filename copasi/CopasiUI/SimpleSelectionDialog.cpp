/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SimpleSelectionDialog.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/06 06:31:48 $
   End CVS Header */

#include "SimpleSelectionDialog.h"
#include "qpushbutton.h"
#include "qhbox.h"
#include "qvbox.h"
#include "qlayout.h"
#include "report/CCopasiObject.h"
#include "simpleselectionwidget.h"

SimpleSelectionDialog::SimpleSelectionDialog(QWidget * parent , const char * name , bool modal): QDialog(parent, name, modal), okButton(NULL), cancelButton(NULL), buttonBox(NULL), mainWidget(NULL), mainLayout(NULL), tmpVector(new std::vector<CCopasiObject*>()), outputVector(NULL)
{
  this->setWFlags(this->getWFlags() | Qt::WDestructiveClose);
  this->mainLayout = new QVBoxLayout(this);
  this->mainLayout->setAutoAdd(false);
  this->mainWidget = new SimpleSelectionWidget(this);
  this->buttonBox = new QHBoxLayout(0);
  ((QBoxLayout*)this->buttonBox->layout())->addStretch();
  this->okButton = new QPushButton(this, "OK");
  this->okButton->setText("OK");
  this->okButton->setDefault(true);
  this->okButton->setAutoDefault(true);
  this->buttonBox->addWidget(this->okButton);
  this->cancelButton = new QPushButton(this, "Cancel");
  this->cancelButton->setText("Cancel");
  this->buttonBox->addWidget(this->cancelButton);
  ((QBoxLayout*)this->buttonBox->layout())->addStretch();

  connect(this->okButton, SIGNAL(clicked()), this, SLOT(okButton_clicked()));
  connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton_clicked()));
  this->mainLayout->addWidget(this->mainWidget);
  this->mainLayout->addLayout(this->buttonBox);
  this->mainWidget->setOutputVector(this->tmpVector);

  this->setTabOrder(this->okButton, this->cancelButton);
  this->setTabOrder(this->cancelButton, this->mainWidget);
}

SimpleSelectionDialog::~SimpleSelectionDialog()
{
  delete this->okButton;
  delete this->cancelButton;
  delete this->buttonBox;
  delete this->mainWidget;
  delete this->mainLayout;
  delete this->tmpVector;
}

void SimpleSelectionDialog::setModel(CModel* model)
{
  this->mainWidget->populateTree(model);
}

void SimpleSelectionDialog::setOutputVector(std::vector<CCopasiObject*>* outputVector)
{
  this->outputVector = outputVector;
}

void SimpleSelectionDialog::okButton_clicked()
{
  // fill outputVector
  if (this->outputVector)
    {
      unsigned int counter;
      unsigned int maxCount = this->tmpVector->size();
      this->outputVector->clear();
      for (counter = 0; counter < maxCount;++counter)
        {
          this->outputVector->push_back(this->tmpVector->at(counter));
        }
    }
  done(QDialog::Accepted);
}

void SimpleSelectionDialog::cancelButton_clicked()
{
  close();
}
