// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/Attic/objectdebug.cpp,v $
//   $Revision: 1.12.2.2 $
//   $Name: Build-33 $
//   $Author: aekamal $
//   $Date: 2011/01/24 17:00:16 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "objectdebug.h"

#include <qvariant.h>
#include <q3textedit.h>
#include <sstream>
#include "copasi.h"
#include "model/CModelAnalyzer.h"
#include "model/CDotOutput.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "UI/qtUtilities.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiRootContainer.h"
/*
 *  Constructs a ObjectDebug as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
ObjectDebug::ObjectDebug(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, name, modal, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ObjectDebug::~ObjectDebug()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ObjectDebug::languageChange()
{
  retranslateUi(this);
}

class MyListViewItemWithPtr : public Q3ListViewItem
{
public:

  MyListViewItemWithPtr(Q3ListViewItem * parent, const CCopasiObject * ptr,
                        QString label1, QString label2 = QString::null,
                        QString label3 = QString::null, QString label4 = QString::null,
                        QString label5 = QString::null, QString label6 = QString::null,
                        QString label7 = QString::null, QString label8 = QString::null)
      : Q3ListViewItem(parent, label1, label2, label3, label4, label5, label6, label7, label8),
      mpObject(ptr)
  {}

  MyListViewItemWithPtr(Q3ListView * parent, const CCopasiObject * ptr,
                        QString label1, QString label2 = QString::null,
                        QString label3 = QString::null, QString label4 = QString::null,
                        QString label5 = QString::null, QString label6 = QString::null,
                        QString label7 = QString::null, QString label8 = QString::null)
      : Q3ListViewItem(parent, label1, label2, label3, label4, label5, label6, label7, label8),
      mpObject(ptr)
  {}

  const CCopasiObject * mpObject;
};

void ObjectDebug::addObjectRecursive(QWidget * parent, const void * ptr)
{
  const CCopasiObject * obj = static_cast<const CCopasiObject *>(ptr);
  Q3ListViewItem * element;

  std::string cn = obj->getCN();
  const CCopasiDataModel * pDM = obj->getObjectDataModel();
  const CCopasiObject* testObj = NULL;

  if (pDM)
    testObj = pDM->getObject(cn);

  //assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  QString flags;
  if (obj->isContainer()) flags += "C"; else flags += " ";
  if (obj->isVector()) flags += "V"; else flags += " ";
  if (obj->isMatrix()) flags += "M"; else flags += " ";
  if (obj->isNameVector()) flags += "N"; else flags += " ";
  if (obj->isReference()) flags += "R"; else flags += " ";
  if (obj->isNonUniqueName()) flags += " Nun"; else flags += " Unn";

  if (obj->isValueInt()) flags += "Int";
  else if (obj->isValueDbl()) flags += "Dbl";
  else if (obj->isValueBool()) flags += "Boo";
  else if (obj->isValueString()) flags += "Str";
  else if (obj->isStaticString()) flags += "SSt";
  else flags += "   ";

  if (!(testObj == obj)) flags += "EEE";

  QString value;

  if (obj->isValueDbl() && obj->getValuePointer())
    value = QString::number(*(C_FLOAT64*)obj->getValuePointer());
  else if (obj->isValueInt() && obj->getValuePointer())
    value = QString::number(*(C_INT32*)obj->getValuePointer());
  else if (obj->isValueString() && obj->getValuePointer())
    value = FROM_UTF8(*(std::string*)obj->getValuePointer());
  else if (obj->isValueBool() && obj->getValuePointer())
    {
      if (*(bool*)obj->getValuePointer()) value = "true"; else value = "false";
    }
  else
    value = "";

  element = new MyListViewItemWithPtr((Q3ListViewItem*)parent, obj,
                                      FROM_UTF8(obj->getObjectName()),
                                      FROM_UTF8(obj->getObjectType()),
                                      flags,
                                      value,
                                      FROM_UTF8(obj->getObjectDisplayName()),
                                      FROM_UTF8(obj->getCN()));

  if (obj->isContainer())
    {
      CCopasiContainer* container;
      container = (CCopasiContainer*)obj;

      CCopasiContainer::objectMap::const_iterator it = container->getObjects().begin();
      // int cnt = container->getObjects().size();

      for (; it != container->getObjects().end(); ++it)
        {
          //the next line skips name references...
          if (it->second->getObjectName() == "Name") continue;

          addObjectRecursive((QWidget*)element, (void*)it->second);
        }

      return;
    }

#ifdef XXXX

  if (obj->isVector())
    {
      CCopasiVector <CCopasiObject> * vect;
      vect = (CCopasiVector <CCopasiObject> *)obj;

      //CCopasiVector<CCopasiObject>::iterator it = vect->begin();
      int cnt = vect->size();

      int i;

      for (i = 0; i != cnt; ++i)
        {addObjectRecursive((QWidget*)element, (void*)(*vect)[i]);}
    }

#endif // XXXX
}

void ObjectDebug::update()
{
  ListOfObjects->clear();

  const CCopasiObject * obj;

  Q3ListViewItem * element;
  element = new MyListViewItemWithPtr(ListOfObjects, NULL, "*");
  element->setOpen(true);

  obj = CCopasiRootContainer::getRoot();

  if (!obj) return;

  addObjectRecursive((QWidget*)element, (const void *) obj);

  ListOfObjects->show();
}

void ObjectDebug::init()
{
  ListOfObjects->clear();
  ListOfObjects->addColumn("Type", -1);
  ListOfObjects->addColumn("Flags", -1);
  ListOfObjects->addColumn("Value", -1);
  ListOfObjects->addColumn("Display Name", -1);
  ListOfObjects->addColumn("CN", -1);
  ListOfObjects->addColumn("Unique name", -1);
  ListOfObjects->setAllColumnsShowFocus(true);
}

void ObjectDebug::writeDot()
{

  CDotOutput dot;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  dot.simpleCall(pDataModel->getModel());
}

void ObjectDebug::checkModel()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModelAnalyzer MA((*CCopasiRootContainer::getDatamodelList())[0]->getModel());

  std::ostringstream ss;
  MA.writeReport(ss, true, true);

  Q3TextEdit* pTE = new Q3TextEdit(FROM_UTF8(ss.str()));
  pTE->show();
}
