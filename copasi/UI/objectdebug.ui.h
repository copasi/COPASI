/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/objectdebug.ui.h,v $
   $Revision: 1.19 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/06 17:01:49 $
   End CVS Header */

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you wish to add, delete or rename functions or slots use
 ** Qt Designer which will update this file, preserving your code. Create an
 ** init() function in place of a constructor, and a destroy() function in
 ** place of a destructor.
 *****************************************************************************/

#include "qtUtilities.h"
#include "utilities/CGlobals.h" 
// #include "utilities/CCopasiVector.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"

class MyListViewItemWithPtr : public QListViewItem
  {
  public:

    MyListViewItemWithPtr(QListViewItem * parent, CCopasiObject * ptr,
                          QString label1, QString label2 = QString::null,
                          QString label3 = QString::null, QString label4 = QString::null,
                          QString label5 = QString::null, QString label6 = QString::null,
                          QString label7 = QString::null, QString label8 = QString::null)
        : QListViewItem(parent, label1, label2, label3, label4, label5, label6, label7, label8),
        mpObject(ptr)
    {}

    MyListViewItemWithPtr(QListView * parent, CCopasiObject * ptr,
                          QString label1, QString label2 = QString::null,
                          QString label3 = QString::null, QString label4 = QString::null,
                          QString label5 = QString::null, QString label6 = QString::null,
                          QString label7 = QString::null, QString label8 = QString::null)
        : QListViewItem(parent, label1, label2, label3, label4, label5, label6, label7, label8),
        mpObject(ptr)
    {}

    CCopasiObject* mpObject;
  };

void ObjectDebug::addObjectRecursive(QWidget * parent, void * ptr)
{
  CCopasiObject* obj = (CCopasiObject*)ptr;
  QListViewItem * element;

  std::string cn = obj->getCN();
  CCopasiObject* testObj = CCopasiContainer::ObjectFromName(cn);

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
  if (obj->isValueDbl())
    value = QString::number(*(C_FLOAT64*)obj->getReference());
  else if (obj->isValueInt())
    value = QString::number(*(C_INT32*)obj->getReference());
  else if (obj->isValueString())
    value = FROM_UTF8(*(std::string*)obj->getReference());
  else if (obj->isValueBool())
    {
      if (*(bool*)obj->getReference()) value = "true"; else value = "false";
    }
  else
    value = "";

  element = new MyListViewItemWithPtr((QListViewItem*)parent, obj,
                                      FROM_UTF8(obj->getObjectName()),
                                      FROM_UTF8(obj->getObjectType()),
                                      flags,
                                      value,
                                      FROM_UTF8(obj->getObjectDisplayName()),
                                      FROM_UTF8(obj->getCN()),
                                      FROM_UTF8(obj->getObjectUniqueName()));

  //std::cout << obj->getName()<< "   " << obj->getObjectType() << std::endl;

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

  QListViewItem * element;
  element = new MyListViewItemWithPtr(ListOfObjects, NULL, "*");
  element->setOpen(true);

  obj = (CCopasiObject*)CCopasiContainer::Root;
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

void ObjectDebug::action(QListViewItem * item, const QPoint & C_UNUSED(pnt), int C_UNUSED(col))
{
  //CCopasiObject* testObj = CCopasiContainer::ObjectFromName((const std::string)((const char*)item->text(5).utf8()));
  CCopasiObject* testObj = ((MyListViewItemWithPtr*)item)->mpObject;

  if (!testObj) return;

  std::cout << testObj->getObjectDisplayName() << std::endl;
  std::cout << *testObj << std::endl;
}
