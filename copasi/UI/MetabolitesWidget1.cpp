/*******************************************************************
 **  $ CopasiUI/MetaboliteWidget1.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the individual
 ** Metabolites----It is the second level of Metabolites
 ********************************************************************/
#include <math.h>

#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include <qbuttongroup.h>

#include "copasi.h"
#include "MetabolitesWidget1.h"
#include "model/CModel.h"
#include "utilities/CMethodParameter.h"
#include "listviews.h"
#include "report/CKeyFactory.h"

/*
 *  Constructs a MetabolitesWidget1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
MetabolitesWidget1::MetabolitesWidget1(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("MetabolitesWidget1");
  setCaption(trUtf8("MetabolitesWidget1"));
  MetabolitesWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "MetabolitesWidget1Layout");

  TextLabel4 = new QLabel(this, "TextLabel4");
  TextLabel4->setText(trUtf8("Metabolite Name"));

  MetabolitesWidget1Layout->addWidget(TextLabel4, 0, 0);

  TextLabel5 = new QLabel(this, "TextLabel5");
  TextLabel5->setText(trUtf8("Compartment Name"));

  MetabolitesWidget1Layout->addWidget(TextLabel5, 1, 0);

  LineEdit1 = new QLineEdit(this, "LineEdit1");
  //  QFont LineEdit1_font(LineEdit1->font());
  //  LineEdit1->setFont(LineEdit1_font);
  LineEdit1->setFrameShape(QLineEdit::LineEditPanel);
  LineEdit1->setFrameShadow(QLineEdit::Sunken);

  MetabolitesWidget1Layout->addMultiCellWidget(LineEdit1, 0, 0, 1, 3);

  ComboBox1 = new QComboBox(FALSE, this, "ComboBox1");

  MetabolitesWidget1Layout->addMultiCellWidget(ComboBox1, 1, 1, 1, 3);

  Line1_3 = new QFrame(this, "Line1_3");
  Line1_3->setFrameShape(QFrame::HLine);
  Line1_3->setFrameShadow(QFrame::Sunken);
  Line1_3->setFrameShape(QFrame::HLine);

  MetabolitesWidget1Layout->addMultiCellWidget(Line1_3, 2, 2, 0, 3);

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Metabolite Status Select"));

  MetabolitesWidget1Layout->addWidget(TextLabel2, 3, 0);

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Metabolite Status"));

  MetabolitesWidget1Layout->addWidget(TextLabel1, 3, 2);

  ButtonGroup3 = new QButtonGroup(this, "ButtonGroup3");
  ButtonGroup3->setFrameShape(QButtonGroup::WinPanel);
  ButtonGroup3->setFrameShadow(QButtonGroup::Sunken);
  ButtonGroup3->setTitle(trUtf8(""));
  ButtonGroup3->setExclusive(TRUE);
  ButtonGroup3->setColumnLayout(0, Qt::Vertical);
  ButtonGroup3->layout()->setSpacing(6);
  ButtonGroup3->layout()->setMargin(11);
  ButtonGroup3Layout = new QGridLayout(ButtonGroup3->layout());
  ButtonGroup3Layout->setAlignment(Qt::AlignTop);

  RadioButton3 = new QRadioButton(ButtonGroup3, "RadioButton3");
  RadioButton3->setEnabled(FALSE);
  RadioButton3->setText(trUtf8("Fixed"));

  ButtonGroup3Layout->addWidget(RadioButton3, 0, 0);

  RadioButton5 = new QRadioButton(ButtonGroup3, "RadioButton5");
  RadioButton5->setEnabled(FALSE);
  RadioButton5->setText(trUtf8("Dependent"));

  ButtonGroup3Layout->addWidget(RadioButton5, 2, 0);

  RadioButton4 = new QRadioButton(ButtonGroup3, "RadioButton4");
  RadioButton4->setEnabled(FALSE);
  RadioButton4->setText(trUtf8("Independent"));

  ButtonGroup3Layout->addWidget(RadioButton4, 1, 0);

  MetabolitesWidget1Layout->addMultiCellWidget(ButtonGroup3, 3, 4, 3, 3);
  QSpacerItem* spacer = new QSpacerItem(100, 70, QSizePolicy::Minimum, QSizePolicy::Expanding);
  MetabolitesWidget1Layout->addItem(spacer, 4, 2);
  QSpacerItem* spacer_2 = new QSpacerItem(100, 70, QSizePolicy::Minimum, QSizePolicy::Expanding);
  MetabolitesWidget1Layout->addItem(spacer_2, 4, 0);

  ButtonGroup2 = new QButtonGroup(this, "ButtonGroup2");
  ButtonGroup2->setFrameShape(QButtonGroup::WinPanel);
  ButtonGroup2->setTitle(trUtf8(""));
  ButtonGroup2->setExclusive(TRUE);
  ButtonGroup2->setColumnLayout(0, Qt::Vertical);
  ButtonGroup2->layout()->setSpacing(6);
  ButtonGroup2->layout()->setMargin(11);
  ButtonGroup2Layout = new QGridLayout(ButtonGroup2->layout());
  ButtonGroup2Layout->setAlignment(Qt::AlignTop);

  RadioButton2 = new QRadioButton(ButtonGroup2, "RadioButton2");
  RadioButton2->setText(trUtf8("Variable"));

  ButtonGroup2Layout->addWidget(RadioButton2, 1, 0);

  RadioButton1 = new QRadioButton(ButtonGroup2, "RadioButton1");
  RadioButton1->setText(trUtf8("Fixed"));

  ButtonGroup2Layout->addWidget(RadioButton1, 0, 0);

  MetabolitesWidget1Layout->addMultiCellWidget(ButtonGroup2, 3, 4, 1, 1);

  Line1_2 = new QFrame(this, "Line1_2");
  Line1_2->setFrameShape(QFrame::HLine);
  Line1_2->setFrameShadow(QFrame::Sunken);
  Line1_2->setFrameShape(QFrame::HLine);

  MetabolitesWidget1Layout->addMultiCellWidget(Line1_2, 5, 5, 0, 3);

  LineEdit5 = new QLineEdit(this, "LineEdit5");

  MetabolitesWidget1Layout->addWidget(LineEdit5, 7, 1);

  TextLabel11 = new QLabel(this, "TextLabel11");
  TextLabel11->setText(trUtf8("Transient Number"));

  MetabolitesWidget1Layout->addWidget(TextLabel11, 7, 2);

  TextLabel8 = new QLabel(this, "TextLabel8");
  TextLabel8->setText(trUtf8("Initial  Number"));

  MetabolitesWidget1Layout->addWidget(TextLabel8, 7, 0);

  TextLabel7 = new QLabel(this, "TextLabel7");
  TextLabel7->setText(trUtf8("Initial  Concentration"));

  MetabolitesWidget1Layout->addWidget(TextLabel7, 6, 0);

  LineEdit7 = new QLineEdit(this, "LineEdit7");
  LineEdit7->setEnabled(FALSE);

  MetabolitesWidget1Layout->addWidget(LineEdit7, 6, 3);

  LineEdit4 = new QLineEdit(this, "LineEdit4");

  MetabolitesWidget1Layout->addWidget(LineEdit4, 6, 1);

  TextLabel12 = new QLabel(this, "TextLabel12");
  TextLabel12->setText(trUtf8("Transient Time"));

  MetabolitesWidget1Layout->addWidget(TextLabel12, 8, 0);

  LineEdit9 = new QLineEdit(this, "LineEdit9");
  LineEdit9->setEnabled(FALSE);

  MetabolitesWidget1Layout->addWidget(LineEdit9, 8, 1);

  LineEdit8 = new QLineEdit(this, "LineEdit8");
  LineEdit8->setEnabled(FALSE);

  MetabolitesWidget1Layout->addWidget(LineEdit8, 7, 3);

  TextLabel10 = new QLabel(this, "TextLabel10");
  TextLabel10->setText(trUtf8("Transient Concentration"));

  MetabolitesWidget1Layout->addWidget(TextLabel10, 6, 2);
  QSpacerItem* spacer_3 = new QSpacerItem(470, 70, QSizePolicy::Minimum, QSizePolicy::Expanding);
  MetabolitesWidget1Layout->addMultiCell(spacer_3, 9, 9, 0, 3);

  Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setFrameShadow(QFrame::Sunken);
  Line1->setFrameShape(QFrame::HLine);

  MetabolitesWidget1Layout->addMultiCellWidget(Line1, 10, 10, 0, 3);

  Layout7 = new QHBoxLayout(0, 0, 6, "Layout7");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout7->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Cancel"));
  Layout7->addWidget(cancelChanges);

  MetabolitesWidget1Layout->addMultiCellLayout(Layout7, 11, 11, 0, 3);

  setTabOrder(LineEdit1, ComboBox1);
  setTabOrder(ComboBox1, RadioButton1);
  setTabOrder(RadioButton1, RadioButton2);
  setTabOrder(RadioButton2, RadioButton3);
  setTabOrder(RadioButton3, RadioButton4);
  setTabOrder(RadioButton4, RadioButton5);
  setTabOrder(RadioButton5, LineEdit4);
  setTabOrder(LineEdit4, LineEdit5);
  setTabOrder(LineEdit5, LineEdit9);
  setTabOrder(LineEdit9, LineEdit7);
  setTabOrder(LineEdit7, LineEdit8);
  setTabOrder(LineEdit8, commitChanges);
  setTabOrder(commitChanges, cancelChanges);

  // OK button
  connect(commitChanges, SIGNAL(clicked()),
          this, SLOT(slotBtnOKClicked()));
  // Cancel button
  connect(cancelChanges, SIGNAL(clicked()),
          this, SLOT(slotBtnCancelClicked()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
MetabolitesWidget1::~MetabolitesWidget1()
{
  // no need to delete child widgets, Qt does it all for us
}

/* This function loads the metabolites widget when its name is
   clicked in the tree   */
