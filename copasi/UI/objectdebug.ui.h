/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/objectdebug.ui.h,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/12/16 14:57:00 $
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

void ObjectDebug::addObjectRecursive(QWidget * parent, void * ptr)
{
  CCopasiObject* obj = (CCopasiObject*)ptr;
  QListViewItem * element;

  std::string cn = obj->getCN();
  //std::vector< CCopasiContainer * > ListOfContainer; //dummy
  CCopasiObject* testObj = CCopasiContainer::ObjectFromName(cn);

  QString flags;
  if (obj->isContainer()) flags += "C"; else flags += " ";
  if (obj->isVector()) flags += "V"; else flags += " ";
  if (obj->isNameVector()) flags += "N"; else flags += " ";
  if (obj->isReference()) flags += "R"; else flags += " ";
  if (obj->isValueInt()) flags += "Int";
else {if (obj->isValueDbl()) flags += "Dbl"; else flags += "   ";}
  if (!(testObj == obj)) flags += "EEE";

  QString value;
  if (obj->isValueDbl())
    value = QString::number(*(C_FLOAT64*)obj->getReference());
  else
    value = "";

  element = new QListViewItem((QListViewItem*)parent, FROM_UTF8(obj->getObjectName()),
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
  element = new QListViewItem(ListOfObjects, "*");

  /*
    obj = (CCopasiObject*)Copasi->pModel;
    if (!obj) return;
   
    while (obj->getObjectParent())
      {obj = (CCopasiObject*)obj->getObjectParent();}
    // now we have the root object
   
    addObjectRecursive((QWidget*)element, (void*)obj);
  */ 
  //zusätzliche Objekte zeigen
  obj = (CCopasiObject*)CCopasiContainer::Root;
  if (!obj) return;

  //while (obj->getObjectParent())
  //  {obj = (CCopasiObject*)obj->getObjectParent();}
  // now we have the root object

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
}

void ObjectDebug::action(QListViewItem * item, const QPoint & pnt, int col)
{
  CCopasiObject* testObj = CCopasiContainer::ObjectFromName((const std::string)((const char*)item->text(5).utf8()));

  if (!testObj) return;

  std::cout << testObj->getObjectDisplayName() << std::endl;
  std::cout << *testObj << std::endl;
}
