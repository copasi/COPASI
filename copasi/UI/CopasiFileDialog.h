// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.h,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/02/03 18:00:41 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_FILE_DIALOG
#define COPASI_FILE_DIALOG

#include <qstring.h>
#include <qdir.h>

class CopasiFileDialog
{
public:
  static void openExampleDir();

  static QString getOpenFileName(QWidget * parent = 0,
                                 const char * name = 0,
                                 const QString & startWith = QString::null,
                                 const QString & filter = QString::null,
                                 const QString & caption = QString::null,
                                 QString * pSelectedFilter = NULL);

  static QString getSaveFileName(QWidget * parent = 0,
                                 const char * name = 0,
                                 const QString & startWith = QString::null,
                                 const QString & filter = QString::null,
                                 const QString & caption = QString::null,
                                 QString * pSelectedFilter = NULL);
private:
  static QDir LastDir;
};

#endif
