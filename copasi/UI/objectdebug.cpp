// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "objectdebug.h"

#include <QVariant>
#include <QDialog>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <sstream>

#include "copasi/copasi.h"
#include "copasi/model/CModelAnalyzer.h"
//#include "copasi/model/CDotOutput.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/core/CDataObject.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/core/CCommonName.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CDataVector.h"
/*
 *  Constructs a ObjectDebug as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
ObjectDebug::ObjectDebug(QWidget* parent, Qt::WindowFlags fl)
  : QDialog(parent, fl)
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

class MyListViewItemWithPtr : public QTreeWidgetItem
{
public:

  MyListViewItemWithPtr(QTreeWidget* parent, const CDataObject * ptr,
                        const QStringList & strings, int type = Type)
    : QTreeWidgetItem(parent, strings, type)
    , mpObject(ptr)
  {}

  MyListViewItemWithPtr(QTreeWidgetItem * parent, const CDataObject * ptr,
                        const QStringList & strings, int type = Type)
    : QTreeWidgetItem(parent, strings, type)
    , mpObject(ptr)
  {}

  /*MyListViewItemWithPtr(QTreeWidgetItem * parent, const CDataObject * ptr,
    QString label1, QString label2 = QString(),
    QString label3 = QString(), QString label4 = QString(),
    QString label5 = QString(), QString label6 = QString(),
    QString label7 = QString(), QString label8 = QString())
    : QTreeWidgetItem(parent, label1, label2, label3, label4, label5, label6, label7, label8),
    mpObject(ptr)
  {}*/

  const CDataObject * mpObject;
};

void ObjectDebug::addObjectRecursive(QTreeWidgetItem * parent, const void * ptr)
{
  const CDataObject * obj = static_cast<const CDataObject *>(ptr);
  QTreeWidgetItem* element;

  std::string cn = obj->getCN();
  const CDataModel * pDM = obj->getObjectDataModel();
  const CDataObject* testObj = NULL;

  if (pDM)
    testObj = static_cast<const CDataObject *>(pDM->getObject(cn));

  //assert(CRootContainer::getDatamodelList()->size() > 0);

  QString flags;

  if (obj->hasFlag(CDataObject::Container)) flags += "C"; else flags += " ";

  if (obj->hasFlag(CDataObject::Vector)) flags += "V"; else flags += " ";

  if (obj->hasFlag(CDataObject::Matrix)) flags += "M"; else flags += " ";

  if (obj->hasFlag(CDataObject::NameVector)) flags += "N"; else flags += " ";

  if (obj->hasFlag(CDataObject::Reference)) flags += "R"; else flags += " ";

  if (obj->hasFlag(CDataObject::NonUniqueName)) flags += " Nun"; else flags += " Unn";

  if (obj->hasFlag(CDataObject::ValueInt)) flags += "Int";
  else if (obj->hasFlag(CDataObject::ValueDbl)) flags += "Dbl";
  else if (obj->hasFlag(CDataObject::ValueBool)) flags += "Boo";
  else if (obj->hasFlag(CDataObject::ValueString)) flags += "Str";
  else if (obj->hasFlag(CDataObject::StaticString)) flags += "SSt";
  else flags += "   ";

  if (testObj != obj && pDM != NULL) flags += "EEE";

  QString value;

  if (obj->hasFlag(CDataObject::ValueDbl) && obj->getValuePointer())
    value = convertToQString(*(C_FLOAT64*)obj->getValuePointer());
  else if (obj->hasFlag(CDataObject::ValueInt) && obj->getValuePointer())
    value = QString::number(*(C_INT32*)obj->getValuePointer());
  else if (obj->hasFlag(CDataObject::ValueString) && obj->getValuePointer())
    value = FROM_UTF8(*(std::string*)obj->getValuePointer());
  else if (obj->hasFlag(CDataObject::ValueBool) && obj->getValuePointer())
    {
      if (*(bool*)obj->getValuePointer()) value = "true"; else value = "false";
    }
  else
    value = "";

  QStringList columns;
  columns << FROM_UTF8(obj->getObjectName())
          << FROM_UTF8(obj->getObjectType())
          << flags
          << value
          << FROM_UTF8(obj->getObjectDisplayName())
          << FROM_UTF8(obj->getCN());

  element = new MyListViewItemWithPtr((QTreeWidgetItem*)parent, obj,
                                      columns);

  if (obj->hasFlag(CDataObject::Container))
    {
      CDataContainer* container;
      container = (CDataContainer*)obj;

      CDataContainer::objectMap::const_iterator it = container->getObjects().begin();
      // int cnt = container->getObjects().size();

      for (; it != container->getObjects().end(); ++it)
        {
          //the next line skips name references...
          if (it->getObjectName() == "Name") continue;

          addObjectRecursive(element, (void*)*it);
        }

      return;
    }

#ifdef XXXX

  if (obj->isVector())
    {
      CCopasiVector <CDataObject> * vect;
      vect = (CCopasiVector <CDataObject> *)obj;

      //CCopasiVector<CDataObject>::iterator it = vect->begin();
      int cnt = vect->size();

      int i;

      for (i = 0; i != cnt; ++i)
        {
          addObjectRecursive((QWidget*)element, (void*)(*vect)[i]);
        }
    }

#endif // XXXX
}

void ObjectDebug::update()
{
  ListOfObjects->clear();

  const CDataObject * obj;

  QTreeWidgetItem * element;
  element = new MyListViewItemWithPtr(ListOfObjects, NULL, QStringList() << "*");
  element->setExpanded(true);

  obj = CRootContainer::getRoot();

  if (!obj) return;

  addObjectRecursive(element, (const void *)obj);

  ListOfObjects->addTopLevelItem(element);
}

void ObjectDebug::init()
{
  ListOfObjects->clear();
  ListOfObjects->setAllColumnsShowFocus(true);
}

void ObjectDebug::writeDot()
{

  //CDotOutput dot;
  //assert(CRootContainer::getDatamodelList()->size() > 0);
  //CDataModel* pDataModel = (*CRootContainer::getDatamodelList())[0];
  //assert(pDataModel != NULL);
  //dot.simpleCall(pDataModel->getModel());
}

void ObjectDebug::checkModel()
{
  assert(CRootContainer::getDatamodelList()->size() > 0);
  CDataVector< CDataModel >& dataModels = (*CRootContainer::getDatamodelList());
  CModelAnalyzer MA(dataModels[0].getModel());

  std::ostringstream ss;
  MA.writeReport(ss, true, true);

  QDialog* pDialog = new QDialog(this);
  pDialog->setLayout(new QGridLayout());
  QTextEdit* pTE = new QTextEdit(FROM_UTF8(ss.str()));
  pDialog->layout()->addWidget(pTE);
  pDialog->exec();
}
