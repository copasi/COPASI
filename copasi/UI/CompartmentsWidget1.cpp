/**********************************************************************
 **  $ CopasiUI/CompartmentsWidget1.cpp                 
 **  $ Author  : Mudita Singhal

 ** This file is used to create the GUI FrontPage for the  information 
 ** obtained from the data model about the Compartments----It is 
 ** Basically the Second level of Compartments.
 ***********************************************************************/
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include <qlistbox.h>
#include <qfont.h>

#include "copasi.h"
#include "utilities/utilities.h"
#include "CompartmentsWidget1.h"
#include "model/model.h"
#include "listviews.h"

/*
 *  Constructs a CompartmentsWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 */

CompartmentsWidget1::CompartmentsWidget1(QWidget *parent, const char * name, WFlags f)
    : QWidget(parent, name, f)

{
  //This is to make the Main Frame of the page
  //The Main layout used is the Vertical Layout
  QVBoxLayout *vboxLayout = new QVBoxLayout(this, 0);
  Frame1 = new QFrame(this, "Frame1");
  Frame1->setFrameShape(QFrame::Box);
  Frame1->setFrameShadow(QFrame::Plain);
  vboxLayout->addWidget(Frame1);
  QVBoxLayout *vboxLayout1 = new QVBoxLayout(Frame1, 0);
  vboxLayout1->addSpacing(1);

  //This Frame had to be added because of the border around the frame
  //The grid Layout is used for this frame
  Frame3 = new QFrame(Frame1, "Frame3");
  vboxLayout1->addWidget(Frame3);
  QGridLayout *gridLayout = new QGridLayout(Frame3, 0);

  //All the other frames(rows) are embeded in it
  Frame2 = new QFrame(Frame3, "Frame2");
  gridLayout->addWidget(Frame2, 0, 0, 0);
  QVBoxLayout *verticalLayout1 = new QVBoxLayout(Frame2, 0);
  verticalLayout1->addSpacing(25);

  //Frame for Ist Row
  Frame4a = new QFrame(Frame2, "Frame4a");
  verticalLayout1->addWidget(Frame4a);
  QHBoxLayout *hBoxLayout4a = new QHBoxLayout(Frame4a, 0);
  hBoxLayout4a->addSpacing(15);

  TextLabel1 = new QLabel("Compartment Name", Frame4a);
  hBoxLayout4a->addWidget(TextLabel1);
  hBoxLayout4a->addSpacing(17);
  LineEdit1 = new QLineEdit("", Frame4a);
  hBoxLayout4a->addWidget(LineEdit1);
  hBoxLayout4a->addSpacing(60);

  verticalLayout1->addSpacing(85);
  Frame4_2 = new QFrame(Frame2, "Frame4_2");
  verticalLayout1->addWidget(Frame4_2);
  QHBoxLayout *hBoxLayout4_2 = new QHBoxLayout(Frame4_2, 0);

  //Frame for 2nd left hand side Row
  Frame4c = new QFrame(Frame4_2, "Frame4c");
  hBoxLayout4_2->addWidget(Frame4c);
  QHBoxLayout *hBoxLayout4c = new QHBoxLayout(Frame4c, 0);
  hBoxLayout4c->addSpacing(15);

  TextLabel3 = new QLabel("Initial  Volume", Frame4c);
  hBoxLayout4c->addWidget(TextLabel3);
  hBoxLayout4c->addSpacing(43);

  LineEdit3 = new QLineEdit("", Frame4c);
  LineEdit3->setGeometry(QRect(150, 90, 121, 21));
  hBoxLayout4c->addWidget(LineEdit3);
  hBoxLayout4c->addSpacing(20);

  //Frame for 2nd right hand side subpart
  Frame4d = new QFrame(Frame4_2, "Frame4d");
  hBoxLayout4_2->addWidget(Frame4d);
  QHBoxLayout *hBoxLayout4d = new QHBoxLayout(Frame4d, 0);

  TextLabel4 = new QLabel("Transient Volume", Frame4d);
  hBoxLayout4d->addWidget(TextLabel4);
  hBoxLayout4d->addSpacing(5);
  LineEdit4 = new QLineEdit("", Frame4d);
  hBoxLayout4d->addWidget(LineEdit4);
  LineEdit4->setEnabled(false);
  hBoxLayout4d->addSpacing(20);

  //Frame for 3rd Row
  Frame4b = new QFrame(Frame2, "Frame4b");
  verticalLayout1->addWidget(Frame4b);
  QHBoxLayout *hBoxLayout4b = new QHBoxLayout(Frame4b, 0);

  TextLabel2 = new QLabel("Metabolite Name", Frame4b);
  hBoxLayout4b->addWidget(TextLabel2);
  //hBoxLayout4b->addSpacing(-36);

  ListBox1 = new QListBox(Frame4b, "ListBox1");
  // ListBox1->setGeometry(QRect(120, 40, 31, 41));
  hBoxLayout4b->addWidget(ListBox1);
  hBoxLayout4b->addSpacing(287);

  Frame4_1 = new QFrame(Frame2, "Frame4_1");
  verticalLayout1->addWidget(Frame4_1);
  QHBoxLayout *hBoxLayout4_1 = new QHBoxLayout(Frame4_1, 0);

  commitChanges = new QPushButton("&Commit Changes", Frame4_1);
  cancelChanges = new QPushButton("&Cancel Changes", Frame4_1);
  commitChanges->setFont(QFont("Times", 10, QFont::Bold));
  cancelChanges->setFont(QFont("Times", 10, QFont::Bold));

  hBoxLayout4_1->addWidget(commitChanges);
  hBoxLayout4_1->addWidget(cancelChanges);

  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
  connect(this, SIGNAL(signal_emitted(QString &)), (ListViews*)parent, SLOT(slotCompartmentTableChanged(QString &)));
}

