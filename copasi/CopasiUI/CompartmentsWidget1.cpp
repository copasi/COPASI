/**********************************************************************
 **  $ CopasiUI/CompartmentsWidget1.cpp                 
 **  $ Author  : Mudita Singhal

 ** This file is used to create the GUI FrontPage for the  information 
 ** obtained from the data model about the Compartments----It is 
 ** Basically the Second level of Compartments.
 ***********************************************************************/
#include "CompartmentsWidget1.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include "listviews.h"
#include <qlistbox.h> 
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
  QGridLayout *gridLayout1 = new QGridLayout(Frame2, 0);

  //Frame for Ist Row
  Frame4a = new QFrame(Frame2, "Frame4a");
  gridLayout1->addWidget(Frame4a, 0, 0, 0);
  QHBoxLayout *hBoxLayout4a = new QHBoxLayout(Frame4a, 0);
  hBoxLayout4a->addSpacing(15);

  TextLabel1 = new QLabel("Compartment Name", Frame4a);
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

  TextLabel2 = new QLabel("Metabolite Name", Frame4b);
  hBoxLayout4b->addWidget(TextLabel2);
  hBoxLayout4b->addSpacing(40);

  ListBox1 = new QListBox(Frame4b, "ListBox1");
  ListBox1->setGeometry(QRect(120, 40, 31, 41));
  hBoxLayout4b->addWidget(ListBox1);
  hBoxLayout4b->addSpacing(20);

  //Frame for 3rd Row
  Frame4c = new QFrame(Frame2, "Frame4c");
  gridLayout1->addWidget(Frame4c, 2, 0, 0);
  QHBoxLayout *hBoxLayout4c = new QHBoxLayout(Frame4c, 0);
  hBoxLayout4c->addSpacing(15);

  TextLabel3 = new QLabel("Initial  Volume", Frame4c);
  hBoxLayout4c->addWidget(TextLabel3);
  hBoxLayout4c->addSpacing(43);

  LineEdit3 = new QLineEdit("", Frame4c);
  LineEdit3->setGeometry(QRect(150, 90, 121, 21));
  hBoxLayout4c->addWidget(LineEdit3);
  hBoxLayout4c->addSpacing(20);

  //Frame for 4th subpart
  Frame4d = new QFrame(Frame2, "Frame4d");
  gridLayout1->addWidget(Frame4d, 2, 1, 0);
  QHBoxLayout *hBoxLayout4d = new QHBoxLayout(Frame4d, 0);

  TextLabel4 = new QLabel("Transient Volume", Frame4d);
  hBoxLayout4d->addWidget(TextLabel4);
  hBoxLayout4d->addSpacing(5);
  LineEdit4 = new QLineEdit("", Frame4d);
  hBoxLayout4d->addWidget(LineEdit4);
  LineEdit4->setEnabled(false);
  hBoxLayout4d->addSpacing(20);

  //This is for the cancel and the commit buttons
  commitChanges = new QPushButton("&Commit Changes", Frame2);
  cancelChanges = new QPushButton("&Cancel Changes", Frame2);
  gridLayout1->addWidget(commitChanges, 6, 0, 0);
  gridLayout1->addWidget(cancelChanges, 6, 1, 0);
}

/*This function is used to connect this class to the listviews
    class to basically choose the right widget to display   */
int CompartmentsWidget1::isName(QString setValue)
{
  if (mModel == NULL)
    {
      return 0;
    }

  CCopasiVectorNS < CCompartment > & compartments = mModel->getCompartments();

  if (compartments[(string) setValue] != NULL)
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
      return ;
    }

  CCopasiVectorNS < CCompartment > & compartments = mModel->getCompartments();

  CCompartment *compartn;

  compartn = compartments[(string)setValue];

  LineEdit1->setText(compartn->getName().c_str());

  CCopasiVectorNS < CMetab > & Metabs = compartn->metabolites();
  C_INT32 noOfMetabolitesRows = Metabs.size();
  CMetab *mtb;
  ListBox1->setFixedSize(100, 150);
  ListBox1->setAutoScrollBar(true);

  for (C_INT32 j = 0; j < noOfMetabolitesRows; j++)
    {
      mtb = Metabs[j];
      ListBox1->insertItem(mtb->getName().c_str());
    }

  LineEdit3->setText(QString::number(compartn->getVolume()));

  LineEdit4->setText(QString::number(compartn->getVolume()));
  LineEdit4->setReadOnly(true);
}

//last function ends
