// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QtCore/QString>
#include <QtCore/QFileInfo>
#include <QTextStream>
#include <QAbstractItemView>

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

  if (lv->getCurrentItemId() != id || (id == C_INVALID_INDEX && !key.empty()))
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

QVariant getParameterValue(const CCopasiParameter * pParameter)
{
  if (pParameter == NULL) return false;

  switch (pParameter->getType())
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        return QVariant(pParameter->getValue< C_FLOAT64 >());
        break;

      case CCopasiParameter::INT:
        return QVariant(pParameter->getValue< C_INT32 >());
        break;

      case CCopasiParameter::UINT:
        return QVariant(pParameter->getValue< unsigned C_INT32 >());
        break;

      case CCopasiParameter::BOOL:;
        return QVariant(pParameter->getValue< bool >());
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
      case CCopasiParameter::CN:
        return QVariant(FROM_UTF8(pParameter->getValue< std::string >()));
        break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        break;
    }

  return QVariant();
}

QVariant getParameterValue(const CCopasiParameterGroup * pGroup,
                           const size_t & index)
{
  return getParameterValue(pGroup->getParameter(index));
}

QVariant getParameterValue(const CCopasiParameterGroup * pGroup,
                           const std::string & name)
{
  return getParameterValue(pGroup->getParameter(name));
}

QList< QPair < QVariant, QVariant > > getParameterValidValues(const CCopasiParameter * pParameter)
{
  QList< QPair < QVariant, QVariant > > ValidValues;

  if (pParameter == NULL ||
      !pParameter->hasValidValues()) return ValidValues;

  switch (pParameter->getType())
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
      {
        std::vector<std::pair< C_FLOAT64, C_FLOAT64 > >::const_iterator it =
          pParameter->getValidValues< C_FLOAT64 >().begin();
        std::vector<std::pair< C_FLOAT64, C_FLOAT64 > >::const_iterator end =
          pParameter->getValidValues< C_FLOAT64 >().end();

        for (; it != end; ++it)
          ValidValues.append(
            QPair<QVariant, QVariant>(QVariant(it->first),
                                      QVariant(it->second)));
      }
      break;

      case CCopasiParameter::INT:
      {
        std::vector< std::pair < C_INT32, C_INT32 > >::const_iterator it = pParameter->getValidValues< C_INT32 >().begin();
        std::vector< std::pair < C_INT32, C_INT32 > >::const_iterator end = pParameter->getValidValues< C_INT32 >().end();

        for (; it != end; ++it)
          ValidValues.append(QPair< QVariant, QVariant >(QVariant(it->first), QVariant(it->second)));
      }
      break;

      case CCopasiParameter::UINT:
      {
        std::vector< std::pair < unsigned C_INT32, unsigned C_INT32 > >::const_iterator it = pParameter->getValidValues< unsigned C_INT32 >().begin();
        std::vector< std::pair < unsigned C_INT32, unsigned C_INT32 > >::const_iterator end = pParameter->getValidValues< unsigned C_INT32 >().end();

        for (; it != end; ++it)
          ValidValues.append(QPair< QVariant, QVariant >(QVariant(it->first), QVariant(it->second)));
      }
      break;

      case CCopasiParameter::BOOL:;
        {
          std::vector< std::pair < bool, bool > >::const_iterator it = pParameter->getValidValues< bool >().begin();
          std::vector< std::pair < bool, bool > >::const_iterator end = pParameter->getValidValues< bool >().end();

          for (; it != end; ++it)
            ValidValues.append(QPair< QVariant, QVariant >(QVariant(it->first), QVariant(it->second)));
        }
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
      case CCopasiParameter::CN:
      {
        std::vector< std::pair < std::string, std::string > >::const_iterator it = pParameter->getValidValues< std::string >().begin();
        std::vector< std::pair < std::string, std::string > >::const_iterator end = pParameter->getValidValues< std::string >().end();

        for (; it != end; ++it)
          ValidValues.append(QPair< QVariant, QVariant >(QVariant(FROM_UTF8(it->first)), QVariant(FROM_UTF8(it->second))));
      }
      break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        break;
    }

  return ValidValues;
}

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
        return pParameter->setValue< CCommonName >(std::string(TO_UTF8(value.toString())));
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

QString toTsvString(QAbstractItemModel* pModel,
                    bool writeColumnHeaders /*= true*/,
                    bool writeRowHeaders /*= true*/)
{
  QString text;
  QTextStream stream(&text);

  if (writeColumnHeaders)
    {
      if (writeRowHeaders)
        stream << '\t';

      for (int j = 0; j < pModel->columnCount(); ++j)
        {
          stream << pModel->headerData(j, Qt::Horizontal).toString().replace('\n', ' ');

          if (j + 1 < pModel->columnCount())
            stream << '\t';
        }

      stream << '\n';
    }

  for (int i = 0; i < pModel->rowCount(); ++i)
    {
      if (writeRowHeaders)
        stream << pModel->headerData(i, Qt::Vertical).toString().replace('\n', ' ') << '\t';

      for (int j = 0; j < pModel->columnCount(); ++j)
        {
          stream << pModel->index(i, j).data().toString();

          if (j + 1 < pModel->columnCount())
            stream << '\t';
        }

      stream << '\n';
    }

  return text;
}

QString toTsvString(QAbstractItemView* pWidget,
                    bool writeColumnHeaders /*= true*/,
                    bool writeRowHeaders /*= true*/)
{
  if (pWidget == NULL)
    return QString();

  QAbstractItemModel* pModel = pWidget->model();
  return toTsvString(pModel, writeColumnHeaders, writeRowHeaders);
}
