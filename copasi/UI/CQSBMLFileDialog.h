// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSBMLFileDialog.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/30 13:50:03 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQSBML_FILE_DIALOG
#define CQSBML_FILE_DIALOG

#include <qstring.h>

#include <vector>

class QWidget;

class CQSBMLFileDialog
  {
  public:
    static
    std::pair<QString, std::pair<unsigned C_INT32, unsigned C_INT32> > getSaveFileName(QWidget * parent,
        const char * name,
        const QString & startWith,
        const QString & caption);
  };

#endif // CQSBML_FILE_DIALOG
