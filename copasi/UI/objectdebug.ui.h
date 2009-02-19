// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/objectdebug.ui.h,v $
//   $Revision: 1.38 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/19 15:37:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you wish to add, delete or rename functions or slots use
 ** Qt Designer which will update this file, preserving your code. Create an
 ** init() function in place of a constructor, and a destroy() function in
 ** place of a destructor.
 *****************************************************************************/

#include "copasi.h"

#include "UI/qtUtilities.h"

#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiRootContainer.h"

class MyListViewItemWithPtr : public Q3ListViewItem
  {
  public:

    MyListViewItemWithPtr(Q3ListViewItem * parent, CCopasiObject * ptr,
                          QString label1, QString label2 = QString::null,
                          QString label3 = QString::null, QString label4 = QString::null,
                          QString label5 = QString::null, QString label6 = QString::null,
                          QString label7 = QString::null, QString label8 = QString::null)
        : Q3ListViewItem(parent, label1, label2, label3, label4, label5, label6, label7, label8),
        mpObject(ptr)
    {}

    MyListViewItemWithPtr(Q3ListView * parent, CCopasiObject * ptr,
                          QString label1, QString label2 = QString::null,
                          QString label3 = QString::null, QString label4 = QString::null,
                          QString label5 = QString::null, QString label6 = QString::null,
                          QString label7 = QString::null, QString label8 = QString::null)
        : Q3ListViewItem(parent, label1, label2, label3, label4, label5, label6, label7, label8),
        mpObject(ptr)
    {}

    CCopasiObject* mpObject;
  };

void ObjectDebug::addObjectRecursive(QWidget * parent, void * ptr)
{
  CCopasiObject* obj = (CCopasiObject*)ptr;
  Q3ListViewItem * element;

  std::string cn = obj->getCN();
  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::Root->getDatamodelList())[0];
  assert(pDataModel != NULL);
  CCopasiObject* testObj = pDataModel->ObjectFromName(cn);

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

  CCopasiObject * obj;

  Q3ListViewItem * element;
  element = new MyListViewItemWithPtr(ListOfObjects, NULL, "*");
  element->setOpen(true);

  obj = (CCopasiObject*)CCopasiRootContainer::Root;
  if (!obj) return;

  addObjectRecursive((QWidget*)element, (void*)obj);

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

#include "model/CDotOutput.h"

void ObjectDebug::writeDot()
{

  CDotOutput dot;
  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::Root->getDatamodelList())[0];
  assert(pDataModel != NULL);
  dot.simpleCall(pDataModel->getModel());
}

#include "model/CModelAnalyzer.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include <q3textedit.h>
#include <sstream>

void ObjectDebug::checkModel()
{
  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  CModelAnalyzer MA((*CCopasiRootContainer::Root->getDatamodelList())[0]->getModel());

  std::ostringstream ss;
  MA.writeReport(ss, true, true);

  Q3TextEdit* pTE = new Q3TextEdit(FROM_UTF8(ss.str()));
  pTE->show();
}
