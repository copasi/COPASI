/**********************************************************************
 **  $ CopasiUI/MetabolitesWidget1.cpp                 
 **  $ Author  : Mudita Singhal

 ** This file is used to create the GUI FrontPage for the  information 
 ** obtained from the data model about the Metabolites----It is 
 ** Basically the Second level of Metabolites.
 ***********************************************************************/
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
#include <qfont.h>

#include "copasi.h"
#include "MetabolitesWidget1.h"
#include "model/model.h"
#include "listviews.h"

/*
 *  Constructs a MetabolitesWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 */

MetabolitesWidget1::MetabolitesWidget1(QWidget *parent, const char * name, WFlags f)
    : QWidget(parent, name, f)

{
  //This is to make the Main Frame of the page
  //The Main layout used is the Vertical Layout
  QVBoxLayout *vboxLayout = new QVBoxLayout(this, 0);
  Frame1 = new QFrame(this, "Frame1");
  Frame1->setFrameShape(QFrame::Box);
  Frame1->setFrameShadow(QFrame::Plain);
  vboxLayout->addWidget(Frame1);

  //This Frame had to be added because of the border around the frame
  //The grid Layout is used for this frame
  QVBoxLayout *vboxLayout1 = new QVBoxLayout(Frame1, 0);
  vboxLayout1->addSpacing(1);
  Frame3 = new QFrame(Frame1, "Frame3");
  vboxLayout1->addWidget(Frame3);
  QGridLayout *gridLayout = new QGridLayout(Frame3, 0);

  //All the other frames(rows) are embedded in it
  Frame2 = new QFrame(Frame3, "Frame2");
  gridLayout->addWidget(Frame2, 0, 0, 0);
  QGridLayout *gridLayout1 = new QGridLayout(Frame2, 0);

  //Frame for Ist Row
  Frame4a = new QFrame(Frame2, "Frame4a");
  gridLayout1->addWidget(Frame4a, 0, 0, 0);
  QHBoxLayout *hBoxLayout4a = new QHBoxLayout(Frame4a, 0);
  hBoxLayout4a->addSpacing(15);

  TextLabel1 = new QLabel("Metabolite Name", Frame4a);
  hBoxLayout4a->addWidget(TextLabel1);
  hBoxLayout4a->addSpacing(17);
  LineEdit1 = new QLineEdit("", Frame4a);
  hBoxLayout4a->addWidget(LineEdit1);
  hBoxLayout4a->addSpacing(20);

  //Frame for 2nd Row
  Frame4b = new QFrame(Frame2, "Frame4b");
  gridLayout1->addWidget(Frame4b, 1, 0, 0);
  QHBoxLayout *hBoxLayout4b = new QHBoxLayout(Frame4b, 0);
  hBoxLayout4b->addSpacing(15);

  TextLabel2 = new QLabel("Compartment Name", Frame4b);
  hBoxLayout4b->addWidget(TextLabel2);
  //hBoxLayout4b->addSpacing(-5);
  ComboBox1 = new QComboBox(Frame4b, "ComboBox1");
  hBoxLayout4b->addWidget(ComboBox1);
  hBoxLayout4b->addSpacing(20);

  //Frame for 3rd Row
  Frame4c = new QFrame(Frame2, "Frame4c");
  gridLayout1->addWidget(Frame4c, 2, 0, 0);
  QHBoxLayout *hBoxLayout4c = new QHBoxLayout(Frame4c, 0);
  hBoxLayout4c->addSpacing(15);

  ButtonGroup1 = new QButtonGroup ("&Metabolite Status Selection", Frame4c);
  hBoxLayout4c->addWidget(ButtonGroup1);
  hBoxLayout4c->addSpacing(20);
  ButtonGroup1->setExclusive(TRUE);

  RadioButton1 = new QRadioButton(ButtonGroup1, "RadioButton1");
  RadioButton1->setGeometry(QRect(10, 30, 87, 20));
  RadioButton1->setText(trUtf8("Fixed"));

  RadioButton2 = new QRadioButton(ButtonGroup1, "RadioButton2");
  RadioButton2->setGeometry(QRect(100, 30, 87, 20));
  RadioButton2->setText(trUtf8("Non-Fixed"));

  //Frame for 4th Row
  Frame4d = new QFrame(Frame2, "Frame4d");
  gridLayout1->addWidget(Frame4d, 3, 0, 0);
  QHBoxLayout *hBoxLayout4d = new QHBoxLayout(Frame4d, 0);
  hBoxLayout4d->addSpacing(15);

  TextLabel4 = new QLabel("Initial  Concentration", Frame4d);
  hBoxLayout4d->addWidget(TextLabel4);
  hBoxLayout4d->addSpacing(5);

  LineEdit4 = new QLineEdit("", Frame4d);
  LineEdit4->setGeometry(QRect(150, 90, 121, 21));
  hBoxLayout4d->addWidget(LineEdit4);
  hBoxLayout4d->addSpacing(20);

  //Frame for 5th Row
  Frame4e = new QFrame(Frame2, "Frame4e");
  gridLayout1->addWidget(Frame4e, 4, 0, 0);
  QHBoxLayout *hBoxLayout4e = new QHBoxLayout(Frame4e, 0);
  hBoxLayout4e->addSpacing(15);

  TextLabel5 = new QLabel("Initial  Number", Frame4e);
  TextLabel5->setGeometry(QRect(30, 360, 260, 40));
  hBoxLayout4e->addWidget(TextLabel5);
  hBoxLayout4e->addSpacing(32);

  LineEdit5 = new QLineEdit("", Frame4e);
  hBoxLayout4e->addWidget(LineEdit5);
  hBoxLayout4e->addSpacing(20);

  //Frame for 6th Row
  Frame4f = new QFrame(Frame2, "Frame4f");
  gridLayout1->addWidget(Frame4f, 2, 1, 0);
  QHBoxLayout *hBoxLayout4f = new QHBoxLayout(Frame4f, 0);

  GroupBox2 = new QGroupBox("Metabolite Status", Frame4f);
  hBoxLayout4f->addWidget(GroupBox2);
  hBoxLayout4f->addSpacing(20);

  RadioButton3 = new QRadioButton(GroupBox2, "RadioButton3");
  RadioButton3->setGeometry(QRect(10, 30, 87, 20));
  RadioButton3->setText(trUtf8("Fixed"));
  RadioButton3->setEnabled(false);

  RadioButton4 = new QRadioButton(GroupBox2, "RadioButton4");
  RadioButton4->setGeometry(QRect(80, 30, 87, 20));
  RadioButton4->setText(trUtf8("Independent"));
  RadioButton4->setEnabled(false);

  RadioButton5 = new QRadioButton(GroupBox2, "RadioButton5");
  RadioButton5->setGeometry(QRect(180, 30, 87, 20));
  RadioButton5->setText(trUtf8("Dependent"));
  RadioButton5->setEnabled(false);

  //Frame for 7th subpart
  Frame4g = new QFrame(Frame2, "Frame4g");
  gridLayout1->addWidget(Frame4g, 3, 1, 0);
  QHBoxLayout *hBoxLayout4g = new QHBoxLayout(Frame4g, 0);

  TextLabel7 = new QLabel("Transient Concentration", Frame4g);
  hBoxLayout4g->addWidget(TextLabel7);
  hBoxLayout4g->addSpacing(5);
  LineEdit7 = new QLineEdit("", Frame4g);
  hBoxLayout4g->addWidget(LineEdit7);
  LineEdit7->setEnabled(false);
  hBoxLayout4g->addSpacing(20);

  //Frame for 8th subpart
  Frame4h = new QFrame(Frame2, "Frame4h");
  gridLayout1->addWidget(Frame4h, 4, 1, 0);
  QHBoxLayout *hBoxLayout4h = new QHBoxLayout(Frame4h, 0);

  TextLabel8 = new QLabel("Transient Number" , Frame4h);
  hBoxLayout4h->addWidget(TextLabel8);
  hBoxLayout4h->addSpacing(32);
  LineEdit8 = new QLineEdit("", Frame4h);
  hBoxLayout4h->addWidget(LineEdit8);
  LineEdit8->setEnabled(false);
  hBoxLayout4h->addSpacing(20);

  //Frame for 9th subpart
  Frame4i = new QFrame(Frame2, "Frame4i");
  gridLayout1->addWidget(Frame4i, 5, 1, 0);
  QHBoxLayout *hBoxLayout4i = new QHBoxLayout(Frame4i, 0);

  TextLabel9 = new QLabel("Transient Time", Frame4i);
  hBoxLayout4i->addWidget(TextLabel9);
  hBoxLayout4i->addSpacing(45);
  LineEdit9 = new QLineEdit("", Frame4i);
  hBoxLayout4i->addWidget(LineEdit9);
  LineEdit9->setEnabled(false);
  hBoxLayout4i->addSpacing(20);

  //This is for the cancel and the commit buttons
  commitChanges = new QPushButton("&Commit Changes", Frame2);
  cancelChanges = new QPushButton("&Cancel Changes", Frame2);

  commitChanges->setFont(QFont("Times", 10, QFont::Bold));
  cancelChanges->setFont(QFont("Times", 10, QFont::Bold));

  gridLayout1->addWidget(commitChanges, 6, 0, 0);
  gridLayout1->addWidget(cancelChanges, 6, 1, 0);

  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
  connect(this, SIGNAL(signal_emitted(QString &)), (ListViews*)parent, SLOT(slotMetaboliteTableChanged(QString &)));

  connect(ComboBox1, SIGNAL(activated(const QString &)), (ListViews*)parent, SLOT(slotCompartmentSelected(const QString &)));
  connect(LineEdit4, SIGNAL(selectionChanged()), (ListViews*)parent, SLOT(slotCompartmentSelected()));
}

