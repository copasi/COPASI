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

  ModelWidgetLayout->addMultiCellLayout(Layout5, 8, 8, 0, 1);

  // signals and slots connections
  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
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
      ComboBox1->setCurrentText(mModel->getTimeUnit().c_str());
      ComboBox2->setCurrentText(mModel->getVolumeUnit().c_str());
      ComboBox3->setCurrentText(mModel->getQuantityUnit().c_str());
    }
}

void ModelWidget::slotBtnCancelClicked()
{}

void ModelWidget::slotBtnOKClicked()
{}
