/*******************************************************************
 **  $ CopasiUI/ModelWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the Model
 ********************************************************************/
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include <qlistbox.h>
#include "copasi.h"
#include "ModelWidget.h"
#include "listviews.h"
#include "model/CModel.h"
#include "utilities/CMethodParameter.h"

/*
 *  Constructs a ModelWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ModelWidget::ModelWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("ModelWidget");
  setCaption(trUtf8("ModelWidget"));
  ModelWidgetLayout = new QGridLayout(this, 1, 1, 11, 5, "ModelWidgetLayout");

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Name"));
  ModelWidgetLayout->addWidget(TextLabel1, 0, 0);
  LineEdit = new QLineEdit(this, "LineEdit");
  ModelWidgetLayout->addWidget(LineEdit, 0, 1);

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Time Unit"));
  ModelWidgetLayout->addWidget(TextLabel2, 1, 0);
  ComboBox1 = new QComboBox(FALSE, this, "ComboBox1");
  ModelWidgetLayout->addWidget(ComboBox1, 1, 1);

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Volume Unit"));
  ModelWidgetLayout->addWidget(TextLabel3, 2, 0);
  ComboBox2 = new QComboBox(FALSE, this, "ComboBox2");
  ModelWidgetLayout->addWidget(ComboBox2, 2, 1);

  TextLabel4 = new QLabel(this, "TextLabel4");
  TextLabel4->setText(trUtf8("Quantity Unit"));
  ModelWidgetLayout->addWidget(TextLabel4, 3, 0);
  ComboBox3 = new QComboBox(FALSE, this, "ComboBox3");
  ModelWidgetLayout->addWidget(ComboBox3, 3, 1);

  TextLabel5 = new QLabel(this, "TextLabel5");
  TextLabel5->setText(trUtf8("Description"));
  ModelWidgetLayout->addWidget(TextLabel5, 4, 0);
  textBrowser = new QTextBrowser (this, "Text Browser");
  ModelWidgetLayout->addWidget(textBrowser, 4, 1);

  Layout5 = new QHBoxLayout(0, 0, 6, "Layout5");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout5->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Cancel"));
  Layout5->addWidget(cancelChanges);

  // preliminary
  splitModel = new QPushButton(this, "irreversible");
  splitModel->setText(trUtf8("-> irreversible"));
  ModelWidgetLayout->addWidget(splitModel, 7, 1);

  ModelWidgetLayout->addMultiCellLayout(Layout5, 8, 8, 0, 1);

  // signals and slots connections
  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
  connect(splitModel, SIGNAL(clicked()), this, SLOT(slotBtnSplitClicked()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
ModelWidget::~ModelWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*This function is to load the model for the compartments*/
void ModelWidget::loadModel(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
      LineEdit->setText(mModel->getTitle().c_str());
      textBrowser->setText(mModel->getComments().c_str());
      textBrowser->setReadOnly(FALSE);
      ComboBox1->clear();
      ComboBox2->clear();
      ComboBox3->clear();
      QStringList comboEntries;

      unsigned int temp1;
      for (temp1 = 0; mModel->TimeUnitName[temp1] != ""; temp1++)
        {
          comboEntries.push_front(mModel->TimeUnitName[temp1].c_str());
          //QMessageBox::information(this, "tIME uNIT", mModel->TimeUnitName[temp1].c_str());
        }
      ComboBox1->insertStringList(comboEntries, -1);
      ComboBox1->setCurrentText(mModel->getTimeUnit().c_str());

      QStringList comboEntries1;
      for (temp1 = 0; CModel::VolumeUnitName[temp1] != ""; temp1++)
        {
          comboEntries1.push_front(CModel::VolumeUnitName[temp1].c_str());
          //QMessageBox::information(this, "Volume Unit", mModel->VolumeUnitName[temp1].c_str());
        }
      ComboBox2->insertStringList(comboEntries1, -1);
      ComboBox2->setCurrentText(mModel->getVolumeUnit().c_str());

      QStringList comboEntries2;
      for (temp1 = 0; CModel::QuantityUnitName[temp1] != ""; temp1++)
        {
          comboEntries2.push_front(CModel::QuantityUnitName[temp1].c_str());
          //QMessageBox::information(this, "Volume Unit", mModel->QuantityUnitName[temp1].c_str());
        }
      ComboBox3->insertStringList(comboEntries2, -1);
      ComboBox3->setCurrentText(mModel->getQuantityUnit().c_str());
    }
}

void ModelWidget::slotBtnCancelClicked()
{}

void ModelWidget::slotBtnOKClicked()
{
  if (mModel != NULL)
    {
      mModel->setTitle(LineEdit->text().latin1());
      mModel->setComments(textBrowser->text().latin1());
      mModel->setTimeUnit(ComboBox1->currentText().latin1());
      mModel->setVolumeUnit(ComboBox2->currentText().latin1());
      mModel->setQuantityUnit(ComboBox3->currentText().latin1());
    }
}

void ModelWidget::slotBtnSplitClicked()
{
  mModel->convert2NonReversible();
}
