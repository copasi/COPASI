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
#include "model/model.h"
#include "listviews.h"

/*
 *  Constructs a CompartmentsWidget1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
CompartmentsWidget1::CompartmentsWidget1(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
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
  connect(this, SIGNAL(name_changed(const QString &)), (ListViews*)parent, SLOT(slotMetaboliteTableChanged(const QString &)));
  connect(this, SIGNAL(signal_emitted(const QString &)), (ListViews*)parent, SLOT(slotCompartmentTableChanged(const QString &)));

  connect(this, SIGNAL(leaf(CModel*)), (ListViews*)parent, SLOT(loadCompartmentsNodes(CModel*)));
  connect(this, SIGNAL(updated()), (ListViews*)parent, SLOT(dataModelUpdated()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CompartmentsWidget1::~CompartmentsWidget1()
{
  // no need to delete child widgets, Qt does it all for us
}

/*This function is used to connect this class to the listviews
    class to basically choose the right widget to display   */
int CompartmentsWidget1::isName(QString setValue)
{
  if (mModel == NULL)
    {
      return 0;
    }

  //  const CCopasiVectorNS < CCompartment > & compartments = mModel->getCompartments();

  //  if (compartments[(std::string) setValue] != NULL)
  if (mModel->getCompartments().getIndex((std::string)setValue.latin1()) != C_INVALID_INDEX)
    {
      loadName(setValue);
      name = setValue;
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

  const CCopasiVectorNS < CCompartment > & compartments = mModel->getCompartments();

  const CCompartment *compartn;

  compartn = compartments[(std::string)setValue.latin1()];

  LineEdit1->setText(compartn->getName().c_str());
  Compartment1_Name = new QString(compartn->getName().c_str());

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

  LineEdit3->setText(QString::number(compartn->getInitialVolume()));

  LineEdit4->setText(QString::number(compartn->getVolume()));
  LineEdit4->setReadOnly(true);
}

void CompartmentsWidget1::slotBtnCancelClicked()
{
  //QMessageBox::information(this, "Compartments Widget", "Do you really want to cancel changes");
  emit signal_emitted(*Compartment1_Name);
}

void CompartmentsWidget1::slotBtnOKClicked()
{
  const CCopasiVectorNS < CCompartment > & compartments1 = mModel->getCompartments();
  CCompartment *compartn1;
  compartn1 = compartments1[name.latin1()];

  QString volume(LineEdit3->text());
  double m1;
  m1 = volume.toDouble();
  compartn1->setInitialVolume(m1);
  compartn1->setName(std::string(LineEdit1->text().latin1()));
  name = LineEdit1->text();

  emit updated();
  emit leaf(mModel);
  emit signal_emitted(*Compartment1_Name);
}

void CompartmentsWidget1::slotListBoxCurrentChanged(const QString & m)
{
  emit name_changed(m);
}
//last function ends
