/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ModelWidget.cpp,v $
   $Revision: 1.28 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/05/03 20:20:18 $
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
  cancelChanges->setText(trUtf8("Cancel"));
  Layout5->addWidget(cancelChanges);

  // preliminary
  splitModel = new QPushButton(this, "irreversible");
  splitModel->setText(trUtf8("Convert All Reactions to Irreversible"));
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
bool ModelWidget::loadModel(CModel *model)
{
  bool ret = true;

  LineEdit->setText(FROM_UTF8(model->getTitle()));
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
      //QMessageBox::information(this, "tIME uNIT", model->TimeUnitName[temp1].);
    }
  ComboBox1->insertStringList(comboEntries, -1);
  ComboBox1->setCurrentText(FROM_UTF8(model->getTimeUnit()));

  QStringList comboEntries1;
  for (temp1 = 0; CModel::VolumeUnitName[temp1]  /*!= ""*/; temp1++)
    {
      comboEntries1.push_front(QString::fromUtf8(CModel::VolumeUnitName[temp1]));
      //QMessageBox::information(this, "Volume Unit", model->VolumeUnitName[temp1].);
    }
  ComboBox2->insertStringList(comboEntries1, -1);
  ComboBox2->setCurrentText(FROM_UTF8(model->getVolumeUnit()));

  QStringList comboEntries2;
  for (temp1 = 0; CModel::QuantityUnitName[temp1] /*!= ""*/; temp1++)
    {
      comboEntries2.push_front(QString::fromUtf8(CModel::QuantityUnitName[temp1]));
      //QMessageBox::information(this, "Volume Unit", model->QuantityUnitName[temp1].);
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

  if ((const char *)LineEdit->text().utf8() != model->getTitle())
    {
      model->setTitle((const char *)LineEdit->text().utf8());
      ListViews::notify(ListViews::MODEL, ListViews::RENAME, objKey);
    }

  if ((const char *)textBrowser->text().utf8() != model->getComments())
    {
      model->setComments((const char *)textBrowser->text().utf8());
      ListViews::notify(ListViews::MODEL, ListViews::CHANGE, objKey);
    }

  if ((const char *)ComboBox1->currentText().utf8() != model->getTimeUnit())
    {
      model->setTimeUnit((const char *)ComboBox1->currentText().utf8());
      ListViews::notify(ListViews::MODEL, ListViews::CHANGE, objKey);
    }

  if ((const char *)ComboBox2->currentText().utf8() != model->getVolumeUnit())
    {
      model->setVolumeUnit((const char *)ComboBox2->currentText().utf8());
      ListViews::notify(ListViews::MODEL, ListViews::CHANGE, objKey);
    }

  if ((const char *)ComboBox3->currentText().utf8() != model->getQuantityUnit())
    {
      model->setQuantityUnit((const char *)ComboBox3->currentText().utf8());
      ListViews::notify(ListViews::MODEL, ListViews::CHANGE, objKey);
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

void ModelWidget::slotBtnSplitClicked()
{
  convert2NonReversible();
}

bool ModelWidget::convert2NonReversible()
{
  //TODO check if there are any reversible reactions
  //TODO warn the user
  //TODO tell the gui about changes
  //TODO generate report ?

  bool ret = true;

  std::vector<std::string> reactionsToDelete;

  CReaction *reac0, *reac1, *reac2;
  CReactionInterface ri1, ri2;
  std::string fn, rn1, rn2;

  CModel* model = dynamic_cast< CModel * >(GlobalKeys.get(objKey));
  if (!model) return false;

  CCopasiVectorN< CReaction > & steps = model->getReactions();

  unsigned C_INT32 i, imax = steps.size();
  for (i = 0; i < imax; ++i)
    if (steps[i]->isReversible())
      {
        ret = false;
        reac0 = steps[i];
        std::cout << i << "  ";

        //create the two new reactions
        reac1 = new CReaction(*reac0, &steps);
        rn1 = reac1->getName() + " (forward)";
        reac1->setName(rn1);
        steps.add(reac1);

        reac2 = new CReaction(*reac0, &steps);
        rn2 = reac2->getName() + " (backward)";
        reac2->setName(rn2);
        steps.add(reac2);

        ri1.initFromReaction(*model, reac1->getKey());
        ri2.initFromReaction(*model, reac2->getKey());

        //set the new function
        fn = reac0->getFunction().getName();
        std::cout << fn << "  " << std::endl;

        if (fn == "Mass action (reversible)")
          {
            ri1.setReversibility(false, "Mass action (irreversible)");
            ri2.reverse(false, "Mass action (irreversible)");
          }
        else if (fn == "Constant flux (reversible)")
          {
            ri1.setReversibility(false, "Constant flux (irreversible)");
            ri2.reverse(false, "Constant flux (irreversible)");
          }
        else
          {
            //ri1.setReversibility(false);
            ri2.reverse(false, "Mass action (irreversible)");
          }

        ri1.writeBackToReaction(*model);
        ri2.writeBackToReaction(*model);

        //set the kinetic parameters

        if (fn == "Mass action (reversible)")
          {
            reac1->setParameterValue("k1", reac0->getParameterValue("k1"));
            reac2->setParameterValue("k1", reac0->getParameterValue("k2"));
            ret = true;
          }
        else
          {
            reac2->setParameterValue("k1", 0);
          }

        //remove the old reaction
        //mSteps.remove(reac0->getName());
        reactionsToDelete.push_back(reac0->getName());
      }

  imax = reactionsToDelete.size();
  for (i = 0; i < imax; ++i)
    steps.remove(reactionsToDelete[i]);

  ListViews::notify(ListViews::MODEL, ListViews::CHANGE, objKey);

  return ret;
}

bool ModelWidget::update(ListViews::ObjectType objectType,
                         ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  switch (objectType)
    {
    case ListViews::MODEL:
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
  //TODO: check if it really is a model

  if (model) return loadModel(model);
  else return false;
}