bool MetabolitesWidget1::loadFromMetabolite(const CMetab* metab)
{
  CCopasiVectorNS< CCompartment > & allcompartments = dataModel->getModel()->getCompartments();
  CCompartment *compt;
  ComboBox1->clear();
  LineEdit1->setText(metab->getName().c_str());
  //Metabolite1_Name = new QString(metab->getName().c_str());

  LineEdit4->setText(QString::number(metab->getInitialConcentration()));

  LineEdit7->setText(QString::number(metab->getConcentration()));
  LineEdit7->setReadOnly(true);

  LineEdit8->setText(QString::number(metab->getNumberDbl()));
  LineEdit8->setReadOnly(true);

  LineEdit5->setText(QString::number(metab->getInitialNumberDbl()));

  LineEdit9->setText(QString::number(metab->getTransitionTime()));
  LineEdit9->setReadOnly(true);
  RadioButton1->setChecked(false);
  RadioButton2->setChecked(false);
  RadioButton3->setChecked(false);
  RadioButton4->setChecked(false);
  RadioButton5->setChecked(false);

  if (metab->getStatus() == CMetab::METAB_FIXED)
    {
      RadioButton1->setChecked(true);
      RadioButton3->setChecked(true);
    }
  else if (metab->getStatus() == CMetab::METAB_VARIABLE)
    {
      RadioButton2->setChecked(true);
      RadioButton4->setChecked(true);
    }
  else if (metab->getStatus() == CMetab::METAB_DEPENDENT)
    {
      RadioButton2->setChecked(true);
      RadioButton5->setChecked(true);
    }

  ComboBox1->setDuplicatesEnabled (false);
  unsigned C_INT32 m;
  for (m = 0; m < allcompartments.size(); m++)
    {
      //showMessage("mudita","It comes here");

      compt = allcompartments[m];
      //ComboBox1->insertStringList(compt->getName().c_str(),j);
      ComboBox1->insertItem(compt->getName().c_str());
    }
  ComboBox1->setCurrentText(metab->getCompartment()->getName().c_str());

  return true;
}

