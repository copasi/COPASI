/****************************************************************************
 ** Form implementation generated from reading ui file '.\MetabolitesWidget1.ui'
 **
 ** Created: Tue Mar 4 00:54:02 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
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
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("MetabolitesWidget1");
  resize(589, 380);
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

  MetabolitesWidget1Layout->addMultiCellWidget(LineEdit1, 0, 0, 1, 2);

  ComboBox1 = new QComboBox(FALSE, this, "ComboBox1");

  MetabolitesWidget1Layout->addMultiCellWidget(ComboBox1, 1, 1, 1, 2);

  LineEdit4 = new QLineEdit(this, "LineEdit4");

  MetabolitesWidget1Layout->addWidget(LineEdit4, 6, 1);

  TextLabel10 = new QLabel(this, "TextLabel10");
  TextLabel10->setText(trUtf8("Transient Concentration"));

  MetabolitesWidget1Layout->addWidget(TextLabel10, 6, 2);

  Layout7 = new QHBoxLayout(0, 0, 6, "Layout7");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit Changes"));
  Layout7->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Cancel Changes"));
  Layout7->addWidget(cancelChanges);

  MetabolitesWidget1Layout->addMultiCellLayout(Layout7, 10, 10, 0, 3);

  TextLabel8 = new QLabel(this, "TextLabel8");
  TextLabel8->setText(trUtf8("Initial  Number"));

  MetabolitesWidget1Layout->addWidget(TextLabel8, 7, 0);

  TextLabel11 = new QLabel(this, "TextLabel11");
  TextLabel11->setText(trUtf8("Transient Number"));

  MetabolitesWidget1Layout->addWidget(TextLabel11, 7, 2);

  LineEdit7 = new QLineEdit(this, "LineEdit7");
  LineEdit7->setEnabled(FALSE);

  MetabolitesWidget1Layout->addWidget(LineEdit7, 6, 3);

  LineEdit9 = new QLineEdit(this, "LineEdit9");
  LineEdit9->setEnabled(FALSE);

  MetabolitesWidget1Layout->addWidget(LineEdit9, 8, 1);

  Line1_2 = new QFrame(this, "Line1_2");
  Line1_2->setFrameShape(QFrame::HLine);
  Line1_2->setFrameShadow(QFrame::Sunken);
  Line1_2->setFrameShape(QFrame::HLine);

  MetabolitesWidget1Layout->addMultiCellWidget(Line1_2, 5, 5, 0, 3);

  LineEdit8 = new QLineEdit(this, "LineEdit8");
  LineEdit8->setEnabled(FALSE);

  MetabolitesWidget1Layout->addWidget(LineEdit8, 7, 3);

  Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setFrameShadow(QFrame::Sunken);
  Line1->setFrameShape(QFrame::HLine);

  MetabolitesWidget1Layout->addMultiCellWidget(Line1, 9, 9, 0, 3);

  TextLabel12 = new QLabel(this, "TextLabel12");
  TextLabel12->setText(trUtf8("Transient Time"));

  MetabolitesWidget1Layout->addWidget(TextLabel12, 8, 0);

  TextLabel7 = new QLabel(this, "TextLabel7");
  TextLabel7->setText(trUtf8("Initial  Concentration"));

  MetabolitesWidget1Layout->addWidget(TextLabel7, 6, 0);

  LineEdit5 = new QLineEdit(this, "LineEdit5");

  MetabolitesWidget1Layout->addWidget(LineEdit5, 7, 1);

  Line1_3 = new QFrame(this, "Line1_3");
  Line1_3->setFrameShape(QFrame::HLine);
  Line1_3->setFrameShadow(QFrame::Sunken);
  Line1_3->setFrameShape(QFrame::HLine);

  MetabolitesWidget1Layout->addMultiCellWidget(Line1_3, 2, 2, 0, 3);

  ButtonGroup2 = new QButtonGroup(this, "ButtonGroup2");
  ButtonGroup2->setFrameShape(QButtonGroup::WinPanel);
  ButtonGroup2->setTitle(trUtf8("&Metabolite Status Selection"));
  ButtonGroup2->setExclusive(TRUE);

  RadioButton1 = new QRadioButton(ButtonGroup2, "RadioButton1");
  RadioButton1->setGeometry(QRect(30, 20, 91, 20));
  RadioButton1->setText(trUtf8("Fixed"));

  RadioButton2 = new QRadioButton(ButtonGroup2, "RadioButton2");
  RadioButton2->setGeometry(QRect(110, 20, 91, 20));
  RadioButton2->setText(trUtf8("Variable"));

  MetabolitesWidget1Layout->addMultiCellWidget(ButtonGroup2, 3, 3, 0, 3);

  ButtonGroup3 = new QButtonGroup(this, "ButtonGroup3");
  ButtonGroup3->setFrameShape(QButtonGroup::WinPanel);
  ButtonGroup3->setFrameShadow(QButtonGroup::Sunken);
  ButtonGroup3->setTitle(trUtf8("&Metabolite Status"));
  ButtonGroup3->setExclusive(TRUE);

  QWidget* privateLayoutWidget = new QWidget(ButtonGroup3, "Layout12");
  privateLayoutWidget->setGeometry(QRect(21, 29, 219, 22));
  Layout12 = new QHBoxLayout(privateLayoutWidget, 0, 6, "Layout12");

  RadioButton3 = new QRadioButton(privateLayoutWidget, "RadioButton3_2");
  RadioButton3->setEnabled(FALSE);
  RadioButton3->setText(trUtf8("Fixed"));
  Layout12->addWidget(RadioButton3);

  RadioButton4 = new QRadioButton(privateLayoutWidget, "RadioButton4_2");
  RadioButton4->setEnabled(FALSE);
  RadioButton4->setText(trUtf8("Independent"));
  Layout12->addWidget(RadioButton4);

  RadioButton5 = new QRadioButton(privateLayoutWidget, "RadioButton5_2");
  RadioButton5->setEnabled(FALSE);
  RadioButton5->setText(trUtf8("Dependent"));
  Layout12->addWidget(RadioButton5);

  MetabolitesWidget1Layout->addMultiCellWidget(ButtonGroup3, 4, 4, 0, 3);
  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
  connect(this, SIGNAL(signal_emitted(QString &)), (ListViews*)parent, SLOT(slotMetaboliteTableChanged(QString &)));
  connect(ComboBox1, SIGNAL(activated(const QString &)), (ListViews*)parent, SLOT(slotCompartmentSelected(const QString &)));
  connect(LineEdit4, SIGNAL(selectionChanged()), (ListViews*)parent, SLOT(slotCompartmentSelected()));
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

  CCopasiVectorN< CMetab > metabolites = mModel->getMetabolites();

  //Now filling the table.
  CMetab *metab1;

  int i = 0;
  int myValue = -1;

  for (; i < metabolites.size(); i++)
    {
      metab1 = metabolites[i];
      int value = QString::compare(metab1->getName().c_str(), setValue);

      if (!value)
        {
          myValue = i;
          break;
        }
    }

  if (myValue != -1)
    {
      metab1 = metabolites[myValue];
      //metab1 = metabolites[(std::string)setValue];

      if (metab1 != NULL)
        {
          loadName(setValue);
          //metab1=NULL;
          return 1;
        }
      else
        return 0;
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

  name = setValue;
  CMetab *metab;

  int i = 0;
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
      int m;
      for (m = 0; m < allcompartments.size(); m++)
        {
          //showMessage("mudita","It comes here");

          compt = allcompartments[m];
          //ComboBox1->insertStringList(compt->getName().c_str(),j);
          ComboBox1->insertItem(compt->getName().c_str(), m - 1);
        }
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
  std::string filename = ((std::string) name.latin1()) + ".gps";
  CWriteConfig *Met = new CWriteConfig(filename);

  CCopasiVectorN< CMetab > metabolites = mModel->getMetabolites();
  CMetab *metab;
  metab = metabolites[myValue];

  //for Initial Concentration and Initial Number
  QString initialConcentration(LineEdit4->text());
  double temp1;
  temp1 = initialConcentration.toDouble();
  metab->setInitialConcentration((float)temp1);

  QString initialNumber(LineEdit5->text());
  int temp2;
  temp2 = initialNumber.toInt();
  metab->setInitialNumberInt(temp2);
  //if (QString::number(metab->getStatus()) == "0")

  if (RadioButton1->isChecked() == true && QString::number(metab->getStatus()) == "0")
    {
      metab->setStatus(0);
    }
  else
    {
      metab->setStatus(1);
    }

  mModel->save(*Met);
  //metab->save(*Met);
  //Copasi->Model->save(*Met);
  delete Met;
}
