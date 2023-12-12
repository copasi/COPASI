// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
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

#include <QtCore/QString>
#include <QtCore/QFileInfo>
#include <QTextStream>
#include <QAbstractItemView>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#  include <QGuiApplication>
#else
#  include <QApplication>
#endif

#include "copasi/copasi.h"
#include <copasi/core/CRootContainer.h>
#include <copasi/commandline/CConfigurationFile.h>
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasiWidget.h"
#include "CQCopasiApplication.h"
#include "copasiui3window.h"
#include "DataModelGUI.h"
#include "listviews.h"

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

DataModelGUI * getDataModel()
{
  CQCopasiApplication * app = CQCopasiApplication::instance();

  if (app == NULL)
    return NULL;

  CopasiUI3Window * win = app->getMainWindow();

  if (win == NULL)
    return NULL;

  return win->getDataModel();
}

bool updateGUI(C_INT32 objectType, C_INT32 action, const std::string & key /*= ""*/)
{
  DataModelGUI* dm = getDataModel();

  if (dm == NULL) return false;

  return dm->notify((ListViews::ObjectType)objectType, (ListViews::Action)action, key);
}

QVariant getParameterValue(const CCopasiParameter * pParameter)
{
  if (pParameter == NULL)
    return QVariant();

  switch (pParameter->getType())
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        return QVariant(pParameter->getValue< C_FLOAT64 >());
        break;

      case CCopasiParameter::Type::INT:
        return QVariant(pParameter->getValue< C_INT32 >());
        break;

      case CCopasiParameter::Type::UINT:
        return QVariant(pParameter->getValue< unsigned C_INT32 >());
        break;

      case CCopasiParameter::Type::BOOL:;
        return QVariant(pParameter->getValue< bool >());
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
      case CCopasiParameter::Type::CN:
        return QVariant(FROM_UTF8(pParameter->getValue< std::string >()));
        break;

      case CCopasiParameter::Type::GROUP:
      {
        const CCopasiParameterGroup * pGroup = dynamic_cast<const CCopasiParameterGroup *>(pParameter);
        if (pGroup != NULL)
        { 
          QList<QVariant> group;
          for (size_t i = 0; i < pGroup->size(); ++i)
            group.append(getParameterValue(pGroup->getParameter(i)));
          return QVariant(group);
        }
      }
      case CCopasiParameter::Type::INVALID:
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
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
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

      case CCopasiParameter::Type::INT:
      {
        std::vector< std::pair < C_INT32, C_INT32 > >::const_iterator it = pParameter->getValidValues< C_INT32 >().begin();
        std::vector< std::pair < C_INT32, C_INT32 > >::const_iterator end = pParameter->getValidValues< C_INT32 >().end();

        for (; it != end; ++it)
          ValidValues.append(QPair< QVariant, QVariant >(QVariant(it->first), QVariant(it->second)));
      }
      break;

      case CCopasiParameter::Type::UINT:
      {
        std::vector< std::pair < unsigned C_INT32, unsigned C_INT32 > >::const_iterator it = pParameter->getValidValues< unsigned C_INT32 >().begin();
        std::vector< std::pair < unsigned C_INT32, unsigned C_INT32 > >::const_iterator end = pParameter->getValidValues< unsigned C_INT32 >().end();

        for (; it != end; ++it)
          ValidValues.append(QPair< QVariant, QVariant >(QVariant(it->first), QVariant(it->second)));
      }
      break;

      case CCopasiParameter::Type::BOOL:;
        {
          std::vector< std::pair < bool, bool > >::const_iterator it = pParameter->getValidValues< bool >().begin();
          std::vector< std::pair < bool, bool > >::const_iterator end = pParameter->getValidValues< bool >().end();

          for (; it != end; ++it)
            ValidValues.append(QPair< QVariant, QVariant >(QVariant(it->first), QVariant(it->second)));
        }
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
      case CCopasiParameter::Type::CN:
      {
        std::vector< std::pair < std::string, std::string > >::const_iterator it = pParameter->getValidValues< std::string >().begin();
        std::vector< std::pair < std::string, std::string > >::const_iterator end = pParameter->getValidValues< std::string >().end();

        for (; it != end; ++it)
          ValidValues.append(QPair< QVariant, QVariant >(QVariant(FROM_UTF8(it->first)), QVariant(FROM_UTF8(it->second))));
      }
      break;

      case CCopasiParameter::Type::GROUP:
      case CCopasiParameter::Type::INVALID:
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
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        return pParameter->setValue< C_FLOAT64 >(value.toDouble());
        break;

      case CCopasiParameter::Type::INT:
        return pParameter->setValue< C_INT32 >(value.toInt());
        break;

      case CCopasiParameter::Type::UINT:
        return pParameter->setValue< unsigned C_INT32 >(value.toUInt());
        break;

      case CCopasiParameter::Type::BOOL:;
        return pParameter->setValue< bool >(value.toBool());
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        return pParameter->setValue< std::string >(TO_UTF8(value.toString()));
        break;

      case CCopasiParameter::Type::CN:
        return pParameter->setValue< CCommonName >(std::string(TO_UTF8(value.toString())));
        break;

      case CCopasiParameter::Type::GROUP:
      case CCopasiParameter::Type::INVALID:
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

C_INT32 checkSelection(QWidget * parent, const QString & file)
{

#ifdef DEBUG_UI
  qDebug() << "Filename on checkSelection = " << file;
#endif

  if (QFileInfo(file).exists())
    {
      if (CDirEntry::isWritable(TO_UTF8(file)))
        return CQMessageBox::question(parent, "File exists!",
                                      "Overwrite existing file " + file + "?",
                                      QMessageBox::Ok | QMessageBox::Cancel,
                                      QMessageBox::Cancel);
      else
        {
          CQMessageBox::information(parent, "File read-only",
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

  if (pModel == NULL)
    return text;

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

QString convertToQString(double number)
{
  C_INT32 precision = CRootContainer::getConfiguration()->getDoublePrecision();
  return QString::number(number, 'g', precision);
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


bool isDarkMode()
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
  QPalette Palette = QGuiApplication::palette();
#else
  QPalette Palette = QApplication::palette();
#endif
  auto foreground = Palette.color(QPalette::Active, QPalette::Text);
  auto background = Palette.color(QPalette::Active, QPalette::Base);

  return (foreground.redF() + foreground.greenF() + foreground.blueF() > background.redF() + background.greenF() + background.blueF());
}

bool isLightMode()
{
    return !isDarkMode();
}