/*This function is used to connect this class to the listviews
    class to basically choose the right widget to display   */
int CompartmentsWidget1::isName(QString setValue)
{
  if (mModel == NULL)
    {
      return 0;
    }

  name = setValue;
  CCopasiVectorNS < CCompartment > & compartments = mModel->getCompartments();

  if (compartments[(std::string) setValue] != NULL)
    {
      loadName(setValue);
      return 1;
    }
  else
    return 0;
}

/*This function is to load the model for the compartments*/
void CompartmentsWidget1::loadCompartments(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
    }
}

/* This function loads the compartments widget when its name is
  clicked in the tree   */
void CompartmentsWidget1::loadName(QString setValue)
{
  if (mModel == NULL)
    {
      return;
    }

  CCopasiVectorNS < CCompartment > & compartments = mModel->getCompartments();

  CCompartment *compartn;

  compartn = compartments[(std::string)setValue];

  LineEdit1->setText(compartn->getName().c_str());
  Compartment1_Name = new QString(compartn->getName().c_str());

  CCopasiVectorNS < CMetab > & Metabs = compartn->metabolites();
  C_INT32 noOfMetabolitesRows = Metabs.size();
  CMetab *mtb;
  ListBox1->setFixedSize(100, 150);
  ListBox1->setAutoScrollBar(true);
  ListBox1->clear();

  for (C_INT32 j = 0; j < noOfMetabolitesRows; j++)
    {
      mtb = Metabs[j];
      ListBox1->insertItem(mtb->getName().c_str());
    }

  LineEdit3->setText(QString::number(compartn->getVolume()));

  LineEdit4->setText(QString::number(compartn->getVolume()));
  LineEdit4->setReadOnly(true);
}

void CompartmentsWidget1::slotBtnCancelClicked()
{
  QMessageBox::information(this, "Compartments Widget", "Do you really want to cancel changes");
  emit signal_emitted(*Compartment1_Name);
}

void CompartmentsWidget1::slotBtnOKClicked()
{
  QMessageBox::information(this, "Compartments Widget", "Do you really want to commit changes");
  std::string filename = ((std::string) name.latin1()) + ".gps";
  CWriteConfig *Com = new CWriteConfig(filename);
  CCopasiVectorNS < CCompartment > & compartments1 = mModel->getCompartments();
  CCompartment *compartn1;
  compartn1 = compartments1[(std::string)name.latin1()];

  QString volume(LineEdit3->text());
  double m1;
  m1 = volume.toDouble();
  compartn1->setVolume((float)m1);
  mModel->save(*Com);
  //compartn1->save(*Com);
  //Copasi->Model->save(*Com);
  delete Com;
}

//last function ends
