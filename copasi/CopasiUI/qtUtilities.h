/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/qtUtilities.h,v $
   $Revision: 1.7.6.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/09/20 12:01:46 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_qtUtilities
#define COPASI_qtUtilities

#include <qstring.h>
#include "utilities/CCopasiParameter.h"

class CCopasiParameterGroup;

/**
 * Retrieve a parameter from a parameter group and convert it to a QString.
 * @param const CCopasiParameterGroup * group
 * @param const unsigned C_INT32 & index
 * @param CCopasiParameter::Type * type (default: NULL)
 * @return QString value
 */
QString getParameterValue(const CCopasiParameterGroup * group,
                          const unsigned C_INT32 & index,
                          CCopasiParameter::Type * type = NULL);
/**
 * Retrieve a parameter from a parameter group and convert it to a QString.
 * @param const CCopasiParameterGroup * group
 * @param const std::string & name
 * @param CCopasiParameter::Type * type (default: NULL)
 * @return QString value
 */
QString getParameterValue(const CCopasiParameterGroup * group,
                          const std::string & name,
                          CCopasiParameter::Type * type = NULL);
/**
 * Set a parameter of a parameter group from a value given as a QString.
 * Success = true is returned when the set operation was succesful, i.e.,
 * value == getParameterValue.
 * @param CCopasiParameterGroup * group
 * @param const std::string & name
 * @param const QString & value
 * @return bool success.
 */
bool setParameterValue(CCopasiParameterGroup * group,
                       const unsigned C_INT32 & index,
                       const QString & value);

/**
 * Set a parameter of a parameter group from a value given as a QString.
 * Success = true is returned when the set operation was succesful, i.e.,
 * value == getParameterValue.
 * @param CCopasiParameterGroup * group
 * @param const unsigned C_INT32 & index
 * @param const QString & value
 * @return bool success.
 */
bool setParameterValue(CCopasiParameterGroup * group,
                       const std::string & name,
                       const QString & value);

/**
 * Convert a utf8 encoded std::string to a QString
 */
#define FROM_UTF8(__x) QString::fromUtf8((__x).c_str())

/**
 * Checks whether the file exists. If the file exist the user
 * is prompted whether to overwrite the file. The return value is
 * one of QMessageBox::Yes, QMessageBox::No, or QMessageBox::Cancel.
 * If the file does not exist QMessageBox::Yes is returned.
 * param const QString & file
 * @return C_INT32 overwrite
 */
C_INT32 checkSelection(const QString & file);

/**
 * This converts a std::vector<std::string> into a QStringList
 */
void vectorOfStrings2QStringList(std::vector<std::string> vs, QStringList & qsl);

#endif // COPASI_qtUtilities
