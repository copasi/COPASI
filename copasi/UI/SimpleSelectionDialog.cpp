/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/SimpleSelectionDialog.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/28 13:48:45 $
   End CVS Header */

#include "SimpleSelectionDialog.h"
#include "qpushbutton.h"
#include "qhbox.h"
#include "qvbox.h"
#include "qlayout.h"
#include "ObjectBrowserWidget.h"
#include "report/CCopasiObject.h"
#include "simpleselectionwidget.h"

SimpleSelectionDialog::SimpleSelectionDialog(QWidget * parent , const char * name , bool modal): QDialog(parent, name, modal), okButton(NULL), cancelButton(NULL), modeButton(NULL), buttonBox(NULL), mainWidget(NULL), simpleSelectionWidget(NULL), objectBrowserWidget(NULL), mainLayout(NULL), tmpVector(new std::vector<CCopasiObject*>()), outputVector(NULL), expertMode(false)
{
  this->setWFlags(this->getWFlags() | Qt::WDestructiveClose);
  this->mainLayout = new QVBoxLayout(this);
  this->mainLayout->setAutoAdd(false);
  this->simpleSelectionWidget = new SimpleSelectionWidget(this);
  this->mainWidget = this->simpleSelectionWidget;
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
  this->modeButton = new QPushButton(this, "ModeButton");
  this->modeButton->setText("Expert");
  this->buttonBox->addWidget(this->modeButton);
  ((QBoxLayout*)this->buttonBox->layout())->addStretch();

  connect(this->okButton, SIGNAL(clicked()), this, SLOT(okButton_clicked()));
  connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton_clicked()));
  connect(this->modeButton, SIGNAL(clicked()), this, SLOT(modeButton_clicked()));
  this->mainLayout->addWidget(this->mainWidget);
  this->mainLayout->addLayout(this->buttonBox);
  this->simpleSelectionWidget->setOutputVector(this->tmpVector);

  this->setTabOrder(this->okButton, this->cancelButton);
  this->setTabOrder(this->cancelButton, this->modeButton);
  this->setTabOrder(this->modeButton, this->mainWidget);
}

SimpleSelectionDialog::~SimpleSelectionDialog()
{
  delete this->okButton;
  delete this->cancelButton;
  delete this->modeButton;
  delete this->buttonBox;
  delete this->mainLayout;
  delete this->tmpVector;
  delete this->simpleSelectionWidget;
  delete this->objectBrowserWidget;
}

void SimpleSelectionDialog::setModel(CModel* model)
{
  this->simpleSelectionWidget->populateTree(model);
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
      if (this->expertMode)
        {
          this->tmpVector->clear();
          this->objectBrowserWidget->commitClicked();
        }
      else
        {
          if (this->simpleSelectionWidget->isSingleSelection())
            {
              this->tmpVector->clear();
              this->simpleSelectionWidget->addButtonClicked();
            }
        }
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

void SimpleSelectionDialog::modeButton_clicked()
{
  if (this->expertMode)
    {
      this->expertMode = false;
      this->tmpVector->clear();
      this->objectBrowserWidget->commitClicked();
      this->simpleSelectionWidget->setOutputVector(this->tmpVector);
      this->modeButton->setText("Expert");
      this->mainWidget->setHidden(true);
      this->mainLayout->remove(this->mainWidget);
      this->mainWidget = this->simpleSelectionWidget;
      this->mainLayout->insertWidget(0, this->mainWidget);
      this->mainWidget->setHidden(false);
    }
  else
    {
      this->expertMode = true;
      this->modeButton->setText("Simple");
      if (!this->objectBrowserWidget)
        {
          this->objectBrowserWidget = new ObjectBrowserWidget(this);
        }
      this->objectBrowserWidget->selectObjects(this->tmpVector);
      this->tmpVector->clear();
      this->objectBrowserWidget->setOutputVector(this->tmpVector);
      this->mainWidget->setHidden(true);
      this->mainLayout->remove(this->mainWidget);
      this->mainWidget = this->objectBrowserWidget;
      this->mainLayout->insertWidget(0, this->mainWidget);
      this->mainWidget->setHidden(false);
    }
}
