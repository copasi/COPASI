/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MoietyWidget1.cpp,v $
   $Revision: 1.47 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/18 16:26:50 $
   End CVS Header */

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
#include "MoietyWidget1.h"
#include "model/CModel.h"
#include "model/CMoiety.h"
#include "listviews.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "qtUtilities.h"
#include "report/CKeyFactory.h"

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

  // signals and slots connections
}

MoietyWidget1::~MoietyWidget1()
{}

bool MoietyWidget1::loadFromMoiety(const CMoiety * moiety)
{
  if (!moiety) return false;

  textBrowser->setText(FROM_UTF8(moiety->getDescription(CCopasiDataModel::Global->getModel())));

  LineEdit3->setText(FROM_UTF8(moiety->getObjectName()));

  LineEdit2->setText(QString::number(moiety->getNumber()));

  return true;
}

bool MoietyWidget1::update(ListViews::ObjectType objectType,
                           ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;
  return loadFromMoiety(dynamic_cast< CMoiety * >(GlobalKeys.get(objKey)));
}

bool MoietyWidget1::leave()
{
  return true;
}

bool MoietyWidget1::enter(const std::string & key)
{
  objKey = key;
  CMoiety* moiety = dynamic_cast< CMoiety * >(GlobalKeys.get(objKey));

  if (moiety) return loadFromMoiety(moiety);
  else return false;
}
