/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CompartmentsWidget1.cpp,v $
   $Revision: 1.58 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:37 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/CompartmentsWidget1.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the individual
 ** Compartments----It is the second level of Compartments
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
#include "utilities/CCopasiVector.h"
#include "CompartmentsWidget1.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "utilities/CMethodParameter.h"
#include "listviews.h"
#include "report/CKeyFactory.h"

/*
 *  Constructs a CompartmentsWidget1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
CompartmentsWidget1::CompartmentsWidget1(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    objKey("")
{
  if (!name)
    setName("CompartmentsWidget1");
  setCaption(trUtf8("CompartmentsWidget1"));
  CompartmentsWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "CompartmentsWidget1Layout");

  LineEdit4 = new QLineEdit(this, "LineEdit4");
  LineEdit4->setEnabled(FALSE);
  LineEdit4->setReadOnly(TRUE);

  CompartmentsWidget1Layout->addWidget(LineEdit4, 3, 1);

  LineEdit1 = new QLineEdit(this, "LineEdit1");

  CompartmentsWidget1Layout->addWidget(LineEdit1, 0, 1);

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Initial  Volume"));

  CompartmentsWidget1Layout->addWidget(TextLabel2, 2, 0);

  TextLabel2_2 = new QLabel(this, "TextLabel2_2");
  TextLabel2_2->setText(trUtf8("Transient Volume"));

  CompartmentsWidget1Layout->addWidget(TextLabel2_2, 3, 0);

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Compartment Name"));

  CompartmentsWidget1Layout->addWidget(TextLabel1, 0, 0);

  Line4 = new QFrame(this, "Line4");
  Line4->setFrameShape(QFrame::HLine);
  Line4->setFrameShadow(QFrame::Sunken);
  Line4->setFrameShape(QFrame::HLine);

  CompartmentsWidget1Layout->addMultiCellWidget(Line4, 1, 1, 0, 1);

  Line4_2 = new QFrame(this, "Line4_2");
  Line4_2->setFrameShape(QFrame::HLine);
  Line4_2->setFrameShadow(QFrame::Sunken);
  Line4_2->setFrameShape(QFrame::HLine);

  CompartmentsWidget1Layout->addMultiCellWidget(Line4_2, 4, 4, 0, 1);

  ListBox1 = new QListBox(this, "ListBox1");

  CompartmentsWidget1Layout->addMultiCellWidget(ListBox1, 5, 6, 1, 1);
  QSpacerItem* spacer = new QSpacerItem(131, 270, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CompartmentsWidget1Layout->addItem(spacer, 6, 0);

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Metabolite Name"));

  CompartmentsWidget1Layout->addWidget(TextLabel3, 5, 0);

  LineEdit3 = new QLineEdit(this, "LineEdit3");
  LineEdit3->setFrameShape(QLineEdit::LineEditPanel);
  LineEdit3->setFrameShadow(QLineEdit::Sunken);

  CompartmentsWidget1Layout->addWidget(LineEdit3, 2, 1);

  Layout5 = new QHBoxLayout(0, 0, 6, "Layout5");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout5->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Cancel"));
  Layout5->addWidget(cancelChanges);

  CompartmentsWidget1Layout->addMultiCellLayout(Layout5, 8, 8, 0, 1);

  Line4_3 = new QFrame(this, "Line4_3");
  Line4_3->setFrameShape(QFrame::HLine);
  Line4_3->setFrameShadow(QFrame::Sunken);
  Line4_3->setFrameShape(QFrame::HLine);

  CompartmentsWidget1Layout->addMultiCellWidget(Line4_3, 7, 7, 0, 1);

  // signals and slots connections
  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
  connect(ListBox1, SIGNAL(selected(const QString&)), this, SLOT(slotListBoxCurrentChanged(const QString&)));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CompartmentsWidget1::~CompartmentsWidget1()
{
  // no need to delete child widgets, Qt does it all for us
}

/* This function loads the compartments widget when its name is
  clicked in the tree   */
bool CompartmentsWidget1::loadFromCompartment(const CCompartment * compartn)
{
  LineEdit1->setText(compartn->getName().c_str());

  const CCopasiVectorNS < CMetab > & Metabs = compartn->getMetabolites();
  C_INT32 noOfMetabolitesRows = Metabs.size();
  const CMetab *mtb;
  ListBox1->setAutoScrollBar(true);
  ListBox1->clear();
  C_INT32 j;
  for (j = 0; j < noOfMetabolitesRows; j++)
    {
      mtb = Metabs[j];
      ListBox1->insertItem(mtb->getName().c_str());
    }

  volumeSave = QString::number(compartn->getInitialVolume());
  LineEdit3->setText(volumeSave);

  LineEdit4->setText(QString::number(compartn->getVolume()));
  LineEdit4->setReadOnly(true);

  return true; //TODO really check
}

bool CompartmentsWidget1::saveToCompartment()
{
  CCompartment* comp = (CCompartment*)(CCopasiContainer*)CKeyFactory::get(objKey);
  if (!comp) return false;

  //name
  QString name(LineEdit1->text());
  if (name.latin1() != comp->getName())
    {
      comp->setName(name.latin1());
      //TODO: update something else in the model?
      ListViews::notify(ListViews::COMPARTMENT, ListViews::RENAME, objKey);
    }

  //volume
  QString volume(LineEdit3->text());
  if (volume != volumeSave)
    {
      double m1;
      m1 = volume.toDouble();
      comp->setInitialVolume(m1);
      ListViews::notify(ListViews::COMPARTMENT, ListViews::CHANGE, objKey);
    }
  return true; //TODO: really check
}

void CompartmentsWidget1::slotBtnCancelClicked()
{
  //let the user confirm
  enter(objKey); // reload
}

void CompartmentsWidget1::slotBtnOKClicked()
{
  //let the user confirm?
  saveToCompartment();
}

void CompartmentsWidget1::slotListBoxCurrentChanged(const QString & m)
{
  //TODO do not really know what to do here. May be switch to metabolite widget?
}

bool CompartmentsWidget1::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
      //TODO: check if it really is a compartment
      if (CKeyFactory::get(objKey)) return loadFromCompartment((CCompartment*)(CCopasiContainer*)CKeyFactory::get(objKey));
      break;

    default:
      break;
    }
  return true;
}

bool CompartmentsWidget1::leave()
{
  //let the user confirm?
  return saveToCompartment();
}

bool CompartmentsWidget1::enter(const std::string & key)
{
  objKey = key;
  CCompartment* comp = (CCompartment*)(CCopasiContainer*)CKeyFactory::get(key);
  //TODO: check if it really is a compartment

  if (comp) return loadFromCompartment(comp);
  else return false;
}
