/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you wish to add, delete or rename functions or slots use
 ** Qt Designer which will update this file, preserving your code. Create an
 ** init() function in place of a constructor, and a destroy() function in
 ** place of a destructor.
 *****************************************************************************/

#include "utilities/CGlobals.h"
#include "utilities/CCopasiVector.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"

void ObjectDebug::addObjectRecursive(QWidget * parent, void * ptr)
{
  CCopasiObject* obj = (CCopasiObject*)ptr;
  QListViewItem * element;

  QString flags;
  if (obj->isContainer()) flags += "C"; else flags += " ";
  if (obj->isVector()) flags += "V"; else flags += " ";
  if (obj->isNameVector()) flags += "N"; else flags += " ";
  if (obj->isReference()) flags += "R"; else flags += " ";
  if (obj->hasValue()) flags += "Val"; else flags += "   ";

  element = new QListViewItem((QListViewItem*)parent, obj->getName().c_str(),
                               obj->getObjectType().c_str(),
                               flags,
                               obj->getCN().c_str());

  //std::cout << obj->getName()<< "   " << obj->getObjectType() << std::endl;

  if (obj->isContainer())
    {
      CCopasiContainer* container;
      container = (CCopasiContainer*)obj;

      std::vector<CCopasiObject*>::const_iterator it = container->getObjects().begin();
      int cnt = container->getObjects().size();

      for (; it != container->getObjects().end(); ++it)
      {addObjectRecursive((QWidget*)element, (void*)(*it));}
      return;
    }

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
}

void ObjectDebug::update()
{
  ListOfObjects->clear();

  CCopasiObject * obj;

  QListViewItem * element;
  element = new QListViewItem(ListOfObjects, "root");

  obj = (CCopasiObject*)Copasi->pModel;
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
  ListOfObjects->addColumn("CN", -1);
}
