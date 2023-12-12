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

#ifndef COPASI_qtUtilities
#define COPASI_qtUtilities

#include <QVariant>

#include <QString>
#include <QStringList>
#include <QComboBox>

#include <copasi/copasi.h>
#include "copasi/utilities/CCopasiParameter.h"
#include <copasi/core/CEnumAnnotation.h>

class CCopasiParameterGroup;
class CopasiWidget;
class QObject;
class QAbstractItemView;
class QAbstractItemModel;
class DataModelGUI;

/**
 * returns the current datamodel being used by the application.
 */
DataModelGUI * getDataModel();

/**
 * notifies the UI of a modification of the model.
 *
 * This function retrieves the DataModelGUI object, and notifies
 * it about the change.
 *
 * @param objectType enumeration value of type ListViews::ObjectType
 * @param action enumeration value of type ListViews::Action
 * @param key
 *
 * @return success
 */
bool updateGUI(C_INT32 objectType, C_INT32 action, const std::string & key = "");

/**
 * Retrieve a parameter from a parameter group and convert it to a QString.
 * @param const CCopasiParameter * pParameter
 * @return QVariant value
 */
QVariant getParameterValue(const CCopasiParameter * pParameter);

/**
 * Retrieve a parameter from a parameter group and convert it to a QString.
 * @param const CCopasiParameterGroup * pGroup
 * @param const size_t & index
 * @return QVariant value
 */
QVariant getParameterValue(const CCopasiParameterGroup * pGroup,
                           const size_t & index);

/**
 * Retrieve a parameter from a parameter group and convert it to a QString.
 * @param const CCopasiParameterGroup * pGroup
 * @param const std::string & name
 * @return QVariant value
 */
QVariant getParameterValue(const CCopasiParameterGroup * pGroup,
                           const std::string & name);

/**
 * Retrieve a valid values for the given parameter.
 * @param const CCopasiParameter * pParameter
 * @return QList< QPair < QVariant, QVariant > > validValues
 */
QList< QPair < QVariant, QVariant > > getParameterValidValues(const CCopasiParameter * pParameter);

/**
 * Set a parameter of a parameter group from a value given as a QString.
 * Success = true is returned when the set operation was successful, i.e.,
 * value == getParameterValue.
 * @param CCopasiParameter * pParameter
 * @param const QVariant & value
 * @return bool success.
 */
bool setParameterValue(CCopasiParameter * pParameter,
                       const QVariant & value);

/**
 * Set a parameter of a parameter group from a value given as a QString.
 * Success = true is returned when the set operation was successful, i.e.,
 * value == getParameterValue.
 * @param CCopasiParameterGroup * group
 * @param const size_t & index
 * @param const QVariant & value
 * @return bool success.
 */
bool setParameterValue(CCopasiParameterGroup * group,
                       const size_t & index,
                       const QVariant & value);

/**
 * Set a parameter of a parameter group from a value given as a QString.
 * Success = true is returned when the set operation was successful, i.e.,
 * value == getParameterValue.
 * @param CCopasiParameterGroup * group
 * @param const size_t & index
 * @param const QString & value
 * @return bool success.
 */
bool setParameterValue(CCopasiParameterGroup * group,
                       const size_t & index,
                       const QString & value);

/**
 * Set a parameter of a parameter group from a value given as a QString.
 * Success = true is returned when the set operation was successful, i.e.,
 * value == getParameterValue.
 * @param CCopasiParameterGroup * group
 * @param const std::string & name
 * @param const QVariant & value
 * @return bool success.
 */
bool setParameterValue(CCopasiParameterGroup * group,
                       const std::string & name,
                       const QVariant & value);

/**
 * Set a parameter of a parameter group from a value given as a QString.
 * Success = true is returned when the set operation was successful, i.e.,
 * value == getParameterValue.
 * @param CCopasiParameterGroup * group
 * @param const std::string & name
 * @param const QString & value
 * @return bool success.
 */
bool setParameterValue(CCopasiParameterGroup * group,
                       const std::string & name,
                       const QVariant & value);

/**
 * Convert a utf8 encoded std::string to a QString
 */
#define FROM_UTF8(__x) QString::fromUtf8((__x).c_str())
#define TO_UTF8(__x) (__x).trimmed().toUtf8().data()
#define TO_UTF8_UNTRIMMED(__x) (__x).toUtf8().data()

/**
 * Retrieve the COPASI data model the displayed data is associated with
 * @param QObject * pObject
 * @return const CopasiWidget * pCopasiWidget
 */
const CopasiWidget * GetCopasiWidget(const QObject * pObject);

/**
 * Checks whether the file exists. If the file exist the user
 * is prompted whether to overwrite the file. The return value is
 * one of QMessageBox::Yes, QMessageBox::No, or QMessageBox::Cancel.
 * If the file does not exist QMessageBox::Yes is returned.
 * param const QString & file
 * @return C_INT32 overwrite
 */
C_INT32 checkSelection(QWidget * parent, const QString & file);

/**
 * This converts a std::vector<std::string> into a QStringList
 */
void vectorOfStrings2QStringList(std::vector<std::string> vs, QStringList & qsl);

/**
 * Returns the contents of a table view as string
 *
 * @param pWidget the table view containing the data to return
 * @param writeColumnHeaders if true (default), the string will contain column headers
 * @param writeRowHeaders if true (default), the string will contain row headers
 *
 * @return a tab separated string containing the contents of the widget
 */
QString toTsvString(QAbstractItemView* pWidget, bool writeColumnHeaders = true, bool writeRowHeaders = true);

/**
 * Returns the contents of a table view as string
 *
 * @param pModel the item model to convert to string
 * @param writeColumnHeaders if true (default), the string will contain column headers
 * @param writeRowHeaders if true (default), the string will contain row headers
 *
 * @return a tab separated string containing the contents of the widget
 */
QString toTsvString(QAbstractItemModel* pModel, bool writeColumnHeaders = true, bool writeRowHeaders = true);

/**
 * converts the given number to a qstring with the precision setup in the
 * preferences
 */
QString convertToQString(double number);

/**
 * Fills the given combobox with all annotations provided
 */
template < class T >
void fillCombobox(QComboBox* pCombo, const CEnumAnnotation< std::string, T>& annotation)
{
  if (!pCombo)
    return;

  pCombo->clear();

  auto it = annotation.begin();

  for (; it != annotation.end(); ++it)
    {
      pCombo->addItem(FROM_UTF8(*it));
    }
}


bool isDarkMode();
bool isLightMode();

#endif // COPASI_qtUtilities
