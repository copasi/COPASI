/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/qtUtilities.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/12 16:53:33 $
   End CVS Header */

#ifndef COPASI_qtUtilities
#define COPASI_qtUtilities

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
#endif // COPASI_qtUtilities
