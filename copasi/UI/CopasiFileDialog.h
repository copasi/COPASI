// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_FILE_DIALOG
#define COPASI_FILE_DIALOG

#include <QFileDialog>
#include <QString>
#include <QDir>

class CopasiFileDialog
{
public:
  static void openExampleDir();

  static QString getOpenFileName(QWidget * parent = 0,
                                 const char * name = 0,
                                 const QString & startWith = QString::null,
                                 const QString & filter = QString::null,
                                 const QString & caption = QString::null,
                                 QString * pSelectedFilter = NULL,
                                 QFileDialog::Options options = 0);

  static QString getSaveFileName(QWidget * parent = 0,
                                 const char * name = 0,
                                 const QString & startWith = QString::null,
                                 const QString & filter = QString::null,
                                 const QString & caption = QString::null,
                                 QString * pSelectedFilter = NULL,
                                 QFileDialog::Options options = 0);
private:
  static QString StartWith(const QString & startWith);
};

#endif