/*This function is used to connect this class to the listviews
    class to basically choose the correct widget to display   */

int MetabolitesWidget1::isName(QString setValue)
{
  if (mModel == NULL)
    {
      return 0;
    }

  vector < CMetab * > metabolites = mModel->getMetabolites();

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
      //metab1 = metabolites[(string)setValue];

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

  vector < CMetab * > metabolites = mModel->getMetabolites();

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
      RadioButton1->setChecked(FALSE);
      RadioButton2->setChecked(FALSE);
      RadioButton3->setChecked(FALSE);
      RadioButton4->setChecked(FALSE);
      RadioButton5->setChecked(FALSE);

      if (QString::number(metab->getStatus()) == "0")
        {
          RadioButton1->setChecked(TRUE);
          RadioButton3->setChecked(TRUE);
        }
      else
        if (QString::number(metab->getStatus()) == "1")
          {
            RadioButton2->setChecked(TRUE);
            RadioButton4->setChecked(TRUE);
          }
        else
          if (QString::number(metab->getStatus()) == "2")
            {
              RadioButton2->setChecked(TRUE);
              RadioButton5->setChecked(TRUE);
            }

      ComboBox1->setDuplicatesEnabled (false);

      for (int m = 0; m < allcompartments.size(); m++)
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
  QMessageBox::information(this, "Metabolites Widget", "Do you really want to cancel the changes?");
  emit signal_emitted(*Metabolite1_Name);
}

void MetabolitesWidget1::slotBtnOKClicked()
{
  QMessageBox::information(this, "Metabolites Widget", "Do you really want to commit the changes?");
  string filename = ((string) name.latin1()) + ".gps";
  CWriteConfig *Met = new CWriteConfig(filename);

  vector < CMetab * > metabolites = mModel->getMetabolites();
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

  if (RadioButton1->isChecked() == TRUE && QString::number(metab->getStatus()) == "0")
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
