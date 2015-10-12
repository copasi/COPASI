// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QtCore/QString>
#include <QtCore/QFileInfo>

#include "copasi.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CDirEntry.h"
#include "copasiWidget.h"
#include "CQCopasiApplication.h"
#include "copasiui3window.h"
#include "DataModelGUI.h"
#include "listviews.h"

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

bool updateGUI(C_INT32 objectType, C_INT32 action, const std::string & key /*= ""*/)
{
  CQCopasiApplication* app = dynamic_cast<CQCopasiApplication*>(qApp->instance());

  if (app == NULL) return false;

  CopasiUI3Window* win = app->getMainWindow();

  if (win == NULL) return false;

  DataModelGUI* dm = win->getDataModel();

  if (dm == NULL) return false;

  return dm->notify((ListViews::ObjectType)objectType, (ListViews::Action)action, key);
}

void switchToWidget(size_t id, const std::string & key /*= ""*/)
{
  CQCopasiApplication* app = dynamic_cast<CQCopasiApplication*>(qApp->instance());

  if (app == NULL) return;

  CopasiUI3Window* win = app->getMainWindow();

  if (win == NULL) return;

  ListViews *lv = win->getMainWidget();

  if (lv == NULL) return;

  if (lv->getCurrentItemId() != id)
    lv->switchToOtherWidget(id, key);
}

void updateCurrentWidget()
{
  CQCopasiApplication* app = dynamic_cast<CQCopasiApplication*>(qApp->instance());

  if (app == NULL) return;

  CopasiUI3Window* win = app->getMainWindow();

  if (win == NULL) return;

  ListViews *lv = win->getMainWidget();

  if (lv == NULL) return;

  CopasiWidget* currentWidget = lv->getCurrentWidget();

  if (currentWidget == NULL) return;

  currentWidget->refresh();
}

QString getParameterValue(const CCopasiParameterGroup * group,
                          const size_t & index,
                          CCopasiParameter::Type * type)
{
  if (index >= group->size())
    return QString::fromLatin1("INVALID");

  if (type) *type = group->getType(index);

  switch (group->getType(index))
    {
      case CCopasiParameter::DOUBLE:
        return QString::number(group->getValue< C_FLOAT64 >(index));
        break;

      case CCopasiParameter::UDOUBLE:
        return QString::number(group->getValue< C_FLOAT64 >(index));
        break;

      case CCopasiParameter::INT:
        return QString::number(group->getValue< C_INT32 >(index));
        break;

      case CCopasiParameter::UINT:
        return QString::number(group->getValue< unsigned C_INT32 >(index));
        break;

      case CCopasiParameter::BOOL:
        return QString::number(group->getValue< bool >(index));
        break;

      case CCopasiParameter::STRING:
        return
          FROM_UTF8(group->getValue< std::string >(index));
        break;

      case CCopasiParameter::KEY:
        return
          FROM_UTF8(group->getValue< std::string >(index));
        break;

      case CCopasiParameter::CN:
        return
          FROM_UTF8(group->getValue< CCopasiObjectName >(index));
        break;

      case CCopasiParameter::GROUP:
        return FROM_UTF8((group->getName(index)));
        break;

      case CCopasiParameter::INVALID:
        return QString::fromUtf8("INVALID");
        break;

      default:
        break;
    }

  return QString::fromLatin1("INVALID");
}

QString getParameterValue(const CCopasiParameterGroup * group,
                          const std::string & name,
                          CCopasiParameter::Type * type)
{return getParameterValue(group, group->getIndex(name), type);}

bool setParameterValue(CCopasiParameter * pParameter,
                       const QVariant & value)
{
  if (pParameter == NULL) return false;

  switch (pParameter->getType())
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        return pParameter->setValue< C_FLOAT64 >(value.toDouble());
        break;

      case CCopasiParameter::INT:
        return pParameter->setValue< C_INT32 >(value.toInt());
        break;

      case CCopasiParameter::UINT:
        return pParameter->setValue< unsigned C_INT32 >(value.toUInt());
        break;

      case CCopasiParameter::BOOL:;
        return pParameter->setValue< bool >(value.toBool());
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        return pParameter->setValue< std::string >(TO_UTF8(value.toString()));
        break;

      case CCopasiParameter::CN:
        return pParameter->setValue< CCopasiObjectName >(std::string(TO_UTF8(value.toString())));
        break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        break;
    }

  return false;
}

bool setParameterValue(CCopasiParameterGroup * pGroup,
                       const size_t & index,
                       const QVariant & value)
{
  return setParameterValue(pGroup->getParameter(index), value);
}

bool setParameterValue(CCopasiParameterGroup * pGroup,
                       const size_t & index,
                       const QString & value)
{
  return setParameterValue(pGroup->getParameter(index), QVariant(value));
}

bool setParameterValue(CCopasiParameterGroup * pGroup,
                       const std::string & name,
                       const QString & value)
{
  return setParameterValue(pGroup->getParameter(name), QVariant(value));
}

bool setParameterValue(CCopasiParameterGroup * pGroup,
                       const std::string & name,
                       const QVariant & value)
{
  return setParameterValue(pGroup->getParameter(name), value);
}

C_INT32 checkSelection(const QString & file)
{

#ifdef DEBUG_UI
  qDebug() << "Filename on checkSelection = " << file;
#endif

  if (QFileInfo(file).exists())
    {
      if (CDirEntry::isWritable(TO_UTF8(file)))
        return CQMessageBox::question(NULL, "File exists!",
                                      "Overwrite existing file " + file + "?",
                                      QMessageBox::Ok | QMessageBox::Cancel,
                                      QMessageBox::Cancel);
      else
        {
          CQMessageBox::information(NULL, "File read-only",
                                    "The file is read-only. Please select another file!",
                                    QMessageBox::Ok, QMessageBox::Ok);
          return QMessageBox::Cancel;
        }
    }
  else
    return QMessageBox::Ok;
}

void vectorOfStrings2QStringList(std::vector<std::string> vs, QStringList & qsl)
{
  qsl.clear();
  size_t i, imax = vs.size();

  for (i = 0; i < imax; ++i) qsl += FROM_UTF8(vs[i]);
}

const CopasiWidget * GetCopasiWidget(const QObject * pObject)
{
  const QObject * pParent = pObject;
  const CopasiWidget * pCopasiWidget = NULL;

  while (pParent != NULL && pCopasiWidget == NULL)
    {
      pCopasiWidget = dynamic_cast< const CopasiWidget * >(pParent);
      pParent = pParent->parent();
    }

  return pCopasiWidget;
}
