/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ModelWidget.cpp,v $
   $Revision: 1.37 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2004/12/20 20:28:38 $
   End CVS Header */

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
#include "CReactionInterface.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"

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
  cancelChanges->setText(trUtf8("Revert"));
  Layout5->addWidget(cancelChanges);

  // preliminary

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
bool ModelWidget::loadModel(CModel *model)
{
  bool ret = true;

  LineEdit->setText(FROM_UTF8(model->getObjectName()));
  textBrowser->setText(FROM_UTF8(model->getComments()));
  textBrowser->setReadOnly(FALSE);
  ComboBox1->clear();
  ComboBox2->clear();
  ComboBox3->clear();
  QStringList comboEntries;

  unsigned int temp1;
  for (temp1 = 0; model->TimeUnitName[temp1] /*!= ""*/; temp1++)
    {
      comboEntries.push_front(QString::fromUtf8(model->TimeUnitName[temp1]));
    }
  ComboBox1->insertStringList(comboEntries, -1);
  ComboBox1->setCurrentText(FROM_UTF8(model->getTimeUnit()));

  QStringList comboEntries1;
  for (temp1 = 0; CModel::VolumeUnitName[temp1]  /*!= ""*/; temp1++)
    {
      comboEntries1.push_front(QString::fromUtf8(CModel::VolumeUnitName[temp1]));
    }
  ComboBox2->insertStringList(comboEntries1, -1);
  ComboBox2->setCurrentText(FROM_UTF8(model->getVolumeUnit()));

  QStringList comboEntries2;
  for (temp1 = 0; CModel::QuantityUnitName[temp1] /*!= ""*/; temp1++)
    {
      comboEntries2.push_front(QString::fromUtf8(CModel::QuantityUnitName[temp1]));
    }
  ComboBox3->insertStringList(comboEntries2, -1);
  ComboBox3->setCurrentText(FROM_UTF8(model->getQuantityUnit()));

  return ret;
}

bool ModelWidget::saveToModel()
{
  CModel* model = dynamic_cast< CModel * >(GlobalKeys.get(objKey));

  if (!model) return false;

  bool success = true;

  if ((const char *)LineEdit->text().utf8() != model->getObjectName())
    {
      model->setTitle((const char *)LineEdit->text().utf8());
      protectedNotify(ListViews::MODEL, ListViews::RENAME, objKey);
    }

  if (textBrowser->isModified())
    {
      model->setComments((const char *)textBrowser->text().utf8());
      protectedNotify(ListViews::MODEL, ListViews::CHANGE, objKey);
    }

  if ((const char *)ComboBox1->currentText().utf8() != model->getTimeUnit())
    {
      model->setTimeUnit((const char *)ComboBox1->currentText().utf8());
      protectedNotify(ListViews::MODEL, ListViews::CHANGE, objKey);
    }

  if ((const char *)ComboBox2->currentText().utf8() != model->getVolumeUnit())
    {
      model->setVolumeUnit((const char *)ComboBox2->currentText().utf8());
      protectedNotify(ListViews::MODEL, ListViews::CHANGE, objKey);
    }

  if ((const char *)ComboBox3->currentText().utf8() != model->getQuantityUnit())
    {
      model->setQuantityUnit((const char *)ComboBox3->currentText().utf8());
      protectedNotify(ListViews::MODEL, ListViews::CHANGE, objKey);
    }

  return success;
}

void ModelWidget::slotBtnCancelClicked()
{
  //TOD: let the user confirm
  enter(objKey); // reload
}

void ModelWidget::slotBtnOKClicked()
{
  //let the user confirm?
  saveToModel();
}

bool ModelWidget::update(ListViews::ObjectType objectType,
                         ListViews::Action C_UNUSED(action), const std::string & key)
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
      enter(key);
      break;

    default:
      break;
    }
  return true;
}

bool ModelWidget::leave()
{
  //let the user confirm?
  return saveToModel();
}

bool ModelWidget::enter(const std::string & key)
{
  objKey = key;
  CModel* model = dynamic_cast< CModel * >(GlobalKeys.get(key));

  if (model) return loadModel(model);
  else return false;
}
