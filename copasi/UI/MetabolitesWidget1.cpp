/*******************************************************************
 **  $ CopasiUI/MetaboliteWidget1.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the individual
 ** Metabolites----It is the second level of Metabolites
 ********************************************************************/
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
#include "model/model.h"
#include "listviews.h"

/*
 *  Constructs a MetabolitesWidget1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
MetabolitesWidget1::MetabolitesWidget1(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("MetabolitesWidget1");
  resize(521, 408);
  QFont f(font());
  f.setFamily("Times New Roman");
  setFont(f);
  setCaption(trUtf8("MetabolitesWidget1"));
  MetabolitesWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "MetabolitesWidget1Layout");

  TextLabel4 = new QLabel(this, "TextLabel4");
  TextLabel4->setText(trUtf8("Metabolite Name"));

  MetabolitesWidget1Layout->addWidget(TextLabel4, 0, 0);

  TextLabel5 = new QLabel(this, "TextLabel5");
  TextLabel5->setText(trUtf8("Compartment Name"));

  MetabolitesWidget1Layout->addWidget(TextLabel5, 1, 0);

  LineEdit1 = new QLineEdit(this, "LineEdit1");
  QFont LineEdit1_font(LineEdit1->font());
  LineEdit1->setFont(LineEdit1_font);
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
  // OK button
  connect(commitChanges, SIGNAL(clicked()),
          this, SLOT(slotBtnOKClicked()));
  // Cancel button
  connect(cancelChanges, SIGNAL(clicked()),
          this, SLOT(slotBtnCancelClicked()));
  //
  connect(this, SIGNAL(signal_emitted(const QString &)),
          (ListViews*)parent,
          SLOT(slotMetaboliteTableChanged(const QString &)));
  //
  connect(this, SIGNAL(leaf(CModel*)),
          (ListViews*)parent, SLOT(loadModelNodes(CModel*)));
  //
  connect(this, SIGNAL(updated()),
          (ListViews*)parent, SLOT(dataModelUpdated()));

  //  connect(ComboBox1, SIGNAL(activated(const QString &)), (ListViews*)parent, SLOT(slotCompartmentSelected(const QString &)));
  //  connect(LineEdit4, SIGNAL(selectionChanged()), (ListViews*)parent, SLOT(slotCompartmentSelected()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
MetabolitesWidget1::~MetabolitesWidget1()
{
  // no need to delete child widgets, Qt does it all for us
}

int MetabolitesWidget1::isName(QString setValue)
{
  if (mModel == NULL)
    {
      return 0;
    }

  if (mModel->getMetabolites().getIndex((std::string)setValue.latin1()) != C_INVALID_INDEX)
    {
      loadName(setValue);
      return 1;
    }

  return 0;
}

/*this function is used to load the model before loading the widget*/
void MetabolitesWidget1::loadMetabolites(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
    }
}

/* This function loads the metabolites widget when its name is
   clicked in the tree   */
void MetabolitesWidget1::loadName(QString setValue)
{
  if (mModel == NULL)
    {
      return;
    }

  CCopasiVectorN< CMetab > metabolites = mModel->getMetabolites();

  CMetab *metab;

  unsigned C_INT32 i = 0;
  myValue = -1;

  for (; i < metabolites.size(); i++)
    {
      metab = metabolites[i];
      int value = QString::compare(metab->getName().c_str(), setValue);

      if (!value)
        {
          myValue = i;
          break;
        }
    }

  if (myValue != -1)
    {
      metab = metabolites[myValue];
      name = setValue;

      CCopasiVectorNS< CCompartment > & allcompartments = mModel->getCompartments();
      CCompartment *compt;
      ComboBox1->clear();
      LineEdit1->setText(metab->getName().c_str());
      Metabolite1_Name = new QString(metab->getName().c_str());

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
    }
}

/***********ListViews::showMessage(QString caption,QString text)------------------------>
 **
 ** Parameters:- 1. QString :- The Title that needs to be displayed in message box
 **              2. QString :_ The Text that needs to be displayed in the message box
 ** Returns  :-  void(Nothing)
 ** Description:- This method is used to show the message box on the screen
 ****************************************************************************************/

void MetabolitesWidget1::slotBtnCancelClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to cancel the changes?");
  emit signal_emitted(*Metabolite1_Name);
}

void MetabolitesWidget1::slotBtnOKClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to commit the changes?");
  CMetab * metab = mModel->getMetabolites()[myValue];

  QString name(LineEdit1->text());
  if (name.latin1() != metab->getName())
    metab->setName(name.latin1());

  QString Compartment = ComboBox1->currentText();
  if (Compartment.latin1() != metab->getCompartment()->getName())
    {
      mModel->getCompartments()[Compartment.latin1()]->addMetabolite(*metab);
      mModel->getCompartments()[metab->getCompartment()->getName()]->getMetabolites().remove(metab->getName());
      mModel->initializeMetabolites();
    }

  //for Initial Concentration and Initial Number
  QString initialConcentration(LineEdit4->text());
  double temp1;
  temp1 = initialConcentration.toDouble();
  if (temp1 != metab->getInitialConcentration())
    metab->setInitialConcentration(temp1);
  else
    {
      QString initialNumber(LineEdit5->text());
      int temp2;
      temp2 = initialNumber.toInt();
      if (temp2 != metab->getInitialNumberInt())
        metab->setInitialNumberInt(temp2);
    }

  //if (QString::number(metab->getStatus()) == "0")

  if (RadioButton1->isChecked() == true)
    {
      metab->setStatus(CMetab::METAB_FIXED);
    }
  else
    {
      metab->setStatus(CMetab::METAB_VARIABLE);
    }

  loadName(name);

  emit updated();
  emit leaf(mModel);
  emit signal_emitted(*Metabolite1_Name);
}