bool MetabolitesWidget1::saveToMetabolite()
{
  //find pointer to metab from key
  CMetab* metab = (CMetab*)(CCopasiContainer*)CKeyFactory::get(objKey);
  if (!metab) return false;

  //name
  QString name(LineEdit1->text());
  if (name.latin1() != metab->getName())
    {
      metab->setName(name.latin1());
      //TODO: update the reactions (the real thing, not the gui)
      //      propably not necessary anymore when reaction uses keys instead of names
      ListViews::notify(ListViews::METABOLITE, ListViews::RENAME, objKey);
    }

  //compartment
  QString Compartment = ComboBox1->currentText();
  if (Compartment.latin1() != metab->getCompartment()->getName())
    {
      dataModel->getModel()->getCompartments()[Compartment.latin1()]->addMetabolite(*metab);
      dataModel->getModel()->getCompartments()[metab->getCompartment()->getName()]->getMetabolites().remove(metab->getName());
      dataModel->getModel()->initializeMetabolites();
      //ListViews::notify(ListViews::MODEL, ListViews::CHANGE, "");
      ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
      ListViews::notify(ListViews::COMPARTMENT, ListViews::CHANGE, "");
    }

  //for Initial Concentration and Initial Number
  QString initialConcentration(LineEdit4->text());
  double temp1;
  temp1 = initialConcentration.toDouble();
  if (fabs(temp1 - metab->getInitialConcentration()) > 1e-10)
    {
      metab->setInitialConcentration(temp1);
      ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
    }

  else
    {
      QString initialNumber(LineEdit5->text());
      C_FLOAT64 temp2;
      temp2 = initialNumber.toDouble();
      if (fabs(temp2 - metab->getInitialNumberDbl()) > 1e-3) //TODO: this is extremely ugly
        {
          metab->setInitialNumberDbl(temp2);
          ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
        }
    }

  //fixed?
  if (RadioButton1->isChecked() == true)
    {
      if (metab->getStatus() != CMetab::METAB_FIXED)
        {
          metab->setStatus(CMetab::METAB_FIXED);
          ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
        }
    }
  else
    {
      if (metab->getStatus() != CMetab::METAB_VARIABLE)
        {
          metab->setStatus(CMetab::METAB_VARIABLE);
          ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
        }
    }

  enter(objKey); //this is a hack to update the initial number when the initial concentration has changed and vice versa

  return true; //TODO: really check
}

void MetabolitesWidget1::slotBtnCancelClicked()
{
  //let the user confirm
  enter(objKey); // reload
}

void MetabolitesWidget1::slotBtnOKClicked()
{
  //let the user confirm?
  saveToMetabolite();
}

bool MetabolitesWidget1::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
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

bool MetabolitesWidget1::leave()
{
  //let the user confirm?
  return saveToMetabolite();
}

bool MetabolitesWidget1::enter(const std::string & key)
{
  objKey = key;
  CMetab* metab = (CMetab*)(CCopasiContainer*)CKeyFactory::get(key);
  //TODO: check if it really is a compartment

  if (metab) return loadFromMetabolite(metab);
  else return false;
}
