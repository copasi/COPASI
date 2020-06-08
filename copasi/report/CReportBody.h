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

/****************************************************************************
 *
 * Created: Tue Aug 11 2003
 *      by: Liang Xu
 *
 *  Created for Copasi by Liang Xu
 ****************************************************************************/

#ifndef COPASI_CREPORT_BODY
#define COPASI_CREPORT_BODY

#include <string>
#include <vector>
#include "copasi/core/CRegisteredCommonName.h"

class CReportTable;
class CCommonName;

class CReportBody
{
private:
  std::vector<CCommonName> mReportObjectName;
  CReportTable *mpReportTable;

public:
  /**
      *  Default constructor.
      */
  CReportBody();

  /**
  cleanup
  */
  void cleanup();

  /**
  *  Destructor.
  */
  ~CReportBody();

  /**
  gets the Table tag  in the Body Tag
  */
  CReportTable* getTable();

  /**
  sets the Table tag in the Body tag
  */
  void setTable(CReportTable *table);
};

class CReportTable
{
private:
  std::vector<CCommonName>* mpObjectNameVector;
  std::string mSeparator;
  bool mPrintTitle;

public:
  /**
      *  Default constructor.
      */
  CReportTable();

  /**
  cleanup
  */
  void cleanup();

  /**
     *  Destructor.
     */
  ~CReportTable();

  /**
  gets the Object tag of the Table tag
  */
  inline std::vector<CCommonName>* getObjectNameVector()
  {
    return mpObjectNameVector;
  }

  /**
     sets the Object tag of the Table tag
  */
  inline void setObjectNameVector(std::vector<CCommonName> *objectVector)
  {
    mpObjectNameVector = objectVector;
  }

  /**
  gets the Separator attribute of the Table tag
  */
  inline const std::string& getSeparator()
  {
    return mSeparator;
  }

  /**
     sets the separator attribute of the Table tag
  */
  inline void setSeparator(const std::string separator)
  {
    mSeparator = separator;
  }

  /**
  gets the printTitle of the Table tag
  */
  bool printTitle()
  {
    return mPrintTitle;
  }

  /**
     sets the print Title of the Table tag
  */
  void setPrintTitle(bool printTitle)
  {
    mPrintTitle = printTitle;
  }
};

#endif
