/*******************************************************************
 **  $ CopasiUI/MoietyWidget1.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the  information 
 ** obtained from the data model about the Moiety----It is 
 ** the Second level of Moieties.
 ********************************************************************/
#include <qlabel.h>
#include <qlistbox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include "copasi.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CMethodParameter.h"
#include "MoietyWidget1.h"
#include "model/CModel.h"
#include "model/CMoiety.h"
#include "listviews.h"

/*
 *  Constructs a MoietyWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 */

MoietyWidget1::MoietyWidget1(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)

{
  if (!name)
    setName("MoietyWidget1");
  setCaption(trUtf8("MoietyWidget1"));
  MoietyWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "MoietyWidget1Layout");

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Equation"));

  MoietyWidget1Layout->addWidget(TextLabel1, 2, 0);

  textBrowser = new QTextBrowser (this, "Text Browser");
  textBrowser->setReadOnly(TRUE);

  MoietyWidget1Layout->addWidget(textBrowser, 2, 1);

  LineEdit2 = new QLineEdit(this, "LineEdit2");
  LineEdit2->setEnabled(FALSE);

  MoietyWidget1Layout->addWidget(LineEdit2, 0, 1);

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Total Particle Number"));

  MoietyWidget1Layout->addWidget(TextLabel2, 0, 0);

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Dependent Metabolite"));

  MoietyWidget1Layout->addWidget(TextLabel3, 1, 0);

  LineEdit3 = new QLineEdit(this, "LineEdit3");
  LineEdit3->setEnabled(FALSE);

  MoietyWidget1Layout->addWidget(LineEdit3, 1, 1);
  QSpacerItem* spacer = new QSpacerItem(430, 171, QSizePolicy::Expanding, QSizePolicy::Minimum);
  MoietyWidget1Layout->addMultiCell(spacer, 3, 3, 0, 1);
  connect(this, SIGNAL(signal_emitted(const QString &)), (ListViews*)parent, SLOT(slotMoietyTableChanged(const QString &)));

  connect(this, SIGNAL(leaf(CModel*)), (ListViews*)parent, SLOT(loadMoietiesNodes(CModel*)));
  connect(this, SIGNAL(updated()), (ListViews*)parent, SLOT(dataModelUpdated()));
}

MoietyWidget1::~MoietyWidget1()
{}

/*This function is used to connect this class to the listviews
    class to basically choose the right widget to display   */
int MoietyWidget1::isName(QString setValue)
{
  if (mModel == NULL)
    {
      return 0;
    }

  //  const CCopasiVectorN < CMoiety > &moieties = mModel->getMoieties();
  //  C_INT32 noOfMoietyRows = moieties.size();
  //  CMoiety *moiety1;

  //  moiety1 = moieties[(std::string) setValue];
  //  if (moiety1 != NULL)
  if (mModel->getMoieties().getIndex((std::string)setValue.latin1()) != C_INVALID_INDEX)
    {
      loadName(setValue);
      return 1;
    }
  else
    return 0;
}

/*This function is to load the model for the Moieties*/
void MoietyWidget1::loadMoieties(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
    }
}

/* This function loads the moiety widget when its name is
   clicked in the tree   */

void MoietyWidget1::loadName(QString setValue)
{
  if (mModel == NULL)
    {
      return;
    }

  const CCopasiVectorN < CMoiety > &moieties = mModel->getMoieties();
  CMoiety *moiety;
  moiety = moieties[(std::string)setValue.latin1()];
  textBrowser->setText(moiety->getDescription().c_str());
  //ListBox1->insertItem(moiety->getDescription().c_str());

  /*  CCopasiVectorNS < CMetab > & Metabs = compartn->metabolites();
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

  */

  LineEdit3->setText(moiety->getName().c_str());
  Moiety1_Name = new QString(moiety->getName().c_str());

  LineEdit2->setText(QString::number(moiety->getNumber()));
}

void MoietyWidget1::slotBtnCancelClicked()
{
  //QMessageBox::information(this, "Moiety Widget","Clicked Ok button On Moiety widget.(Inside MoietyWidget::slotBtnCancelClicked())");
  emit signal_emitted(*Moiety1_Name);
}

void MoietyWidget1::slotBtnOKClicked()
{
  QMessageBox::information(this, "Moiety Widget", "Clicked Ok button On Moiety widget.(Inside MoietyWidget::slotBtnCancelClicked())");
  // emit signal_emitted(*Compartment1_Name);
}

///end of all the functions
